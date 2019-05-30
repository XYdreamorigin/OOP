#pragma once
#include"vector.h"
#include<fstream>
#include<sstream>
#include<ios>
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <time.h> 
#include<windows.h>
#include<algorithm>
#include<ctime>   //计时器需要的库
extern int choice;
using namespace std;









#include<windows.h>
#define    WIN32_LEAN_AND_MEAN

using std::vector;
#define false 0
#define true 1

int choice = 0;    //一个全局的来显示用户输入的选择



vector<packet> all_player; //所有闯关者
vector<string>all_online_player;  //所有在线的闯关者
vector<string> all_online_test_maker; //所有在线的出题者
vector<packet> all_test_maker;//所有出题者
player cur_player;//当前的闯关者
test_maker cur_test_maker; //当前出题者
vector<string> all_words; //单词题库



int main()
{
	SetConsoleTitle(L"单次消除游戏"); // 设置窗口标题

	//加载套接字库，创建套接字
	WORD sockVerson = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVerson, &wsaData) != 0)
		return 0;

	//建立客户端socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	game word_match;//开始一个游戏
part: // 注册登录界面
	choice = 0;
	int choice1; //注册或者登录的选择
	word_match.show_sign();//输出框口，详情见game.cpp

	cin >> choice1;
	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		word_match.wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		word_match.show_sign();//输出框口，详情见game.cpp
		cin >> choice1;
	}
	if (choice1 == 1)//注册
	{
		//part1:  //注册界面
		int choice1_1;//注册类型的选择
		//system("cls");
		word_match.show_sign_in_type();//输出框口，详情见game.cp p
		//SetPosition(50, 20);
		cin >> choice1_1;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			word_match.wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			word_match.show_sign_in_type();//输出框口，详情见game.cp p
			cin >> choice1_1;
		}
		if (choice1_1 == 1 || choice1_1 == 2)
		{
			char which = 'a';
			send(clientSocket, &which, 1, 0);//发送信息
		}

		if (choice1_1 == 1)  //注册闯关者
		{
			player new_player;// 建立一个新的闯关者
			new_player.sign_in();//闯关者注册


			word_match.sign_in_success();//注册成功输出框口，详情见game.cpp
			/*
			char which =  'a' ;
			send(clientSocket, &which, 1, 0);//发送信息

			packet a_player_data(SIGN_IN_FOR_PLAYER,new_player.show_name(),new_player.show_password(), 0, 1, 0);
			char send_buf[SIZE];
			memset(send_buf, 'z', SIZE);//清空缓存
			memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
			send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息*/

			goto part; //回到注册登录界面
		}
		else if (choice1_1 == 2) //注册出题者
		{
			test_maker new_test_maker; //建立一个新的出题者;
			new_test_maker.sign_in();//出题者注册
			word_match.sign_in_success(); //注册成功输出框口，详情见game.cpp
			/*
			char which =  'a' ;
			send(clientSocket, &which, 1, 0);//发送信息

			packet a_test_maker_data(SIGN_IN_FOR_TEST_MAKER,new_test_maker.show_name(), new_test_maker.show_password(), 0, 1, 0);
			char send_buf[SIZE];
			memset(send_buf, 'z', SIZE);//清空缓存
			memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
			send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息*/

			goto part;  //回到注册登录界面
		}
		else if (choice1_1 == 3) //返回
		{
			goto part;  //回到注册登录界面
		}
		else
		{
			word_match.wrong();// 输入错误
			goto part; //回到注册界面,重新输入
		}
	}
	else if (choice1 == 2) //登录
	{
	part2: //登录界面
		int choice2_1;//登录类型的选择
		word_match.show_sign_up_type();//输出框口，详情见game.cpp
		cin >> choice2_1;

		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			word_match.wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			word_match.show_sign_up_type();//输出框口，详情见game.cp p
			cin >> choice2_1;
		}
		if (choice2_1 == 1 || choice2_1 == 2)
		{
			char which = 'a';
			send(clientSocket, &which, 1, 0);//发送信息
		}
		if (choice2_1 == 1) //闯关者登录
		{
			player  new_player; //当做这个闯关者
			new_player.sign_up(); //闯关者登录
			if (choice == 1) //如果用户不存在就先注册
				goto part;  //回到注册登录界面
			else
			{
				word_match.sign_up_success(); //登录成功输出框口，详情见game.cpp
			}
			goto player_start;  //登录成功后去往闯关者开始游戏页面
		}
		else if (choice2_1 == 2) //出题者登录
		{
			test_maker new_test_maker; //当做这个出题者;
			new_test_maker.sign_up();//出题者登录
			if (choice == 1) //如果用户不存在就先注册
				goto part;  //回到注册登录界面
			else
			{
				word_match.sign_up_success(); //登录成功输出框口，详情见game.cpp
				//new_test_maker = *cur_test_maker;//找到后把数据覆盖
			}

			goto test_maker_start;  //登录成功后去往出题者开始游戏页面
		}
		else if (choice2_1 == 3)
		{
			goto part;  //回到注册登录界面
		}
		else
		{
			word_match.wrong();// 输入错误
			goto part2; //回到登录界面,重新输入
		}
	}
	else if (choice1 == 3) //退出游戏
	{
		//关闭套接字，关闭加载的套接字库
		char which = 'c';
		send(clientSocket, &which, 1, 0);//发送信息
		closesocket(clientSocket);
		WSACleanup();

		return 0;
	}
	else
	{
		word_match.wrong();// 输入错误
		goto part;  //回到注册登录界面
	}

