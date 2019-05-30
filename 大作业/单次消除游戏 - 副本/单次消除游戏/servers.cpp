#include"servers.h"
#include <string.h> 

#define SIZE 100
typedef struct
{
	char name[15];
	char pass = 'c';
	int num;
}packet;


DWORD WINAPI ServerThread(LPVOID lpParameter)
{

	SOCKET* revSocket = (SOCKET*)lpParameter;  //��Ӧ��ʱ���������ӵ��׽��ֵľ��

	//�ȴ��ͻ������󣬷�������������


	char revData[255] = "";
	char* sendData = new char[100];

	//ͨ�����������ӽ���ͨ��
	int res = recv(*revSocket, revData, 255, 0);
	if (res > 0)
	{
		printf("�յ����ݴ�С: %d\n", res);
		printf("�ͻ��˷��͵�����: %s\n", revData);
	}
	else if (res == 0)
		printf("�Ͽ�����\n");
	else
		printf("����ʧ��: %d\n", WSAGetLastError());

	//int recv( SOCKET s,     char FAR *buf,      int len,     int flags     ); 

	//�����ǿͻ����Ƿ�����Ӧ�ó�����recv������TCP���ӵ���һ�˽������ݣ����ݷ���ֵ�ж����ݽ��������

	//sָ�����ն��׽�����������

	//bufָ��һ�����������û������������recv�������յ������ݣ�

	//lenָ��buf�ĳ��ȣ�

	//flagsһ��Ϊ0��
	cin >> sendData;
	getchar();
	send(*revSocket, sendData, strlen(sendData), 0);
	cout << "------------" << endl;
	/*
	while (cin >> sendData)
	{
		//cout << strlen(sendData) << endl;
		if (strcmp(sendData, "q") == 0)
		{
			printf("������ֹͣ�������ݣ�\n");
			break;
		}
		//��������
		send(*revSocket, sendData, strlen(sendData), 0);
	}*/
	//int send( SOCKET s,  const char FAR *buf,  int len,   int flags ); 
	//�������ͬrecv()������

	//�ر��׽��֣��رռ��ص��׽��ֿ�
	char revSerData[100] = "";
	int rest = recv(*revSocket, revSerData, sizeof(revSerData), 0);
	cout << revSerData;

	cin >> sendData;
	getchar();
	send(*revSocket, sendData, strlen(sendData), 0);
	cout << "------------" << endl;

	rest = recv(*revSocket, revSerData, sizeof(revSerData), 0);
	cout << revSerData;



	packet send_a;
	for (int i = 0; i < 15; i++)
		send_a.name[i] = 96 + i;
	send_a.num = 15;

	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &send_a, sizeof(send_a)); //�ṹ��ת�����ַ���
	//send_buf[SIZE] = ' ';
	send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
	cout << send_buf << "+++++++++++" << endl;


	packet recv_a;
	char recv_buf[SIZE]="";
	memset(recv_buf, 'z', SIZE);//��ջ���
	res = recv(*revSocket, recv_buf, strlen(recv_buf), 0);//��ȡ����
	
	cout << recv_buf << "  666 "  << endl;
	memset(&recv_a, 0, sizeof(recv_a));//��սṹ��
	memcpy(&recv_a, recv_buf, sizeof(recv_a));//�ѽ��յ�����Ϣת���ɽṹ��
	cout << *recv_buf << "  666 " << recv_a.num << endl;
	return 0;
}

int main()
{

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //WSAStartup����0��ʾ���ó�ʼ���ɹ�
		return 0;

	//�����׽���
	//AF_INET��ʾIPv4��SOCK_STREAM���ݴ��䷽ʽ��IPPROTO_TCP����Э��;
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("�׽��ִ���ʧ��");
		WSACleanup();
		return 0;
	}
	//1��WORD��΢��SDK�е��޷���16λ������;WSADATA��һ���ṹ�壻

	//��2��MAKEWORD(a,b)��һ���꣬��������ָ��ʹ�õ�Winsock�汾��

	//��3��WSAStartup����WSA(Windows Sockets Asynchronous��Windows�첽�׽���)���������

	//	 WSAStartup������Ӧ�ó����DLL���õĵ�һ��Windows Sockets������

	//     ������Ӧ�ó����DLLָ��Windows Sockets API�İ汾�ż�����ض�Windows Socketsʵ�ֵ�ϸ�ڡ�

	//	Ӧ�ó����DLLֻ����һ�γɹ���WSAStartup()����֮����ܵ��ý�һ����Windows Sockets API������

