#include "../stdafx.h"
#include "XMLParser.h"
#include "FileStdio.h"
#include "platform.h" // Plat_Alloc Plat_Free
//#include "mynew.h" // Plat_Alloc Plat_Free
#include <stdlib.h> // wcstol
#include "strtools.h" // WideCharToChar
#ifndef WIN32
#include <malloc_np.h>
#endif

IMPLEMENT_CLASS( IXMLParser, IBaseObj )

IXMLParser::IXMLParser(void)
{
	m_pRoot = NULL;
	m_bExtern = FALSE;
}

IXMLParser::IXMLParser( McbXMLElement * pElement )
{
	//Assert( pElement );

	m_pRoot = NULL;
	m_bExtern = FALSE;
	Verify( Build( pElement ) );
}

IXMLParser::IXMLParser( IXMLParser * pElement, LPCWSTR lpName )
{
	m_pRoot = NULL;
	m_bExtern = pElement ? TRUE : FALSE;
	Verify( Build( pElement, lpName ) );
}

IXMLParser::~IXMLParser(void)
{
	Release( );
}

BOOL IXMLParser::Load( LPCWSTR lpName, LPCWSTR lpPathID )
{
	char szAnsiName[256];
	char szAnsiPathID[256];
/*
printf("===== 1\n");
int nCountSrc = wcslen( lpName ) + 1;
printf("nCount=%d  \n", nCountSrc);
const void* p=lpName;
for(int i=0; i<nCountSrc*WCHAR_BYTE_SIZE; i++)
	printf("%02X ",((char*)p)[i]);
printf("\n");
for(int i=0; i<nCountSrc*WCHAR_BYTE_SIZE; i++)
{
	if( ((char*)p)[i]==0 ) continue;
	printf("%c",((char*)p)[i]);
}
printf("\n");
p=lpPathID;
for(int i=0; i<nCountSrc*WCHAR_BYTE_SIZE; i++)
{
	if( ((char*)p)[i]==0 ) continue;
	printf("%c",((char*)p)[i]);
}
printf("\n");
//*/
	WideCharToChar( lpName, szAnsiName, 256 );
	if( lpPathID )
	{
		WideCharToChar( lpPathID, szAnsiPathID, 256 );
		return Load( szAnsiName, szAnsiPathID );
	}
	return Load( szAnsiName, NULL );
}

