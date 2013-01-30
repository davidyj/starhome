//############################################################################
//##                                                                        ##
//##  EXAMW32.C                                                             ##
//##                                                                        ##
//##  Example of using Bink with BinkBuffers on Win32                       ##
//##                                                                        ##
//##  Author: Jeff Roberts                                                  ##
//##                                                                        ##
//############################################################################
//##                                                                        ##
//##  Copyright (C) RAD Game Tools, Inc.                                    ##
//##                                                                        ##
//##  For technical support, contact RAD Game Tools at 425 - 893 - 4300.    ##
//##                                                                        ##
//############################################################################


#include "bink.h"





#include <string.h>

#include "bink.h"
#include "simpmix.h"
#include "radmemutils.h"

#include <\devel\libs\SDL\SDL.h>
#include <\devel\libs\SDL\SDL_mixer.h>


// Sound channel descriptor and access macro
typedef struct SNDCHANNEL        // Kept in bs->snddata array, must not exceed 128 bytes in size!
{
  S32 vol;
  S32 pan;
  S32 status;
  S32 paused;    // 1 if paused, 0 if playing
  MIXINFO info;
  struct BINKSND * prev;
  struct BINKSND * next;
} SNDCHANNEL;

#define BS ( ( SNDCHANNEL * ) ( & ( bs->snddata[ 0 ] ) ) )
#define SC( v ) ( ( SNDCHANNEL * ) ( & ( (v)->snddata[ 0 ] ) ) )


static struct BINKSND * list = 0;
static MIXINFO sdl_info;
static S32 sdl_rate, sdl_bits, sdl_chans;
static U32 mix_size_adj;


// mixes from the internal Bink data into the supplied address
static void mix_track( S32 * dest, U32 dest_len, struct BINKSND * bs )
{
  U8 * dest_end;

  dest_end = ( (U8*) dest ) + dest_len;

  // loop while we have more sound and while there is room to put it
  while ( ( bs->sndamt ) && ( ( (U8*) dest ) < dest_end ) )
  {
    U32 left;
    U8 * s;
  
    // save the starting source position
    s = bs->sndreadpos;

    // Bink uses a circular buffer, so we need to see if we are at the end of the buffer
    //   and wrap if necessary
    if ( s == bs->sndend )
    {
      bs->sndreadpos = bs->sndbuf;
      s = bs->sndbuf;
    }

    // now we need to see if mixing all of our audio would wrap around the end of the 
    //   circular buffer.  if so, clamp the total, so we only go to the end.
    left = bs->sndend - s;
    if ( left > bs->sndamt )
    {
      left = bs->sndamt;
    }
 
    // mix the chunk of audio
    simp_mix( &BS->info, &dest, (void**) &s, dest_end - (U8*) dest, left ); 

    // update the src amount based on how much the source moved
    LockedAddFunc(&bs->sndamt, bs->sndreadpos - s );
    bs->sndreadpos = s;
  }
}


// on receiving this callback, spin through all of the playing Bink sound tracks and mix 
//   them together along with the incoming SDL buffer, and then copy all of the mixed
//   data back into the SDL buffer.

static void sdl_callback( int chan, void * out, int len, void * user_data )
{
  while( len )
  {
    U32 out_len, in_len;
    struct BINKSND * bs;
    S32 buffer[ 1024 ];

    // calculate how many S32 samples "len" actually is.  clamp it to the total size
    //  of our local mixing buffer.

    out_len = len << mix_size_adj;
    if ( out_len > sizeof( buffer ) )
    {
      out_len = sizeof( buffer );
    }
    in_len = out_len >> mix_size_adj;

    
    // clear the mixing buffer 
    memset( buffer, 0 , out_len );

    // run through all of the Bink sound tracks that are playing
    bs = list;
    while ( bs )
    {
      // if we are playing, then mix the sound from Bink into out mixing buffer.
      if ( ( !BS->paused ) && ( bs->OnOff ) )
      {
        mix_track( buffer, out_len, bs );
      }

      bs = BS->next;
    }
    
    // now mix in existing data from sdl
    {
      S32 * dest;
      void * src;
      dest = buffer;
      src = out;
  
      simp_mix( &sdl_info, &dest, &src, out_len, in_len );

      dest=dest;
    }

    // finally, take our mixed buffer and copy it back into the SDL buffer (now with all of the
    //   Bink sound tracks mixed together with the original data).
    if ( sdl_bits == 16 )
    {
      out = clamp_to_s16( out, buffer, out_len );
    }
    else
    {
      out = clamp_to_u8( out, buffer, out_len );
    }

    len -= in_len;    
  }
}


