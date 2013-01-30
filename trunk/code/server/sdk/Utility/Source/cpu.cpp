#include "../stdafx.h"
#include "platform.h"
#include "CommDef.h"
#include "fasttimer.h"
#include "dbg.h"
#include <math.h>
#include <string.h>

#define RDTSC _asm _emit 0x0f _asm _emit 0x31

#ifdef X64_WIN
#include <intrin.h>
#endif

static bool cpuid(unsigned long function, unsigned long& out_eax, unsigned long& out_ebx, unsigned long& out_ecx, unsigned long& out_edx)
{
	bool retval = true;
#ifdef WIN32
#ifdef X64_WIN
	
	int CPUInfo[4] = {-1};
	__cpuid(CPUInfo, function);

	out_eax = CPUInfo[0];
	out_ebx = CPUInfo[1];
	out_ecx = CPUInfo[2];
	out_edx = CPUInfo[3];
	
//	assert(0);

#else
	unsigned long local_eax, local_ebx, local_ecx, local_edx;
	_asm pushad;

	__try
	{
        _asm
		{
			xor edx, edx		// Clue the compiler that EDX is about to be used.
            mov eax, function   // set up CPUID to return processor version and features
								//      0 = vendor string, 1 = version info, 2 = cache info
            cpuid				// code bytes = 0fh,  0a2h
            mov local_eax, eax	// features returned in eax
            mov local_ebx, ebx	// features returned in ebx
            mov local_ecx, ecx	// features returned in ecx
            mov local_edx, edx	// features returned in edx
		}
    } 
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{ 
		retval = false; 
	}

	out_eax = local_eax;
	out_ebx = local_ebx;
	out_ecx = local_ecx;
	out_edx = local_edx;

	_asm popad
#endif
	return retval;
#else	

//	asm("cpuid": "=a" (out_eax), "=b" (out_ebx), "=c" (out_ecx), "=d" (out_edx) : "a" (function));

#ifdef X86AMD64
	uint64_t local_rax, local_rbx, local_rcx, local_rdx;
	asm volatile("push %%rbx      \n\t"
                 "cpuid           \n\t"
                 "mov %%rbx, %1   \n\t"
                 "pop %%rbx       \n\t"
                 : "=a"(local_rax), "=r"(local_rbx), "=c"(local_rcx), "=d"(local_rdx)
                 : "a"(function)
                 : "cc");

	out_eax = local_rax;
	out_ebx = local_rbx;
	out_ecx = local_rcx;
	out_edx = local_rdx;
#else
    asm volatile("pushl %%ebx      \n\t"
                 "cpuid            \n\t"
                 "movl %%ebx, %1   \n\t"
                 "popl %%ebx       \n\t"
                 : "=a"(out_eax), "=r"(out_ebx), "=c"(out_ecx), "=d"(out_edx)
                 : "a"(function)
                 : "cc");
#endif


	return true;
#endif


}

bool CheckMMXTechnology(void)
{
    unsigned long eax,ebx,edx,unused;
    if( !cpuid(1,eax,ebx,unused,edx) )
		return false;

    return ( edx & 0x800000 ) != 0;
}

bool CheckSSETechnology(void)
{
    unsigned long eax,ebx,edx,unused;
    if( !cpuid(1,eax,ebx,unused,edx) )
		return false;

    return ( edx & 0x2000000L ) != 0;
}

bool CheckSSE2Technology(void)
{
    unsigned long eax,ebx,edx,unused;
    if( !cpuid(1,eax,ebx,unused,edx) )
		return false;

    return ( edx & 0x04000000 ) != 0;
}

bool Check3DNowTechnology(void)
{
    unsigned long eax, unused;
    if( !cpuid(0x80000000,eax,unused,unused,unused) )
		return false;

    if ( eax > 0x80000000L )
    {
     	if( !cpuid(0x80000001,unused,unused,unused,eax) )
			return false;

		return ( eax & 1<<31 ) != 0;
    }
    return false;
}

bool CheckCMOVTechnology()
{
    unsigned long eax,ebx,edx,unused;
    if( !cpuid(1,eax,ebx,unused,edx) )
		return false;

    return ( edx & (1<<15) ) != 0;
}