BOOL IXMLParser::Load( LPCSTR lpName, LPCSTR lpPathID )
{
	//Warning("Load %s File \n",lpName);
	//Assert( m_pRoot == NULL );
//printf("IXMLParser::Load lpName=%s\n",lpName);
	CFileStdio XMLFile;
	if( XMLFile.Open( lpName, "rb", lpPathID ) )
	{
		//WCHAR ID = 0;	//freebsd sizeof(WCHAR)==4    li9chuan		2011-1-13
		WORD ID = 0;
		XMLFile.Read( &ID, sizeof( WORD ) );
		// 校验是否为Unicode编码的文件

		if( ID == ((WORD)0xFEFF) )
		{
			// 读取文件内容
			int nLength = XMLFile.GetLength( );
#if WCHAR_BYTE_SIZE==2
			LPWSTR lpXMLText = (LPWSTR)Plat_Alloc( nLength );
#elif WCHAR_BYTE_SIZE==4
			LPWSTR lpXMLText = (LPWSTR)Plat_Alloc( nLength*2 );
#else
#error "WCHAR_BIT_SIZE undefine ! \n"
#endif
			Assert( lpXMLText );
			if( !lpXMLText )
				return FALSE;
			//int len = malloc_usable_size(lpXMLText);
			//printf("lpXMLText len =  %d \n", len);
			//XMLFile.Read( lpXMLText, nLength - sizeof(WCHAR) );	//freebsd sizeof(WCHAR)==4    li9chuan		2011-1-13
			XMLFile.Read( lpXMLText, nLength - sizeof(WORD) );

#if WCHAR_BYTE_SIZE==4	//	如果wchar_t占4字符，那么将读入到文件扩展。   0x41 0x00  =>   0x41 0x00 0x00 0x00		li9chuan		2011-1-17

//			memset( (void*)((unsigned int)lpXMLText+nLength), 0, nLength );
			memset( (void*)((uintptr_t)lpXMLText+nLength), 0, nLength );
			unsigned int  nTextTail = nLength-1;

			for( int  lpidx=nLength*2-1; lpidx>=0; lpidx-=4 )
			{
				((char*)(void*)lpXMLText)[lpidx]   = 0;
				((char*)(void*)lpXMLText)[lpidx-1] = 0;
				((char*)(void*)lpXMLText)[lpidx-2] = ((char*)(void*)lpXMLText)[nTextTail--];
				((char*)(void*)lpXMLText)[lpidx-3] = ((char*)(void*)lpXMLText)[nTextTail--];
			}
#endif
///*
//			#ifdef WIN32
			lpXMLText[nLength/2-1] = L'\0';
//			#else		//	nLength是XML文件的大小，在这里都是/2，所以将下面注掉		li9chuan		2011-1-17
//			lpXMLText[nLength/4-1] = L'\0'; //ucs 4 on FreeBSD
//			#endif
//*/
//			lpXMLText[nLength/WCHAR_BYTE_SIZE-1] = L'\0';

//			wprintf(L"%ls\n",lpXMLText);

/*
			CFileStdio fs;
			fs.Open("dmp.log","wb","/home/li9chuan/code/ServerPrj/DataServer/freebsd_d/");
			fs.Write(lpXMLText,nLength*2);
			fs.Close();
//*/
			// 构建XML根节点
			BOOL ret = LoadFromBuffer( lpXMLText ) ;
			if (!ret){
				printf("%s LoadFromBuffer failed in file %s line %d\n", lpName, __FILE__, __LINE__);
				return ret;
			} 
			Plat_Free( lpXMLText );
			XMLFile.Close( );
			return ret;
		}

		else
		{
			AssertMsg1( FALSE, "(%s)不是Unicode编码的文件.", lpName );
			Log( "(%s)不是Unicode编码的文件.", lpName );
		}
		XMLFile.Close( );
	}
	return FALSE;
}

BOOL IXMLParser::LoadFromBuffer( LPCWSTR lpText )
{
	Assert( lpText );

	// 构建XML根节点
	McbXMLResults results;
	m_pRoot = McbParseXML( lpText, &results );
	if (!m_pRoot)
		return FALSE;
	return TRUE;
}

BOOL IXMLParser::LoadEx( LPCSTR lpName )
{
	FILE* XMLFile=NULL;
	if( XMLFile = fopen(lpName,"rb"))
	{
		WORD wID;
		fread(&wID,sizeof(char),sizeof(WORD),XMLFile);
		// 校验是否为Unicode编码的文件
		if( wID == ((WORD)0xFEFF) )
		{
			// 读取文件内容
			fseek(XMLFile,0,SEEK_END);								//移动指针到文件尾
			int nLength =   ftell(XMLFile)+sizeof(WCHAR);			//取指针的位置来获得长度
			fseek(XMLFile,0,SEEK_SET);
			LPWSTR lpXMLText = (LPWSTR)Plat_Alloc( nLength );
			Assert( lpXMLText );
			if( !lpXMLText )
				return FALSE;
			memset(lpXMLText,0,nLength);
			fread(lpXMLText,sizeof(char),nLength,XMLFile);
			lpXMLText[nLength/2-1] = L'\0';

			// 构建XML根节点
			LoadFromBuffer( lpXMLText );

			Plat_Free( lpXMLText );
			fclose(XMLFile);

			return TRUE;
		}
		else
		{
			AssertMsg1( FALSE, "(%s)不是Unicode编码的文件.", lpName );
		}
		fclose(XMLFile);
	}
	return FALSE;
}

BOOL IXMLParser::GetXMLString( LPWSTR & lpString, int & nLength )
{
	lpString = McbCreateXMLString( m_pRoot, 1, &nLength );
	return lpString != NULL;
}

