/*#pragma once
#include<winsock2.h>
#include<iostream>
#include<string>
#include<Ws2tcpip.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

#define PACKET_SIZE  100
//�¼����  
#define SIGN_IN_FOR_PLAYER 1
#define SIGN_IN_FOR_TEST_MAKER 2

#define SIGN_UP_FOR_PLAYER 3
#define SIGN_UP_FOR_TEST_MAKER 4

#define SEARCH_PLAYER_NAME 5
#define SEARCH_PLAYER_LEVEL 6
#define SEARCH_PLAYER_RANK 7
#define SEARCH_PLAYER_EXPERIENCES 8

#define SEARCH_TEST_MAKER_NAME 9
#define SEARCH_TEST_MAKER_LEVEL 10
#define SEARCH_TEST_MAKER_TEST_NUM 11
#define SEARCH_TEST_MAKER_EXPERIENCES 12

#define RANK_FOR_PLAYER 13
#define RANK_FOR_TEST_MAKER 14

#define WATCH_ONLINE_PLAYER 15
#define WATCH_ONLINE_TEST_MAKER 16

#define PLAYER_LOG_OUT 17
#define TEST_MAKER_LOG_OUT 18

#define START_PLAYER_GAME 0
#define ADD_NEW_WORDS 1

struct packet  //���ͻ��˷��͵���Ϣ
{
	int operate;   //����ʲô���͵���Ϣ
	string name;  //Ҫ���͵���Ϣ,����
	string passwords; //����
	int experiences;
	int level;  //�ȼ�
	int rank_or_test_num; //�����ؿ������߳�����
	packet(){}
	packet(int _operate,string _name, string _passwords, int _experiences, int _level, int _rank_or_test_num)
	{
		operate = _operate;
		name = _name;
		passwords = _passwords;
		experiences = _experiences;
		level = _level;
		rank_or_test_num = _rank_or_test_num;
	}
};

struct words
{
	int operate=1; //��ʲô�������淢��
	int cur_level; //�ڼ��صĵ���
	string a_word; //һ������
	words() {}
	words(int _operate, int _cur_level, string _a_word)
	{
		operate = _operate;
		cur_level = _cur_level;
		a_word = _a_word;
	}
};*/