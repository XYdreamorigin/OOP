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
#include<ctime>   //��ʱ����Ҫ�Ŀ�
extern int choice;
using namespace std;

void player::sign_in() //������ע��,������a�Ѿ�����ʼ��
{
	part1:
		cout << "������ע�ᣡ" << endl;
		cout << "�����봳�����û���(���ܳ���15���ַ�):";
		cin >> name;
		while (name.empty() || name.size() > 15)   //����ַ���Ϊ��
		{
			cout << "�û������Ϻ��淶��" << endl;
			cout << "����������:";
			cin >> name; //��������ֱ����Ϊ��
		}

		bool player_exist = false; //�жϴ������Ƿ��Ѿ����ڵ�����
	
		for (vector<player>::iterator it=all_player.begin(); it!=all_player.end(); it++) //�жϴ������Ƿ��Ѿ�����
		{
			if (name == it->name)
			{
				player_exist = true;
				break;
			}
		}
		if (player_exist == false)//���������δ��ע���
		{
	
			cout << "����������(���ܳ���15���ַ�):";
			cin >> passwords;
			while (passwords.empty() || passwords.size() > 15)   //����ַ���Ϊ��
			{
				cout << "���벻�Ϻ��淶��" << endl;
				cout << "����������:";
				cin >> passwords; //��������ֱ����Ϊ��
			}
			cout << "ע��ɹ���" << endl;

			all_player.push_back(*this); //��ע����û���������������
			return;
		}
		else
		{
			cout << "�ô������Ѵ��ڣ�������ע��";
			goto part1;
		}

}

void player::sign_up()
{

	string player_name, player_passwords;
	cout << "��ӭ��¼��" << endl;
	cout << "�����봳�����û���:";
//part:
	cin >> player_name;

	bool player_exist = false; //�жϴ������Ƿ��Ѿ����ڵ�����

	//vector<player>::iterator temp_it = all_player.begin();
	for (cur_player = all_player.begin(); cur_player != all_player.end(); cur_player++) //�жϳ������Ƿ��Ѿ�����
	{
		if (player_name == cur_player->name)
		{
			player_exist = true;
			break;
		}
	}

	if (player_exist == true) //�����ߴ��ڣ���������
	{
		cout << "����������:";
		cin >> player_passwords;
		while (player_passwords != cur_player->passwords)
		{
			cout << "�������������,����������!";
			cin >> player_passwords;
		}
	}
	else   //�����߲�����
	{
		cout << "�����߲����ڣ�����ע��!" << endl;;
		choice = 1;//  �����߲�����Ҫ�ص�ע�����
		//goto part;
	}
}

player::player()
{
	experience = 0;
	level = 0;
	rank = 0;
}

player::player(const player &a)   //�������캯��
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

void player::upgrade(vector<player>::iterator it)  //������������vector<player>��ԭ������Ϊ��ǰ���cur_player�Ǹ����͵�
{
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
	if (it->experience <= it->level * 100)
	{
		int add_experience = (int)(40000 / (play_end - play_start)); //ǿ������ת��,ע��play_end��play_start��msΪ��λ 40/1/1000=40000
		add_experience += it->level * 5;
		it->experience += add_experience;  //���Ӿ���ֵ�ɹؿ��ѶȺʹ���ʱ�乲ͬ����
		cout << "��ϲ�����" << add_experience << "�㾭��ֵ" << endl;
		cout << play_end << "            " << play_start << endl;
	}
	
	if (it->experience > it->level * 100)
	{
		//cout << it->experience << "***" << it->level << "***" << endl;
		it->level++;
		cout << "��ϲ������" << it->level << "��" << endl;
		//it->experience %= it->level * 100;
	}
	it->rank++;//�����ؿ�������
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
}