void IXMLParser::ReleaseXMLString( LPWSTR & lpString )
{
	Plat_Free( lpString );	
	lpString = NULL;
}

BOOL IXMLParser::Save( LPCWSTR lpName, LPCWSTR lpPathID )
{
	char szAnsiName[256];
	char szAnsiPathID[256];
	WideCharToChar( lpName, szAnsiName, 256 );
	WideCharToChar( lpPathID, szAnsiPathID, 256 );

	return Save( szAnsiName, szAnsiPathID );
}

BOOL IXMLParser::Save( LPCSTR lpName, LPCSTR lpPathID )
{
	Assert( m_pRoot );

	CFileStdio XMLFile;
	if( XMLFile.Open( lpName, "wb", lpPathID ) )
	{
		int nLength;
		LPWSTR lpXMLText;
		GetXMLString( lpXMLText, nLength );
		if( lpXMLText && nLength > 0 )
		{
			WORD wID = 0xFEFF;
			// 写入Unicode编码的文件头
			XMLFile.Write( &wID, sizeof( WORD ) );
			XMLFile.Write( lpXMLText, nLength * sizeof( WCHAR ) );

			ReleaseXMLString( lpXMLText );
			XMLFile.Close( );

			return TRUE;
		}
		else
		{
			AssertMsg( FALSE, "构造XML字符串失败." );
		}
		XMLFile.Close( );
	}
	return FALSE;
}

// By David yang
BOOL IXMLParser::SaveEx(LPCTSTR lpName)
{
	Assert( m_pRoot );

	FILE* XMLFile=NULL;
	if( XMLFile = fopen( lpName, "wb" ) )
	{
		int nLength;
		LPWSTR lpXMLText;
		GetXMLString( lpXMLText, nLength );
		if( lpXMLText && nLength > 0 )
		{
			WORD wID = 0xFEFF;
			// 写入Unicode编码的文件头
			fwrite(&wID,sizeof(char),sizeof(WORD),XMLFile);
			fwrite(lpXMLText, sizeof(WCHAR),nLength,XMLFile);

			ReleaseXMLString( lpXMLText );
			fclose(XMLFile);

			return TRUE;
		}
		else
		{
			AssertMsg( FALSE, "构造XML字符串失败." );
		}
		fclose(XMLFile);
	}
	return FALSE;
}

BOOL IXMLParser::Build( McbXMLElement * pElement )
{
	//Assert( pElement );
	Assert( m_pRoot == NULL );
	m_bExtern = TRUE;
	m_pRoot = pElement;
	return TRUE;
}

BOOL IXMLParser::Build( IXMLParser * pElement, LPCWSTR lpName )
{
	Assert( m_pRoot == NULL );

	if( pElement && pElement->GetElement( ) )
	{
//		Assert( lpName );
		m_bExtern = TRUE;
		if( lpName )
			m_pRoot = McbAddElement( pElement->GetElement( ), McbStrdup( lpName, 0 ), FALSE, McbGROWBY );
		else
			m_pRoot = pElement->GetElement( );
	}
	else
	{
		m_bExtern = FALSE;
		m_pRoot = McbCreateRoot( );
		if( lpName )
			SetName( lpName );
	}
	return TRUE;
}

void IXMLParser::Destroy( LPCWSTR lpPath )
{
	if( m_pRoot )
	{
		if( lpPath )
		{
			McbXMLElement * pElement = McbFindElement( m_pRoot, lpPath );
			if( pElement )
				McbDeleteElement( pElement );
		}
		else
		{
			McbDeleteElement( m_pRoot );
		}
	}
}

