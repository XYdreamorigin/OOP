
#pragma once
#include"vector.h"
#include<windows.h>
#include<iostream>
#include<vector>

using std::vector;
#define false 0
#define true 1

int choice = 0;    //һ��ȫ�ֵ�����ʾ�û������ѡ��

using namespace std;

/*void SetPosition(short int x, short int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	getchar();
}*/
vector<player> all_player; //���д�����
vector<player>all_online_player;  //�������ߵĴ�����
vector<test_maker> all_test_maker;//���г�����
vector<player>::iterator cur_player;//��ǰ�Ĵ�����
vector<test_maker>::iterator cur_test_maker; //��ǰ������
vector<string> all_words; //�������



int main()
{
	
	SetConsoleTitle(L"����������Ϸ"); // ���ô��ڱ���
	game word_match;//��ʼһ����Ϸ
	word_match.read_all_words(); //�����е��ʴ��ļ����뵽all_words������
	word_match.read_all_player(); //�����д�������Ϣ���뵽all_palyer������
	word_match.read_all_test_maker();//�����г�������Ϣ���뵽all_test_maker������

part: // ע���¼����
	choice = 0;
	int choice1; //ע����ߵ�¼��ѡ��
	word_match.show_sign();//�����ڣ������game.cpp

	cin >> choice1;
	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		word_match.wrong();// �������
		cin.clear();
		while (cin.get() != '\n') 
		{
			continue;
		}
		word_match.show_sign();//�����ڣ������game.cpp
		cin >> choice1;
	}
	if (choice1 == 1)//ע��
	{
	//part1:  //ע�����
		int choice1_1;//ע�����͵�ѡ��
		//system("cls");
		word_match.show_sign_in_type();//�����ڣ������game.cp p
		//SetPosition(50, 20);
		cin >> choice1_1;
		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			word_match.wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			word_match.show_sign_in_type();//�����ڣ������game.cp p
			cin >> choice1_1;
		}

		if (choice1_1 == 1)  //ע�ᴳ����
		{
			player new_player;// ����һ���µĴ�����
			new_player.sign_in();//������ע��
			word_match.sign_in_success();//ע��ɹ������ڣ������game.cpp
			goto part; //�ص�ע���¼����
		}
		else if (choice1_1 == 2) //ע�������
		{
			test_maker new_test_maker; //����һ���µĳ�����;
			new_test_maker.sign_in();//������ע��
			word_match.sign_in_success(); //ע��ɹ������ڣ������game.cpp
			goto part;  //�ص�ע���¼����
		}
		else if (choice1_1 == 3) //����
		{
			goto part;  //�ص�ע���¼����
		}
		else
		{
			word_match.wrong();// �������
			goto part; //�ص�ע�����,��������
		}
	}
	else if (choice1 == 2) //��¼
	{
	part2: //��¼����
		int choice2_1;//��¼���͵�ѡ��
		word_match.show_sign_up_type();//�����ڣ������game.cpp
		cin >> choice2_1;

		while (cin.fail())  //������ƣ�����������Ͳ�����
		{
			word_match.wrong();// �������
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			word_match.show_sign_up_type();//�����ڣ������game.cp p
			cin >> choice2_1;
		}

		if (choice2_1 == 1) //�����ߵ�¼
		{
			player  new_player; //�������������
			new_player.sign_up(); //�����ߵ�¼
			if (choice == 1) //����û������ھ���ע��
				goto part;  //�ص�ע���¼����
			else
			{
				word_match.sign_up_success();//��¼�ɹ������ڣ������game.cpp
				//new_player = *cur_player;   //�ҵ�������ݸ���
			}
			goto player_start;  //��¼�ɹ���ȥ�������߿�ʼ��Ϸҳ��
		}
		else if (choice2_1 == 2) //�����ߵ�¼
		{
			test_maker new_test_maker; //�������������;
			new_test_maker.sign_up();//�����ߵ�¼
			if (choice == 1) //����û������ھ���ע��
				goto part;  //�ص�ע���¼����
			else
			{
				word_match.sign_up_success(); //��¼�ɹ������ڣ������game.cpp
				//new_test_maker = *cur_test_maker;//�ҵ�������ݸ���
			}
				
			goto test_maker_start;  //��¼�ɹ���ȥ�������߿�ʼ��Ϸҳ��
		}
		else if (choice2_1 == 3)
		{
			goto part;  //�ص�ע���¼����
		}
		else
		{
			word_match.wrong();// �������
			goto part2; //�ص���¼����,��������
		}
	}
	else if(choice1 == 3) //�˳���Ϸ
	{
		return 0;
	}
	else
	{
		word_match.wrong();// �������
		goto part;  //�ص�ע���¼����
	}

player_start:  //������ҳ��
	choice = -1; //�ȳ�ʼ��Ϊ-1
	word_match.player_main_menu(); //���������˵�

	int choice_player;  //������ѡ��
	cin >> choice_player;

	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		word_match.wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		word_match.player_main_menu(); //���������˵�
		cin >> choice_player;
	}


	if (choice_player == 1)  //���ѡ��ʼ��Ϸ
	{
		//player new_player = *cur_player;
		word_match.start_player_game(); //��ʼ��Ϸ
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 2) //��ѯ������
	{
		word_match.player_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 3) //��ѯ������
	{
		word_match.test_maker_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 4) //���а�
	{
		word_match.see_player_rank();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 5)  //�˳���¼
	{

		word_match.write_in_player();  //д��Ϣ
		goto part;
	}
	else
	{
		word_match.wrong();// �������
		goto player_start;  //�������ȥ������ҳ��
	}

test_maker_start:

	choice = -1; //�ȳ�ʼ��Ϊ-1
	word_match.test_maker_main_menu();// ��������ҳ��

	int choice_test_maker;  //������ѡ��
	cin >> choice_test_maker;

	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		word_match.wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		word_match.player_main_menu(); //���������˵�
		cin >> choice_test_maker;
	}

	if (choice_test_maker == 1)  //���ѡ��ʼ��Ϸ
	{
		//player new_player = *cur_player;
		word_match.start_test_maker_game(); //���ӵ���
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 2) //��ѯ������
	{
		word_match.player_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 3) //��ѯ������
	{
		word_match.test_maker_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 4) //���а�
	{
		word_match.see_test_maker_rank();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 5)  //�˳���¼
	{
		word_match.write_in_test_maker();  //д��Ϣ
		goto part;
	}
	else
	{
		word_match.wrong();// �������
		goto test_maker_start;  //�������ȥ������ҳ��
	}

}