player_start:  //闯关者页面
	choice = -1; //先初始化为-1
	word_match.player_main_menu(); //闯关者主菜单

	int choice_player;  //闯关者选择
	cin >> choice_player;

	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		word_match.wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		word_match.player_main_menu(); //闯关者主菜单
		cin >> choice_player;
	}


	if (choice_player == 1)  //如果选择开始游戏
	{
		//player new_player = *cur_player;
		word_match.start_player_game(); //开始游戏
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 2) //查询当前在线玩家
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_player_data(WATCH_ONLINE_PLAYER, temp, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		words rev_all_player_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//清空结构体
		memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//把接收到的信息转换成结构体

		cout << "当前在线的闯关者" << endl;
		for (int i = 0; i < rev_all_player_size.operate; i++)  //接收了所有的玩家信息除了密码
		{
			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			recv(clientSocket, recv_buf, SIZE, 0);//读取数据
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体
			cout << rev_a_player_data.name << endl;
		}
		goto player_start; //回到闯关者页面
	}
	else if (choice_player == 3) //查询闯关者
	{
		word_match.player_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 4) //查询出题者
	{
		word_match.test_maker_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 5) //排行榜
	{
		word_match.see_player_rank();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 6)  //退出登录
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_player_data(PLAYER_LOG_OUT, cur_player.show_name(), temp, cur_player.show_experience(), cur_player.show_level(), cur_player.show_rank());
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		goto part;
	}
	else
	{
		word_match.wrong();// 输入错误
		goto player_start;  //输入错误去闯关者页面
	}

test_maker_start:

	choice = -1; //先初始化为-1
	word_match.test_maker_main_menu();// 出题者主页面

	int choice_test_maker;  //闯关者选择
	cin >> choice_test_maker;

	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		word_match.wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		word_match.player_main_menu(); //闯关者主菜单
		cin >> choice_test_maker;
	}

	if (choice_test_maker == 1)  //如果选择开始游戏
	{
		//player new_player = *cur_player;
		word_match.start_test_maker_game(); //增加单词
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 2)
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_test_maker_data(WATCH_ONLINE_TEST_MAKER, temp, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//清空结构体
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//把接收到的信息转换成结构体


		cout << "当前在线的出题者" << endl;
		for (int i = 0; i < rev_all_test_maker_size.operate; i++)  //接收了所有的玩家信息除了密码
		{
			packet rev_a_test_maker_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			recv(clientSocket, recv_buf, SIZE, 0);//读取数据
			memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
			memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体
			cout << rev_a_test_maker_data.name << endl;
		}
		goto test_maker_start; //回到出题者页面
	}
	else if (choice_test_maker == 3) //查询闯关者
	{
		word_match.player_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 4) //查询出题者
	{
		word_match.test_maker_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 5) //排行榜
	{
		word_match.see_test_maker_rank();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 6)  //退出登录
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_test_maker_data(TEST_MAKER_LOG_OUT, cur_test_maker.show_name(), temp, cur_test_maker.show_experience(), cur_test_maker.show_level(), cur_test_maker.show_test_num());
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		goto part;
	}
	else
	{
		word_match.wrong();// 输入错误
		goto test_maker_start;  //输入错误去闯关者页面
	}

}



