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

	SOCKET* revSocket = (SOCKET*)lpParameter;  //对应此时所建立连接的套接字的句柄

	//等待客户端请求，服务器接收请求


	char revData[255] = "";
	char* sendData = new char[100];

	//通过建立的连接进行通信
	int res = recv(*revSocket, revData, 255, 0);
	if (res > 0)
	{
		printf("收到数据大小: %d\n", res);
		printf("客户端发送的数据: %s\n", revData);
	}
	else if (res == 0)
		printf("断开连接\n");
	else
		printf("接受失败: %d\n", WSAGetLastError());

	//int recv( SOCKET s,     char FAR *buf,      int len,     int flags     ); 

	//不论是客户还是服务器应用程序都用recv函数从TCP连接的另一端接收数据，根据返回值判断数据接收情况。

	//s指定接收端套接字描述符；

	//buf指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；

	//len指明buf的长度；

	//flags一般为0；
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
			printf("服务器停止发送数据！\n");
			break;
		}
		//发送数据
		send(*revSocket, sendData, strlen(sendData), 0);
	}*/
	//int send( SOCKET s,  const char FAR *buf,  int len,   int flags ); 
	//含义基本同recv()函数。

	//关闭套接字，关闭加载的套接字库
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
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &send_a, sizeof(send_a)); //结构体转换成字符串
	//send_buf[SIZE] = ' ';
	send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
	cout << send_buf << "+++++++++++" << endl;


	packet recv_a;
	char recv_buf[SIZE]="";
	memset(recv_buf, 'z', SIZE);//清空缓存
	res = recv(*revSocket, recv_buf, strlen(recv_buf), 0);//读取数据
	
	cout << recv_buf << "  666 "  << endl;
	memset(&recv_a, 0, sizeof(recv_a));//清空结构体
	memcpy(&recv_a, recv_buf, sizeof(recv_a));//把接收到的信息转换成结构体
	cout << *recv_buf << "  666 " << recv_a.num << endl;
	return 0;
}

int main()
{

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //WSAStartup返回0表示设置初始化成功
		return 0;

	//创建套接字
	//AF_INET表示IPv4，SOCK_STREAM数据传输方式，IPPROTO_TCP传输协议;
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("套接字创建失败");
		WSACleanup();
		return 0;
	}
	//1）WORD是微软SDK中的无符号16位整形数;WSADATA是一个结构体；

	//（2）MAKEWORD(a,b)是一个宏，这里用来指定使用的Winsock版本；

	//（3）WSAStartup，即WSA(Windows Sockets Asynchronous，Windows异步套接字)的启动命令；

	//	 WSAStartup必须是应用程序或DLL调用的第一个Windows Sockets函数。

	//     它允许应用程序或DLL指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节。

	//	应用程序或DLL只能在一次成功的WSAStartup()调用之后才能调用进一步的Windows Sockets API函数。

//	(4）函数socket()，socket()函数用于根据指定的地址族、数据类型和协议来分配一个套接口的描述字及其所用的资源；

	//	若无错误发生，socket()返回引用新套接口的描述字。否则的话，返回INVALID_SOCKET错误。



	//绑定IP和端口

		//配置监听地址和端口
	sockaddr_in addrListen;
	addrListen.sin_family = AF_INET;     //指定IP格式
	addrListen.sin_port = htons(8888);   //绑定端口号
	addrListen.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  //表示任何IP   service.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(listenSocket, (SOCKADDR*)& addrListen, sizeof(addrListen)) == SOCKET_ERROR)  //(SOCKADDR*)
	{
		printf("绑定失败");
		closesocket(listenSocket);
		return 0 ;
	}
	//（1）sockaddr_in是一个数据结构；用做bind、connect、recvfrom、sendto等函数的参数，指明地址信息。

	//  （2）bind()函数int bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);

	//		bind()函数通过给一个套接字接口分配一个地址来建立捆绑。！



	//开始监听

	if (listen(listenSocket, 5) == SOCKET_ERROR)
	{
		printf("监听出错");
		closesocket(listenSocket);
		return 0;
	}
	//int listen( int sockfd, int backlog);

	//sockfd：用于标识一个已捆绑未连接套接口的描述字。

	//backlog：等待连接队列的最大长度。


	//等待连接，连接后建立一个新的套接字
	printf("等待连接...\n");

	while (1)
	{


		SOCKET* revSocket = new SOCKET;  //对应此时所建立连接的套接字的句柄
		revSocket = (SOCKET*)malloc(sizeof(SOCKET));
		sockaddr_in remoteAddr;   //接收连接到服务器上的地址信息
		int remoteAddrLen = sizeof(remoteAddr);
		*revSocket = accept(listenSocket, (SOCKADDR*)& remoteAddr, &remoteAddrLen);  //等待客户端接入，直到有客户端连接上来为止
		if (*revSocket == INVALID_SOCKET)
		{
			printf("客户端发出请求，服务器接收请求失败：%d \n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 0;
		}
		else
		{
			printf("客服端与服务器建立连接成功： \n");//, inet_ntoa(remoteAddr.sin_addr));
		}

		//1）首先定义一个新的套接字，注意该套接字是与之前的不同，数据传输时，使用本套接字。

		//（2）SOCKET accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

		//    函数从等待连接队列中抽取第一个连接，创建一个同类的新的套接口并返回句柄;

		//    sockfd：套接字描述符，该套接口在listen()后监听连接；

		//    addr：（可选）指针，指向一缓冲区，其中接收为通讯层所知的连接实体的地址。Addr参数的实际格式由套接口创建时所产生的地址族确定。

		 //   addrlen：（可选）指针，输入参数，配合addr一起使用，指向存有addr地址长度的整型数。

		//int ret = pthread_create(&tids[time++], NULL, servers, NULL);
		CreateThread(NULL, 0, &ServerThread, revSocket, 0, NULL);
	}

	closesocket(listenSocket);

	WSACleanup();

	return 0;
}