bool CheckFCMOVTechnology(void)
{
    unsigned long eax,ebx,edx,unused;
    if( !cpuid(1,eax,ebx,unused,edx) )
		return false;

    return ( edx & (1<<16) ) != 0;
}

bool CheckRDTSCTechnology(void)
{
    unsigned long eax,ebx,edx,unused;
    if( !cpuid(1,eax,ebx,unused,edx) )
		return false;

    return ( edx & 0x10 ) != 0;
}

// Return the Processor's vendor identification string, or "Generic_x86" if it doesn't exist on this CPU
const char* GetProcessorVendorId()
{
	unsigned long unused, VendorIDRegisters[3];

	static char VendorID[13];
	
	memset( VendorID, 0, sizeof(VendorID) );
	if( !cpuid(0,unused, VendorIDRegisters[0], VendorIDRegisters[2], VendorIDRegisters[1] ) )
	{
		strcpy( VendorID, "Generic_x86" ); 
	}
	else
	{
		memcpy( VendorID+0, &(VendorIDRegisters[0]), sizeof( VendorIDRegisters[0] ) );
		memcpy( VendorID+4, &(VendorIDRegisters[1]), sizeof( VendorIDRegisters[1] ) );
		memcpy( VendorID+8, &(VendorIDRegisters[2]), sizeof( VendorIDRegisters[2] ) );
	}


	return VendorID;
}

// Returns non-zero if Hyper-Threading Technology is supported on the processors and zero if not.  This does not mean that 
// Hyper-Threading Technology is necessarily enabled.
static bool HTSupported(void)
{
	const unsigned int HT_BIT		 = 0x10000000;  // EDX[28] - Bit 28 set indicates Hyper-Threading Technology is supported in hardware.
	const unsigned int FAMILY_ID     = 0x0f00;      // EAX[11:8] - Bit 11 thru 8 contains family processor id
	const unsigned int EXT_FAMILY_ID = 0x0f00000;	// EAX[23:20] - Bit 23 thru 20 contains extended family  processor id
	const unsigned int PENTIUM4_ID   = 0x0f00;		// Pentium 4 family processor id

	unsigned long unused,
				  reg_eax = 0, 
				  reg_edx = 0,
				  vendor_id[3] = {0, 0, 0};

	// verify cpuid instruction is supported
	if( !cpuid(0,unused, vendor_id[0],vendor_id[2],vendor_id[1]) 
	 || !cpuid(1,reg_eax,unused,unused,reg_edx) )
	 return false;

	//  Check to see if this is a Pentium 4 or later processor
	if (((reg_eax & FAMILY_ID) ==  PENTIUM4_ID) || (reg_eax & EXT_FAMILY_ID))
		if (vendor_id[0] == 'uneG' && vendor_id[1] == 'Ieni' && vendor_id[2] == 'letn')
			return (reg_edx & HT_BIT) != 0;	// Genuine Intel Processor with Hyper-Threading Technology

	return false;  // This is not a genuine Intel processor.
}

// Returns the number of logical processors per physical processors.
static unsigned char LogicalProcessorsPerPackage(void)
{
	const unsigned NUM_LOGICAL_BITS = 0x00FF0000; // EBX[23:16] indicate number of logical processors per package

    unsigned long unused,
		          reg_ebx = 0;
    if (!HTSupported()) 
		return 1; 

	if( !cpuid(1,unused,reg_ebx,unused,unused) )
		return 1;

	return (unsigned char) ((reg_ebx & NUM_LOGICAL_BITS) >> 16);
}

#define ROUND_THRESHOLD		6
DWORD s_Cycle=0;
DWORD s_CP10K=0;

