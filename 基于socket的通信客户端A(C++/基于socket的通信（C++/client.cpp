//#include"client.h"
/*
#include"vector.h"



void client()
{
	//�����׽��ֿ⣬�����׽���
	WORD sockVerson = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVerson, &wsaData) != 0)
		return ;

	//�����ͻ���socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("�׽��ִ���ʧ��");
		WSACleanup();
		return ;
	}


	//�������������������
	//����Ҫ���ӵķ�������ַ

	sockaddr_in addrConServer;
	addrConServer.sin_family = AF_INET;
	addrConServer.sin_port = htons(8888);
	addrConServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(clientSocket, (SOCKADDR*)& addrConServer, sizeof(addrConServer)) == SOCKET_ERROR)
	{
		printf("�ͻ��˽�������ʧ�ܣ�\n");
		closesocket(clientSocket);
		WSACleanup();
		return ;
	}
	else
		printf("�ͻ��˽������ӳɹ���׼���������ݣ�\n");


	//int connect(SOCKET s, const struct sockaddr * name, int namelen);

	//���������ڴ�����ָ���ⲿ�˿ڵ����ӣ����������׽ӿڣ�SOCK_STREAM���ͣ���

	//������������һ��Զ�������������ӣ�һ���׽ӿڵ��óɹ����أ��������շ������ˡ�

	//�������ݱ����׽ӿڣ�SOCK_DGRAM���ͣ��������ó�һ��ȱʡ��Ŀ�ĵ�ַ�������������к�����send()��recv()���á�



	//�������֮��������ݴ���
	//��������
	/*
	char* sendBuf = new char[100];
	
	
	int sendRes = send(clientSocket, sendBuf, (int)strlen(sendBuf), 0);
	if (sendRes == SOCKET_ERROR)
	{
		printf("�ͻ���send()���ִ��� : %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return ;
	}
	else
		printf("�ͻ��˷������ݳɹ�!\n");
	
	 
	//�ر��׽��֣��رռ��ص��׽��ֿ�
	closesocket(clientSocket);
	WSACleanup();
	return;
}

*/