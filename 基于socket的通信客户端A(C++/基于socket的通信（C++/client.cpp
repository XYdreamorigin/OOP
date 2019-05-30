//#include"client.h"
/*
#include"vector.h"



void client()
{
	//加载套接字库，创建套接字
	WORD sockVerson = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVerson, &wsaData) != 0)
		return ;

	//建立客户端socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("套接字创建失败");
		WSACleanup();
		return ;
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
		return ;
	}
	else
		printf("客户端建立连接成功，准备发送数据！\n");


	//int connect(SOCKET s, const struct sockaddr * name, int namelen);

	//本函数用于创建与指定外部端口的连接，对于流类套接口（SOCK_STREAM类型），

	//利用名字来与一个远程主机建立连接，一旦套接口调用成功返回，它就能收发数据了。

	//对于数据报类套接口（SOCK_DGRAM类型），则设置成一个缺省的目的地址，并用它来进行后续的send()与recv()调用。



	//与服务器之间进行数据传输
	//发送数据
	/*
	char* sendBuf = new char[100];
	
	
	int sendRes = send(clientSocket, sendBuf, (int)strlen(sendBuf), 0);
	if (sendRes == SOCKET_ERROR)
	{
		printf("客户端send()出现错误 : %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return ;
	}
	else
		printf("客户端发送数据成功!\n");
	
	 
	//关闭套接字，关闭加载的套接字库
	closesocket(clientSocket);
	WSACleanup();
	return;
}

*/