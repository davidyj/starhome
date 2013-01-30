#include "../stdafx.h"
#ifdef _MINICLIENT
#include "AsyncFileRead.h"
#include "../../RenderPerson/include/c_baseentity.h"
#include "../../RenderPerson/include/c_baseanimating.h"
#include "SLock.h"
#include "DynamicResMgr.h"


//////////////////////////////////////////////////////////////////////////
MyDownLoadMgr& MyDownLoadMgr::Mgr()
{
	static MyDownLoadMgr s_MyDownLoadMgr;
	return s_MyDownLoadMgr;
}

DownLoadNode* MyDownLoadMgr::GetEmpeyNode()
{
	size_t size = m_DownArray.size();
	for (size_t i = 0; i < size; ++i)
	{
		DownLoadNode& node = m_DownArray[i];
		if (!node.isUse)
		{
			return &node;
		}
	}
	return NULL;
}

void MyDownLoadMgr::Destroy()
{
	SetEvent(m_hEvent[2]);

}

bool MyDownLoadMgr::Init()
{
	//SThread::Create()
	for (int i = 0; i != 3; ++i)
	{
		m_hEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	m_hopen = InternetOpen("liangshan", INTERNET_OPEN_TYPE_PRECONFIG,NULL, NULL, NULL); //同步模式打开 INTERNET 连接
	if (m_hopen == NULL)
	{
		return false;
	}

	//CreateThread(NULL,0,AsyncCallbackThread,NULL,0,NULL);
	//WaitEvent();

	char exepath[MAX_PATH];
	memset(exepath,0x00,sizeof(exepath));
	HMODULE hmodule =  GetModuleHandle( NULL );
	GetModuleFileName( hmodule, exepath, sizeof(exepath) );		//为了得到 当前的 EXE路径 也许 SDK 有地方直接就能取到到值 我不知道 所以就这么做了
	int len = strlen(exepath);
	for (int i = 0; i < len; ++i)
	{
		if (exepath[i] == '\\')
			exepath[i] = '/';
	}
	m_ExePath = exepath;
	if (m_ExePath.length() > 0)
	{
		int index = m_ExePath.find_last_of('/',m_ExePath.length()-1);
		if (index > 0)
		{
			m_ExePath = m_ExePath.substr(0,index);
		}
	}
	return true;
}

bool* MyDownLoadMgr::AddDownLoad(const char* filename)
{
	if (m_DownRecord.find(filename) == m_DownRecord.end())
	{
		m_DownRecord[filename] = false;
		m_Lock.Enter();
		DownLoadNode* node = GetEmpeyNode();
		if (node == NULL)
		{
			DownLoadNode temp;
			temp.isUse = true;
			temp.filename = filename;
			m_DownArray.push_back(temp);
		}
		else
		{
			node->filename = filename;
			node->isUse = true;
		}
		m_Lock.Leave();
	}

	return &m_DownRecord[filename];
}
int test = 10;
void MyDownLoadMgr::Run()
{
	if (m_hopen != NULL)
	{
		size_t index = 0;
		while (true)
		{
			m_Lock.Enter();
			if (index < m_DownArray.size())
			{
				if (m_DownArray[index].isUse)
				{
					string filename = m_DownArray[index].filename;
					if (StartDownLoad(filename))
					{
						m_DownArray[index].Clear();
					}
				}
				++index;
			}
			else
				index = 0;
			m_Lock.Leave();
			Sleep(1);
		}
	}
}

bool MyDownLoadMgr::GetHttpPath(string& filename, char(&path)[MAX_PATH])
{
	int index = filename.find_first_of(m_ExePath,0);
	if (index >= 0)
	{
		string str = filename.substr(index + m_ExePath.length());
		str.insert(0,"http://172.16.3.49/liangshan");
		strcpy_s(path,str.c_str());
		return true;
	}
	return false;
}

bool MyDownLoadMgr::GetTempFilePath(string& filename, char(&path)[MAX_PATH])
{
	if (filename.length() > 0)
	{
		int index = filename.find_last_of('.',filename.length()-1);
		if (index >= 0)
		{
			string str = filename.substr(0,index);
			str += ".tmp";
			strcpy_s(path,str.c_str());
			return true;
		}
	}
	return false;
}

bool MyDownLoadMgr::WaitEvent()
{
	DWORD dwRet = WaitForMultipleObjects(3,m_hEvent,FALSE,INFINITE);  
	return WAIT_OBJECT_0 != dwRet;
}

bool MyDownLoadMgr::StartDownLoad(string& filename)
{
	char path[MAX_PATH];
	if (!GetHttpPath(filename,path))
	{
		return false;
	}
	m_hfile = InternetOpenUrl(m_hopen, path, NULL, NULL, INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD, 0); //直接连接 HTTP资源
	
	if (NULL == m_hfile)
	{
		return false;
		//if   (ERROR_IO_PENDING == GetLastError())   
		//{   
		//	if (WaitEvent()) //激活了 错误事件  
		//	{
		//		return false;
		//	}   
		//}   
		//else   
		//{
		//	return false;
		//}   
	}   


	DWORD dCode = 0;
	DWORD dwSize= sizeof(dCode);

	if(!HttpQueryInfo(m_hfile,HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER,&dCode,&dwSize,NULL)) //获取 HTTP 连接属性
	{
		InternetCloseHandle(m_hfile);
		return false;
	}

	if (dCode != 200)	//状态不为 OK	200代表 连接成功
	{
		InternetCloseHandle(m_hfile);
		return false;
	}
	memset(path,0x00,sizeof(path));
	if (!GetTempFilePath(filename,path))
	{
		InternetCloseHandle(m_hfile);
		return false;
	}

	FILE* file;
	if (fopen_s(&file,path,"wb") != 0)
	{
		InternetCloseHandle(m_hfile);
		return false;
	}
	
	//开始下载数据 每次 10K

	/*INTERNET_BUFFERS InetBuff;
	FillMemory(&InetBuff, sizeof(InetBuff), 0);
	InetBuff.dwStructSize = sizeof(InetBuff);
	InetBuff.lpvBuffer = m_loadbuffer;
	InetBuff.dwBufferLength = LOADBUFFER - 1;*/
	memset(m_loadbuffer,0x00, sizeof(m_loadbuffer));
	DWORD bread = 0;
	while (true)
	{
		if (InternetReadFile(m_hfile,(LPVOID)m_loadbuffer,LOADBUFFER-1,&bread))
		{
			if (bread == 0)
			{
				break;
			}
			else
			{
				fwrite(m_loadbuffer,bread,1,file);
				memset(m_loadbuffer,0x00, sizeof(m_loadbuffer));
			}
		}
		else
		{
			fclose(file);
			InternetCloseHandle(m_hfile);
			return false;
		}

		//	if (GetLastError() == ERROR_IO_PENDING)
		//	{
		//		if (WaitEvent()) //激活了 错误事件  
		//		{
		//			fclose(file);
		//			InternetCloseHandle(m_hfile);
		//			return false;
		//		}
		//	}
		//	else
		//	{
		//		fclose(file);
		//		InternetCloseHandle(m_hfile);
		//		return false;
		//	}
		//}
		//else
		//{
		//	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hEvent[2],0))   
		//	{
		//		fclose(file);
		//		InternetCloseHandle(m_hfile);
		//		return false;
		//	}
		//}

		//fwrite(m_loadbuffer,InetBuff.dwBufferLength,1,file);
		//m_loadbuffer[InetBuff.dwBufferLength] = 0;
		//if (InetBuff.dwBufferLength == 0)
		//	break;

		//Sleep(1);
	}

	fclose(file);

	InternetCloseHandle(m_hfile);
	rename(path,filename.c_str());
	m_DownRecord[filename] = true;
	return true;
}

void __stdcall CallBack	(HINTERNET hInternet, DWORD dwContext,
						 DWORD dwInternetStatus,
						 LPVOID lpvStatusInformation,
						 DWORD dwStatusInformationLength)
{

	switch (dwInternetStatus)
	{
	case INTERNET_STATUS_HANDLE_CREATED:    //句柄被创建
		{
			INTERNET_ASYNC_RESULT *pRes = (INTERNET_ASYNC_RESULT *)lpvStatusInformation;
			MyDownLoadMgr::Mgr().m_hfile = (HINTERNET)pRes->dwResult;
		}
		break;
	case INTERNET_STATUS_HANDLE_CLOSING:	//句柄被关闭
		//SetEvent(MyDownLoadMgr::Mgr().m_hEvent[1]);
		break;
	case INTERNET_STATUS_REQUEST_COMPLETE:
		{
			if (ERROR_SUCCESS == ((LPINTERNET_ASYNC_RESULT)(lpvStatusInformation))->dwError) //成功
			{
				SetEvent(MyDownLoadMgr::Mgr().m_hEvent[0]);
			}
			else
			{
				//出现错误
				DWORD error = GetLastError();
				SetEvent(MyDownLoadMgr::Mgr().m_hEvent[2]);
			}
		}
		break;
	}
}

DWORD WINAPI AsyncCallbackThread(LPVOID arg) //
{
	InternetSetStatusCallback(MyDownLoadMgr::Mgr().m_hopen,CallBack);  

	//通知子线程回调函数设置成功，子线程可以继续工作   
	SetEvent(MyDownLoadMgr::Mgr().m_hEvent[0]);
	WaitForSingleObject(MyDownLoadMgr::Mgr().m_hEvent[2],INFINITE);
	return 0;
}

#endif