void test_maker::sign_in()
{
part1:
	cout << "������ע�ᣡ" << endl;
	cout << "������������û���(���ܳ���15���ַ�):";
	cin >> name;
	while (name.empty() || name.size() > 15)   //����ַ���Ϊ��
	{
		cout << "�û������Ϻ��淶��" << endl;
		cout << "����������:";
		cin >> name; //��������ֱ����Ϊ��
	}

	bool test_maker_exist = false; //�жϳ������Ƿ��Ѿ����ڵ�����

	for (vector<test_maker>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++) //�жϳ������Ƿ��Ѿ�����
	{
		if (name == it->name)
		{
			test_maker_exist = true;
			break;
		}
	}
	if (test_maker_exist == false)//���������δ��ע���
	{

		cout << "����������(���ܳ���15���ַ�):";
		cin >> passwords;
		while (passwords.empty() || passwords.size() > 15)   //����ַ���Ϊ��
		{
			cout << "���벻�Ϻ��淶��" << endl;
			cout << "����������:";
			cin >> passwords; //��������ֱ����Ϊ��
		}
		cout << "ע��ɹ���" << endl;

		all_test_maker.push_back(*this); //��ע����û���������������
		return;
	}
	else
	{
		cout << "���û����Ѵ��ڣ�������ע��";
		goto part1;
	}

}

void test_maker::sign_up()
{

	string test_maker_name, test_maker_passwords;
	cout << "��ӭ��¼��" << endl;
	cout << "������������û���:";
//part:
	cin >> test_maker_name;

	bool test_maker_exist = false; //�жϴ������Ƿ��Ѿ����ڵ�����

	//vector<test_maker>::iterator it = all_test_maker.begin();
	for (cur_test_maker= all_test_maker.begin(); cur_test_maker != all_test_maker.end(); cur_test_maker++) //�жϳ������Ƿ��Ѿ�����
	{
		if (test_maker_name == cur_test_maker->name)
		{
			test_maker_exist = true;
			break;
		}
	}
	if (test_maker_exist == true) //�����ߴ��ڣ���������
	{
		cout << "����������:";
		cin >> test_maker_passwords;
		while (test_maker_passwords != cur_test_maker->passwords)
		{
			cout << "�������������,����������!";
			cin >> test_maker_passwords;
		}
	}
	else   //�����߲�����
	{
		cout << "�����߲����ڣ�����ע�ᣡ" << endl;
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

void test_maker::upgrade(vector<test_maker>::iterator it)//������������������vector<test_maker>��ԭ������Ϊ��ǰ���cur_test_maker�Ǹ����͵�
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
		cout << "��ϲ������" << it->level << "��" << endl;
		it->experience %= it->level * 100;
	}
	it->test_num++;//�����ؿ�������
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->test_num << "  *  " << it->experience << endl;
}