// since our sdl support code copies directly out ot the bink tracks, we don't use
//   ready, lock or unlock (everything gets sucked out in the callback)

static S32 RADLINK Ready( struct BINKSND PTR4* bs )
{
  return( 0 );
}

static S32 RADLINK Lock( struct BINKSND PTR4* bs, U8 PTR4* PTR4* addr, U32 PTR4* len )
{
  return( 0 );
}

static S32  RADLINK Unlock (struct BINKSND PTR4* bs,U32 filled)
{
  return( 0 );
}

// set the volume 0=quiet, 32767=max, 65536=double volume (not always supported)
static void RADLINK Volume ( struct BINKSND PTR4* bs, S32 volume )
{
  if ( volume >= 65536 )
  {
    volume = 65535;
  }
  BS->vol = volume;
  set_mix_volume( &BS->info, volume, BS->pan );
}

// set the pan 0=left, 32767=middle, 65536=right
static void RADLINK Pan( struct BINKSND PTR4* bs, S32 pan )
{
  if ( pan > 65536 )
  {
    pan = 65536;
  }
  BS->pan = pan;
  set_mix_volume( &BS->info, BS->vol, pan );
}


// called to turn the sound on or off
static S32  RADLINK SetOnOff( struct BINKSND PTR4* bs, S32 status )
{
  bs->OnOff = status;
  return( bs->OnOff );
}


// pauses/resumes the playback
static S32  RADLINK Pause( struct BINKSND PTR4* bs, S32 status )  // 1=pause, 0=resume, -1=resume and clear
{
  BS->paused = status;
  return( BS->paused );
}


// closes this channel

static void RADLINK Close( struct BINKSND PTR4* bs )
{
  // TODO lock background
  if ( list == bs )
  {
    list = BS->next;
  }
  if ( BS->prev )
  {
    SC(BS->prev)->next = BS->next;
  }
  if ( BS->next )
  {
    SC(BS->next)->prev = BS->prev;
  }

  if ( list == 0 )
  {
    // remove from SDL
    Mix_UnregisterEffect( MIX_CHANNEL_POST, sdl_callback );
  }
  // TODO unlock background
}


static S32 RADLINK Open( struct BINKSND PTR4* bs, U32 freq, S32 bits, S32 chans, U32 flags, HBINK bink )
{
  //
  // Init sound descriptor
  //

  memset( bs, 0, sizeof( *bs ) );

  bs->SoundDroppedOut = 0;

  bs->freq  = freq;
  bs->bits  = 16;   // we always take 16-bit input and let our mixer convert it
  bs->chans = chans;

  //
  // Set initial values
  //

  BS->vol =  32768;
  BS->pan =  32768;

  //
  // Set initial status
  //

  BS->paused    = 0;
  bs->OnOff     = 1;

  //
  // Set up the function calls
  //

  bs->Ready    = Ready;
  bs->Lock     = Lock;
  bs->Unlock   = Unlock;
  bs->Volume   = Volume;
  bs->Pan      = Pan;
  bs->Pause    = Pause;
  bs->SetOnOff = SetOnOff;
  bs->Close    = Close;

  bs->Latency = 0;

  if ( list == 0 )
  {
    U16 format;

    // make sure SDL_mixer has been opened and if so, retrieve the sound config
    if ( Mix_QuerySpec( (int*)&sdl_rate, &format, (int*)&sdl_chans ) == 0 )
    {
      return( 0 );
    }

    // install our sdl callback as an effect callback
    if ( Mix_RegisterEffect( MIX_CHANNEL_POST, sdl_callback, 0, 0 ) == 0 )
    {
      return( 0 );
    }

    sdl_bits = ( ( format == AUDIO_S8 ) || ( format == AUDIO_U8 ) ) ? 8 : 16;
    mix_size_adj = ( sdl_bits == 8 ) ? 2 : 1; // adjustment from sample size to 32 bits mixing size

    // fill in the mixing info structure
    init_mix_info( &sdl_info, sdl_rate, sdl_rate, sdl_chans, sdl_chans, sdl_bits );
    init_mix_info( &BS->info, sdl_rate, bs->freq, sdl_chans, bs->chans, bs->bits );
  }

  BS->prev = 0;
  BS->next = list;
  if ( list )
    SC(list)->prev = bs;
  list = bs;

  return( 1 );
}


