#include"client.h"

#define SIZE 100
typedef struct
{
	char name[15];
	char pass = 'g';
	int num;
}packet;

int main()
{
	//�����׽��ֿ⣬�����׽���
	WORD sockVerson = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVerson, &wsaData) != 0)
		return 0;

	//�����ͻ���socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("�׽��ִ���ʧ��");
		WSACleanup();
		return 0;
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
		return 0;
	}
	else
		printf("�ͻ��˽������ӳɹ���׼���������ݣ�\n");


	//int connect(SOCKET s, const struct sockaddr * name, int namelen);

	//���������ڴ�����ָ���ⲿ�˿ڵ����ӣ����������׽ӿڣ�SOCK_STREAM���ͣ���

	//������������һ��Զ�������������ӣ�һ���׽ӿڵ��óɹ����أ��������շ������ˡ�

	//�������ݱ����׽ӿڣ�SOCK_DGRAM���ͣ��������ó�һ��ȱʡ��Ŀ�ĵ�ַ�������������к�����send()��recv()���á�



	//�������֮��������ݴ���
	//��������

	char* sendBuf = new char[100];


	int sendRes = send(clientSocket, sendBuf, (int)strlen(sendBuf), 0);
	if (sendRes == SOCKET_ERROR)
	{
		printf("�ͻ���send()���ִ��� : %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	else
		printf("�ͻ��˷������ݳɹ�!\n");

	cout << "sadasdasd";
	char revSerData[100] = "";
	int res = recv(clientSocket, revSerData, sizeof(revSerData), 0);

	cout << "**************";
	char sends[100] = "12212122";
	send(clientSocket, sends, (int)strlen(sendBuf), 0);

	char revSerDatas[100] = "";
	res = recv(clientSocket, revSerDatas, sizeof(revSerData), 0);



	cout << "**************";
	char sendss[100] = "------";
	send(clientSocket, sendss, (int)strlen(sendBuf), 0);
	//���շ��������
	//ͨ�����������ӽ���ͨ��
	/*int res;
	do
	{
		char revSerData[100] = "";
		res = recv(clientSocket, revSerData, sizeof(revSerData), 0);
		if (res > 0)
		{
			printf("�յ����ݴ�С: %d\n", res);
			printf("���������͵�����: %s\n", revSerData);
		}
		else if (res == 0)
			printf("�Ͽ�����\n");
		else
			printf("����ʧ��: %d\n", WSAGetLastError());
	} while (res > 0);*/
	packet recv_a;
	char recv_buf[SIZE] = "";
	memset(recv_buf, 'z', SIZE);//��ջ���
	res = recv(clientSocket, recv_buf, strlen(recv_buf), 0);//��ȡ����
	memset(&recv_a, 0, sizeof(recv_a));//��սṹ��
	memcpy(&recv_a, recv_buf, sizeof(recv_a));//�ѽ��յ�����Ϣת���ɽṹ��
	cout << recv_buf << "   " << recv_a.num << endl;

	packet send_a;
	for (int i = 0; i < 15; i++)
		send_a.name[i] = 98 + i;
	send_a.num = 15;

	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &send_a, sizeof(send_a)); //�ṹ��ת�����ַ���
	//send_buf[SIZE] = ' ';
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
	cout << send_buf << "+++++++++++" << endl;
	
	//�ر��׽��֣��رռ��ص��׽��ֿ�
	closesocket(clientSocket);
	WSACleanup();

}

