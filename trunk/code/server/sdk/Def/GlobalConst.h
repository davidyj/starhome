/*
 * ���ļ�����DataServer����Ҫ��һЩϵͳ������������������ڵ������Ա��Ż�����
 * ���ͷ�ļ�������ͷ�ļ��ĺ����¶�����
 * ʹ�÷���:
 * 
 * 1 �������ͷ�ļ���ͷ�ļ��ѱ��ļ���Ϊ���һ��include�ļ�
 */

#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

////////////////////////Gamenetcommon/////////////////////////////////////////
//DataDefine.h
//#define BASE_BUFFER_MAX		512
//#define SEND_BUFFER_SIZE	(BASE_BUFFER_MAX)
//#define RECV_BUFFER_SIZE	(BASE_BUFFER_MAX*2)
//#define CHUNK_BUFFER_SIZE	(BASE_BUFFER_MAX*2)

//����ѹ��֮ǰ���ĳ���
//#define COMPRESSION_BUFFER_LEN (BASE_BUFFER_MAX*2)

//���128��PACKET_COMMAND����ѹ����һ��PACKET_COMMAND
#define COMPRESSION_BUFFER_MAX_PKT_CNT 100

#define PACKET_BUFFER_SIZE (1024-sizeof(int))

//�ַ�����Ϣ����С(base64����)������ = PACKET_BUFFER_SIZE*4/3 + ��ͷ���� + ���ɷָ��� + '\0'
#define PACKET_STRING_SIZE	2048		

//Chunk define
//const int CHUNK_COUNT_MAX	= 10240;
//PacketDefine.h
//#define MAX_PAYLOAD_LEN (PACKET_BUFFER_SIZE - PACKET_COMMAND::DATA_PARAM)
//#ifdef WIN32
//iocp�ڴ�صĲ���
//g_overlappedpool�ڴ�صĳ�ʼ�������
//#define OVERLAPED_INIT_COUNT 2000
//����
//#define OVERLAPED_INCRU_COUNT 2
//#define CONTEXT_INIT_COUNT 10
//#define CONTEXT_INCRU_COUNT 1
//#endif //WIN32
////////////////////////Gamenetcommon ends/////////////////////////////////////////

//CompressionBufferMgr.h
/*
 * ����ѹ��
 * ���룺���ɸ�PACKET_COMMAND���͵Ķ���
 * note:�����Ŀͻ���Ҫ��������Send()��������������
 */



#endif //CONST_H

