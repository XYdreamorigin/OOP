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

void player::sign_in() //闯关者注册,闯关者a已经被初始化
{
	part1:
		cout << "闯关者注册！" << endl;
		cout << "请输入闯关者用户名(不能超过15个字符):";
		cin >> name;
		while (name.empty() || name.size() > 15)   //如果字符串为空
		{
			cout << "用户名不合乎规范！" << endl;
			cout << "请重新输入:";
			cin >> name; //重新输入直到不为空
		}

		bool player_exist = false; //判断闯关者是否已经存在的依据
	
		for (vector<player>::iterator it=all_player.begin(); it!=all_player.end(); it++) //判断闯关者是否已经存在
		{
			if (name == it->name)
			{
				player_exist = true;
				break;
			}
		}
		if (player_exist == false)//如果闯关者未被注册过
		{
	
			cout << "请输入密码(不能超过15个字符):";
			cin >> passwords;
			while (passwords.empty() || passwords.size() > 15)   //如果字符串为空
			{
				cout << "密码不合乎规范！" << endl;
				cout << "请重新输入:";
				cin >> passwords; //重新输入直到不为空
			}
			cout << "注册成功！" << endl;

			all_player.push_back(*this); //将注册的用户名保存在容器中
			return;
		}
		else
		{
			cout << "该闯关者已存在，请重新注册";
			goto part1;
		}

}