void game::show_sign()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                             ��ѡ��                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                         1 ע��              2 ��¼             3 �˳�                                *" << endl;
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
	cout << "*                                           ��ѡ��ע������                                             *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                         1 ������            2 ������           3 ����                                *" << endl;
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
	cout << "*                                           ��ѡ���¼����                                             *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                         1 ������            2 ������           3 ����                                *" << endl;
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
	cout << "*                                         ��ϲע��ɹ���                                               *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::sign_up_success()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                         ��ϲ��¼�ɹ���                                               *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::wrong()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                     �Ƿ����룬���������룡��                                         *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;
}
void game::passwords_wrong()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                     ����������������룡��                                         *" << endl;
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
	cout << "*                                             ���˵�                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 ��ʼ��Ϸ                                                  *" << endl;
	cout << "*                                          2 ��ѯ������                                                *" << endl;
	cout << "*                                          3 ��ѯ������                                                *" << endl;
	cout << "*                                          4 ���а�                                                    *" << endl;
	cout << "*                                          5 �˳���¼                                                  *" << endl;
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
	cout << "*                                       ѡ���ѯ�Ĵ���������                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �û���                                                    *" << endl;
	cout << "*                                          2 �ȼ�                                                      *" << endl;
	cout << "*                                          3 ͨ���ؿ���                                                *" << endl;
	cout << "*                                          4 ����ֵ                                                    *" << endl;
	cout << "*                                          5 �������˵�                                                *" << endl;
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

	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_player_search(); //�����߲�ѯҳ��
		cin >> search_choice;
	}

	if (search_choice == 1)  //ѡ���ѯ�û���
	{
		string search_player_name;
		cout << "������ô������û���:" << endl;
	

		cin >> search_player_name;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
		
			cin >> search_player_name;
		}
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_player)
		{
			if (search.show_name() == search_player_name)
			{
				if (time == 0)
				{
					cout << "�ô�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 2)  //ѡ���ѯ�û��ȼ�
	{
		int search_player_level;
		cout << "������ô����ߵȼ�:" << endl;
		cin >> search_player_level;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_player_level;
		}
		
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_player)
		{
			if (search.show_level() == search_player_level)
			{
				if (time == 0)
				{
					cout << "�ô�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 3)  //ѡ���ѯ������ͨ���ؿ���
	{
		int search_player_rank;
		cout << "������ô�����ͨ���ؿ���:" << endl;

		cin >> search_player_rank;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_player_rank;
		}
		
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_player)
		{
			if (search.show_rank() == search_player_rank)
			{
				if (time == 0)
				{
					cout << "�ô�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 4)  //ѡ���ѯ�����߾���ֵ
	{
		int search_player_experience;
		cout << "������ô����߾���ֵ:" << endl;

		cin >> search_player_experience;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_player_experience;
		}
		
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_player)
		{
			if (search.show_experience() == search_player_experience)
			{
				if (time == 0)
				{
					cout << "�ô�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_rank() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 5)  //ѡ�񷵻����˵�
	{
		choice = 0;
	}
	else
	{
		cout << "�������" << endl;
		goto main_part;
	}

}
void game::show_player_search_rank()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                       ��       ��       ��                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �û���                                                    *" << endl;
	cout << "*                                          2 �ȼ�                                                      *" << endl;
	cout << "*                                          3 ͨ���ؿ���                                                *" << endl;
	cout << "*                                          4 ����ֵ                                                    *" << endl;
	cout << "*                                          5 �������˵�                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;

}
void game::see_player_rank()
{
main_part:

	show_player_search_rank();
	int see_which_element; //����ʲô���У�
	cin >> see_which_element;
	
	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_player_search_rank(); //����ʲô����ҳ��
		cin >> see_which_element;
	}

	if (see_which_element == 1)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		std::sort(all_player.begin(), all_player.end(),comp_name_player);
	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_level_player);
		
	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_rank_player);
	}
	else if (see_which_element == 4)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_experience_player);
	}
	else if (see_which_element == 5)
	{
		choice = 0; //�������˵�
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<player>::iterator it = all_player.begin(); it != all_player.end(); it++)  //������а�
	{
		cout.width(10);
		cout << it->show_name() << "\t\t" << it->show_level() << "\t\t" << it->show_rank() <<"\t\t\t" << it->show_experience() << endl;
	}
	getchar();//�̻س�
	cout << "��Enter����" << endl;
	if (getchar() != NULL)
		goto main_part;
}
void game::test_maker_main_menu()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                             ���˵�                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �����´�                                                  *" << endl;
	cout << "*                                          2 ��ѯ������                                                *" << endl;
	cout << "*                                          3 ��ѯ������                                                *" << endl;
	cout << "*                                          4 ���а�                                                    *" << endl;
	cout << "*                                          5 �˳���¼                                                  *" << endl;
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
	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_test_maker_search(); //�����߲�ѯҳ��
		cin >> search_choice;
	}

	if (search_choice == 1)  //ѡ���ѯ�û���
	{
		string search_test_maker_name;
		cout << "������ô������û���:" << endl;

		cin >> search_test_maker_name;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_test_maker_name;
		}
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_test_maker)
		{
			if (search.show_name() == search_test_maker_name)
			{
				if (time == 0)
				{
					cout << "�ó�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 2)  //ѡ���ѯ�û��ȼ�
	{
		int search_test_maker_level;
		cout << "������ó����ߵȼ�:" << endl;

		cin >> search_test_maker_level;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_test_maker_level;
		}
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_test_maker)
		{
			if (search.show_level() == search_test_maker_level)
			{
				if (time == 0)
				{
					cout << "�ô�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		goto main_part;
	
	}
	else if (search_choice == 3)  //ѡ���ѯ������ͨ���ؿ���
	{
		int search_test_maker_test_num;
		cout << "������ó�����ͨ���ؿ���:" << endl;

		cin >> search_test_maker_test_num;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_test_maker_test_num;
		}
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_test_maker)
		{
			if (search.show_test_num() == search_test_maker_test_num)
			{
				if (time == 0)
				{
					cout << "�ó�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 4)  //ѡ���ѯ�����߾���ֵ
	{
		int search_test_maker_experience;
		cout << "������ó����߾���ֵ:" << endl;
		cin >> search_test_maker_experience;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cin >> search_test_maker_experience;
		}
		int time = 0, judge = 0;//ֻ���һ�α�ͷ���ж��Ƿ��ҵ��ı�־
		for (auto search : all_test_maker)
		{
			if (search.show_experience() == search_test_maker_experience)
			{
				if (time == 0)
				{
					cout << "�ó�������Ϣ���£�" << endl;
					cout.width(10);
					cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
					time++;
				}
				cout.width(10);
				cout << search.show_name() << "\t\t" << search.show_level() << "\t\t" << search.show_test_num() << "\t\t\t" << search.show_experience() << endl;
				judge = 1;
			}
		}
		if (judge == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		goto main_part;
	}
	else if (search_choice == 5)  //ѡ�񷵻����˵�
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
	cout << "*                                       ѡ���ѯ�ĳ���������                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �û���                                                    *" << endl;
	cout << "*                                          2 �ȼ�                                                      *" << endl;
	cout << "*                                          3 ������Ŀ                                                  *" << endl;
	cout << "*                                          4 ����ֵ                                                    *" << endl;
	cout << "*                                          5 �������˵�                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;

}
void game::see_test_maker_rank()
{
main_part:
	show_test_maker_search();
	int see_which_element; //����ʲô���У�
	cin >> see_which_element;

	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		show_test_maker_search(); //�����߲�ѯҳ��
		cin >> see_which_element;
	}

	if (see_which_element == 1)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_name_test_maker);
	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_level_test_maker);

	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_test_num_test_maker);
	}
	else if (see_which_element == 4)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_experience_test_maker);
	}
	else if (see_which_element == 5)
	{
		choice = 0; //�������˵�
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<test_maker>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++)  //������а�
	{
		cout.width(10);
		cout << it->show_name() << "\t\t" << it->show_level() << "\t\t" << it->show_test_num() << "\t\t\t" << it->show_experience() << endl;
	}
	getchar();//�̻س�
	cout << "��Enter����" << endl;
	if (getchar() != NULL)
		goto main_part;
}