void IXMLParser::Release( )
{
	// 非外部构造的节点才会释放内存
	if( !m_bExtern && m_pRoot )
	{
		McbDeleteRoot( m_pRoot );
	}
	m_pRoot = NULL;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, LPWSTR lpValue, int nSize )
{
	Assert( m_pRoot );
	Assert(lpValue);
	Assert(lpAttribute);

	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		int nLength = wcslen( pAttribute->lpszValue );
		Assert( nLength <= nSize );
		if( nLength <= nSize )
		{
//			swscanf( pAttribute->lpszValue, L"\"%s\"", lpValue );
//			scanf不能截掉结尾的 \" 号，所以下面代码发现结尾是\" 号强行截掉
			LPCWSTR lpTemp = pAttribute->lpszValue;
			if( *lpTemp == L'\"' )
			{
				lpTemp++;
				nLength--;
			}
			wcsncpy( lpValue, lpTemp, nLength );
			lpValue[nLength] = L'\0';
			WCHAR * ch = lpValue + wcslen(lpValue) - 1;
			if( *ch == L'\"' )
				*ch = L'\0';
			return TRUE;
		}
	}
	lpValue[0] = L'\0';

	return FALSE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, LPSTR lpValue, int nSize )
{
	wchar_t * szwValue = (wchar_t *)stackalloc( ( nSize + 1 ) * sizeof( wchar_t ) );
	if( GetAttribute( lpAttribute, szwValue, nSize ) )
	{
		WideCharToChar( szwValue, lpValue, nSize );
		return TRUE;
	}
	return FALSE;
}

#define GET_ATTRIBUTE( lpAttribute, format, nValue )					\
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );	\
	if( pAttribute )								\
	{										\
		swscanf( pAttribute->lpszValue, format, &nValue );			\
		return TRUE;								\
	}										\
	return FALSE;

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, int & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%d\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%d\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, uint16 & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%hu\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%hu\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, uint & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%u\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%u\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, float & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%f\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%f\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, long & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%ld\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%ld\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, uint8 & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%d\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%d\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, int16 & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	GET_ATTRIBUTE( lpAttribute, L"\"%d\"", nValue );
/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		swscanf( pAttribute->lpszValue, L"\"%d\"", &nValue );
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, uint64 & nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

#ifdef WIN32
	GET_ATTRIBUTE( lpAttribute, L"\"%I64d\"", nValue );
#else
	GET_ATTRIBUTE( lpAttribute, L"\"%lld\"", nValue );
#endif

/*
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
#ifdef WIN32
		swscanf( pAttribute->lpszValue, L"\"%I64d\"", &nValue );
#else
		swscanf( pAttribute->lpszValue, L"\"%lld\"", &nValue );
#endif
		return TRUE;
	}

	return FALSE;*/
	return TRUE;
}