void player::sign_up()
{

	string player_name, player_passwords;
	cout << "欢迎登录！" << endl;
	cout << "请输入闯关者用户名:";
//part:
	cin >> player_name;

	bool player_exist = false; //判断闯关者是否已经存在的依据

	//vector<player>::iterator temp_it = all_player.begin();
	for (cur_player = all_player.begin(); cur_player != all_player.end(); cur_player++) //判断出题者是否已经存在
	{
		if (player_name == cur_player->name)
		{
			player_exist = true;
			break;
		}
	}

	if (player_exist == true) //闯关者存在，输入密码
	{
		cout << "请输入密码:";
		cin >> player_passwords;
		while (player_passwords != cur_player->passwords)
		{
			cout << "闯关者密码错误,请重新输入!";
			cin >> player_passwords;
		}
	}
	else   //闯关者不存在
	{
		cout << "闯关者不存在，请先注册!" << endl;;
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

player::player(const player &a)   //拷贝构造函数
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

void player::upgrade(vector<player>::iterator it)  //升级，参数是vector<player>的原因是因为当前玩家cur_player是该类型的
{
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
	if (it->experience <= it->level * 100)
	{
		int add_experience = (int)(40000 / (play_end - play_start)); //强制类型转换,注意play_end和play_start以ms为单位 40/1/1000=40000
		add_experience += it->level * 5;
		it->experience += add_experience;  //所加经验值由关卡难度和闯关时间共同决定
		cout << "恭喜您获得" << add_experience << "点经验值" << endl;
		cout << play_end << "            " << play_start << endl;
	}
	
	if (it->experience > it->level * 100)
	{
		//cout << it->experience << "***" << it->level << "***" << endl;
		it->level++;
		cout << "恭喜您升到" << it->level << "级" << endl;
		//it->experience %= it->level * 100;
	}
	it->rank++;//闯过关卡数增加
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
}

void test_maker::sign_in()
{
part1:
	cout << "出题者注册！" << endl;
	cout << "请输入出题者用户名(不能超过15个字符):";
	cin >> name;
	while (name.empty() || name.size() > 15)   //如果字符串为空
	{
		cout << "用户名不合乎规范！" << endl;
		cout << "请重新输入:";
		cin >> name; //重新输入直到不为空
	}

	bool test_maker_exist = false; //判断出题者是否已经存在的依据

	for (vector<test_maker>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++) //判断出题者是否已经存在
	{
		if (name == it->name)
		{
			test_maker_exist = true;
			break;
		}
	}
	if (test_maker_exist == false)//如果闯关者未被注册过
	{

		cout << "请输入密码(不能超过15个字符):";
		cin >> passwords;
		while (passwords.empty() || passwords.size() > 15)   //如果字符串为空
		{
			cout << "密码不合乎规范！" << endl;
			cout << "请重新输入:";
			cin >> passwords; //重新输入直到不为空
		}
		cout << "注册成功！" << endl;

		all_test_maker.push_back(*this); //将注册的用户名保存在容器中
		return;
	}
	else
	{
		cout << "该用户名已存在，请重新注册";
		goto part1;
	}

}

void test_maker::sign_up()
{

	string test_maker_name, test_maker_passwords;
	cout << "欢迎登录！" << endl;
	cout << "请输入出题者用户名:";
//part:
	cin >> test_maker_name;

	bool test_maker_exist = false; //判断闯关者是否已经存在的依据

	//vector<test_maker>::iterator it = all_test_maker.begin();
	for (cur_test_maker= all_test_maker.begin(); cur_test_maker != all_test_maker.end(); cur_test_maker++) //判断出题者是否已经存在
	{
		if (test_maker_name == cur_test_maker->name)
		{
			test_maker_exist = true;
			break;
		}
	}
	if (test_maker_exist == true) //出题者存在，输入密码
	{
		cout << "请输入密码:";
		cin >> test_maker_passwords;
		while (test_maker_passwords != cur_test_maker->passwords)
		{
			cout << "出题者密码错误,请重新输入!";
			cin >> test_maker_passwords;
		}
	}
	else   //出题者不存在
	{
		cout << "出题者不存在，请先注册！" << endl;
		choice = 1;
		//goto part;
	}
}

test_maker::test_maker()
{
	experience = 0;
	level = 0;
	test_num = 0;
}

test_maker::test_maker(const test_maker& a)
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

test_maker& test_maker::operator=(const test_maker& a)
{
	if (this == &a) return *this;
	name = a.name;
	passwords = a.passwords;
	level = a.level;
	test_num = a.test_num;
	experience = a.experience;
	return *this;
}

void test_maker::upgrade(vector<test_maker>::iterator it)//出题者升级，参数是vector<test_maker>的原因是因为当前玩家cur_test_maker是该类型的
{
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->test_num << "  *  " << it->experience << endl;
	if (it->experience <= it->level * 100)
	{
		it->experience += (it->test_num + 1) * 10;
	}
	if (it->experience > it->level * 100)
	{
		//cout << it->experience << "***" << it->level << "***" << endl;
		it->level++;
		cout << "恭喜您升到" << it->level << "级" << endl;
		it->experience %= it->level * 100;
	}
	it->test_num++;//闯过关卡数增加
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
	cout << "*                                          2 查询闯关者                                                *" << endl;
	cout << "*                                          3 查询出题者                                                *" << endl;
	cout << "*                                          4 排行榜                                                    *" << endl;
	cout << "*                                          5 退出登录                                                  *" << endl;
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
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_player)
		{
			if (search.show_name() == search_player_name)
			{
				if (time == 0)
				{
					cout << "该闯关者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的闯关者" << endl;
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
		
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_player)
		{
			if (search.show_level() == search_player_level)
			{
				if (time == 0)
				{
					cout << "该闯关者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的闯关者" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 3)  //选择查询闯关者通过关卡数
	{
		int search_player_rank;
		cout << "请输入该闯关者通过关卡数:" << endl;

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
		
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_player)
		{
			if (search.show_rank() == search_player_rank)
			{
				if (time == 0)
				{
					cout << "该闯关者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的闯关者" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 4)  //选择查询闯关者经验值
	{
		int search_player_experience;
		cout << "请输入该闯关者经验值:" << endl;

		cin >> search_player_experience;
		while (cin.fail())  //错误控制，如果输入类型不符合
		{
			wrong();// 输入错误
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_player_experience;
		}
		
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_player)
		{
			if (search.show_experience() == search_player_experience)
			{
				if (time == 0)
				{
					cout << "该闯关者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的闯关者" << endl;
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
void game::show_player_search_rank()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                       排       行       榜                                           *" << endl;
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
void game::see_player_rank()
{
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
		std::sort(all_player.begin(), all_player.end(),comp_name_player);
	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_level_player);
		
	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_rank_player);
	}
	else if (see_which_element == 4)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "通过关卡数" << "\t\t" << "经验值" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_experience_player);
	}
	else if (see_which_element == 5)
	{
		choice = 0; //返回主菜单
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<player>::iterator it = all_player.begin(); it != all_player.end(); it++)  //输出排行榜
	{
		cout.width(10);
		cout << it->show_name() << "\t\t" << it->show_level() << "\t\t" << it->show_rank() <<"\t\t\t" << it->show_experience() << endl;
	}
	getchar();//吞回车
	cout << "按Enter返回" << endl;
	if (getchar() != NULL)
		goto main_part;
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
	cout << "*                                          2 查询闯关者                                                *" << endl;
	cout << "*                                          3 查询出题者                                                *" << endl;
	cout << "*                                          4 排行榜                                                    *" << endl;
	cout << "*                                          5 退出登录                                                  *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
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
		cout << "请输入该闯关者用户名:" << endl;

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
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_test_maker)
		{
			if (search.show_name() == search_test_maker_name)
			{
				if (time == 0)
				{
					cout << "该出题者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的出题者" << endl;
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
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_test_maker)
		{
			if (search.show_level() == search_test_maker_level)
			{
				if (time == 0)
				{
					cout << "该闯关者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的出题者" << endl;
		}
		goto main_part;
	
	}
	else if (search_choice == 3)  //选择查询闯关者通过关卡数
	{
		int search_test_maker_test_num;
		cout << "请输入该出题者通过关卡数:" << endl;

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
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_test_maker)
		{
			if (search.show_test_num() == search_test_maker_test_num)
			{
				if (time == 0)
				{
					cout << "该出题者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的出题者" << endl;
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
		int time = 0, judge = 0;//只输出一次标头，判断是否找到的标志
		for (auto search : all_test_maker)
		{
			if (search.show_experience() == search_test_maker_experience)
			{
				if (time == 0)
				{
					cout << "该出题者信息如下：" << endl;
					cout.width(10);
					cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "未找到匹配的出题者" << endl;
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
void game::see_test_maker_rank()
{
main_part:
	show_test_maker_search();
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
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_name_test_maker);
	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_level_test_maker);

	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_test_num_test_maker);
	}
	else if (see_which_element == 4)
	{
		cout.width(10);
		cout << "用户名" << "\t\t" << "等级" << "\t\t" << "出题数目" << "\t\t" << "经验值" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_experience_test_maker);
	}
	else if (see_which_element == 5)
	{
		choice = 0; //返回主菜单
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<test_maker>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++)  //输出排行榜
	{
		cout.width(10);
		cout << it->show_name() << "\t\t" << it->show_level() << "\t\t" << it->show_test_num() << "\t\t\t" << it->show_experience() << endl;
	}
	getchar();//吞回车
	cout << "按Enter返回" << endl;
	if (getchar() != NULL)
		goto main_part;
}

void game::read_all_words()
{
	fstream f_wordlist("wordlist.csv", ios::in); //打开文件       ios::in 文件以输入方式打开(文件数据输入到内存) 
	if (!f_wordlist)  //打开文件失败
	{
		cout << "无法打开文件wordlist" << endl;
		return;
	}
	//f_wordlist.seekg(0, fstream::beg);  
	string word;
	while (!f_wordlist.eof())   //如果没有读到文件末尾
	{
		getline(f_wordlist, word); //从f_wordlist 读取一行，因为存储时一行只存储了一个单词，所以读取一行就是读取一个单词
		all_words.push_back(word);  //将这个单词存入到vector<string> all_words中
	}
	//f_wordlist析构时文件自动关闭
}

void game::read_all_player()
{
	fstream f_playerlist("playerlist.csv", ios::in); //打开文件
	if (!f_playerlist) //打开文件失败
	{
		cout << "无法打开文件playerlist" << endl;
		return;
	}

	string line, line_part; //定义一个字符串读取一行，一个字符串读取一行中某一段，取决于信息存储的方式  name , passwords ,experience , level, rank
	string name, passwords;
	int experience, level, rank;
	while (getline(f_playerlist, line))//读取一行
	{
		stringstream line_sin(line); ////将整行字符串line读入到字符串流line_sin中,该函数包含在头文件#include<sstream>中


		//读取文件这块也没太明白
		getline(line_sin, name, ',');//字符串流遇见','停止，将之前的字符串赋给name

		getline(line_sin, passwords, ',');//字符串流遇见','停止，将之前的字符串赋给passwords
		line_sin >> level;
		getline(line_sin, line_part, ',');
		line_sin >> rank;   //为什么能直接赋值给int类型?因为通过stringstream类对象实现字符串转换
		getline(line_sin, line_part, ',');
		line_sin >> experience;
		getline(line_sin, line_part);
		//cout << name << "*	" << passwords << " *  " << level << " *  " << rank << "*  " << experience << "**" << endl;
		player temp_player(name, passwords, experience, level, rank);//将文件读取的数据存入一个闯关者类中
		all_player.push_back(temp_player); //将这个玩家存入all_player容器中
	}
}

void game::read_all_test_maker()
{
	fstream f_test_makerlist("test_makerlist.csv", ios::in); //打开文件
	if (!f_test_makerlist) //打开文件失败
	{
		cout << "无法打开文件test_makerlist" << endl;
		return;
	}

	string line, line_part; //定义一个字符串读取一行，一个字符串读取一行中某一段，取决于信息存储的方式  name , passwords ,experience , level, rank
	string name, passwords;
	int experience, level, test_num;
	while (getline(f_test_makerlist, line)) //读取一行
	{
		
		stringstream line_sin(line); ////将整行字符串line读入到字符串流line_sin中,该函数包含在头文件#include<sstream>中

		getline(line_sin, name, ',');
		
		getline(line_sin, passwords, ',');
		line_sin >> level;
		getline(line_sin, line_part, ',');
		line_sin >> test_num;   
		getline(line_sin, line_part, ',');
		line_sin >> experience;
		line_sin >> test_num;

		//cout << name << "*	" << passwords << " *  " << level << " *  " << test_num << "*  " << experience << "**" << endl;
		test_maker temp_test_maker(name, passwords, experience, level, test_num);//将文件读取的数据存入一个闯关者类中
		all_test_maker.push_back(temp_test_maker); //将这个玩家存入all_player容器中
	}
}

void game::start_player_game()
{
	srand((unsigned)time(NULL));
	string input_word;
	int wordlist_size = all_words.size();//获得词库大小，方便分难度
	int passed_level = 1; //当前难度等级
	int all_level = 10;
	int play_choice = -1;
	int loc;  //在词库中的第几个单词
	while (play_choice != 0)
	{
		cout << "总共" << all_level << "个等级," << "当前难度等级:" << passed_level << endl;
		cout << "请记住这个单词（3s后消失）：" << endl;
		//要取得[a,b)的随机整数，使用(rand() % (b-a))+ a; 
		loc = (rand() % ((wordlist_size / all_level) * (passed_level)-(wordlist_size / all_level) * (passed_level - 1))) + (wordlist_size / all_level) * (passed_level - 1);
		cout << loc << "*******************" << endl;
		cout << all_words.at(loc); //输出这个单词

		Sleep(3000-passed_level*200);  //等待3秒,随着等级增加减少时间

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
		if (input_word == all_words.at(loc))//正确
		{
			cout << "输入单词正确，闯关成功\n";
			play_end = clock(); //闯关成功 ,计时器停止
			/*更新等级、经验*/
			player::upgrade(cur_player); //当前玩家加经验,闯过关卡增加
		}
		else//错误
		{
			cout << "输入单词错误，闯关失败\t刚才显示的单词是：" << all_words.at(loc) << endl;
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
			if (passed_level == 10)
			{
				cout << "已经到最大难度！" << endl;
			}
			else
				passed_level++;
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
		vector<string>::iterator insert_words;
		insert_words = find(all_words.begin(), all_words.end(), add_words); //查找词库是否有该单词

		if (insert_words == all_words.end())//插入成功检验:单词不存在
		{

			all_words.push_back(add_words);
			std::sort(all_words.begin(), all_words.end(), comp_string);
			/*写入文件*/
			fstream f_wordlist("wordlist.csv", ios::out);
			if (!f_wordlist)
			{
				cout << "无法打开文件wordlist.csv" << endl;
				return;
			}
			int len = all_words.size();
			for (int i = 0; i < len; i++)
			{
				f_wordlist << all_words[i] << endl;  //因为vector重载了[ ]运算符，所以我直接把它当作数组用了，当然可以用vector的迭代器iterator访问。
													//	只是我用迭代器遍历会报错。。。。
			}

			/*出题者属性修改：单词数、经验值、等级*/
			test_maker::upgrade(cur_test_maker); //当前出题者加经验,出题数目增加
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

void game::write_in_player() //将闯关者的信息写入文件
{
	/*写player*/
	fstream f_playerlist("playerlist.csv", ios::out);
	vector<player>::iterator it_player;
	for (it_player = all_player.begin();it_player != all_player.end();it_player++)
	{
		f_playerlist << it_player->show_name()<< ','
			         <<it_player->show_password()<<','
					 << it_player->show_level() << ','
					 << it_player->show_rank() << ','
					 << it_player->show_experience() << endl;
	}
}

void game::write_in_test_maker()//将出题者的信息写入文件
{
	fstream f_test_makerlist("test_makerlist.csv", ios::out);
	vector<test_maker>::iterator it_test_maker;
	for (it_test_maker = all_test_maker.begin(); it_test_maker != all_test_maker.end(); it_test_maker++)
	{
		f_test_makerlist << it_test_maker->show_name() << ',' 
			             << it_test_maker->show_password() << ',' 
			             << it_test_maker->show_level() << ',' 
			             << it_test_maker->show_test_num() << ','
			             << it_test_maker->show_experience() << endl;
	}
}
