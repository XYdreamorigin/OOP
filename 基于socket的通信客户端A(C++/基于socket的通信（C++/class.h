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
/*建立了对于player类和test_maker类的顺序容器，
  所以这两个类必须支持赋值操作operator=,
  对象实例还必须支持拷贝构造                 */


static SOCKET clientSocket;// = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

class user
{
protected://为了能被派生类成员函数访问到
	string name; //闯关者或者出题者用户名
	string passwords; //闯关者或者出题者密码

	int experience = 0; //闯关者或者出题者经验值
	int level = 1; //闯关者或者出题者等级

public:
	string show_name() { return name; }           //为了保护数据的安全性但是又能够让继承类对象查看用户的信息所以建立了这些函数
	int show_experience() { return experience; }
	int show_level() { return level; }
	string show_password() { return passwords; }

};
class player :public user
{
private:
	int rank = 0; //闯关者已经闯过的关卡数

protected:
	double play_start = 0, play_end = 0;   //计时器开始和结束
public:
	int show_rank() { return rank; }

	void sign_in();//闯关者注册
	void sign_up();//闯关者登陆
	player();//构造函数，初始化
	player(const player& a);  //拷贝构造函数，顺序容器的约束，详情见class.h
	player(string in_name, string in_passwords, int in_experience, int in_level, int in_rank);//为了读取文件时直接赋值，不然就得建立一个game类，造成了浪费
	player& operator=(const player& a);
	void upgrade(int play_level);
	//赋值运算符重载

	//void upgrade(vector<player>::iterator it); //闯关者升级

	//bool comp_name(const player& a, const player& b); //自定义比较用户名的函数
};

class test_maker :public user
{
private:
	int test_num = 0;//出题者出题数目
public:

	int show_test_num() { return test_num; }



	void sign_in();//出题者注册
	void sign_up();//出题者登录
	test_maker();//构造函数 初始化
	test_maker(const test_maker& a); //拷贝构造函数，顺序容器的约束，详情见class.h
	test_maker(string in_name, string in_passwords, int in_experience, int in_level, int in_test_num);//为了读取文件时直接赋值，不然就得建立一个game类，造成了浪费
	test_maker& operator=(const test_maker& a);//赋值运算符重载

	void upgrade(); //出题者玩家升级

};

class game :public player, public test_maker
{

public:
	void show_sign();//开始注册
	void show_sign_in_type();//注册类型窗口
	void show_sign_up_type();//登录类型窗口
	void sign_in_success();//注册成功
	void sign_up_success();//登录成功
	void wrong(); //输出错误
	void passwords_wrong();//密码错误

	void player_main_menu();//闯关者主菜单页面
	void show_player_search(); //闯关者查询页面
	void player_search(); //闯关者查询
	void show_player_search_rank(); //排行榜页面
	void see_player_rank(); //查看闯关者排行榜

	void test_maker_main_menu(); //出题者主菜单页面
	void show_test_maker_search(); //出题者查询页面
	void test_maker_search(); //出题者查询
	void show_test_maker_search_rank(); //排行榜页面
	void see_test_maker_rank(); //查看出题者排行榜


	void start_player_game(); //开始一个闯关者的游戏

	void start_test_maker_game();  //开始一个出题者的游戏

	

};



//事件标号  
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

struct packet  //给客户端发送的信息
{
	int operate=-1;   //发送什么类型的信息
	char name[16]="";  //要发送的信息,姓名
	char passwords[16]=""; //密码
	int experiences=0;
	int level=1;  //等级
	int rank_or_test_num=0; //闯过关卡数或者出题数
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
	int operate = 1; //在什么操作里面发送
	int cur_level; //第几关的单词
	char a_word[20]; //一个单词
	words() {}
	
	words(int _operate, int _cur_level, string _a_word)
	{
		operate = _operate;
		cur_level = _cur_level;
		_a_word.copy(a_word, _a_word.length(), 0);
		*(a_word + _a_word.length()) = '\0';
	}
};

//定义比较函数为了之后能进行排序，排行榜需要排序，对容器内的内容排序
static bool comp_rank_or_test_num(packet a, packet b) { return a.rank_or_test_num > b.rank_or_test_num; }//自定义比较用户通过关卡数 闯关者 降序
static bool comp_experiences(packet a, packet b) { return a.experiences > b.experiences; } //自定义经验值比较函数  闯关者 降序
static bool comp_level(packet a, packet& b) { return a.level > b.level; } // 自定义等级比较函数  闯关者 降序
/*为什么加static ? 不加的话会报错说sort默认两个参数却给了三个。
原因是 成员函数第一个参数默认是this指针， 所以这两个函数其实是3个参数
  加static   静态函数就没有this指针   */