BOOL IXMLParser::GetAttribute( LPCWSTR lpAttribute, Vector4D& nValue )
{
	Assert(m_pRoot);
	Assert(lpAttribute);

	wchar_t* pBuffer = NULL;
	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if ( pAttribute )
	{
		int nLength = wcslen( pAttribute->lpszValue );
		if(nLength < 4)	return FALSE;
		pBuffer = new wchar_t[nLength + 1];
		Assert(pBuffer);
		wcscpy(pBuffer, pAttribute->lpszValue);

		for (int i = 0, idx = 0, commaIdx = 0; i < nLength; i++)
		{
			if (pBuffer[i] == L',')
			{
				if(idx == 0)
				{
					wchar_t* pWx = new wchar_t[i];
					Assert(pWx);
					memset(pWx, 0, i * sizeof(wchar_t));
					wcsncpy(pWx, &(pBuffer[1]), i - 1);
					swscanf( pWx, L"%f", &(nValue.x));
					SAFE_DELETE_ARRAY(pWx);
				}
				else if(idx == 1)
				{
					wchar_t* pWy = new wchar_t[i - commaIdx];
					Assert(pWy);
					memset(pWy, 0, (i - commaIdx) * sizeof(wchar_t));
					wcsncpy(pWy, &(pBuffer[commaIdx + 1]), i - commaIdx - 1);
					swscanf(pWy, L"%f", &(nValue.y));
					SAFE_DELETE_ARRAY(pWy);
				}
				else if(idx == 2)
				{
					wchar_t* pWz = new wchar_t[i - commaIdx];
					Assert(pWz);
					memset(pWz, 0, (i - commaIdx) * sizeof(wchar_t));
					wcsncpy(pWz, &(pBuffer[commaIdx + 1]), i - commaIdx - 1);
					swscanf(pWz, L"%f", &(nValue.z));
					SAFE_DELETE_ARRAY(pWz);
				}

				idx++;
				commaIdx = i;
			}

			if(i == nLength - 1)
			{
				wchar_t* pWw = new wchar_t[i - commaIdx];
				Assert(pWw);
				memset(pWw, 0, (i - commaIdx) * sizeof(wchar_t));
				wcsncpy(pWw, &(pBuffer[commaIdx + 1]), i - commaIdx - 1);
				swscanf(pWw, L"%f", &(nValue.w));
				SAFE_DELETE_ARRAY(pWw);
			}
		}

		SAFE_DELETE_ARRAY(pBuffer);
		return TRUE;
	}

	return FALSE;
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, LPCWSTR lpValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
	if( pAttribute )
	{
		int nLength = 0;
		if( pAttribute->lpszValue )
			nLength = wcslen( pAttribute->lpszValue );
		int nNewLength = wcslen( lpValue ) + 2; // 属性被夹在两个"之间所以要加2
		// 新的属性占用空间比原来的大，根据新属性重新分配内存空间
		if( nNewLength > nLength )
		{
			if( pAttribute->lpszValue )
				pAttribute->lpszValue = (LPWSTR)Plat_Realloc( pAttribute->lpszValue, ( nNewLength + 1 ) * sizeof( WCHAR ) );
			else
				pAttribute->lpszValue = (LPWSTR)Plat_Alloc( ( nNewLength + 1 ) * sizeof( WCHAR ) );
			//pAttribute->lpszValue = (LPWSTR)Plat_Realloc( pAttribute->lpszValue, ( nNewLength + 1 ) * sizeof( WCHAR ) );
		}
#ifdef WIN32
		swprintf( pAttribute->lpszValue, L"\"%s\"", lpValue );
#else
		swprintf( pAttribute->lpszValue,nNewLength, L"\"%s\"", lpValue );
#endif
		return TRUE;
	}
	else
	{
		// 新建属性
		int nLength = wcslen( lpValue );
		int nNewLength = nLength + 2; // 属性被夹在两个"之间所以要加2
		LPWSTR lpNewValue = (LPWSTR)Plat_Alloc( ( nNewLength + 1 ) * sizeof( WCHAR ) );
		int nStart = 0;
		if( lpValue[0] != L'\"' )
		{
			lpNewValue[0] = L'\"';
			nStart++;
		}
		wcscpy( lpNewValue+nStart, lpValue );
		if( lpValue[nLength-1] != L'\"' )
		{
			lpNewValue[nNewLength-2+nStart] = L'\"';
			nStart++;
		}
		lpNewValue[nNewLength-2+nStart] = L'\0';

		McbXMLAttribute * pAttribute = McbFindAttribute( m_pRoot, lpAttribute );
		pAttribute = McbAddAttribute( m_pRoot, McbStrdup( lpAttribute, 0 ), lpNewValue, McbGROWBY );
		if( pAttribute )
			return TRUE;
	}

	return FALSE;
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, LPCSTR lpValue )
{
	int nSize = Q_strlen( lpValue ) + 1;
	wchar_t * szwValue = (wchar_t *)stackalloc( ( nSize ) * sizeof( wchar_t ) );
	CharToWideChar( lpValue, szwValue, nSize );
	return SetAttribute( lpAttribute, szwValue );
}

#ifdef WIN32
#define SET_ATTRIBUTE( lpAttribute, format, nValue )\
	WCHAR lpValue[20];\
	swprintf( lpValue, format, nValue );\
	return SetAttribute( lpAttribute, lpValue );
#else
#define SET_ATTRIBUTE( lpAttribute, format, nValue )\
	WCHAR lpValue[20];\
	swprintf( lpValue, 20, format, nValue );\
	return SetAttribute( lpAttribute, lpValue );