// Measure the processor clock speed by sampling the cycle count, waiting
// for some fraction of a second, then measuring the elapsed number of cycles.
static int64 CalculateClockSpeed()
{
#ifdef WIN32

	LARGE_INTEGER waitTime, startCount, curCount;
	QueryPerformanceCounter(&startCount);
	QueryPerformanceFrequency(&waitTime);
	int scale = 2;		// Take 1/32 of a second for the measurement.
	waitTime.QuadPart >>= scale;

	CCycleCount start, end;
	start.Sample();
	do
	{
		QueryPerformanceCounter(&curCount);
	}
	while(curCount.QuadPart - startCount.QuadPart < waitTime.QuadPart);
	end.Sample();

	return (end.m_Int64 - start.m_Int64) << scale;
/*

	int raw_freq;		// Raw frequency of CPU in MHz

	int norm_freq;	// Normalized frequency of CPU
	//   in MHz.
	LARGE_INTEGER t0,t1;			// Variables for High-
	//   Resolution Performance
	//   Counter reads

	DWORD freq  =0;			// Most current frequ. calculation
	DWORD freq2 =0;			// 2nd most current frequ. calc.
	DWORD freq3 ;			// 3rd most current frequ. calc.

	DWORD total;			// Sum of previous three frequency
	//   calculations

	int tries=0;			// Number of times a calculation has
	//   been made on this call to 
	//   cpuspeed

	DWORD  total_cycles=0, cycles;	// Clock cycles elapsed 
	//   during test

	DWORD  stamp0 = 0;
	DWORD  stamp1 = 0;			// Time Stamp Variable 
	//   for beginning and end 
	//   of test

	DWORD  total_ticks=0, ticks;	// Microseconds elapsed 
	//   during test

	LARGE_INTEGER count_freq;		// High Resolution 
	//   Performance Counter 
	//   frequency

	int iPriority;
	HANDLE hThread = GetCurrentThread();

	if( !QueryPerformanceFrequency ( &count_freq ) )
		return 0;

	// On processors supporting the Read 
	//   Time Stamp opcode, compare elapsed
	//   time on the High-Resolution Counter
	//   with elapsed cycles on the Time 
	//   Stamp Register.

	do {			// This do loop runs up to 20 times or
		//   until the average of the previous 
		//   three calculated frequencies is 
		//   within 1 MHz of each of the 
		//   individual calculated frequencies. 
		//   This resampling increases the 
		//   accuracy of the results since
		//   outside factors could affect this
		//   calculation

		tries++;		// Increment number of times sampled
		//   on this call to cpuspeed

		freq3 = freq2;	// Shift frequencies back to make
		freq2 = freq;	//   room for new frequency 
		//   measurement

		QueryPerformanceCounter(&t0);	
		// Get high-resolution performance 
		//   counter time

		t1.LowPart = t0.LowPart;		// Set Initial time
		t1.HighPart = t0.HighPart;

		iPriority = GetThreadPriority(hThread);
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
		}

		while ( (DWORD )t1.LowPart - (DWORD )t0.LowPart<50) {	  
			// Loop until 50 ticks have 
			//   passed	since last read of hi-
			//	 res counter. This accounts for
			//   overhead later.

			QueryPerformanceCounter(&t1);

			RDTSC;						// Read Time Stamp
			_asm {
				MOV stamp0, EAX
			}
		}


		t0.LowPart = t1.LowPart;		// Reset Initial 
		t0.HighPart = t1.HighPart;		//   Time

		while ((DWORD )t1.LowPart-(DWORD )t0.LowPart<1000 ) {
			// Loop until 1000 ticks have 
			//   passed	since last read of hi-
			//   res counter. This allows for
			//   elapsed time for sampling.


			QueryPerformanceCounter(&t1);


			RDTSC;						// Read Time Stamp
			__asm {
				MOV stamp1, EAX
			}
		}


		// Reset priority
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, iPriority);
		}

		cycles = stamp1 - stamp0;	// Number of internal 
		//   clock cycles is 
		//   difference between 
		//   two time stamp 
		//   readings.

		ticks = (DWORD ) t1.LowPart - (DWORD ) t0.LowPart;	
		// Number of external ticks is
		//   difference between two
		//   hi-res counter reads.


		// Note that some seemingly arbitrary mulitplies and
		//   divides are done below. This is to maintain a 
		//   high level of precision without truncating the 
		//   most significant data. According to what value 
		//   ITERATIIONS is set to, these multiplies and
		//   divides might need to be shifted for optimal
		//   precision.

		ticks = ticks * 100000;	
		// Convert ticks to hundred
		//   thousandths of a tick

		ticks = ticks / ( count_freq.LowPart/10 );		
		// Hundred Thousandths of a 
		//   Ticks / ( 10 ticks/second )
		//   = microseconds (us)

		if( ticks <= 0 )
			ticks = 1;

		total_ticks += ticks;
		total_cycles += cycles;

		if ( ticks%count_freq.LowPart > count_freq.LowPart/2 )
			ticks++;			// Round up if necessary

		freq = cycles/ticks;	// Cycles / us  = MHz

		if ( cycles%ticks > ticks/2 )
			freq++;				// Round up if necessary

		total = ( freq + freq2 + freq3 );
		// Total last three frequency 
		//   calculations

	} while ( (tries < 3 ) || 		
		(tries < 20)&&
		((abs(int(3 * freq -total) > 3) )||
		(abs(int(3 * freq2-total) > 3) )||
		(abs(int(3 * freq3-total) > 3) )));	
	// Compare last three calculations to 
	//   average of last three calculations.		

	// Try one more significant digit.
	freq3 = ( total_cycles * 10 ) / total_ticks;
	freq2 = ( total_cycles * 100 ) / total_ticks;


	if ( freq2 - (freq3 * 10) >= ROUND_THRESHOLD )
		freq3++;

	s_CP10K= (int) ((double)total_cycles / total_ticks * 100);
	s_Cycle = s_CP10K * 1000;
	raw_freq = total_cycles / total_ticks;
	norm_freq = raw_freq;

	freq = raw_freq * 10;
	if( (freq3 - freq) >= ROUND_THRESHOLD )
		norm_freq++;

	return norm_freq;
*/
#else
	uint64 CalculateCPUFreq(); // from cpu_linux.cpp
	int64 freq =(int64)CalculateCPUFreq();
	if ( freq == 0 ) // couldn't calculate clock speed
	{
		Error( "Unable to determine CPU Frequency\n" );
	}
	return freq;
#endif
}