RADEXPFUNC BINKSNDOPEN RADEXPLINK BinkOpenSDLMixer( U32 param )
{
  return( &Open );          // Return the proc pointer
}




















#include <windows.h>

//
// Example globals
//

static HBINK Bink = 0;
static HBINKBUFFER Bink_buffer = 0;


//############################################################################
//##                                                                        ##
//## Clear_to_black - just fills a window with black pixels.                ##
//##                                                                        ##
//############################################################################

static void Clear_to_black( HWND window )
{
  PAINTSTRUCT ps;
  HDC dc;

  //
  // Get the repaint DC and then fill the window with black.
  //

  dc = BeginPaint( window, &ps );

  PatBlt( dc, 0, 0, 4096, 4096, BLACKNESS );

  EndPaint( window, &ps );
}


//############################################################################
//##                                                                        ##
//## WindowProc - the main window message procedure.                        ##
//##                                                                        ##
//############################################################################

LONG FAR PASCAL WindowProc( HWND   window,
                            UINT   message,
                            WPARAM wparam,
                            LPARAM lparam )
{

  switch( message )
  {
    //
    // Just close the window if the user hits a key.
    //

    case WM_CHAR:
      DestroyWindow( window );
      break;

    //
    // Pause/resume the video when the focus changes.
    //

    case WM_KILLFOCUS:
      BinkPause( Bink, 1 );
      break;

    case WM_SETFOCUS:
      BinkPause( Bink, 0 );
      break;

    //
    // Handle the window paint messages.
    //

    case WM_PAINT:
      Clear_to_black( window );

      //
      // Redraw the frame (or the color mask for overlays).
      //

      if ( Bink_buffer )
        BinkBufferBlit( Bink_buffer, 0, 1 );

      return( 0 );

    case WM_ERASEBKGND:
      return( 1 );

    //
    // Handle the window being moved.
    //

    case WM_WINDOWPOSCHANGING:
      //
      // Is the window even being moved?
      //

      if ( ! ( ( ( WINDOWPOS* )lparam )->flags & SWP_NOMOVE ) )
      {

        if ( Bink_buffer )
        {
          S32 x,y;

          //
          // Yup, it's being moved - ask the BinkBuffer API to align the
          //   coordinates to a fast boundary.
          //

          x = ( ( WINDOWPOS* )lparam )->x;
          y = ( ( WINDOWPOS* )lparam )->y;
          BinkBufferCheckWinPos( Bink_buffer, &x, &y );
          ( ( WINDOWPOS* )lparam )->x = x;
          ( ( WINDOWPOS* )lparam )->y = y;
        }

      }
      break;

    case WM_WINDOWPOSCHANGED:
      //
      // Tell the BinkBuffer API when the window moves.
      //

      if ( Bink_buffer )
        BinkBufferSetOffset( Bink_buffer, 0, 0 );
      break;

    //
    // Post the quit message.
    //

    case WM_DESTROY:
      PostQuitMessage( 0 );
      return( 0 );
  }

  //
  // Call the OS default window procedure.
  //

  return( DefWindowProc( window, message, wparam, lparam ) );
}