void game::read_all_words()
{
	fstream f_wordlist("wordlist.csv", ios::in); //���ļ�       ios::in �ļ������뷽ʽ��(�ļ��������뵽�ڴ�) 
	if (!f_wordlist)  //���ļ�ʧ��
	{
		cout << "�޷����ļ�wordlist" << endl;
		return;
	}
	//f_wordlist.seekg(0, fstream::beg);  
	string word;
	while (!f_wordlist.eof())   //���û�ж����ļ�ĩβ
	{
		getline(f_wordlist, word); //��f_wordlist ��ȡһ�У���Ϊ�洢ʱһ��ֻ�洢��һ�����ʣ����Զ�ȡһ�о��Ƕ�ȡһ������
		all_words.push_back(word);  //��������ʴ��뵽vector<string> all_words��
	}
	//f_wordlist����ʱ�ļ��Զ��ر�
}

void game::read_all_player()
{
	fstream f_playerlist("playerlist.csv", ios::in); //���ļ�
	if (!f_playerlist) //���ļ�ʧ��
	{
		cout << "�޷����ļ�playerlist" << endl;
		return;
	}

	string line, line_part; //����һ���ַ�����ȡһ�У�һ���ַ�����ȡһ����ĳһ�Σ�ȡ������Ϣ�洢�ķ�ʽ  name , passwords ,experience , level, rank
	string name, passwords;
	int experience, level, rank;
	while (getline(f_playerlist, line))//��ȡһ��
	{
		stringstream line_sin(line); ////�������ַ���line���뵽�ַ�����line_sin��,�ú���������ͷ�ļ�#include<sstream>��


		//��ȡ�ļ����Ҳû̫����
		getline(line_sin, name, ',');//�ַ���������','ֹͣ����֮ǰ���ַ�������name

		getline(line_sin, passwords, ',');//�ַ���������','ֹͣ����֮ǰ���ַ�������passwords
		line_sin >> level;
		getline(line_sin, line_part, ',');
		line_sin >> rank;   //Ϊʲô��ֱ�Ӹ�ֵ��int����?��Ϊͨ��stringstream�����ʵ���ַ���ת��
		getline(line_sin, line_part, ',');
		line_sin >> experience;
		getline(line_sin, line_part);
		//cout << name << "*	" << passwords << " *  " << level << " *  " << rank << "*  " << experience << "**" << endl;
		player temp_player(name, passwords, experience, level, rank);//���ļ���ȡ�����ݴ���һ������������
		all_player.push_back(temp_player); //�������Ҵ���all_player������
	}
}