void player::sign_in() //闯关者注册,闯关者a已经被初始化
{
	
part1:
	string temp_name, temp_passwords;
	cout << "闯关者注册！" << endl;
	cout << "请输入闯关者用户名(不能超过15个字符):";
	cin >> temp_name;
	while (temp_name.empty() || temp_name.size() > 15)   //如果字符串为空
	{
		cout << "用户名不合乎规范！" << endl;
		cout << "请重新输入:";
		cin >> temp_name; //重新输入直到不为空
	}
	cout << "请输入密码(不能超过15个字符):";
	cin >> temp_passwords;
	while (temp_passwords.empty() || temp_passwords.size() > 15)   //如果字符串为空
	{
		cout << "密码不合乎规范！" << endl;
		cout << "请重新输入:";
		cin >> temp_passwords; //重新输入直到不为空
	}

	packet a_player_data(SIGN_IN_FOR_PLAYER, temp_name, temp_passwords, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

	cout << "已经发送packet" << endl;

	char judge;
	recv(clientSocket, &judge, 1, 0);

	if (judge == 'r')
	{
		cout << "该闯关者已存在，请重新注册";
		goto part1;
	}
	else
	{
		cout << "注册成功！" << endl;
		
	}
}
void player::sign_up()
{
	string temp_name, temp_passwords;
	cout << "欢迎登录！" << endl;
	cout << "请输入闯关者用户名:";
	cin >> temp_name;
	cout << "请输入密码:";
	cin >> temp_passwords;


	packet a_player_data(SIGN_UP_FOR_PLAYER, temp_name, temp_passwords, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

	char rev_temp;
	recv(clientSocket, &rev_temp, 1, 0);//接受一个判断客户传什么信息的标志

	if (rev_temp == 'a')//登陆成功
	{
		packet rev_a_player_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
		memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体

		this->experience = rev_a_player_data.experiences;
		this->level = rev_a_player_data.level;
		this->rank = rev_a_player_data.rank_or_test_num;

		
	    cur_player.name= rev_a_player_data.name;
		cur_player.passwords = rev_a_player_data.passwords;
		cur_player.experience = rev_a_player_data.experiences;
		cur_player.level = rev_a_player_data.level;
		cur_player.rank= rev_a_player_data.rank_or_test_num;
	}
	else  //失败
	{
		cout << "闯关者用户名或密码错误！" << endl;;
		choice = 1;//  闯关者不存在要回到注册界面
		//goto part;
	}

}
player::player()
{
	experience = 0;
	level = 0;
	rank = 0;
}
player::player(const player& a)   //拷贝构造函数
{
	name = a.name;
	passwords = a.passwords;
	level = a.level;
	rank = a.rank;
	experience = a.experience;
}
player::player(string in_name, string in_passwords, int in_experience, int in_level, int in_rank)
{
	name = in_name;
	passwords = in_passwords;
	experience = in_experience;
	level = in_level;
	rank = in_rank;
}
player& player::operator=(const player& a)
{
	if (this == &a) return *this;
	name = a.name;
	passwords = a.passwords;
	level = a.level;
	rank = a.rank;
	experience = a.experience;
	return *this;
}
void player::upgrade(int play_level)  //升级，参数是vector<player>的原因是因为当前玩家cur_player是该类型的
{																  //第二个参数是玩家玩的难度
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
	if (cur_player.experience <= cur_player.level * 100)
	{
		int add_experience = (int)(20000 / (play_end - play_start)); //强制类型转换,注意play_end和play_start以ms为单位 40/1/1000=40000
		add_experience += play_level * 5;
		cur_player.experience += add_experience;  //所加经验值由关卡难度和闯关时间共同决定
		cout << "恭喜您获得" << add_experience << "点经验值" << endl;
		cout << play_end << "            " << play_start << endl;
	}

	if (cur_player.experience > cur_player.level * 100)
	{
		//cout << it->experience << "***" << it->level << "***" << endl;
		cur_player.level++;
		cout << "恭喜您升到" << cur_player.level << "级" << endl;
		//it->experience %= it->level * 100;
	}
	cur_player.rank++;//闯过关卡数增加
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
}

void test_maker::sign_in()
{
	
part1:
	string temp_name, temp_pass;
	cout << "出题者注册！" << endl;
	cout << "请输入出题者用户名(不能超过15个字符):";
	cin >> temp_name;
	while (temp_name.empty() || temp_name.size() > 15)   //如果字符串为空
	{
		cout << "用户名不合乎规范！" << endl;
		cout << "请重新输入:";
		cin >> temp_name; //重新输入直到不为空
	}

	cout << "请输入密码(不能超过15个字符):";
	cin >> temp_pass;
	while (temp_pass.empty() || temp_pass.size() > 15)   //如果字符串为空
	{
		cout << "密码不合乎规范！" << endl;
		cout << "请重新输入:";
		cin >> temp_pass; //重新输入直到不为空
	}
	cout << "注册成功！" << endl;


	packet a_test_maker_data(SIGN_IN_FOR_TEST_MAKER, temp_name, temp_pass, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


	char judge;
	recv(clientSocket, &judge, 1, 0);

	if (judge == 'r')
	{
		cout << "该出题者已存在，请重新注册";
		goto part1;
	}
	else
	{
		cout << "注册成功！" << endl;
		return;
	}

}
void test_maker::sign_up()
{
	
	string test_maker_name, test_maker_passwords;
	cout << "欢迎登录！" << endl;
	cout << "请输入出题者用户名:";
	cin >> test_maker_name;
	cout << "请输入密码:";
	cin >> test_maker_passwords;

	packet a_test_maker_data(SIGN_UP_FOR_TEST_MAKER, test_maker_name, test_maker_passwords, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

	char rev_temp;
	recv(clientSocket, &rev_temp, 1, 0);//接受一个判断客户传什么信息的标志

	if (rev_temp == 'a')
	{
		packet rev_a_test_maker_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
		memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体

		this->experience = rev_a_test_maker_data.experiences;
		this->level = rev_a_test_maker_data.level;
		this->test_num = rev_a_test_maker_data.rank_or_test_num;

		cur_test_maker.name = this->name;
		cur_test_maker.passwords = this->passwords;
		cur_test_maker.experience = this->experience;
		cur_test_maker.level = this->level;
		cur_test_maker.test_num = this->test_num;
	}
	else
	{
		cout << "出题者用户名或密码错误！" << endl;;
		choice = 1;//  闯关者不存在要回到注册界面
		//goto part;
	}

	
}
test_maker::test_maker()
{
	experience = 0;
	level = 0;
	test_num = 0;
}
test_maker::test_maker(const test_maker & a)
{
	name = a.name;
	passwords = a.passwords;
	level = a.level;
	test_num = a.test_num;
	experience = a.experience;
}
test_maker::test_maker(string in_name, string in_passwords, int in_experience, int in_level, int in_test_num)
{
	name = in_name;
	passwords = in_passwords;
	experience = in_experience;
	level = in_level;
	test_num = in_test_num;
}
test_maker& test_maker::operator=(const test_maker & a)
{
	if (this == &a) return *this;
	name = a.name;
	passwords = a.passwords;
	level = a.level;
	test_num = a.test_num;
	experience = a.experience;
	return *this;
}
void test_maker::upgrade()//出题者升级，参数是vector<test_maker>的原因是因为当前玩家cur_test_maker是该类型的
{
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->test_num << "  *  " << it->experience << endl;
	if (cur_test_maker.experience <= cur_test_maker.level * 100)
	{
		cur_test_maker.experience += (cur_test_maker.test_num + 1) * 10;
	}
	if (cur_test_maker.experience > cur_test_maker.level * 100)
	{
		//cout << it->experience << "***" << it->level << "***" << endl;
		cur_test_maker.level++;
		cout << "恭喜您升到" << cur_test_maker.level << "级" << endl;
		//it->experience %= it->level * 100;
	}
	cur_test_maker.test_num++;//闯过关卡数增加
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->test_num << "  *  " << it->experience << endl;
}


void game::show_sign()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                             请选择                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                         1 注册              2 登录             3 退出                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::show_sign_in_type()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                           请选择注册类型                                             *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                         1 闯关者            2 出题者           3 返回                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::show_sign_up_type()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                           请选择登录类型                                             *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                         1 闯关者            2 出题者           3 返回                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::sign_in_success()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                         恭喜注册成功！                                               *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::sign_up_success()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                         恭喜登录成功！                                               *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::wrong()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                     非法输入，请重新输入！！                                         *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::passwords_wrong()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                     密码错误，请重新输入！！                                         *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::player_main_menu()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                             主菜单                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 开始游戏                                                  *" << endl;
	cout << "*                                          2 查看当前在线                                              *" << endl;
	cout << "*                                          3 查询闯关者                                                *" << endl;
	cout << "*                                          4 查询出题者                                                *" << endl;
	cout << "*                                          5 排行榜                                                    *" << endl;
	cout << "*                                          6 退出登录                                                  *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::show_player_search()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                       选择查询的闯关者属性                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 用户名                                                    *" << endl;
	cout << "*                                          2 等级                                                      *" << endl;
	cout << "*                                          3 通过关卡数                                                *" << endl;
	cout << "*                                          4 经验值                                                    *" << endl;
	cout << "*                                          5 返回主菜单                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::show_player_search_rank()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                       排       行       榜                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 等级                                                      *" << endl;
	cout << "*                                          2 通过关卡数                                                *" << endl;
	cout << "*                                          3 经验值                                                    *" << endl;
	cout << "*                                          4 返回主菜单                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;

}
void game::show_test_maker_search_rank() //排行榜页面
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                     排       行       榜                                             *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 等级                                                      *" << endl;
	cout << "*                                          2 出题数目                                                  *" << endl;
	cout << "*                                          3 经验值                                                    *" << endl;
	cout << "*                                          4 返回主菜单                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::test_maker_main_menu()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                             主菜单                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 增加新词                                                  *" << endl;
	cout << "*                                          2 查看当前在线                                              *" << endl;
	cout << "*                                          3 查询闯关者                                                *" << endl;
	cout << "*                                          4 查询出题者                                                *" << endl;
	cout << "*                                          5 排行榜                                                    *" << endl;
	cout << "*                                          6 退出登录                                                  *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::show_test_maker_search()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                       选择查询的出题者属性                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 用户名                                                    *" << endl;
	cout << "*                                          2 等级                                                      *" << endl;
	cout << "*                                          3 出题数目                                                  *" << endl;
	cout << "*                                          4 经验值                                                    *" << endl;
	cout << "*                                          5 返回主菜单                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;

}
void game::player_search()
{
	
main_part:

	show_player_search();
	int search_choice;
	cin >> search_choice;

	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_player_search(); //闯关者查询页面
		cin >> search_choice;
	}

	if (search_choice == 1)  //选择查询用户名
	{
		string search_player_name;
		cout << "请输入该闯关者用户名:" << endl;


		cin >> search_player_name;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}

			cin >> search_player_name;
		}

		char which=  'a' ;
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_player_data(SEARCH_PLAYER_NAME, search_player_name, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		words rev_all_player_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//清空结构体
		memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//把接收到的信息转换成结构体

		

		if (rev_all_player_size.operate == 0)
		{
			cout << "未找到匹配的闯关者" << endl;
		}
		else
		{
			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			recv(clientSocket, recv_buf, SIZE, 0);//读取数据
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体

			cout << "该闯关者信息如下：" << endl;
			cout.width(10);
			cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
			cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		}

		goto main_part;
	}
	else if (search_choice == 2)  //选择查询用户等级
	{
		int search_player_level;
		cout << "请输入该闯关者等级:" << endl;


		cin >> search_player_level;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}

			cin >> search_player_level;
		}

		char which=  'a' ;
		send(clientSocket, &which, 1, 0);//发送信息
		string temp;
		packet a_player_data(SEARCH_PLAYER_LEVEL, temp, temp, 0, search_player_level, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


		words rev_all_player_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//清空结构体
		memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//把接收到的信息转换成结构体


		if (rev_all_player_size.operate == 0)
		{
			cout << "未找到匹配的闯关者" << endl;
		}
		else
		{

			cout << "该闯关者信息如下：" << endl;
			cout.width(10);
			cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
			//cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
			for (int i = 0; i < rev_all_player_size.operate; i++)
			{
				packet rev_a_player_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//清空缓存
				recv(clientSocket, recv_buf, SIZE, 0);//读取数据
				memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
				memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体
				cout.width(10);
				cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
			}
		}

		goto main_part;
	}
	else if (search_choice == 3)  //选择查询闯关者通过关卡数
	{
	int search_player_rank;
	cout << "请输入该闯关者关卡数:" << endl;


	cin >> search_player_rank;
	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}

		cin >> search_player_rank;
	}

	char which =  'a' ;
	send(clientSocket, &which, 1, 0);//发送信息
	string temp;
	packet a_player_data(SEARCH_PLAYER_RANK, temp, temp, 0, 1, search_player_rank);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


	words rev_all_player_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//清空缓存
	recv(clientSocket, recv_buf, SIZE, 0);//读取数据
	memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//清空结构体
	memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//把接收到的信息转换成结构体


	if (rev_all_player_size.operate == 0)
	{
		cout << "未找到匹配的闯关者" << endl;
	}
	else
	{

		cout << "该闯关者信息如下：" << endl;
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		//cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		for (int i = 0; i < rev_all_player_size.operate; i++)
		{

			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			recv(clientSocket, recv_buf, SIZE, 0);//读取数据
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体
			cout.width(10);
			cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		}
	}

	goto main_part;
	}
	else if (search_choice == 4)  //选择查询闯关者经验值
	{
	int search_player_experiences;
	cout << "请输入该闯关者经验值:" << endl;


	cin >> search_player_experiences;
	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}

		cin >> search_player_experiences;
	}

	char which =  'a' ;
	send(clientSocket, &which, 1, 0);//发送信息
	string temp;
	packet a_player_data(SEARCH_PLAYER_EXPERIENCES, temp, temp, search_player_experiences, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


	words rev_all_player_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//清空缓存
	recv(clientSocket, recv_buf, SIZE, 0);//读取数据
	memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//清空结构体
	memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//把接收到的信息转换成结构体


	if (rev_all_player_size.operate == 0)
	{
		cout << "未找到匹配的闯关者" << endl;
	}
	else
	{

		cout << "该闯关者信息如下：" << endl;
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		//cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		for (int i = 0; i < rev_all_player_size.operate; i++)
		{

			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			recv(clientSocket, recv_buf, SIZE, 0);//读取数据
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体
			cout.width(10);
			cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		}
	}

	goto main_part;
	}

	else if (search_choice == 5)  //选择返回主菜单
	{
		choice = 0;
	}
	else
	{
		cout << "输入错误！" << endl;
		goto main_part;
	}
	
}