#endif

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, int nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%d", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%d", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, uint nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%u", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%u", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, uint16 nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%hu", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%hu", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, long nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%ld", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%ld", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, float nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%f", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%f", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, uint8 nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%d", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%d", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, int16 nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

	SET_ATTRIBUTE( lpAttribute, L"%d", nValue );
/*
	WCHAR lpValue[20];
	swprintf( lpValue, L"%d", nValue );

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, uint64 nValue )
{
	Assert( m_pRoot );
	Assert(lpAttribute);

#ifdef win32
	SET_ATTRIBUTE( lpAttribute, L"%I64d", nValue );
#else
	SET_ATTRIBUTE( lpAttribute, L"%lld", nValue );
#endif

/*
	WCHAR lpValue[20];
#ifdef WIN32
	swprintf( lpValue, L"%I64d", nValue );
#else
	swprintf( lpValue, L"%lld", nValue );
#endif

	return SetAttribute( lpAttribute, lpValue );*/
}

BOOL IXMLParser::SetAttribute( LPCWSTR lpAttribute, Vector4D& nValue )
{
	Assert(m_pRoot);
	Assert(lpAttribute);

	char lpValue[MAX_PATH];
	memset(lpValue, 0, MAX_PATH);
	sprintf( lpValue, "%d,%d,%d,%d", (int)nValue.x, (int)nValue.y, (int)nValue.z, (int)nValue.w);
	return SetAttribute( lpAttribute, lpValue );
}

void IXMLParser::SetName( LPCWSTR lpName )
{
	Assert( m_pRoot );

	int nLength = 0;
	if( m_pRoot->lpszName )
		nLength = wcslen( m_pRoot->lpszName );
	int nNewLength = wcslen( lpName );
	if( nNewLength > nLength )
	{
		if( m_pRoot->lpszName )
			m_pRoot->lpszName = (LPWSTR)Plat_Realloc( m_pRoot->lpszName, ( nNewLength + 1 ) * sizeof( WCHAR ) );
		else
			m_pRoot->lpszName = (LPWSTR)Plat_Alloc( ( nNewLength + 1 ) * sizeof( WCHAR ) );
		//m_pRoot->lpszName = (LPWSTR)Plat_Realloc( m_pRoot->lpszName, ( nNewLength + 1 ) * sizeof( WCHAR ) );
	}
	wcsncpy( m_pRoot->lpszName, lpName, nNewLength );
	m_pRoot->lpszName[nNewLength] = L'\0';
}

LPCWSTR IXMLParser::GetName( )
{
	Assert( m_pRoot );
	return m_pRoot->lpszName;
}

void IXMLParser::SetText( LPCWSTR lpText )
{
	Assert( m_pRoot );

	int nIndex = 0;
	McbXMLNode *pChild;
	while( pChild = McbEnumNodes( m_pRoot, &nIndex ) )
	{
		if( pChild->type == eNodeText )
		{
			int nLength = 0;
			if( pChild->node.pText->lpszValue )
				nLength = wcslen( pChild->node.pText->lpszValue );
			int nNewLength = wcslen( lpText );
			if( nNewLength > nLength )
			{
				pChild->node.pText->lpszValue = (LPWSTR)Plat_Realloc( pChild->node.pText->lpszValue, ( nNewLength + 1 ) * sizeof( WCHAR ) );
//				pChild->node.pText->lpszValue = (LPWSTR)myrenew( pChild->node.pText->lpszValue, ( nNewLength + 1 ) * sizeof( WCHAR ) );
			}
			wcsncpy( pChild->node.pText->lpszValue, lpText, nNewLength );
			pChild->node.pText->lpszValue[nNewLength] = L'\0';
			return;
		}
	}
	McbAddText( m_pRoot, McbStrdup( lpText, 0 ), McbGROWBY );
}

LPCWSTR IXMLParser::GetText( )
{
	Assert( m_pRoot );

	int nIndex = 0;
	McbXMLNode *pChild;
	while( pChild = McbEnumNodes( m_pRoot, &nIndex ) )
	{
		if( pChild->type == eNodeText )
			return pChild->node.pText->lpszValue;
	}
	return NULL;
}