void game::read_all_test_maker()
{
	fstream f_test_makerlist("test_makerlist.csv", ios::in); //���ļ�
	if (!f_test_makerlist) //���ļ�ʧ��
	{
		cout << "�޷����ļ�test_makerlist" << endl;
		return;
	}

	string line, line_part; //����һ���ַ�����ȡһ�У�һ���ַ�����ȡһ����ĳһ�Σ�ȡ������Ϣ�洢�ķ�ʽ  name , passwords ,experience , level, rank
	string name, passwords;
	int experience, level, test_num;
	while (getline(f_test_makerlist, line)) //��ȡһ��
	{
		
		stringstream line_sin(line); ////�������ַ���line���뵽�ַ�����line_sin��,�ú���������ͷ�ļ�#include<sstream>��

		getline(line_sin, name, ',');
		
		getline(line_sin, passwords, ',');
		line_sin >> level;
		getline(line_sin, line_part, ',');
		line_sin >> test_num;   
		getline(line_sin, line_part, ',');
		line_sin >> experience;
		line_sin >> test_num;

		//cout << name << "*	" << passwords << " *  " << level << " *  " << test_num << "*  " << experience << "**" << endl;
		test_maker temp_test_maker(name, passwords, experience, level, test_num);//���ļ���ȡ�����ݴ���һ������������
		all_test_maker.push_back(temp_test_maker); //�������Ҵ���all_player������
	}
}