//	(4������socket()��socket()�������ڸ���ָ���ĵ�ַ�塢�������ͺ�Э��������һ���׽ӿڵ������ּ������õ���Դ��

	//	���޴�������socket()�����������׽ӿڵ������֡�����Ļ�������INVALID_SOCKET����



	//��IP�Ͷ˿�

		//���ü�����ַ�Ͷ˿�
	sockaddr_in addrListen;
	addrListen.sin_family = AF_INET;     //ָ��IP��ʽ
	addrListen.sin_port = htons(8888);   //�󶨶˿ں�
	addrListen.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  //��ʾ�κ�IP   service.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(listenSocket, (SOCKADDR*)& addrListen, sizeof(addrListen)) == SOCKET_ERROR)  //(SOCKADDR*)
	{
		printf("��ʧ��");
		closesocket(listenSocket);
		return 0 ;
	}
	//��1��sockaddr_in��һ�����ݽṹ������bind��connect��recvfrom��sendto�Ⱥ����Ĳ�����ָ����ַ��Ϣ��

	//  ��2��bind()����int bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);

	//		bind()����ͨ����һ���׽��ֽӿڷ���һ����ַ���������󡣣�



	//��ʼ����

	if (listen(listenSocket, 5) == SOCKET_ERROR)
	{
		printf("��������");
		closesocket(listenSocket);
		return 0;
	}
	//int listen( int sockfd, int backlog);

	//sockfd�����ڱ�ʶһ��������δ�����׽ӿڵ������֡�

	//backlog���ȴ����Ӷ��е���󳤶ȡ�


	//�ȴ����ӣ����Ӻ���һ���µ��׽���
	printf("�ȴ�����...\n");

	while (1)
	{


		SOCKET* revSocket = new SOCKET;  //��Ӧ��ʱ���������ӵ��׽��ֵľ��
		revSocket = (SOCKET*)malloc(sizeof(SOCKET));
		sockaddr_in remoteAddr;   //�������ӵ��������ϵĵ�ַ��Ϣ
		int remoteAddrLen = sizeof(remoteAddr);
		*revSocket = accept(listenSocket, (SOCKADDR*)& remoteAddr, &remoteAddrLen);  //�ȴ��ͻ��˽��룬ֱ���пͻ�����������Ϊֹ
		if (*revSocket == INVALID_SOCKET)
		{
			printf("�ͻ��˷������󣬷�������������ʧ�ܣ�%d \n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 0;
		}
		else
		{
			printf("�ͷ�����������������ӳɹ��� \n");//, inet_ntoa(remoteAddr.sin_addr));
		}

		//1�����ȶ���һ���µ��׽��֣�ע����׽�������֮ǰ�Ĳ�ͬ�����ݴ���ʱ��ʹ�ñ��׽��֡�

		//��2��SOCKET accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

		//    �����ӵȴ����Ӷ����г�ȡ��һ�����ӣ�����һ��ͬ����µ��׽ӿڲ����ؾ��;

		//    sockfd���׽��������������׽ӿ���listen()��������ӣ�

		//    addr������ѡ��ָ�룬ָ��һ�����������н���ΪͨѶ����֪������ʵ��ĵ�ַ��Addr������ʵ�ʸ�ʽ���׽ӿڴ���ʱ�������ĵ�ַ��ȷ����

		 //   addrlen������ѡ��ָ�룬������������addrһ��ʹ�ã�ָ�����addr��ַ���ȵ���������

		//int ret = pthread_create(&tids[time++], NULL, servers, NULL);
		CreateThread(NULL, 0, &ServerThread, revSocket, 0, NULL);
	}

	closesocket(listenSocket);

	WSACleanup();

	return 0;
}

