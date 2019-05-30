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
	//加载套接字库，创建套接字
	WORD sockVerson = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVerson, &wsaData) != 0)
		return 0;

	//建立客户端socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("套接字创建失败");
		WSACleanup();
		return 0;
	}


	//向服务器发出连接请求
	//定义要连接的服务器地址

	sockaddr_in addrConServer;
	addrConServer.sin_family = AF_INET;
	addrConServer.sin_port = htons(8888);
	addrConServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(clientSocket, (SOCKADDR*)& addrConServer, sizeof(addrConServer)) == SOCKET_ERROR)
	{
		printf("客户端建立连接失败！\n");
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	else
		printf("客户端建立连接成功，准备发送数据！\n");


	//int connect(SOCKET s, const struct sockaddr * name, int namelen);

	//本函数用于创建与指定外部端口的连接，对于流类套接口（SOCK_STREAM类型），

	//利用名字来与一个远程主机建立连接，一旦套接口调用成功返回，它就能收发数据了。

	//对于数据报类套接口（SOCK_DGRAM类型），则设置成一个缺省的目的地址，并用它来进行后续的send()与recv()调用。



	//与服务器之间进行数据传输
	//发送数据

	char* sendBuf = new char[100];


	int sendRes = send(clientSocket, sendBuf, (int)strlen(sendBuf), 0);
	if (sendRes == SOCKET_ERROR)
	{
		printf("客户端send()出现错误 : %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	else
		printf("客户端发送数据成功!\n");

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
	//接收服务端数据
	//通过建立的连接进行通信
	/*int res;
	do
	{
		char revSerData[100] = "";
		res = recv(clientSocket, revSerData, sizeof(revSerData), 0);
		if (res > 0)
		{
			printf("收到数据大小: %d\n", res);
			printf("服务器发送的数据: %s\n", revSerData);
		}
		else if (res == 0)
			printf("断开连接\n");
		else
			printf("接受失败: %d\n", WSAGetLastError());
	} while (res > 0);*/
	packet recv_a;
	char recv_buf[SIZE] = "";
	memset(recv_buf, 'z', SIZE);//清空缓存
	res = recv(clientSocket, recv_buf, strlen(recv_buf), 0);//读取数据
	memset(&recv_a, 0, sizeof(recv_a));//清空结构体
	memcpy(&recv_a, recv_buf, sizeof(recv_a));//把接收到的信息转换成结构体
	cout << recv_buf << "   " << recv_a.num << endl;

	packet send_a;
	for (int i = 0; i < 15; i++)
		send_a.name[i] = 98 + i;
	send_a.num = 15;

	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &send_a, sizeof(send_a)); //结构体转换成字符串
	//send_buf[SIZE] = ' ';
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息
	cout << send_buf << "+++++++++++" << endl;
	
	//关闭套接字，关闭加载的套接字库
	closesocket(clientSocket);
	WSACleanup();

}