void game::start_player_game()
{
	srand((unsigned)time(NULL));
	string input_word;
	int wordlist_size = all_words.size();//��ôʿ��С��������Ѷ�
	int passed_level = 1; //��ǰ�Ѷȵȼ�
	int all_level = 10;
	int play_choice = -1;
	int loc;  //�ڴʿ��еĵڼ�������
	while (play_choice != 0)
	{
		cout << "�ܹ�" << all_level << "���ȼ�," << "��ǰ�Ѷȵȼ�:" << passed_level << endl;
		cout << "���ס������ʣ�3s����ʧ����" << endl;
		//Ҫȡ��[a,b)�����������ʹ��(rand() % (b-a))+ a; 
		loc = (rand() % ((wordlist_size / all_level) * (passed_level)-(wordlist_size / all_level) * (passed_level - 1))) + (wordlist_size / all_level) * (passed_level - 1);
		cout << loc << "*******************" << endl;
		cout << all_words.at(loc); //����������

		Sleep(3000-passed_level*200);  //�ȴ�3��,���ŵȼ����Ӽ���ʱ��

		cout << "\r                                                            ";
		//system("cls");  //����
		cout << "\r������ղų��ֵĵ��ʣ�";
		//cin.clear();
		//cin.ignore(5, '\n');//�����������з����������е���������
		play_start = clock(); //��ʱ����ʼ��ʱ
		cin >> input_word;

		if (cin.fail())
		{
			cout << "��������!" << endl;
			cin.clear();
			cin.ignore(99999, '\n');//�����������з����������е���������
			continue;
			play_end = clock(); // ��������ʱ��ֹͣ
		}
		if (input_word == all_words.at(loc))//��ȷ
		{
			cout << "���뵥����ȷ�����سɹ�\n";
			play_end = clock(); //���سɹ� ,��ʱ��ֹͣ
			/*���µȼ�������*/
			player::upgrade(cur_player); //��ǰ��ҼӾ���,�����ؿ�����
		}
		else//����
		{
			cout << "���뵥�ʴ��󣬴���ʧ��\t�ղ���ʾ�ĵ����ǣ�" << all_words.at(loc) << endl;
			play_end = clock(); // ��������ʱ��ֹͣ
		}
	part:
		cout << "0�������˵�  1�������Ѷ�  2 ��һ�Ѷ� " << endl;;
		cin >> play_choice;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cout << "0�������˵�  1�������Ѷ�  2 ��һ�Ѷ� " << endl;
			cin >> play_choice;
		}

		if (play_choice == 0)
		{
			choice = 0; //����ȫ�ֵ�ѡ���һ����־��֮���������н��д���
		}
		else if (play_choice == 2) //ѡ����һ�Ѷ����Ѷ�����
		{
			if (passed_level == 10)
			{
				cout << "�Ѿ�������Ѷȣ�" << endl;
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
			//����д��˳���������
		}

	}
}

void game::start_test_maker_game()//��ʼһ�������ߵ���Ϸ;
{
	string add_words;
	int play_choice = -1;
	while (play_choice != 0)
	{
		cout << "������Ҫ��ӵĵ���" << endl;
		cin >> add_words;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cout << "������Ҫ��ӵĵ���" << endl;
			cin >> add_words;
		}
		vector<string>::iterator insert_words;
		insert_words = find(all_words.begin(), all_words.end(), add_words); //���Ҵʿ��Ƿ��иõ���

		if (insert_words == all_words.end())//����ɹ�����:���ʲ�����
		{

			all_words.push_back(add_words);
			std::sort(all_words.begin(), all_words.end(), comp_string);
			/*д���ļ�*/
			fstream f_wordlist("wordlist.csv", ios::out);
			if (!f_wordlist)
			{
				cout << "�޷����ļ�wordlist.csv" << endl;
				return;
			}
			int len = all_words.size();
			for (int i = 0; i < len; i++)
			{
				f_wordlist << all_words[i] << endl;  //��Ϊvector������[ ]�������������ֱ�Ӱ��������������ˣ���Ȼ������vector�ĵ�����iterator���ʡ�
													//	ֻ�����õ����������ᱨ��������
			}

			/*�����������޸ģ�������������ֵ���ȼ�*/
			test_maker::upgrade(cur_test_maker); //��ǰ�����߼Ӿ���,������Ŀ����
		}
		else
		{
			cout << "�õ����Ѵ���\n";
		}
	part:
		cout << "0�������˵�  1������ӵ��� " << endl;
		cin >> play_choice;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			//show_test_maker_search(); //�����߲�ѯҳ��
			cout << "0�������˵�  1������ӵ��� " << endl;
			cin >> play_choice;
		}
		if (play_choice == 0)
		{
			choice = 0; //����ȫ�ֵ�ѡ���һ����־��֮���������н��д���
		}
		else if (play_choice != 0 && play_choice != 1)  //���벻���ڵ�ѡ������
		{
			wrong();
			goto part;
		}
		else
		{
			 //˳��ִ�У�����������
		}
	}
}

void game::write_in_player() //�������ߵ���Ϣд���ļ�
{
	/*дplayer*/
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

void game::write_in_test_maker()//�������ߵ���Ϣд���ļ�
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
