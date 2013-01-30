#include "../stdafx.h"
#if 0
#include <stdlib.h>
#include "FtpDown.h"
#include "AsyncFileDownload.h"
#include "SLock.h"

#include "platform.h"
#include "utllinkedlist.h"
#include "dbg.h"
#include <mmsystem.h>

static SCritSect	g_downListLock;
static SEvent		g_closeEvent( true , false );  //bManualReset = true;bInitialState = false;
static SEvent		g_downEvent( false, false );
static SThread		g_backDownloadThread;

static CUtlLinkedList<std::string> g_downList;

static DWORD WINAPI BackDownloadThread( PVOID pParam);

static DWORD WINAPI BackDownloadThread(PVOID pParam)
{
	InitReadList();
	while (g_closeEvent.Wait(0) != WAIT_OBJECT_0)
	{
		DWORD ret = g_downEvent.Wait(500);
		if (ret != WAIT_TIMEOUT)
		{
			if (ret != WAIT_OBJECT_0)
			{
				Assert(0);
				MessageBox(NULL,"waitResult == OSWAIT_OBJECT_0 ", "错误", 0);
				exit(0);
			}
			CFtpDown* pFtp = new CFtpDown();
			BOOL ss = pFtp->ConnectToServer("192.168.3.251",23);
			ss = pFtp->UserLogin("t1","1");
			while (true)
			{
				g_downListLock.Enter();

				int downListHead = g_downList.Head();
				if (g_downList.IsValidIndex(downListHead))
				{
					std::string sFile;
					sFile = g_downList[downListHead];
					g_downList.Remove(downListHead);
					create_paths(sFile.c_str());
					ss = pFtp->GetFile(sFile,sFile);
					Sleep(500);
					Assert(sFile.c_str());
					g_downListLock.Leave();

				}
				else
				{
					g_downListLock.Leave();
					break;
				}
			}
		}
	}
	g_downEvent.Set( );
	return 0;
}

void BackDownloadThreadInitial()
{
	g_closeEvent.Reset();
	SThread::Create(BackDownloadThread,NULL,g_backDownloadThread,"BackDownload");
}

void BackDownloadThreadDestroy()
{
	g_closeEvent.Set();
	g_downEvent.Set();
	g_backDownloadThread.Wait(INFINITE);

	Assert(g_downList.Count() == 0);
	if (g_downList.Count() != 0 )
	{
		Log("Error! BackDownloadThread 's g_downList's count == 0");
	}
}

BOOL InitReadList()
{	
	char path[1231];
	GetCurrentDirectory(sizeof(path),path);
	FILE* fp = fopen(".\\filelist.ini","r");
	if (fp==NULL)
	{
		MessageBox(NULL,"服务器配置文件错误","aa",MB_OK);
		return FALSE;
	}
	char cFileList[65535];
	std::string sName;
	::GetPrivateProfileString("Server","name","AF_001.tga",cFileList,sizeof(cFileList),".\\filelist.ini");

	for (int i=0;i<strlen(cFileList);i++)
	{
		if (cFileList[i]=='*')
		{
			g_downList.AddToTail(sName);
			sName.clear();
			continue;
		}
		sName.push_back(cFileList[i]);
	}
	return TRUE;
}

ENGINE_GLOBAL void TestEvent()
{
	g_downEvent.Set();
}

BOOL fexist( char* fileName )
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(fileName, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) 
		return FALSE;
	return TRUE;
}

void create_paths(const char* szNewPath)
{
	char* strPath=(char*)szNewPath;
	int len=(int)strlen(strPath);
	char strDir[512];
	for(int i=0;i<len;i++)
	{
		strDir[i]=strPath[i];
		if(strPath[i]!='/')
		{
			continue;
		}
		else
		{
			strDir[i]=0;
			if(!fexist(strDir))
				::CreateDirectory(strDir,NULL);
			strDir[i]='\\';
		}
	}
	SetFileAttributes(szNewPath,FILE_ATTRIBUTE_NORMAL);
}
#endif