const CPUInformation& GetCPUInformation()
{
	static CPUInformation pi;

	// Has the structure already been initialized and filled out?
	if( pi.m_Size == sizeof(pi) )
		return pi;

	// Redundant, but just in case the user somehow messes with the size.
	memset(&pi, 0, sizeof(pi));

	// Fill out the structure, and return it:
	pi.m_Size = sizeof(pi);

	// Grab the processor frequency:
	pi.m_Speed = CalculateClockSpeed();

	
	// Get the logical and physical processor counts:
	pi.m_nLogicalProcessors = LogicalProcessorsPerPackage();

#ifdef WIN32
	SYSTEM_INFO si;
	memset(&si, 0, sizeof(si));
	GetSystemInfo( &si );

	pi.m_nPhysicalProcessors = (unsigned char)(si.dwNumberOfProcessors / pi.m_nLogicalProcessors);
	pi.m_nLogicalProcessors *= pi.m_nPhysicalProcessors;

	// Make sure I always report at least one, when running WinXP with the /ONECPU switch, 
	// it likes to report 0 processors for some reason.
	if( pi.m_nPhysicalProcessors == 0 && pi.m_nLogicalProcessors == 0 )
	{
		pi.m_nPhysicalProcessors = 1;
		pi.m_nLogicalProcessors = 1;
	}
#else
	// TODO: poll /dev/cpuinfo when we have some benefits from multithreading
	pi.m_nPhysicalProcessors = 1;
	pi.m_nLogicalProcessors = 1;
#endif

	// Determine Processor Features:
	pi.m_bRDTSC = CheckRDTSCTechnology();
	pi.m_bCMOV  = CheckCMOVTechnology();
	pi.m_bFCMOV = CheckFCMOVTechnology();
	pi.m_bMMX   = CheckMMXTechnology();
	pi.m_bSSE   = CheckSSETechnology();
	pi.m_bSSE2  = CheckSSE2Technology();
	pi.m_b3DNow = Check3DNowTechnology();

	pi.m_szProcessorID = (char*)GetProcessorVendorId();
	return pi;
}


