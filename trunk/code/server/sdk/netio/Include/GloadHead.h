#pragma once 

#include "stdafx.h"
#include "utllinkedlist.h"

//00000000 0000 0001 0000000000000000 �û���id
#define USERIDTYPE 65536
//00000000 0000 0000 1111111111111111 
#define USERID 65535

//00000000 0000 1111 0000000000000000
#define GETLOGIN 983040

//00000000 1111 0000 0000000000000000 ������������id
#define GETSCENE 15728640

// �õ�Ԥ���ĵ�½��������ֵ
#define SETLOGININDEX( nn )		nn << 16
// �õ�Ԥ���ĳ���������
#define SETSCENEINDEX( nn )		nn << 24


#define SOCKETMAX		10						// conser����socket���������ֵ

#define PACKCOUNTMAX	8193
#define PACKINDEXMAX	3000					// ����������������ݵ�����
#define NET_BUFFER_SIZE	409600

#define MAXSERVERCOUNTS 500					//�¼��������������
#define IP_SIZE			50					//ip�ַ�������
#define INVALID_NUM		-1					// ��Ч��ֵ


typedef CUtlLinkedList<SOCKET,int>	SOCKETLIST;





