// MUD Programming
// Ron Penton
// (C)2003
// ThreadException.h - Main header for the thread exceptions.
// This holds the ThreadException class, error codes, and functions
// to print the error codes.

#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <exception>

// ============================================================================
//  Include Files for the threading libraries
// ============================================================================
#ifdef WIN32                // windows95 and above
    #include <windows.h>
#else                       // linux
    #include <pthread.h>
#endif


namespace ThreadLib
{

    enum ThreadError
    {
        Unspecified,                // unspecified error
        InitFailure,                // thread library not initialized
        CreationFailure             // thread cannot be created
    };


    class Exception : public std::exception
    {
    public:
        // ====================================================================
        // Description: set the error code of the exception, with a default of 
        //              Unspecified.
        // ====================================================================
        Exception( ThreadError p_error = Unspecified )
        {
            m_error = p_error;
        }

        // ====================================================================
        // Description: Gets the error code of the exception
        // ====================================================================
        ThreadError GetError() const
        {
            return m_error;
        }

    protected:
        ThreadError m_error;
    };
}

#endif
