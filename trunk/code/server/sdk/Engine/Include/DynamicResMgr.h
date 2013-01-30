#pragma once
#ifdef _MINICLIENT			//目前用的同步下载方式， 其实这样的写法 没什么问题 而且同步方式 简单稳定。 反正下载线程是另开的 不会影响到主线程
#include "EngineDefine.h"

#define LOADBUFFER	10240

struct DownLoadNode
{
	bool	isUse;
	string  filename;

	DownLoadNode()
	{
		Clear();
	}

	void Clear()
	{
		isUse = false;
		filename.clear();
	}
};

class C_BaseAnimating;
class ENGINE_CLASS MyDownLoadMgr
{
public:
	HINTERNET					m_hopen;		//InternetOpen 句柄
	HINTERNET					m_hfile;		//InternetOpen 句柄
	HANDLE						m_hEvent[3];	//
private:
	vector<DownLoadNode>		m_DownArray;	//下载任务队列
	map<string,bool>			m_DownRecord;	//下载记录 记录我下载过什么资源 避免重复下载
	SCritSect					m_Lock;			
	char						m_loadbuffer[LOADBUFFER];	//下载 BUFFER  10K 
	string						m_ExePath;		//记录 游戏EXE 路径 用来算 资源的路径

	MyDownLoadMgr(void){}
	DownLoadNode*				GetEmpeyNode();
	bool						GetHttpPath(string& filename, char(&path)[MAX_PATH]);  //转换 得到 HTTP地址 IP写死了
	bool						GetTempFilePath(string& filename, char(&path)[MAX_PATH]); //得到 保存文件路径 下载完成前 扩展名为 .tmp 文件下载完成后 改为正确扩展名
	bool						StartDownLoad(string& filename);
	bool						WaitEvent();  //异步模式 用到的函数
public:
	static MyDownLoadMgr&		Mgr();
	bool						Init();		//加载下载资源队列 加载完成后 开始下载
	bool*						AddDownLoad(const char* filename);	//添加下载任务 添加的任务会立刻放在下载队列头部
	void						Run();		//从m_DownArray 里取出下载任务 下载
	void						Destroy();
};

DWORD WINAPI	AsyncCallbackThread(LPVOID arg); //使用单独的一个线程来设置异步回调函数，微软的文档建议这么做
void WINAPI		CallBack(HINTERNET hInternet,DWORD dwContext,DWORD dwInternetStatus,LPVOID lpvStatusInformation,DWORD dwStatusInformationLength);
#endif