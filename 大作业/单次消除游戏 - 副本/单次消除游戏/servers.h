#pragma once
#include<iostream>
#include <WinSock2.h>
#include<WS2tcpip.h>
#include <pthread.h>
#pragma comment(lib,"ws2_32.lib")   //��̬����һ��lib�ļ�
#pragma comment(lib,"pthreadVC2.lib")
using namespace std;
#define NUM_THREADS 2
#define _WINSOCK_DEPRECATED_NO_WARNINGS 0
