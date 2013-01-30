#pragma once
#ifdef _MINICLIENT			//Ŀǰ�õ�ͬ�����ط�ʽ�� ��ʵ������д�� ûʲô���� ����ͬ����ʽ ���ȶ��� ���������߳������� ����Ӱ�쵽���߳�
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
	HINTERNET					m_hopen;		//InternetOpen ���
	HINTERNET					m_hfile;		//InternetOpen ���
	HANDLE						m_hEvent[3];	//
private:
	vector<DownLoadNode>		m_DownArray;	//�����������
	map<string,bool>			m_DownRecord;	//���ؼ�¼ ��¼�����ع�ʲô��Դ �����ظ�����
	SCritSect					m_Lock;			
	char						m_loadbuffer[LOADBUFFER];	//���� BUFFER  10K 
	string						m_ExePath;		//��¼ ��ϷEXE ·�� ������ ��Դ��·��

	MyDownLoadMgr(void){}
	DownLoadNode*				GetEmpeyNode();
	bool						GetHttpPath(string& filename, char(&path)[MAX_PATH]);  //ת�� �õ� HTTP��ַ IPд����
	bool						GetTempFilePath(string& filename, char(&path)[MAX_PATH]); //�õ� �����ļ�·�� �������ǰ ��չ��Ϊ .tmp �ļ�������ɺ� ��Ϊ��ȷ��չ��
	bool						StartDownLoad(string& filename);
	bool						WaitEvent();  //�첽ģʽ �õ��ĺ���
public:
	static MyDownLoadMgr&		Mgr();
	bool						Init();		//����������Դ���� ������ɺ� ��ʼ����
	bool*						AddDownLoad(const char* filename);	//����������� ��ӵ���������̷������ض���ͷ��
	void						Run();		//��m_DownArray ��ȡ���������� ����
	void						Destroy();
};

DWORD WINAPI	AsyncCallbackThread(LPVOID arg); //ʹ�õ�����һ���߳��������첽�ص�������΢����ĵ�������ô��
void WINAPI		CallBack(HINTERNET hInternet,DWORD dwContext,DWORD dwInternetStatus,LPVOID lpvStatusInformation,DWORD dwStatusInformationLength);
#endif