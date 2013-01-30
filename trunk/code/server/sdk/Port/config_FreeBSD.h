#ifndef CONFIG_FREEBSD_H
#define CONFIG_FREEBSD_H
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <strings.h>
#include <ctype.h>

#define POSIX

#define USE_ATT_ASM 1

#define LONG long
#define DWORD unsigned int
#define WORD  unsigned short
#define SOCKET int

#define BOOL int
#define TRUE 1
#define FALSE 0
/**/
typedef const char *LPCTSTR;
typedef const char *LPCSTR;
typedef char *	LPTSTR;
typedef const char *PCSTR;
typedef char *LPSTR;
typedef char *PCHAR;
typedef unsigned char BYTE;

typedef int64_t __int64;
typedef int64_t int64;
typedef int64_t INT64;
typedef uint64_t uint64;
typedef unsigned long ULONG;
typedef uint64_t UINT64;
typedef void *LPVOID;
typedef unsigned int UINT;
typedef uint32_t UINT32;
typedef int32_t INT32;
typedef int INT;
typedef void *PVOID;
typedef long long LONGLONG;
typedef DWORD   COLORREF;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned char UINT8, *PUINT8;
#ifndef WCHAR
#define WCHAR wchar_t
#endif /* WCHAR */

#ifndef LPCWSTR
#define LPCWSTR const wchar_t *
#endif /* LPCWSTR */

#ifndef LPWSTR
#define LPWSTR wchar_t *
#endif /* LPWSTR */

//#define L (const wchar_t *)
#define INVALID_SOCKET -1
#define WINAPI
#define HWND int

#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5

/*
 * MessageBox() Flags
 */
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L


#include <strings.h>
#define strcmpi stricmp
inline int stricmp(const char *s1, const char *s2)
{
	return strcasecmp(s1, s2);
}

inline int strnicmp(const char *s1, const char *s2, size_t len)
{
	return strncasecmp(s1, s2, len);
}
/**/
//'a' - 'A' = 32
inline char *strupr(char *str)
{
	if(!str)
		return NULL;
	int i = 0;
	for(; str[i]; i++){
		if ((str[i] >= 'a') && (str[i] <= 'z')) {
			str[i] -= 32;
		}
	}
	return str;
}

#define _strupr strupr
/**/
inline char *strlwr(char *str)
{
	if(!str)
		return NULL;
	int i = 0;
	for(; str[i]; i++){
		if ((str[i] >= 'A') && (str[i] <= 'Z')) {
			str[i] += 32;
		}
	}
	return str;
}

#define _strlwr strlwr

#define _atoi64 atoll

inline int NetWorkStart()
{
	return 1;
}

inline int WSAGetLastError()
{
	return errno;
}

/*
 * return value: whether we set nonblock succ
 */
inline int SetNonblock(SOCKET sockfd)
{
	int val = fcntl(sockfd, F_GETFL, 0);
	if (val < 0){
		return 0;
	}
	fcntl(sockfd, F_SETFL, val | O_NONBLOCK);
	return 1;
}

inline int Setblock(SOCKET sockfd)
{
	int val = fcntl(sockfd, F_GETFL, 0);
	if (val < 0){
		return 0;
	}
	fcntl(sockfd, F_SETFL, val & ~O_NONBLOCK);
	return 1;
}

#define closesocket close
#define HANDLE int

//#define __try
//#define __except(var1, var2)


inline int Sleep(int milliseconds)
{
	if (milliseconds > 0){
		usleep(milliseconds*1000);
		return milliseconds;
	}
	else
		return 0;
}


typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG HighPart;
	};
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
	long long QuadPart;
} LARGE_INTEGER;


//#ifndef  max
//#define max(a,b)            (((a) > (b)) ? (a) : (b))
//#endif

typedef void *(*LPTHREAD_START_ROUTINE)(void *);

#define __cdecl

#define MAX_PATH PATH_MAX
/*
//this struct def is copied from winbase.h
typedef struct _WIN32_FIND_DATAW {
DWORD dwFileAttributes;
//FILETIME ftCreationTime;
//FILETIME ftLastAccessTime;
//FILETIME ftLastWriteTime;
DWORD nFileSizeHigh;
DWORD nFileSizeLow;
char  cFileName[PATH_MAX];
} WIN32_FIND_DATA;
*/

#define INVALID_HANDLE_VALUE -1
#define _stat stat
#define _vsnprintf vsnprintf
#define _snprintf snprintf
#define ZeroMemory bzero

#include <sys/types.h>
#include <sys/stat.h>
#include <wchar.h>
#include <wctype.h>
#define _mkdir(pathname)  mkdir(pathname, S_IRWXU)
#define _alloca alloca
#define _wtoi(wstr) wcstoul((wstr), NULL, 10)
#define _wcsnicmp  wcsncasecmp

/*
 * This function is defined by the open group, see:
 * http://www.opengroup.org/onlinepubs/9699919799/functions/wcscasecmp.html
 * But it is not implemented on FreeBSD
 */
inline int wcsncasecmp(const wchar_t *ws1, const wchar_t *ws2, size_t n)
{
	if ((!ws1) || (!ws2) || (n<=0))
		return 0;
	wchar_t wc1, wc2;
	while (n > 0){
		if (ws1 && ws2) {
			wc1 = towlower(*ws1);
			wc2 = towlower(*ws2);
			if (wc1 == wc2) {
				ws1++;
				ws2++;
			} else if (wc1 < wc2) {
				return -1;
			} else {
				return 1;
			}
			n--;
		} else if (ws1) {
			return 1;
		} else if (ws2) {
			return -1;
		} else {
			return 0;
		}
	}
	return 0;
}

//this struct is copied from windef.h
typedef struct tagRECT
{
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

#ifndef WAIT_OBJECT_0
#define WAIT_OBJECT_0 0
#endif

#ifndef WAIT_TIMEOUT
#define WAIT_TIMEOUT  ((int)258)
#endif

typedef struct tagPOINT
{
	LONG  x;
	LONG  y;
} POINT;


typedef struct tagPOINTS
{
	short x;
	short y;
} POINTS, *PPOINTS, *LPPOINTS;

typedef struct tagSIZE
{
	LONG cx;
	LONG cy;
} SIZE;


#define IN
#define OUT

template<typename T>
inline  T abs(T x)
{
	if (x >= 0)
		return x;
	else
		return x*(-1);
}

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

inline ULONG timeGetTime(void)
{
	struct timeval t;
	// get the time of day
	gettimeofday( &t, 0 );
	// calculate the number of milliseconds represented by the seconds
	return t.tv_sec*1000 + t.tv_usec/1000;
}

#define ExitProcess(n) exit(n)