void game::see_player_rank()
{
	

	char which= 'a' ;
	send(clientSocket, &which, 1, 0);//发送信息

	string temp;
	packet a_player_data(RANK_FOR_PLAYER, temp, temp, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


	words rev_all_player_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//清空缓存
	recv(clientSocket, recv_buf, SIZE, 0);//读取数据
	memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//清空结构体
	memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//把接收到的信息转换成结构体

	for (int i = 0; i < rev_all_player_size.operate; i++)  //接收了所有的玩家信息除了密码
	{
		packet rev_a_player_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//清空结构体
		memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//把接收到的信息转换成结构体
		all_player.push_back(rev_a_player_data); 
	}

main_part:

	show_player_search_rank();
	int see_which_element; //按照什么排行？
	cin >> see_which_element;

	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_player_search_rank(); //按照什么排行页面
		cin >> see_which_element;
	}

	
	if (see_which_element == 1)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_level);

	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_rank_or_test_num);
	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_experiences);
	}
	else if (see_which_element == 4)
	{
		choice = 0; //返回主菜单
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<packet>::iterator it = all_player.begin(); it != all_player.end(); it++)  //输出排行榜
	{
		cout.width(10);
		cout << it->name<< "\t\t" << it->level << "\t\t" << it->rank_or_test_num<< "\t\t\t" << it->experiences << endl;
	}
	getchar();//吞回车
	cout << "按Enter返回" << endl;
	if (getchar() != NULL)
		goto main_part;
}

void game::test_maker_search()
{
	
main_part:
	show_test_maker_search();
	int search_choice;
	cin >> search_choice;
	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_test_maker_search(); //出题者查询页面
		cin >> search_choice;
	}

	if (search_choice == 1)  //选择查询用户名
	{

		string search_test_maker_name;
		cout << "请输入该出题者用户名:" << endl;


		cin >> search_test_maker_name;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}

			cin >> search_test_maker_name;
		}

		char which =  'a' ;
		send(clientSocket, &which, 1, 0);//发送信息
		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_NAME, search_test_maker_name, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//清空结构体
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//把接收到的信息转换成结构体


		
		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "未找到匹配的出题者" << endl;
		}
		else
		{

			cout << "该出题者信息如下：" << endl;
			cout.width(10);
			cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{
				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//清空缓存
				recv(clientSocket, recv_buf, SIZE, 0);//读取数据
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
		}

		goto main_part;
	}
	else if (search_choice == 2)  //选择查询用户等级
	{
		int search_test_maker_level;
		cout << "请输入该出题者等级:" << endl;


		cin >> search_test_maker_level;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}

			cin >> search_test_maker_level;
		}

		char which =  'a' ;
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_LEVEL, temp, temp, 0, search_test_maker_level, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息


		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//清空结构体
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//把接收到的信息转换成结构体

	
		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "未找到匹配的出题者" << endl;
		}
		else
		{
			cout << "该出题者信息如下：" << endl;
			cout.width(10);
			cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{

				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//清空缓存
				recv(clientSocket, recv_buf, SIZE, 0);//读取数据
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
		}

		goto main_part;

	}
	else if (search_choice == 3)  //选择查询出题者出题数目
	{
		int search_test_maker_test_num;
		cout << "请输入该出题者出题数目:" << endl;


		cin >> search_test_maker_test_num;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
		{
			continue;
		}

		cin >> search_test_maker_test_num;
		}

		char which=  'a' ;
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_TEST_NUM, temp, temp, 0, 1, search_test_maker_test_num);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//清空结构体
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//把接收到的信息转换成结构体

		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "未找到匹配的出题者" << endl;
		}
		else
		{

			cout << "该闯关者信息如下：" << endl;
			cout.width(10);
			cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{
				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//清空缓存
				recv(clientSocket, recv_buf, SIZE, 0);//读取数据
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
		}

		goto main_part;

	}
	else if (search_choice == 4)  //选择查询闯关者经验值
	{
		
		int search_test_maker_experience;
		cout << "请输入该出题者经验值:" << endl;


		cin >> search_test_maker_experience;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}

			cin >> search_test_maker_experience;
		}

		char which= 'a' ;
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_EXPERIENCES, temp, temp, search_test_maker_experience, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//清空结构体
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//把接收到的信息转换成结构体

		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "未找到匹配的出题者" << endl;
		}
		else
		{

			cout << "该闯关者信息如下：" << endl;
			cout.width(10);
			cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{

				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//清空缓存
				recv(clientSocket, recv_buf, SIZE, 0);//读取数据
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
		}

		goto main_part;

	}
	else if (search_choice == 5)  //选择返回主菜单
	{
		choice = 0;
	}
	else
	{
		wrong();
		goto main_part;
	}
}

void game::see_test_maker_rank()
{
	

	char which =  'a' ;
	send(clientSocket, &which, 1, 0);//发送信息
	string temp;
	packet a_test_maker_data(RANK_FOR_TEST_MAKER, temp, temp, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//清空缓存
	memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
	send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

	words rev_all_test_maker_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//清空缓存
	recv(clientSocket, recv_buf, SIZE, 0);//读取数据
	memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//清空结构体
	memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//把接收到的信息转换成结构体

	for (int i = 0; i < rev_all_test_maker_size.operate; i++)  //接收了所有的玩家信息除了密码
	{
		packet rev_a_test_maker_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//清空结构体
		memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//把接收到的信息转换成结构体
		all_test_maker.push_back(rev_a_test_maker_data);
	}



main_part:
	show_test_maker_search_rank();
	int see_which_element; //按照什么排行？
	cin >> see_which_element;

	while (cin.fail())  //错误控制，如果输入类型不符合
	{
		wrong();// 输入错误
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_test_maker_search(); //出题者查询页面
		cin >> see_which_element;
	}

	
	if (see_which_element == 1)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_level);

	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_rank_or_test_num);
	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_experiences);
	}
	else if (see_which_element == 4)
	{
		choice = 0; //返回主菜单
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<packet>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++)  //输出排行榜
	{
		cout.width(10);
		cout << it->name << "\t\t" << it->level<< "\t\t" << it->rank_or_test_num<< "\t\t\t" << it->experiences << endl;
	}
	getchar();//吞回车
	cout << "按Enter返回" << endl;
	if (getchar() != NULL)
		goto main_part;
}

void game::start_player_game()
{
	
	string input_word;
	
	int passed_level = 1; //当前难度等级
	int all_level = 4;  //共有4个等级
	int play_choice = -1;

	while (play_choice != 0)
	{
		cout << "总共" << all_level << "个等级," << "当前难度等级:" << passed_level << endl;
		cout << "请记住这个单词（3s后消失）：" << endl;
		
		char which =  'b' ;
		send(clientSocket, &which, 1, 0);//发送信息

		string temp;
		words send_a_word(START_PLAYER_GAME, passed_level, temp);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &send_a_word, sizeof(send_a_word)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息

		words rev_a_word;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//清空缓存
		recv(clientSocket, recv_buf, SIZE, 0);//读取数据
		memset(&rev_a_word, 0, sizeof(rev_a_word));//清空结构体
		memcpy(&rev_a_word, recv_buf, sizeof(rev_a_word));//把接收到的信息转换成结构体

		cout << rev_a_word.a_word;


		Sleep(3000 - passed_level * 200);  //等待3秒,随着等级增加减少时间

		cout << "\r                                                            ";
		//system("cls");  //清屏
		cout << "\r请输入刚才出现的单词：";
		//cin.clear();
		//cin.ignore(5, '\n');//放弃包含换行符的输入流中的所有内容
		play_start = clock(); //计时器开始计时
		cin >> input_word;

		if (cin.fail())
		{
			cout << "错误输入!" << endl;
			cin.clear();
			cin.ignore(99999, '\n');//放弃包含换行符的输入流中的所有内容
			continue;
			play_end = clock(); // 输入错误计时器停止
		}
		if (input_word == rev_a_word.a_word)//正确
		{
			cout << "输入单词正确，闯关成功\n";
			play_end = clock(); //闯关成功 ,计时器停止
			/*更新等级、经验*/
			player::upgrade(passed_level); //当前玩家加经验,闯过关卡增加,根据难度加经验
		}
		else//错误
		{
			cout << "输入单词错误，闯关失败\t刚才显示的单词是：" << rev_a_word.a_word << endl;
			play_end = clock(); // 输入错误计时器停止
		}
	part:
		cout << "0返回主菜单  1继续该难度  2 下一难度 " << endl;;
		cin >> play_choice;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cout << "0返回主菜单  1继续该难度  2 下一难度 " << endl;
			cin >> play_choice;
		}

		if (play_choice == 0)
		{
			choice = 0; //这是全局的选择的一个标志，之后到主函数中进行处理
		}
		else if (play_choice == 2) //选择下一难度则难度增加
		{
			if (passed_level == all_level)
			{
				cout << "已经到最大难度！" << endl;
			}
			else
			{
				passed_level++;
			}

		}
		else if (play_choice != 0 && play_choice != 1 && play_choice != 2)
		{
			wrong();
			goto part;
		}
		else
		{
			//不用写，顺序操作就行
		}

	}
}
void game::start_test_maker_game()//开始一个出题者的游戏;
{
	
	string add_words;
	int play_choice = -1;
	while (play_choice != 0)
	{
		cout << "请输入要添加的单词" << endl;
		cin >> add_words;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cout << "请输入要添加的单词" << endl;
			cin >> add_words;
		}

		char which= 'b' ;
		send(clientSocket, &which, 1, 0);//发送信息

		words send_a_word(ADD_NEW_WORDS, NULL, add_words);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//清空缓存
		memcpy(send_buf, &send_a_word, sizeof(send_a_word)); //结构体转换成字符串
		send(clientSocket, send_buf, sizeof(send_buf), 0);//发送信息



		vector<string>::iterator insert_words;
		insert_words = find(all_words.begin(), all_words.end(), add_words); //查找词库是否有该单词

		char rev;
		recv(clientSocket, &rev, 1, 0);//接受一个判断客户传什么信息的标志


		if (rev == 'r')//插入成功检验:单词不存在
		{
			/*出题者属性修改：单词数、经验值、等级*/
			test_maker::upgrade(); //当前出题者加经验,出题数目增加
		}
		else
		{
			cout << "该单词已存在\n";
		}
	part:
		cout << "0返回主菜单  1继续添加单词 " << endl;
		cin >> play_choice;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			//show_test_maker_search(); //出题者查询页面
			cout << "0返回主菜单  1继续添加单词 " << endl;
			cin >> play_choice;
		}
		if (play_choice == 0)
		{
			choice = 0; //这是全局的选择的一个标志，之后到主函数中进行处理
		}
		else if (play_choice != 0 && play_choice != 1)  //输入不存在的选择数字
		{
			wrong();
			goto part;
		}
		else
		{
			//顺序执行，即继续出题
		}
	}
}