//############################################################################
//##                                                                        ##
//## Build_window_handle - creates a window class and window handle.        ##
//##                                                                        ##
//############################################################################

static HWND Build_window_handle( HINSTANCE instance,
                                 HINSTANCE previous_instance )
{
  //
  // Create the window class if this is the first instance.
  //

  if ( !previous_instance )
  {
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = LoadIcon( instance, MAKEINTRESOURCE( 101 ) );
    wc.hCursor = LoadCursor( 0, IDC_ARROW );;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = "BinkExam";

    //
    // Try to register the class.
    //

    if ( !RegisterClass( &wc ) )
    {
      return( 0 );
    }
  }

  //
  // Return the new window with a tiny initial default size (it is resized
  //   later on with the help of the BinkBuffer API).
  //

  return( CreateWindow( "BinkExam",
                        "Bink Example Player",
			   WS_CAPTION|WS_POPUP|WS_CLIPCHILDREN|
                        WS_SYSMENU|WS_MINIMIZEBOX,
                        64, 64,
                        64, 64,
                        0, 0, instance,0 ) );
}


//############################################################################
//##                                                                        ##
//## Show_next_frame - advances to the next Bink frame.                     ##
//##                                                                        ##
//############################################################################

static void Show_next_frame( HBINK bink,
                             HBINKBUFFER bink_buffer,
                             HWND window )
{
  //
  // Decompress the Bink frame.
  //

  BinkDoFrame( bink );

  //
  // Lock the BinkBuffer so that we can copy the decompressed frame into it.
  //

  if ( BinkBufferLock( bink_buffer ) )
  {
    //
    // Copy the decompressed frame into the BinkBuffer (this might be on-screen).
    //

    BinkCopyToBuffer( bink,
                      bink_buffer->Buffer,
                      bink_buffer->BufferPitch,
                      bink_buffer->Height,
                      0,0,
                      bink_buffer->SurfaceType);
    
    //
    // Unlock the BinkBuffer.
    //

    BinkBufferUnlock( bink_buffer );
  }

  //
  // Tell the BinkBuffer to blit the pixels onto the screen (if the
  //   BinkBuffer is using an off-screen blitting style).
  //

  BinkBufferBlit( bink_buffer,
                  bink->FrameRects,
                  BinkGetRects( bink, bink_buffer->SurfaceType ) );

  //
  // Are we at the end of the movie?
  //

  if ( bink->FrameNum == bink->Frames )
  {
    //
    // Yup, close the window.
    //

    DestroyWindow( window );
  }
  else
  {
    //
    // Nope, advance to the next frame.
    //

    BinkNextFrame( bink );
  }
}


//############################################################################
//##                                                                        ##
//##  Good_sleep_us - sleeps for a specified number of MICROseconds.        ##
//##    The task switcher in Windows has a latency of 15 ms.  That means    ##
//##    you can ask for a Sleep of one millisecond and actually get a       ##
//##    sleep of 15 ms!  In normal applications, this is no big deal,       ##
//##    however, with a video player at 30 fps, 15 ms is almost half our    ##
//##    frame time!  The Good_sleep_us function times each sleep and keeps  ##
//##    the average sleep time to what you requested.  It also give more    ##
//##    accuracy than Sleep - Good_sleep_us() uses microseconds instead of  ##
//##    milliseconds.                                                       ##
//##                                                                        ##
//############################################################################

