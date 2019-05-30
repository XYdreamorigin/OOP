#pragma once
#include <cstdio>
#include<string>
#include<winsock2.h>
#include<algorithm>
#include<iostream>
#include<Ws2tcpip.h>
#include<fstream>
#include<sstream>
#include<ios>
#include<vector>
#include <stdlib.h>
#include <time.h> 
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"pthreadVC2.lib")


using namespace std;
#define SIZE 255
/*�����˶���player���test_maker���˳��������
  ���������������֧�ָ�ֵ����operator=,
  ����ʵ��������֧�ֿ�������                 */


static SOCKET clientSocket;// = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

class user
{
protected://Ϊ���ܱ��������Ա�������ʵ�
	string name; //�����߻��߳������û���
	string passwords; //�����߻��߳���������

	int experience = 0; //�����߻��߳����߾���ֵ
	int level = 1; //�����߻��߳����ߵȼ�

public:
	string show_name() { return name; }           //Ϊ�˱������ݵİ�ȫ�Ե������ܹ��ü̳������鿴�û�����Ϣ���Խ�������Щ����
	int show_experience() { return experience; }
	int show_level() { return level; }
	string show_password() { return passwords; }

};
class player :public user
{
private:
	int rank = 0; //�������Ѿ������Ĺؿ���

protected:
	double play_start = 0, play_end = 0;   //��ʱ����ʼ�ͽ���
public:
	int show_rank() { return rank; }

	void sign_in();//������ע��
	void sign_up();//�����ߵ�½
	player();//���캯������ʼ��
	player(const player& a);  //�������캯����˳��������Լ���������class.h
	player(string in_name, string in_passwords, int in_experience, int in_level, int in_rank);//Ϊ�˶�ȡ�ļ�ʱֱ�Ӹ�ֵ����Ȼ�͵ý���һ��game�࣬������˷�
	player& operator=(const player& a);
	void upgrade(int play_level);
	//��ֵ���������

	//void upgrade(vector<player>::iterator it); //����������

	//bool comp_name(const player& a, const player& b); //�Զ���Ƚ��û����ĺ���
};

class test_maker :public user
{
private:
	int test_num = 0;//�����߳�����Ŀ
public:

	int show_test_num() { return test_num; }



	void sign_in();//������ע��
	void sign_up();//�����ߵ�¼
	test_maker();//���캯�� ��ʼ��
	test_maker(const test_maker& a); //�������캯����˳��������Լ���������class.h
	test_maker(string in_name, string in_passwords, int in_experience, int in_level, int in_test_num);//Ϊ�˶�ȡ�ļ�ʱֱ�Ӹ�ֵ����Ȼ�͵ý���һ��game�࣬������˷�
	test_maker& operator=(const test_maker& a);//��ֵ���������

	void upgrade(); //�������������

};

class game :public player, public test_maker
{

public:
	void show_sign();//��ʼע��
	void show_sign_in_type();//ע�����ʹ���
	void show_sign_up_type();//��¼���ʹ���
	void sign_in_success();//ע��ɹ�
	void sign_up_success();//��¼�ɹ�
	void wrong(); //�������
	void passwords_wrong();//�������

	void player_main_menu();//���������˵�ҳ��
	void show_player_search(); //�����߲�ѯҳ��
	void player_search(); //�����߲�ѯ
	void show_player_search_rank(); //���а�ҳ��
	void see_player_rank(); //�鿴���������а�

	void test_maker_main_menu(); //���������˵�ҳ��
	void show_test_maker_search(); //�����߲�ѯҳ��
	void test_maker_search(); //�����߲�ѯ
	void show_test_maker_search_rank(); //���а�ҳ��
	void see_test_maker_rank(); //�鿴���������а�


	void start_player_game(); //��ʼһ�������ߵ���Ϸ

	void start_test_maker_game();  //��ʼһ�������ߵ���Ϸ

	

};



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
	int operate=-1;   //����ʲô���͵���Ϣ
	char name[16]="";  //Ҫ���͵���Ϣ,����
	char passwords[16]=""; //����
	int experiences=0;
	int level=1;  //�ȼ�
	int rank_or_test_num=0; //�����ؿ������߳�����
	packet() 
	{
		name[15] = '\0';
		passwords[15] = '\0';
	}
	packet(int _operate, string _name, string  _passwords, int _experiences, int _level, int _rank_or_test_num)
	{
		operate = _operate;
		_name.copy(name,_name.length(),0);
		*(name + _name.length()) = '\0';

	    _passwords.copy(passwords,_passwords.length(),0);
		*(passwords + _passwords.length()) = '\0';

		experiences = _experiences;
		level = _level;
		rank_or_test_num = _rank_or_test_num;
	}
};

struct words
{
	int operate = 1; //��ʲô�������淢��
	int cur_level; //�ڼ��صĵ���
	char a_word[20]; //һ������
	words() {}
	
	words(int _operate, int _cur_level, string _a_word)
	{
		operate = _operate;
		cur_level = _cur_level;
		_a_word.copy(a_word, _a_word.length(), 0);
		*(a_word + _a_word.length()) = '\0';
	}
};

//����ȽϺ���Ϊ��֮���ܽ����������а���Ҫ���򣬶������ڵ���������
static bool comp_rank_or_test_num(packet a, packet b) { return a.rank_or_test_num > b.rank_or_test_num; }//�Զ���Ƚ��û�ͨ���ؿ��� ������ ����
static bool comp_experiences(packet a, packet b) { return a.experiences > b.experiences; } //�Զ��徭��ֵ�ȽϺ���  ������ ����
static bool comp_level(packet a, packet& b) { return a.level > b.level; } // �Զ���ȼ��ȽϺ���  ������ ����
/*Ϊʲô��static ? ���ӵĻ��ᱨ��˵sortĬ����������ȴ����������
ԭ���� ��Ա������һ������Ĭ����thisָ�룬 ����������������ʵ��3������
  ��static   ��̬������û��thisָ��   */





