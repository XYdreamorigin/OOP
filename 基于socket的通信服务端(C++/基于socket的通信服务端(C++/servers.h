#pragma once
#include<iostream>
#include <WinSock2.h>
#include<fstream>
#include<sstream>
#include<ios>
#include<vector>
#include<cstring>
#include <algorithm>
#include <pthread.h>
#pragma comment(lib,"ws2_32.lib")   //��̬����һ��lib�ļ�
#pragma comment(lib,"pthreadVC2.lib")
using namespace std;
#define SIZE  255
#define NUM_THREADS 2
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

struct user
{
	int choice=0;
	char name[16]="";
	char passwords[16]="";
	int experiences=0;
	int level=1;
	int rank_or_test_num=0;
	user()
	{
		name[15] = '\0';
		passwords[15] = '\0';
	}
	user(string _name,string _passwords,int _experiences,int _level,int _rank_or_test_num)
	{
		_name.copy(name, _name.length(), 0);
		*(name + _name.length()) = '\0';
	    _passwords.copy(passwords, _passwords.length(), 0);
		*(passwords + _passwords.length()) = '\0';
		experiences = _experiences;
		level = _level;
		rank_or_test_num = _rank_or_test_num;
	}
};

struct words
{
	int operate; //��ʲô�������淢��
	int cur_level; //�ڼ��صĵ���
	char a_word[20]; //һ������
	words(){}
	words(int _operate, int _cur_level, string _a_word)
	{
		operate = _operate;
		cur_level = _cur_level;
		_a_word.copy(a_word, _a_word.length(), 0);
		*(a_word + _a_word.length()) = '\0';
	}
};


vector<user> all_player; //���д�����
vector<user>all_online_player;  //�������ߵĴ�����
vector<user> all_test_maker;//���г�����
vector<user> all_online_test_maker; //�������ߵĳ�����
vector<user>::iterator cur_player;//��ǰ�Ĵ�����
vector<user>::iterator cur_test_maker; //��ǰ������
vector<string> all_words; //�������

