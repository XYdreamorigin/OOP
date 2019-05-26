
#pragma once
#include"vector.h"
#include<windows.h>
#include<iostream>
#include<vector>

using std::vector;
#define false 0
#define true 1

int choice = 0;    //一个全局的来显示用户输入的选择

using namespace std;

/*void SetPosition(short int x, short int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	getchar();
}*/
vector<player> all_player; //所有闯关者
vector<player>all_online_player;  //所有在线的闯关者
vector<test_maker> all_test_maker;//所有出题者
vector<player>::iterator cur_player;//当前的闯关者
vector<test_maker>::iterator cur_test_maker; //当前出题者
vector<string> all_words; //单词题库



int main()
{
	
	SetConsoleTitle(L"单次消除游戏"); // 设置窗口标题
	game word_match;//开始一个游戏
	word_match.read_all_words(); //将所有单词从文件读入到all_words容器中
	word_match.read_all_player(); //将所有闯关者信息读入到all_palyer容器中
	word_match.read_all_test_maker();//将所有出题者信息读入到all_test_maker容器中

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

		if (choice1_1 == 1)  //注册闯关者
		{
			player new_player;// 建立一个新的闯关者
			new_player.sign_in();//闯关者注册
			word_match.sign_in_success();//注册成功输出框口，详情见game.cpp
			goto part; //回到注册登录界面
		}
		else if (choice1_1 == 2) //注册出题者
		{
			test_maker new_test_maker; //建立一个新的出题者;
			new_test_maker.sign_in();//出题者注册
			word_match.sign_in_success(); //注册成功输出框口，详情见game.cpp
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

		if (choice2_1 == 1) //闯关者登录
		{
			player  new_player; //当做这个闯关者
			new_player.sign_up(); //闯关者登录
			if (choice == 1) //如果用户不存在就先注册
				goto part;  //回到注册登录界面
			else
			{
				word_match.sign_up_success();//登录成功输出框口，详情见game.cpp
				//new_player = *cur_player;   //找到后把数据覆盖
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
	else if(choice1 == 3) //退出游戏
	{
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
	else if (choice_player == 2) //查询闯关者
	{
		word_match.player_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 3) //查询出题者
	{
		word_match.test_maker_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 4) //排行榜
	{
		word_match.see_player_rank();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto player_start; //回到闯关者页面
		}
	}
	else if (choice_player == 5)  //退出登录
	{

		word_match.write_in_player();  //写信息
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
	else if (choice_test_maker == 2) //查询闯关者
	{
		word_match.player_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 3) //查询出题者
	{
		word_match.test_maker_search();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 4) //排行榜
	{
		word_match.see_test_maker_rank();
		if (choice == 0) //在游戏中选择了返回主菜单
		{
			goto test_maker_start; //回到出题者页面
		}
	}
	else if (choice_test_maker == 5)  //退出登录
	{
		word_match.write_in_test_maker();  //写信息
		goto part;
	}
	else
	{
		word_match.wrong();// 输入错误
		goto test_maker_start;  //输入错误去闯关者页面
	}

}

