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









#include<windows.h>
#define    WIN32_LEAN_AND_MEAN

using std::vector;
#define false 0
#define true 1

int choice = 0;    //һ��ȫ�ֵ�����ʾ�û������ѡ��



vector<packet> all_player; //���д�����
vector<string>all_online_player;  //�������ߵĴ�����
vector<string> all_online_test_maker; //�������ߵĳ�����
vector<packet> all_test_maker;//���г�����
player cur_player;//��ǰ�Ĵ�����
test_maker cur_test_maker; //��ǰ������
vector<string> all_words; //�������



int main()
{
	SetConsoleTitle(L"����������Ϸ"); // ���ô��ڱ���

	//�����׽��ֿ⣬�����׽���
	WORD sockVerson = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVerson, &wsaData) != 0)
		return 0;

	//�����ͻ���socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("�׽��ִ���ʧ��");
		WSACleanup();
		return 0;
	}


	//�������������������
	//����Ҫ���ӵķ�������ַ

	sockaddr_in addrConServer;
	addrConServer.sin_family = AF_INET;
	addrConServer.sin_port = htons(8888);
	addrConServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(clientSocket, (SOCKADDR*)& addrConServer, sizeof(addrConServer)) == SOCKET_ERROR)
	{
		printf("�ͻ��˽�������ʧ�ܣ�\n");
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	else
		printf("�ͻ��˽������ӳɹ���׼���������ݣ�\n");
	//int connect(SOCKET s, const struct sockaddr * name, int namelen);

	//���������ڴ�����ָ���ⲿ�˿ڵ����ӣ����������׽ӿڣ�SOCK_STREAM���ͣ���

	//������������һ��Զ�������������ӣ�һ���׽ӿڵ��óɹ����أ��������շ������ˡ�

	//�������ݱ����׽ӿڣ�SOCK_DGRAM���ͣ��������ó�һ��ȱʡ��Ŀ�ĵ�ַ�������������к�����send()��recv()���á�

	game word_match;//��ʼһ����Ϸ
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
		if (choice1_1 == 1 || choice1_1 == 2)
		{
			char which = 'a';
			send(clientSocket, &which, 1, 0);//������Ϣ
		}

		if (choice1_1 == 1)  //ע�ᴳ����
		{
			player new_player;// ����һ���µĴ�����
			new_player.sign_in();//������ע��


			word_match.sign_in_success();//ע��ɹ������ڣ������game.cpp
			/*
			char which =  'a' ;
			send(clientSocket, &which, 1, 0);//������Ϣ

			packet a_player_data(SIGN_IN_FOR_PLAYER,new_player.show_name(),new_player.show_password(), 0, 1, 0);
			char send_buf[SIZE];
			memset(send_buf, 'z', SIZE);//��ջ���
			memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
			send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ*/

			goto part; //�ص�ע���¼����
		}
		else if (choice1_1 == 2) //ע�������
		{
			test_maker new_test_maker; //����һ���µĳ�����;
			new_test_maker.sign_in();//������ע��
			word_match.sign_in_success(); //ע��ɹ������ڣ������game.cpp
			/*
			char which =  'a' ;
			send(clientSocket, &which, 1, 0);//������Ϣ

			packet a_test_maker_data(SIGN_IN_FOR_TEST_MAKER,new_test_maker.show_name(), new_test_maker.show_password(), 0, 1, 0);
			char send_buf[SIZE];
			memset(send_buf, 'z', SIZE);//��ջ���
			memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
			send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ*/

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
		if (choice2_1 == 1 || choice2_1 == 2)
		{
			char which = 'a';
			send(clientSocket, &which, 1, 0);//������Ϣ
		}
		if (choice2_1 == 1) //�����ߵ�¼
		{
			player  new_player; //�������������
			new_player.sign_up(); //�����ߵ�¼
			if (choice == 1) //����û������ھ���ע��
				goto part;  //�ص�ע���¼����
			else
			{
				word_match.sign_up_success(); //��¼�ɹ������ڣ������game.cpp
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
	else if (choice1 == 3) //�˳���Ϸ
	{
		//�ر��׽��֣��رռ��ص��׽��ֿ�
		char which = 'c';
		send(clientSocket, &which, 1, 0);//������Ϣ
		closesocket(clientSocket);
		WSACleanup();

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
	else if (choice_player == 2) //��ѯ��ǰ�������
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_player_data(WATCH_ONLINE_PLAYER, temp, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		words rev_all_player_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//��սṹ��
		memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//�ѽ��յ�����Ϣת���ɽṹ��

		cout << "��ǰ���ߵĴ�����" << endl;
		for (int i = 0; i < rev_all_player_size.operate; i++)  //���������е������Ϣ��������
		{
			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��
			cout << rev_a_player_data.name << endl;
		}
		goto player_start; //�ص�������ҳ��
	}
	else if (choice_player == 3) //��ѯ������
	{
		word_match.player_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 4) //��ѯ������
	{
		word_match.test_maker_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 5) //���а�
	{
		word_match.see_player_rank();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto player_start; //�ص�������ҳ��
		}
	}
	else if (choice_player == 6)  //�˳���¼
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_player_data(PLAYER_LOG_OUT, cur_player.show_name(), temp, cur_player.show_experience(), cur_player.show_level(), cur_player.show_rank());
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

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
	else if (choice_test_maker == 2)
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_test_maker_data(WATCH_ONLINE_TEST_MAKER, temp, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//��սṹ��
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//�ѽ��յ�����Ϣת���ɽṹ��


		cout << "��ǰ���ߵĳ�����" << endl;
		for (int i = 0; i < rev_all_test_maker_size.operate; i++)  //���������е������Ϣ��������
		{
			packet rev_a_test_maker_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
			memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
			memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��
			cout << rev_a_test_maker_data.name << endl;
		}
		goto test_maker_start; //�ص�������ҳ��
	}
	else if (choice_test_maker == 3) //��ѯ������
	{
		word_match.player_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 4) //��ѯ������
	{
		word_match.test_maker_search();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 5) //���а�
	{
		word_match.see_test_maker_rank();
		if (choice == 0) //����Ϸ��ѡ���˷������˵�
		{
			goto test_maker_start; //�ص�������ҳ��
		}
	}
	else if (choice_test_maker == 6)  //�˳���¼
	{
		char which = 'a';
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_test_maker_data(TEST_MAKER_LOG_OUT, cur_test_maker.show_name(), temp, cur_test_maker.show_experience(), cur_test_maker.show_level(), cur_test_maker.show_test_num());
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		goto part;
	}
	else
	{
		word_match.wrong();// �������
		goto test_maker_start;  //�������ȥ������ҳ��
	}

}



void player::sign_in() //������ע��,������a�Ѿ�����ʼ��
{
	
part1:
	string temp_name, temp_passwords;
	cout << "������ע�ᣡ" << endl;
	cout << "�����봳�����û���(���ܳ���15���ַ�):";
	cin >> temp_name;
	while (temp_name.empty() || temp_name.size() > 15)   //����ַ���Ϊ��
	{
		cout << "�û������Ϻ��淶��" << endl;
		cout << "����������:";
		cin >> temp_name; //��������ֱ����Ϊ��
	}
	cout << "����������(���ܳ���15���ַ�):";
	cin >> temp_passwords;
	while (temp_passwords.empty() || temp_passwords.size() > 15)   //����ַ���Ϊ��
	{
		cout << "���벻�Ϻ��淶��" << endl;
		cout << "����������:";
		cin >> temp_passwords; //��������ֱ����Ϊ��
	}

	packet a_player_data(SIGN_IN_FOR_PLAYER, temp_name, temp_passwords, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

	cout << "�Ѿ�����packet" << endl;

	char judge;
	recv(clientSocket, &judge, 1, 0);

	if (judge == 'r')
	{
		cout << "�ô������Ѵ��ڣ�������ע��";
		goto part1;
	}
	else
	{
		cout << "ע��ɹ���" << endl;
		
	}
}
void player::sign_up()
{
	string temp_name, temp_passwords;
	cout << "��ӭ��¼��" << endl;
	cout << "�����봳�����û���:";
	cin >> temp_name;
	cout << "����������:";
	cin >> temp_passwords;


	packet a_player_data(SIGN_UP_FOR_PLAYER, temp_name, temp_passwords, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

	char rev_temp;
	recv(clientSocket, &rev_temp, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־

	if (rev_temp == 'a')//��½�ɹ�
	{
		packet rev_a_player_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
		memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��

		this->experience = rev_a_player_data.experiences;
		this->level = rev_a_player_data.level;
		this->rank = rev_a_player_data.rank_or_test_num;

		
	    cur_player.name= rev_a_player_data.name;
		cur_player.passwords = rev_a_player_data.passwords;
		cur_player.experience = rev_a_player_data.experiences;
		cur_player.level = rev_a_player_data.level;
		cur_player.rank= rev_a_player_data.rank_or_test_num;
	}
	else  //ʧ��
	{
		cout << "�������û������������" << endl;;
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
player::player(const player& a)   //�������캯��
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
void player::upgrade(int play_level)  //������������vector<player>��ԭ������Ϊ��ǰ���cur_player�Ǹ����͵�
{																  //�ڶ����������������Ѷ�
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
	if (cur_player.experience <= cur_player.level * 100)
	{
		int add_experience = (int)(20000 / (play_end - play_start)); //ǿ������ת��,ע��play_end��play_start��msΪ��λ 40/1/1000=40000
		add_experience += play_level * 5;
		cur_player.experience += add_experience;  //���Ӿ���ֵ�ɹؿ��ѶȺʹ���ʱ�乲ͬ����
		cout << "��ϲ�����" << add_experience << "�㾭��ֵ" << endl;
		cout << play_end << "            " << play_start << endl;
	}

	if (cur_player.experience > cur_player.level * 100)
	{
		//cout << it->experience << "***" << it->level << "***" << endl;
		cur_player.level++;
		cout << "��ϲ������" << cur_player.level << "��" << endl;
		//it->experience %= it->level * 100;
	}
	cur_player.rank++;//�����ؿ�������
	//cout << it->name << "  *  " << it->passwords << "  *  " << it->level << "  *  " << it->rank << "  *  " << it->experience << endl;
}

void test_maker::sign_in()
{
	
part1:
	string temp_name, temp_pass;
	cout << "������ע�ᣡ" << endl;
	cout << "������������û���(���ܳ���15���ַ�):";
	cin >> temp_name;
	while (temp_name.empty() || temp_name.size() > 15)   //����ַ���Ϊ��
	{
		cout << "�û������Ϻ��淶��" << endl;
		cout << "����������:";
		cin >> temp_name; //��������ֱ����Ϊ��
	}

	cout << "����������(���ܳ���15���ַ�):";
	cin >> temp_pass;
	while (temp_pass.empty() || temp_pass.size() > 15)   //����ַ���Ϊ��
	{
		cout << "���벻�Ϻ��淶��" << endl;
		cout << "����������:";
		cin >> temp_pass; //��������ֱ����Ϊ��
	}
	cout << "ע��ɹ���" << endl;


	packet a_test_maker_data(SIGN_IN_FOR_TEST_MAKER, temp_name, temp_pass, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


	char judge;
	recv(clientSocket, &judge, 1, 0);

	if (judge == 'r')
	{
		cout << "�ó������Ѵ��ڣ�������ע��";
		goto part1;
	}
	else
	{
		cout << "ע��ɹ���" << endl;
		return;
	}

}
void test_maker::sign_up()
{
	
	string test_maker_name, test_maker_passwords;
	cout << "��ӭ��¼��" << endl;
	cout << "������������û���:";
	cin >> test_maker_name;
	cout << "����������:";
	cin >> test_maker_passwords;

	packet a_test_maker_data(SIGN_UP_FOR_TEST_MAKER, test_maker_name, test_maker_passwords, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

	char rev_temp;
	recv(clientSocket, &rev_temp, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־

	if (rev_temp == 'a')
	{
		packet rev_a_test_maker_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
		memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��

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
		cout << "�������û������������" << endl;;
		choice = 1;//  �����߲�����Ҫ�ص�ע�����
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
void test_maker::upgrade()//������������������vector<test_maker>��ԭ������Ϊ��ǰ���cur_test_maker�Ǹ����͵�
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
		cout << "��ϲ������" << cur_test_maker.level << "��" << endl;
		//it->experience %= it->level * 100;
	}
	cur_test_maker.test_num++;//�����ؿ�������
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
	cout << "*                                          2 �鿴��ǰ����                                              *" << endl;
	cout << "*                                          3 ��ѯ������                                                *" << endl;
	cout << "*                                          4 ��ѯ������                                                *" << endl;
	cout << "*                                          5 ���а�                                                    *" << endl;
	cout << "*                                          6 �˳���¼                                                  *" << endl;
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
void game::show_player_search_rank()
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                       ��       ��       ��                                           *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �ȼ�                                                      *" << endl;
	cout << "*                                          2 ͨ���ؿ���                                                *" << endl;
	cout << "*                                          3 ����ֵ                                                    *" << endl;
	cout << "*                                          4 �������˵�                                                *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "********************************************************************************************************" << endl;

}
void game::show_test_maker_search_rank() //���а�ҳ��
{
	cout << "********************************************************************************************************" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                     ��       ��       ��                                             *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �ȼ�                                                      *" << endl;
	cout << "*                                          2 ������Ŀ                                                  *" << endl;
	cout << "*                                          3 ����ֵ                                                    *" << endl;
	cout << "*                                          4 �������˵�                                                *" << endl;
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
	cout << "*                                             ���˵�                                                   *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                                                                                      *" << endl;
	cout << "*                                          1 �����´�                                                  *" << endl;
	cout << "*                                          2 �鿴��ǰ����                                              *" << endl;
	cout << "*                                          3 ��ѯ������                                                *" << endl;
	cout << "*                                          4 ��ѯ������                                                *" << endl;
	cout << "*                                          5 ���а�                                                    *" << endl;
	cout << "*                                          6 �˳���¼                                                  *" << endl;
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

		char which=  'a' ;
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_player_data(SEARCH_PLAYER_NAME, search_player_name, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		words rev_all_player_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//��սṹ��
		memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//�ѽ��յ�����Ϣת���ɽṹ��

		

		if (rev_all_player_size.operate == 0)
		{
			cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
		}
		else
		{
			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��

			cout << "�ô�������Ϣ���£�" << endl;
			cout.width(10);
			cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
			cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
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

		char which=  'a' ;
		send(clientSocket, &which, 1, 0);//������Ϣ
		string temp;
		packet a_player_data(SEARCH_PLAYER_LEVEL, temp, temp, 0, search_player_level, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


		words rev_all_player_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//��սṹ��
		memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//�ѽ��յ�����Ϣת���ɽṹ��


		if (rev_all_player_size.operate == 0)
		{
			cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
		}
		else
		{

			cout << "�ô�������Ϣ���£�" << endl;
			cout.width(10);
			cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
			//cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
			for (int i = 0; i < rev_all_player_size.operate; i++)
			{
				packet rev_a_player_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//��ջ���
				recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
				memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
				memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��
				cout.width(10);
				cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
			}
		}

		goto main_part;
	}
	else if (search_choice == 3)  //ѡ���ѯ������ͨ���ؿ���
	{
	int search_player_rank;
	cout << "������ô����߹ؿ���:" << endl;


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

	char which =  'a' ;
	send(clientSocket, &which, 1, 0);//������Ϣ
	string temp;
	packet a_player_data(SEARCH_PLAYER_RANK, temp, temp, 0, 1, search_player_rank);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


	words rev_all_player_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//��ջ���
	recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
	memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//��սṹ��
	memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//�ѽ��յ�����Ϣת���ɽṹ��


	if (rev_all_player_size.operate == 0)
	{
		cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
	}
	else
	{

		cout << "�ô�������Ϣ���£�" << endl;
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		//cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		for (int i = 0; i < rev_all_player_size.operate; i++)
		{

			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��
			cout.width(10);
			cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		}
	}

	goto main_part;
	}
	else if (search_choice == 4)  //ѡ���ѯ�����߾���ֵ
	{
	int search_player_experiences;
	cout << "������ô����߾���ֵ:" << endl;


	cin >> search_player_experiences;
	while (cin.fail())  //������ƣ�����������Ͳ�����
	{
		wrong();// �������
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}

		cin >> search_player_experiences;
	}

	char which =  'a' ;
	send(clientSocket, &which, 1, 0);//������Ϣ
	string temp;
	packet a_player_data(SEARCH_PLAYER_EXPERIENCES, temp, temp, search_player_experiences, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


	words rev_all_player_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//��ջ���
	recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
	memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//��սṹ��
	memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//�ѽ��յ�����Ϣת���ɽṹ��


	if (rev_all_player_size.operate == 0)
	{
		cout << "δ�ҵ�ƥ��Ĵ�����" << endl;
	}
	else
	{

		cout << "�ô�������Ϣ���£�" << endl;
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		//cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		for (int i = 0; i < rev_all_player_size.operate; i++)
		{

			packet rev_a_player_data;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
			memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
			memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��
			cout.width(10);
			cout << rev_a_player_data.name << "\t\t" << rev_a_player_data.level << "\t\t" << rev_a_player_data.rank_or_test_num << "\t\t" << rev_a_player_data.experiences << endl;
		}
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

void game::see_player_rank()
{
	

	char which= 'a' ;
	send(clientSocket, &which, 1, 0);//������Ϣ

	string temp;
	packet a_player_data(RANK_FOR_PLAYER, temp, temp, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


	words rev_all_player_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//��ջ���
	recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
	memset(&rev_all_player_size, 0, sizeof(rev_all_player_size));//��սṹ��
	memcpy(&rev_all_player_size, recv_buf, sizeof(rev_all_player_size));//�ѽ��յ�����Ϣת���ɽṹ��

	for (int i = 0; i < rev_all_player_size.operate; i++)  //���������е������Ϣ��������
	{
		packet rev_a_player_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_a_player_data, 0, sizeof(rev_a_player_data));//��սṹ��
		memcpy(&rev_a_player_data, recv_buf, sizeof(rev_a_player_data));//�ѽ��յ�����Ϣת���ɽṹ��
		all_player.push_back(rev_a_player_data); 
	}

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
		std::sort(all_player.begin(), all_player.end(), comp_level);

	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_rank_or_test_num);
	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "ͨ���ؿ���" << "\t\t" << "����ֵ" << endl;
		std::sort(all_player.begin(), all_player.end(), comp_experiences);
	}
	else if (see_which_element == 4)
	{
		choice = 0; //�������˵�
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<packet>::iterator it = all_player.begin(); it != all_player.end(); it++)  //������а�
	{
		cout.width(10);
		cout << it->name<< "\t\t" << it->level << "\t\t" << it->rank_or_test_num<< "\t\t\t" << it->experiences << endl;
	}
	getchar();//�̻س�
	cout << "��Enter����" << endl;
	if (getchar() != NULL)
		goto main_part;
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
		cout << "������ó������û���:" << endl;


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

		char which =  'a' ;
		send(clientSocket, &which, 1, 0);//������Ϣ
		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_NAME, search_test_maker_name, temp, 0, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//��սṹ��
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//�ѽ��յ�����Ϣת���ɽṹ��


		
		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		else
		{

			cout << "�ó�������Ϣ���£�" << endl;
			cout.width(10);
			cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{
				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//��ջ���
				recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
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

		char which =  'a' ;
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_LEVEL, temp, temp, 0, search_test_maker_level, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//��սṹ��
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//�ѽ��յ�����Ϣת���ɽṹ��

	
		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		else
		{
			cout << "�ó�������Ϣ���£�" << endl;
			cout.width(10);
			cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{

				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//��ջ���
				recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
		}

		goto main_part;

	}
	else if (search_choice == 3)  //ѡ���ѯ�����߳�����Ŀ
	{
		int search_test_maker_test_num;
		cout << "������ó����߳�����Ŀ:" << endl;


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

		char which=  'a' ;
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_TEST_NUM, temp, temp, 0, 1, search_test_maker_test_num);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//��սṹ��
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//�ѽ��յ�����Ϣת���ɽṹ��

		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		else
		{

			cout << "�ô�������Ϣ���£�" << endl;
			cout.width(10);
			cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{
				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//��ջ���
				recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
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

		char which= 'a' ;
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		packet a_test_maker_data(SEARCH_TEST_MAKER_EXPERIENCES, temp, temp, search_test_maker_experience, 1, 0);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		words rev_all_test_maker_size;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//��սṹ��
		memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//�ѽ��յ�����Ϣת���ɽṹ��

		if (rev_all_test_maker_size.operate == 0)
		{
			cout << "δ�ҵ�ƥ��ĳ�����" << endl;
		}
		else
		{

			cout << "�ô�������Ϣ���£�" << endl;
			cout.width(10);
			cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
			//cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			for (int i = 0; i < rev_all_test_maker_size.operate; i++)
			{

				packet rev_a_test_maker_data;
				char recv_buf[SIZE];
				memset(recv_buf, 'z', SIZE);//��ջ���
				recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
				memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
				memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��
				cout.width(10);
				cout << rev_a_test_maker_data.name << "\t\t" << rev_a_test_maker_data.level << "\t\t" << rev_a_test_maker_data.rank_or_test_num << "\t\t" << rev_a_test_maker_data.experiences << endl;
			}
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

void game::see_test_maker_rank()
{
	

	char which =  'a' ;
	send(clientSocket, &which, 1, 0);//������Ϣ
	string temp;
	packet a_test_maker_data(RANK_FOR_TEST_MAKER, temp, temp, 0, 1, 0);
	char send_buf[SIZE];
	memset(send_buf, 'z', SIZE);//��ջ���
	memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
	send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

	words rev_all_test_maker_size;
	char recv_buf[SIZE];
	memset(recv_buf, 'z', SIZE);//��ջ���
	recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
	memset(&rev_all_test_maker_size, 0, sizeof(rev_all_test_maker_size));//��սṹ��
	memcpy(&rev_all_test_maker_size, recv_buf, sizeof(rev_all_test_maker_size));//�ѽ��յ�����Ϣת���ɽṹ��

	for (int i = 0; i < rev_all_test_maker_size.operate; i++)  //���������е������Ϣ��������
	{
		packet rev_a_test_maker_data;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_a_test_maker_data, 0, sizeof(rev_a_test_maker_data));//��սṹ��
		memcpy(&rev_a_test_maker_data, recv_buf, sizeof(rev_a_test_maker_data));//�ѽ��յ�����Ϣת���ɽṹ��
		all_test_maker.push_back(rev_a_test_maker_data);
	}



main_part:
	show_test_maker_search_rank();
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
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_level);

	}
	else if (see_which_element == 2)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_rank_or_test_num);
	}
	else if (see_which_element == 3)
	{
		cout.width(10);
		cout << "�û���" << "\t\t" << "�ȼ�" << "\t\t" << "������Ŀ" << "\t\t" << "����ֵ" << endl;
		std::sort(all_test_maker.begin(), all_test_maker.end(), comp_experiences);
	}
	else if (see_which_element == 4)
	{
		choice = 0; //�������˵�
		return;
	}
	else
	{
		wrong();
		goto main_part;
	}
	for (vector<packet>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++)  //������а�
	{
		cout.width(10);
		cout << it->name << "\t\t" << it->level<< "\t\t" << it->rank_or_test_num<< "\t\t\t" << it->experiences << endl;
	}
	getchar();//�̻س�
	cout << "��Enter����" << endl;
	if (getchar() != NULL)
		goto main_part;
}

void game::start_player_game()
{
	
	string input_word;
	
	int passed_level = 1; //��ǰ�Ѷȵȼ�
	int all_level = 4;  //����4���ȼ�
	int play_choice = -1;

	while (play_choice != 0)
	{
		cout << "�ܹ�" << all_level << "���ȼ�," << "��ǰ�Ѷȵȼ�:" << passed_level << endl;
		cout << "���ס������ʣ�3s����ʧ����" << endl;
		
		char which =  'b' ;
		send(clientSocket, &which, 1, 0);//������Ϣ

		string temp;
		words send_a_word(START_PLAYER_GAME, passed_level, temp);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &send_a_word, sizeof(send_a_word)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

		words rev_a_word;
		char recv_buf[SIZE];
		memset(recv_buf, 'z', SIZE);//��ջ���
		recv(clientSocket, recv_buf, SIZE, 0);//��ȡ����
		memset(&rev_a_word, 0, sizeof(rev_a_word));//��սṹ��
		memcpy(&rev_a_word, recv_buf, sizeof(rev_a_word));//�ѽ��յ�����Ϣת���ɽṹ��

		cout << rev_a_word.a_word;


		Sleep(3000 - passed_level * 200);  //�ȴ�3��,���ŵȼ����Ӽ���ʱ��

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
		if (input_word == rev_a_word.a_word)//��ȷ
		{
			cout << "���뵥����ȷ�����سɹ�\n";
			play_end = clock(); //���سɹ� ,��ʱ��ֹͣ
			/*���µȼ�������*/
			player::upgrade(passed_level); //��ǰ��ҼӾ���,�����ؿ�����,�����ѶȼӾ���
		}
		else//����
		{
			cout << "���뵥�ʴ��󣬴���ʧ��\t�ղ���ʾ�ĵ����ǣ�" << rev_a_word.a_word << endl;
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
			if (passed_level == all_level)
			{
				cout << "�Ѿ�������Ѷȣ�" << endl;
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

		char which= 'b' ;
		send(clientSocket, &which, 1, 0);//������Ϣ

		words send_a_word(ADD_NEW_WORDS, NULL, add_words);
		char send_buf[SIZE];
		memset(send_buf, 'z', SIZE);//��ջ���
		memcpy(send_buf, &send_a_word, sizeof(send_a_word)); //�ṹ��ת�����ַ���
		send(clientSocket, send_buf, sizeof(send_buf), 0);//������Ϣ



		vector<string>::iterator insert_words;
		insert_words = find(all_words.begin(), all_words.end(), add_words); //���Ҵʿ��Ƿ��иõ���

		char rev;
		recv(clientSocket, &rev, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־


		if (rev == 'r')//����ɹ�����:���ʲ�����
		{
			/*�����������޸ģ�������������ֵ���ȼ�*/
			test_maker::upgrade(); //��ǰ�����߼Ӿ���,������Ŀ����
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