static void Good_sleep_us( S32 microseconds )
{
  static S32 total_sleep=0;
  static S32 slept_in_advance=0;
  static U64 frequency=1000;
  static S32 got_frequency=0;

  //
  // If this is the first time called, get the high-performance timer count.
  //

  if ( !got_frequency )
  {
    got_frequency = 1;
    QueryPerformanceFrequency( ( LARGE_INTEGER* )&frequency );
  }

  total_sleep += microseconds;

  //
  // Have we exceeded our reserve of slept microseconds?
  //

  if (( total_sleep - slept_in_advance ) > 1000)
  {
    U64 start, end;
    total_sleep -= slept_in_advance;

    //
    // Do the timed sleep.
    //

    QueryPerformanceCounter( ( LARGE_INTEGER* )&start );
    Sleep( total_sleep / 1000 );
    QueryPerformanceCounter( ( LARGE_INTEGER* )&end );

    //
    // Calculate delta time in microseconds.
    //

    end = ( (end - start) * (U64)1000000 ) / frequency;

    //
    // Keep track of how much extra we slept.
    //

    slept_in_advance = ( U32 )end - total_sleep;
    total_sleep %= 1000;
  }
}

//############################################################################
//##                                                                        ##
//## WinMain - the primary function entry point                             ##
//##                                                                        ##
//############################################################################

int PASCAL WinMain( HINSTANCE instance,
                    HINSTANCE previous_instance,
                    LPSTR cmd_line,
                    int cmd_show )
{
  //
  // Win32 locals.
  //

  HWND window = 0;
  MSG msg;

  //
  // Try to create our window.
  //

  window = Build_window_handle( instance,
                                previous_instance );
  if ( !window )
  {
    MessageBox( 0,
                "Error creating window.",
                "Windows",
                MB_OK | MB_ICONSTOP );
    return( 1 );
  }

  //
  // Tell Bink to use DirectSound (must be before BinkOpen)!
  //

//  BinkSoundUseDirectSound( 0 );
Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096);
BinkSetSoundSystem(BinkOpenSDLMixer,0);
  //
  // Try to open the Bink file.
  //
  
  Bink = BinkOpen( cmd_line, 0 );
  if ( !Bink )
  {
    MessageBox( window,
                BinkGetError( ),
                "Bink Error",
                MB_OK | MB_ICONSTOP );

    DestroyWindow( window );
    return( 3 );
  }

  //
  // Try to open the Bink buffer.
  //

  Bink_buffer = BinkBufferOpen( window, Bink->Width, Bink->Height, 0 );
  if ( !Bink_buffer )
  {
    MessageBox( window,
                BinkBufferGetError( ),
                "Bink Error",
                MB_OK | MB_ICONSTOP );

    DestroyWindow( window );
    BinkClose( Bink );

    return( 4 );
  }

  //
  // Size the window such that its client area exactly fits our Bink movie.
  //

  SetWindowPos( window, 0,
                0, 0,
                Bink_buffer->WindowWidth,
                Bink_buffer->WindowHeight,
                SWP_NOMOVE );

  //
  // Now display the window and start the message loop.
  //

  ShowWindow( window, cmd_show );

  for ( ; ; )
  {
    //
    // Are there any messages to handle?
    //

    if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
    {
      //
      // Yup, handle them.
      //

      if ( msg.message == WM_QUIT )
        break;

      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
    else
    {
      //
      // Is it time for a new Bink frame?
      //

      if ( !BinkWait( Bink ) )
      {
        //
        // Yup, draw the next frame.
        //

        Show_next_frame( Bink,
                         Bink_buffer,
                         window );
      }
      else
      {
        //
        // Nope, give the rest of the system a chance to run (500 MICROseconds).
        //

        Good_sleep_us( 500 );
      }

    }
  }

  //
  // Close the Bink file.
  //

  if ( Bink )
  {
    BinkClose( Bink );
    Bink = 0;
  }

  //
  // Close the Bink buffer.
  //

  if ( Bink_buffer )
  {
    BinkBufferClose( Bink_buffer );
    Bink_buffer = 0;
  }

  //
  // And exit.
  //

  return( 0 );
}


// some stuff for the RAD build utility
// @cdep pre $DefaultsWinEXE
// @cdep pre $requiresbinary($BuildDir/binkw32.lib)
// @cdep pre $requiresbinary(\devel\libs\sdl\sdl_mixer.lib)
// @cdep post $BuildWinEXE( , )
