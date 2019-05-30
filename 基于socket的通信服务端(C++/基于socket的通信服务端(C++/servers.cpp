#include"servers.h"
using namespace std;
void read_all_words()
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
void read_all_player()
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
		user temp_player(name, passwords, experience, level, rank);//���ļ���ȡ�����ݴ���һ������������
		all_player.push_back(temp_player); //�������Ҵ���all_player������
	}
}
void read_all_test_maker()
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
		user temp_test_maker(name, passwords, experience, level, test_num);//���ļ���ȡ�����ݴ���һ������������
		all_test_maker.push_back(temp_test_maker); //�������Ҵ���all_player������
	}
}
static bool comp_string(string a, string b) { return a.length() < b.length(); } //�Ƚ��ַ�������
void write_in_player() //�������ߵ���Ϣд���ļ�
{
	/*дplayer*/
	fstream f_playerlist("playerlist.csv", ios::out);
	vector<user>::iterator it_player;
	string temp = "test1";
	for (it_player = all_player.begin(); it_player != all_player.end(); it_player++)
	{
		f_playerlist << it_player->name << ','
			<< it_player->passwords << ','
			<< it_player->level << ','
			<< it_player->rank_or_test_num << ','
			<< it_player->experiences << endl;
			
	}
}
void write_in_test_maker() //�������ߵ���Ϣд���ļ�
{
	fstream f_test_makerlist("test_makerlist.csv", ios::out);
	vector<user>::iterator it_test_maker;
	for (it_test_maker = all_test_maker.begin(); it_test_maker != all_test_maker.end(); it_test_maker++)
	{
		f_test_makerlist << it_test_maker->name << ','
			<< it_test_maker->passwords << ','
			<< it_test_maker->level << ','
			<< it_test_maker->rank_or_test_num << ','
			<< it_test_maker->experiences << endl;
	}
}
DWORD WINAPI ServerThread(LPVOID lpParameter)
{
	SOCKET* revSocket= (SOCKET*)lpParameter;  //��Ӧ��ʱ���������ӵ��׽��ֵľ��

	//�ȴ��ͻ������󣬷�������������
	cout << "************" << endl;
	while (1)
	{
	mainpart:
		char which ;
		recv(*revSocket, &which, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־
		
		if (which == 'a')  //��user
		{
		part1:
			user accept;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			int res = recv(*revSocket, recv_buf, strlen(recv_buf), 0);//��ȡ����
			memset(&accept, 0, sizeof(accept));//��սṹ��
			memcpy(&accept, recv_buf, sizeof(accept));//�ѽ��յ�����Ϣת���ɽṹ��
			
			if (res > 0)
			{
				cout << "�յ����ݴ�С:" << res << endl;
				cout << "�ͻ��˷��͵�����:";
				cout << accept.choice << " *" << accept.name << "* " << accept.passwords << " " << accept.experiences << " " << accept.level << " " << accept.rank_or_test_num << " " << endl;
				switch (accept.choice)
				{
				case SIGN_IN_FOR_PLAYER:  //������ע��
				{
					char judge = 'w';
					string compare = accept.name;
					for (auto search : all_player)
					{
						if (search.name == compare) //������û���ע��
						{
							judge = 'r';
							cout << "������r" << endl;
							send(*revSocket, &judge, 1, 0);
							goto part1;
							break;
						}
					}
					if (judge == 'w')
					{
						cout << "������w" << endl;
						send(*revSocket, &judge, 1, 0);
						all_player.push_back(accept); //�����ע����û�������
					}
					break;
				}

				case SIGN_IN_FOR_TEST_MAKER: //������ע��
				{
					char judge = 'w';
					string compare = accept.name;
					for (auto search : all_test_maker)
					{
						if (search.name == compare)
						{
							judge = 'r';
							cout << "������r" << endl;
							send(*revSocket, &judge, 1, 0);
							goto part1;
							break;
						}
					}
					if (judge == 'w')
					{
						cout << "������w" << endl;
						send(*revSocket, &judge, 1, 0);
						all_test_maker.push_back(accept); //�����ע��ĳ����߱���
					}
					break;
				}
				case SIGN_UP_FOR_PLAYER: //�����ߵ�¼
				{
					int judge = 0;
					string com_name = accept.name;
					string com_pass = accept.passwords;
					for (auto search : all_player)
					{
						if (com_name == search.name && com_pass == search.passwords) //�û�����������ȷ
						{
							char temp = 'a';
							send(*revSocket, &temp, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־

							user a_player_data(com_name, com_pass, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
							judge = 1;
							all_online_player.push_back(accept);//��¼�ͷ��ڵ�ǰ����
							cout << "������" << com_name << "�Ѿ�����" << endl;
							break;
						}
					}
					if (judge == 0) //��½ʧ��
					{
						char temp = 'b';
						send(*revSocket, &temp, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־
						goto mainpart;
					}

					break;
				}

				case SIGN_UP_FOR_TEST_MAKER: //�����ߵ�¼
				{
					int judge = 0;
					string com_name = accept.name;
					string com_pass = accept.passwords;
					for (auto search : all_test_maker)
					{
						if (com_name == search.name&& com_pass== search.passwords) //��½�ɹ�
						{
							char temp =  'a';
							send(*revSocket, &temp, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־

							user a_test_maker_data(com_name, com_pass, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
							judge = 1;
							all_online_test_maker.push_back(accept);//��¼�ͷ��ڵ�ǰ����
							cout << "������" << com_name << "�Ѿ�����" << endl;
							break;
						}
					}
					if (judge == 0) //��½ʧ��
					{
						char temp =  'b' ;
						send(*revSocket, &temp, 1, 0);//����һ���жϿͻ���ʲô��Ϣ�ı�־
						goto mainpart;
					}
					break;
				}

				case SEARCH_PLAYER_NAME:
				{
					int num = 0;
					string temp=accept.name;
					for (auto search : all_player)
					{
						if (temp == search.name)
						{
							num++;
						}
					}
					words player_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &player_size, sizeof(player_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					string _name=accept.name;
					for (auto search : all_player)
					{
						if (_name == search.name)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//����
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
							break;
						}
					}
					break;
				}

				case SEARCH_PLAYER_LEVEL:
				{
					int num = 0;
					for (auto search : all_player)
					{
						if (accept.level == search.level)
						{
							num++;
						}
					}
					string temp;
					words player_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &player_size, sizeof(player_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					for (auto search : all_player)
					{
						if (accept.level == search.level)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//����
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
						}
					}
					

					break;
				}

				case SEARCH_PLAYER_RANK:
				{
					int num = 0;
					for (auto search : all_player)
					{
						if (accept.rank_or_test_num == search.rank_or_test_num)
						{
							num++;
						}
					}
					string temp;
					words player_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &player_size, sizeof(player_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					for (auto search : all_player)
					{
						if (accept.rank_or_test_num == search.rank_or_test_num)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//����
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
						}
					}
					break;
				}

				case SEARCH_PLAYER_EXPERIENCES:
				{
					int num = 0;
					for (auto search : all_player)
					{
						if (accept.experiences == search.experiences)
						{
							num++;
						}
					}
					string temp;
					words player_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &player_size, sizeof(player_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					for (auto search : all_player)
					{
						if (accept.experiences == search.experiences)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//����
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
						}
					}
					break;
				}


				case SEARCH_TEST_MAKER_NAME:
				{
					int num = 0;
					string temp = accept.name;
					for (auto search : all_test_maker)
					{
						if (temp == search.name)
						{
							num++;
						}
					}
					words test_maker_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					string _name=accept.name;

					for (auto search : all_test_maker)
					{
						if (_name == search.name)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
							break;
						}
					}
					break;
				}

				case SEARCH_TEST_MAKER_LEVEL:
				{
					int num = 0;
					string temp;
					for (auto search : all_test_maker)
					{
						if (accept.level == search.level)
						{
							num++;
						}
					}

					words test_maker_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					for (auto search : all_test_maker)
					{
						if (accept.level == search.level)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
						}
					}
					break;
				}

				case SEARCH_TEST_MAKER_TEST_NUM:
				{
					int num = 0;
					string temp;
					for (auto search : all_test_maker)
					{
						if (accept.rank_or_test_num == search.rank_or_test_num)
						{
							num++;
						}
					}

					words test_maker_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


					for (auto search : all_test_maker)
					{
						if (accept.rank_or_test_num == search.rank_or_test_num)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
						}
					}
					break;
				}

				case SEARCH_TEST_MAKER_EXPERIENCES:
				{
					int num = 0;
					string temp;
					for (auto search : all_test_maker)
					{
						if (accept.experiences == search.experiences)
						{
							num++;
						}
					}

					words test_maker_size(num, 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ


					for (auto search : all_test_maker)
					{
						if (accept.experiences == search.experiences)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//��ջ���
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
							send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
						}
					}
					break;
				}


				case RANK_FOR_PLAYER:
				{
					string temp;
					words test_maker_size(all_player.size(), 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					for (vector<user>::iterator it = all_player.begin(); it != all_player.end(); it++)
					{
						user a_test_maker_data(it->name, temp, it->experiences, it->level, it->rank_or_test_num); //����������
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//��ջ���
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
						send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
					}
					break;
				}


				case RANK_FOR_TEST_MAKER:
				{
					string temp;
					words test_maker_size(all_test_maker.size(), 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					for (vector<user>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++)
					{
						user a_test_maker_data(it->name, temp, it->experiences, it->level, it->rank_or_test_num);
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//��ջ���
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
						send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
					}
					break;
				}

				case WATCH_ONLINE_PLAYER:
				{
					words snd_all_player_size;
					snd_all_player_size.operate = all_online_player.size();
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &snd_all_player_size, sizeof(snd_all_player_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ

					string out;
					for (vector<user>::iterator it = all_online_player.begin(); it != all_online_player.end(); it++)
					{
						out = it->name;
						cout << "�����˵�ǰ���ߴ�����" << it->name << endl;
						user a_test_maker_data(it->name, it->passwords, it->experiences, it->level, it->rank_or_test_num);
						
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//��ջ���
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
						send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
					}
					break;
				}

				case WATCH_ONLINE_TEST_MAKER:
				{
					words snd_all_test_maker_size;
					snd_all_test_maker_size.operate = all_online_test_maker.size();
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &snd_all_test_maker_size, sizeof(snd_all_test_maker_size)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
					string out;
				
					for (vector<user>::iterator it = all_online_test_maker.begin(); it != all_online_test_maker.end(); it++)
					{
						out = it->name;
						cout << "�����˵�ǰ���߳�����" << it->name << endl;
						user a_test_maker_data(it->name, it->passwords, it->experiences, it->level, it->rank_or_test_num);
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//��ջ���
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //�ṹ��ת�����ַ���
						send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
					}
					break;
				}

				case PLAYER_LOG_OUT:
				{
					string out = accept.name;
					for (vector<user>::iterator it = all_player.begin(); it != all_player.end(); it++)
					{
						
						if (strcmp(it->name, accept.name)==0)
						{
							cout << "д���ļ�" << accept.experiences << "  " << accept.level << "  " << accept.rank_or_test_num << endl;
							//���������д��
							it->experiences = accept.experiences;
							it->level = accept.level;
							it->rank_or_test_num = accept.rank_or_test_num;
							cout << it->experiences << "   " << it->level << "   " << it->rank_or_test_num << endl;
							write_in_player();//д���ļ�
							cout << "�û�" << out << "�Ѿ�ע��" << endl;
							break;
						}
					}

					for (vector<user>::iterator it = all_online_player.begin(); it != all_online_player.end(); it++)
					{
						if (strcmp(it->name , accept.name)==0)
						{
							all_online_player.erase(it);  //д���ӵ�ǰ�����˳�
							break;
						}
					}
					break;
				}

				case TEST_MAKER_LOG_OUT:
				{
					string out = accept.name;
					for (auto it : all_test_maker)
					{
						if (strcmp(it.name, accept.name)==0)
						{
							cout << "д���ļ�" << accept.experiences << "  " << accept.level << "  " << accept.rank_or_test_num << endl;
							it.experiences = accept.experiences;
							it.level = accept.level;
							it.rank_or_test_num = accept.rank_or_test_num;
							write_in_test_maker();//д���ļ�
							break;
						}
					}
					for (vector<user>::iterator it = all_online_test_maker.begin(); it != all_online_test_maker.end(); it++)
					{
						if (strcmp(it->name , accept.name)==0)
						{
							all_online_test_maker.erase(it);  //д���ӵ�ǰ�����˳�
							break;
						}
					}
					break;
				}

				}
			}
			else if (res == 0)
				cout << "�Ͽ�����\n" << endl;
			else
				cout << "����ʧ��: " << WSAGetLastError() << endl;


		}
		else if (which == 'b')  //��words
		{
			cout << "������b" << endl;
			srand((unsigned)time(NULL));
			words accept;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//��ջ���
			int res = recv(*revSocket, recv_buf, SIZE, 0);//��ȡ����
			memset(&accept, 0, sizeof(accept));//��սṹ��
			memcpy(&accept, recv_buf, sizeof(accept));//�ѽ��յ�����Ϣת���ɽṹ��

			if (res > 0)
			{
				cout << "�յ����ݴ�С:" << res << endl;
				cout << "�ͻ��˷��͵�����:";
				cout << accept.cur_level << " " << accept.a_word << " " << endl;
				switch (accept.operate)
				{
				case START_PLAYER_GAME:
				{
					int words_start = 0, words_end = 0; //�Ѷȵȼ��ĵ��ʵĿ�ʼ�ͽ��������
					int loc = 0;  //�ڴʿ��еĵڼ�������
					int all_level = 4;  //����4���ȼ�
					for (auto search_size : all_words)  //���Ҹó��ȵĵ�һ������
					{
						loc++;
						if (search_size.length() > (accept.cur_level - 1) * 4)
						{
							words_start = loc;
							loc = 0;
							break;
						}

					}
					for (auto search_size : all_words)  //���Ҹó��ȵ����һ������
					{
						loc++;
						if (accept.cur_level == all_level) //�����ǰ�Ѷ����
						{
							words_end = all_words.size(); //�����Ѷȵ�ĩβ���Ǵʿ�ĩβ
							break;
						}
						if (search_size.length() > accept.cur_level * 4)
						{
							words_end = loc - 1;
							loc = 0;
							break;
						}
					}
					loc = (rand() % (words_end - words_start)) + words_start; //��ȡ��ǰ�Ѷȵ����

					words send_a_word(START_PLAYER_GAME, accept.cur_level, all_words.at(loc));
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//��ջ���
					memcpy(send_buf, &send_a_word, sizeof(send_a_word)); //�ṹ��ת�����ַ���
					send(*revSocket, send_buf, sizeof(send_buf), 0);//������Ϣ
					break;
				}

				case ADD_NEW_WORDS:
				{

					vector<string>::iterator insert_words;
					insert_words = find(all_words.begin(), all_words.end(), accept.a_word); //���Ҵʿ��Ƿ��иõ���

					if (insert_words == all_words.end())//����ɹ�����:���ʲ�����
					{

						all_words.push_back(accept.a_word);
						std::sort(all_words.begin(), all_words.end(), comp_string);
						/*д���ļ�*/
						fstream f_wordlist("wordlist.csv", ios::out);
						if (!f_wordlist)
						{
							cout << "�޷����ļ�wordlist.csv" << endl;
							return 0;
						}
						int len = all_words.size();
						for (int i = 0; i < len; i++)
						{
							f_wordlist << all_words[i] << endl;  //��Ϊvector������[ ]�������������ֱ�Ӱ��������������ˣ���Ȼ������vector�ĵ�����iterator���ʡ�
																//	ֻ�����õ����������ᱨ��������
						}

						char judge = 'r';
						send(*revSocket, &judge, 1, 0);

					}
					else
					{
						char judge = 'w';
						send(*revSocket, &judge, 1, 0);
						cout << "�õ����Ѵ���\n";
					}
					break;
				}

				}
			}
			else if (res == 0)
				cout << "�Ͽ�����\n" << endl;
			else
				cout << "����ʧ��: " << WSAGetLastError() << endl;

		}
		else
		{
			cout << "�˳�һ���߳�" << endl;
			write_in_player();
			write_in_test_maker();
			return 0;
		}

	}
	
	
	//int recv( SOCKET s,     char FAR *buf,      int len,     int flags     ); 

	//�����ǿͻ����Ƿ�����Ӧ�ó�����recv������TCP���ӵ���һ�˽������ݣ����ݷ���ֵ�ж����ݽ��������

	//sָ�����ն��׽�����������

	//bufָ��һ�����������û������������recv�������յ������ݣ�

	//lenָ��buf�ĳ��ȣ�

	//flagsһ��Ϊ0��

	return 0;
}

int main()
{
	read_all_words();
	read_all_player();
	read_all_test_maker();

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //WSAStartup����0��ʾ���ó�ʼ���ɹ�
		return 0;

	//�����׽���
	//AF_INET��ʾIPv4��SOCK_STREAM���ݴ��䷽ʽ��IPPROTO_TCP����Э��;
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("�׽��ִ���ʧ��");
		WSACleanup();
		return 0;
	}
	//1��WORD��΢��SDK�е��޷���16λ������;WSADATA��һ���ṹ�壻

	//��2��MAKEWORD(a,b)��һ���꣬��������ָ��ʹ�õ�Winsock�汾��

	//��3��WSAStartup����WSA(Windows Sockets Asynchronous��Windows�첽�׽���)���������

	//	 WSAStartup������Ӧ�ó����DLL���õĵ�һ��Windows Sockets������

	//     ������Ӧ�ó����DLLָ��Windows Sockets API�İ汾�ż�����ض�Windows Socketsʵ�ֵ�ϸ�ڡ�

	//	Ӧ�ó����DLLֻ����һ�γɹ���WSAStartup()����֮����ܵ��ý�һ����Windows Sockets API������

//	(4������socket()��socket()�������ڸ���ָ���ĵ�ַ�塢�������ͺ�Э��������һ���׽ӿڵ������ּ������õ���Դ��

	//	���޴�������socket()�����������׽ӿڵ������֡�����Ļ�������INVALID_SOCKET����



	//��IP�Ͷ˿�

		//���ü�����ַ�Ͷ˿�
	sockaddr_in addrListen;
	addrListen.sin_family = AF_INET;     //ָ��IP��ʽ
	addrListen.sin_port = htons(8888);   //�󶨶˿ں�
	addrListen.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  //��ʾ�κ�IP   service.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(listenSocket, (SOCKADDR*)& addrListen, sizeof(addrListen)) == SOCKET_ERROR)  //(SOCKADDR*)
	{
		printf("��ʧ��");
		closesocket(listenSocket);
		return 0;
	}
	//��1��sockaddr_in��һ�����ݽṹ������bind��connect��recvfrom��sendto�Ⱥ����Ĳ�����ָ����ַ��Ϣ��

	//  ��2��bind()����int bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);

	//		bind()����ͨ����һ���׽��ֽӿڷ���һ����ַ���������󡣣�



	//��ʼ����

	if (listen(listenSocket, 5) == SOCKET_ERROR)
	{
		printf("��������");
		closesocket(listenSocket);
		return 0;
	}
	//int listen( int sockfd, int backlog);

	//sockfd�����ڱ�ʶһ��������δ�����׽ӿڵ������֡�

	//backlog���ȴ����Ӷ��е���󳤶ȡ�


	//�ȴ����ӣ����Ӻ���һ���µ��׽���
	printf("�ȴ�����...\n");

	//pthread_t tids[NUM_THREADS];
	//int time = 0;
	while (1)
	{

		SOCKET *revSocket = new SOCKET;  //��Ӧ��ʱ���������ӵ��׽��ֵľ��
		revSocket = (SOCKET*)malloc(sizeof(SOCKET));
		sockaddr_in remoteAddr;   //�������ӵ��������ϵĵ�ַ��Ϣ
		int remoteAddrLen = sizeof(remoteAddr);
		*revSocket = accept(listenSocket, (SOCKADDR*)& remoteAddr, &remoteAddrLen);  //�ȴ��ͻ��˽��룬ֱ���пͻ�����������Ϊֹ
		if (*revSocket == INVALID_SOCKET)
		{
			printf("�ͻ��˷������󣬷�������������ʧ�ܣ�%d \n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 0;
		}
		else
		{
			printf("�ͷ�����������������ӳɹ���%s \n", inet_ntoa(remoteAddr.sin_addr));
		}

		//1�����ȶ���һ���µ��׽��֣�ע����׽�������֮ǰ�Ĳ�ͬ�����ݴ���ʱ��ʹ�ñ��׽��֡�

		//��2��SOCKET accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

		//    �����ӵȴ����Ӷ����г�ȡ��һ�����ӣ�����һ��ͬ����µ��׽ӿڲ����ؾ��;

		//    sockfd���׽��������������׽ӿ���listen()��������ӣ�

		//    addr������ѡ��ָ�룬ָ��һ�����������н���ΪͨѶ����֪������ʵ��ĵ�ַ��Addr������ʵ�ʸ�ʽ���׽ӿڴ���ʱ�������ĵ�ַ��ȷ����

		 //   addrlen������ѡ��ָ�룬������������addrһ��ʹ�ã�ָ�����addr��ַ���ȵ���������

		//int ret = pthread_create(&tids[time++], NULL, servers, NULL);
		CreateThread(NULL, 0, &ServerThread, revSocket, 0, NULL);
	}
	
	closesocket(listenSocket);

	WSACleanup();

	//int send( SOCKET s,  const char FAR *buf,  int len,   int flags ); 
	//�������ͬrecv()������

	//�ر��׽��֣��رռ��ص��׽��ֿ�

	return 0;
}


