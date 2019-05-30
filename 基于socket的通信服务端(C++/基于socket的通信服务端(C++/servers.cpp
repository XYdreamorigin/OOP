#include"servers.h"
using namespace std;
void read_all_words()
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
void read_all_player()
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
		user temp_player(name, passwords, experience, level, rank);//将文件读取的数据存入一个闯关者类中
		all_player.push_back(temp_player); //将这个玩家存入all_player容器中
	}
}
void read_all_test_maker()
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
		user temp_test_maker(name, passwords, experience, level, test_num);//将文件读取的数据存入一个闯关者类中
		all_test_maker.push_back(temp_test_maker); //将这个玩家存入all_player容器中
	}
}
static bool comp_string(string a, string b) { return a.length() < b.length(); } //比较字符串长度
void write_in_player() //将闯关者的信息写入文件
{
	/*写player*/
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
void write_in_test_maker() //将出题者的信息写入文件
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
	SOCKET* revSocket= (SOCKET*)lpParameter;  //对应此时所建立连接的套接字的句柄

	//等待客户端请求，服务器接收请求
	cout << "************" << endl;
	while (1)
	{
	mainpart:
		char which ;
		recv(*revSocket, &which, 1, 0);//接受一个判断客户传什么信息的标志
		
		if (which == 'a')  //传user
		{
		part1:
			user accept;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			int res = recv(*revSocket, recv_buf, strlen(recv_buf), 0);//读取数据
			memset(&accept, 0, sizeof(accept));//清空结构体
			memcpy(&accept, recv_buf, sizeof(accept));//把接收到的信息转换成结构体
			
			if (res > 0)
			{
				cout << "收到数据大小:" << res << endl;
				cout << "客户端发送的数据:";
				cout << accept.choice << " *" << accept.name << "* " << accept.passwords << " " << accept.experiences << " " << accept.level << " " << accept.rank_or_test_num << " " << endl;
				switch (accept.choice)
				{
				case SIGN_IN_FOR_PLAYER:  //闯关者注册
				{
					char judge = 'w';
					string compare = accept.name;
					for (auto search : all_player)
					{
						if (search.name == compare) //如果该用户被注册
						{
							judge = 'r';
							cout << "发送了r" << endl;
							send(*revSocket, &judge, 1, 0);
							goto part1;
							break;
						}
					}
					if (judge == 'w')
					{
						cout << "发送了w" << endl;
						send(*revSocket, &judge, 1, 0);
						all_player.push_back(accept); //把这个注册的用户存起来
					}
					break;
				}

				case SIGN_IN_FOR_TEST_MAKER: //出题者注册
				{
					char judge = 'w';
					string compare = accept.name;
					for (auto search : all_test_maker)
					{
						if (search.name == compare)
						{
							judge = 'r';
							cout << "发送了r" << endl;
							send(*revSocket, &judge, 1, 0);
							goto part1;
							break;
						}
					}
					if (judge == 'w')
					{
						cout << "发送了w" << endl;
						send(*revSocket, &judge, 1, 0);
						all_test_maker.push_back(accept); //把这个注册的出题者保存
					}
					break;
				}
				case SIGN_UP_FOR_PLAYER: //闯关者登录
				{
					int judge = 0;
					string com_name = accept.name;
					string com_pass = accept.passwords;
					for (auto search : all_player)
					{
						if (com_name == search.name && com_pass == search.passwords) //用户名和密码正确
						{
							char temp = 'a';
							send(*revSocket, &temp, 1, 0);//接受一个判断客户传什么信息的标志

							user a_player_data(com_name, com_pass, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
							judge = 1;
							all_online_player.push_back(accept);//登录就放在当前在线
							cout << "闯关者" << com_name << "已经上线" << endl;
							break;
						}
					}
					if (judge == 0) //登陆失败
					{
						char temp = 'b';
						send(*revSocket, &temp, 1, 0);//接受一个判断客户传什么信息的标志
						goto mainpart;
					}

					break;
				}

				case SIGN_UP_FOR_TEST_MAKER: //出题者登录
				{
					int judge = 0;
					string com_name = accept.name;
					string com_pass = accept.passwords;
					for (auto search : all_test_maker)
					{
						if (com_name == search.name&& com_pass== search.passwords) //登陆成功
						{
							char temp =  'a';
							send(*revSocket, &temp, 1, 0);//接受一个判断客户传什么信息的标志

							user a_test_maker_data(com_name, com_pass, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
							judge = 1;
							all_online_test_maker.push_back(accept);//登录就放在当前在线
							cout << "出题者" << com_name << "已经上线" << endl;
							break;
						}
					}
					if (judge == 0) //登陆失败
					{
						char temp =  'b' ;
						send(*revSocket, &temp, 1, 0);//接受一个判断客户传什么信息的标志
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &player_size, sizeof(player_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					string _name=accept.name;
					for (auto search : all_player)
					{
						if (_name == search.name)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//个数
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &player_size, sizeof(player_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					for (auto search : all_player)
					{
						if (accept.level == search.level)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//个数
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &player_size, sizeof(player_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					for (auto search : all_player)
					{
						if (accept.rank_or_test_num == search.rank_or_test_num)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//个数
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &player_size, sizeof(player_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					for (auto search : all_player)
					{
						if (accept.experiences == search.experiences)
						{
							user a_player_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							a_player_data.choice++;//个数
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_player_data, sizeof(a_player_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					string _name=accept.name;

					for (auto search : all_test_maker)
					{
						if (_name == search.name)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					for (auto search : all_test_maker)
					{
						if (accept.level == search.level)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息


					for (auto search : all_test_maker)
					{
						if (accept.rank_or_test_num == search.rank_or_test_num)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息


					for (auto search : all_test_maker)
					{
						if (accept.experiences == search.experiences)
						{
							user a_test_maker_data(search.name, search.passwords, search.experiences, search.level, search.rank_or_test_num);
							char send_buf[SIZE];
							memset(send_buf, 'z', SIZE);//清空缓存
							memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
							send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
						}
					}
					break;
				}


				case RANK_FOR_PLAYER:
				{
					string temp;
					words test_maker_size(all_player.size(), 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					for (vector<user>::iterator it = all_player.begin(); it != all_player.end(); it++)
					{
						user a_test_maker_data(it->name, temp, it->experiences, it->level, it->rank_or_test_num); //不发送密码
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//清空缓存
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
						send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
					}
					break;
				}


				case RANK_FOR_TEST_MAKER:
				{
					string temp;
					words test_maker_size(all_test_maker.size(), 0, temp);
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &test_maker_size, sizeof(test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					for (vector<user>::iterator it = all_test_maker.begin(); it != all_test_maker.end(); it++)
					{
						user a_test_maker_data(it->name, temp, it->experiences, it->level, it->rank_or_test_num);
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//清空缓存
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
						send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
					}
					break;
				}

				case WATCH_ONLINE_PLAYER:
				{
					words snd_all_player_size;
					snd_all_player_size.operate = all_online_player.size();
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &snd_all_player_size, sizeof(snd_all_player_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息

					string out;
					for (vector<user>::iterator it = all_online_player.begin(); it != all_online_player.end(); it++)
					{
						out = it->name;
						cout << "发送了当前在线闯关者" << it->name << endl;
						user a_test_maker_data(it->name, it->passwords, it->experiences, it->level, it->rank_or_test_num);
						
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//清空缓存
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
						send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
					}
					break;
				}

				case WATCH_ONLINE_TEST_MAKER:
				{
					words snd_all_test_maker_size;
					snd_all_test_maker_size.operate = all_online_test_maker.size();
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &snd_all_test_maker_size, sizeof(snd_all_test_maker_size)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
					string out;
				
					for (vector<user>::iterator it = all_online_test_maker.begin(); it != all_online_test_maker.end(); it++)
					{
						out = it->name;
						cout << "发送了当前在线出题者" << it->name << endl;
						user a_test_maker_data(it->name, it->passwords, it->experiences, it->level, it->rank_or_test_num);
						char send_buf[SIZE];
						memset(send_buf, 'z', SIZE);//清空缓存
						memcpy(send_buf, &a_test_maker_data, sizeof(a_test_maker_data)); //结构体转换成字符串
						send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
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
							cout << "写入文件" << accept.experiences << "  " << accept.level << "  " << accept.rank_or_test_num << endl;
							//将玩家数据写入
							it->experiences = accept.experiences;
							it->level = accept.level;
							it->rank_or_test_num = accept.rank_or_test_num;
							cout << it->experiences << "   " << it->level << "   " << it->rank_or_test_num << endl;
							write_in_player();//写入文件
							cout << "用户" << out << "已经注销" << endl;
							break;
						}
					}

					for (vector<user>::iterator it = all_online_player.begin(); it != all_online_player.end(); it++)
					{
						if (strcmp(it->name , accept.name)==0)
						{
							all_online_player.erase(it);  //写入后从当前在线退出
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
							cout << "写入文件" << accept.experiences << "  " << accept.level << "  " << accept.rank_or_test_num << endl;
							it.experiences = accept.experiences;
							it.level = accept.level;
							it.rank_or_test_num = accept.rank_or_test_num;
							write_in_test_maker();//写入文件
							break;
						}
					}
					for (vector<user>::iterator it = all_online_test_maker.begin(); it != all_online_test_maker.end(); it++)
					{
						if (strcmp(it->name , accept.name)==0)
						{
							all_online_test_maker.erase(it);  //写入后从当前在线退出
							break;
						}
					}
					break;
				}

				}
			}
			else if (res == 0)
				cout << "断开连接\n" << endl;
			else
				cout << "接受失败: " << WSAGetLastError() << endl;


		}
		else if (which == 'b')  //传words
		{
			cout << "接受了b" << endl;
			srand((unsigned)time(NULL));
			words accept;
			char recv_buf[SIZE];
			memset(recv_buf, 'z', SIZE);//清空缓存
			int res = recv(*revSocket, recv_buf, SIZE, 0);//读取数据
			memset(&accept, 0, sizeof(accept));//清空结构体
			memcpy(&accept, recv_buf, sizeof(accept));//把接收到的信息转换成结构体

			if (res > 0)
			{
				cout << "收到数据大小:" << res << endl;
				cout << "客户端发送的数据:";
				cout << accept.cur_level << " " << accept.a_word << " " << endl;
				switch (accept.operate)
				{
				case START_PLAYER_GAME:
				{
					int words_start = 0, words_end = 0; //难度等级的单词的开始和结束的序号
					int loc = 0;  //在词库中的第几个单词
					int all_level = 4;  //共有4个等级
					for (auto search_size : all_words)  //查找该长度的第一个单词
					{
						loc++;
						if (search_size.length() > (accept.cur_level - 1) * 4)
						{
							words_start = loc;
							loc = 0;
							break;
						}

					}
					for (auto search_size : all_words)  //查找该长度的最后一个单词
					{
						loc++;
						if (accept.cur_level == all_level) //如果当前难度最大
						{
							words_end = all_words.size(); //第五难度的末尾就是词库末尾
							break;
						}
						if (search_size.length() > accept.cur_level * 4)
						{
							words_end = loc - 1;
							loc = 0;
							break;
						}
					}
					loc = (rand() % (words_end - words_start)) + words_start; //获取当前难度的题库

					words send_a_word(START_PLAYER_GAME, accept.cur_level, all_words.at(loc));
					char send_buf[SIZE];
					memset(send_buf, 'z', SIZE);//清空缓存
					memcpy(send_buf, &send_a_word, sizeof(send_a_word)); //结构体转换成字符串
					send(*revSocket, send_buf, sizeof(send_buf), 0);//发送信息
					break;
				}

				case ADD_NEW_WORDS:
				{

					vector<string>::iterator insert_words;
					insert_words = find(all_words.begin(), all_words.end(), accept.a_word); //查找词库是否有该单词

					if (insert_words == all_words.end())//插入成功检验:单词不存在
					{

						all_words.push_back(accept.a_word);
						std::sort(all_words.begin(), all_words.end(), comp_string);
						/*写入文件*/
						fstream f_wordlist("wordlist.csv", ios::out);
						if (!f_wordlist)
						{
							cout << "无法打开文件wordlist.csv" << endl;
							return 0;
						}
						int len = all_words.size();
						for (int i = 0; i < len; i++)
						{
							f_wordlist << all_words[i] << endl;  //因为vector重载了[ ]运算符，所以我直接把它当作数组用了，当然可以用vector的迭代器iterator访问。
																//	只是我用迭代器遍历会报错。。。。
						}

						char judge = 'r';
						send(*revSocket, &judge, 1, 0);

					}
					else
					{
						char judge = 'w';
						send(*revSocket, &judge, 1, 0);
						cout << "该单词已存在\n";
					}
					break;
				}

				}
			}
			else if (res == 0)
				cout << "断开连接\n" << endl;
			else
				cout << "接受失败: " << WSAGetLastError() << endl;

		}
		else
		{
			cout << "退出一个线程" << endl;
			write_in_player();
			write_in_test_maker();
			return 0;
		}

	}
	
	
	//int recv( SOCKET s,     char FAR *buf,      int len,     int flags     ); 

	//不论是客户还是服务器应用程序都用recv函数从TCP连接的另一端接收数据，根据返回值判断数据接收情况。

	//s指定接收端套接字描述符；

	//buf指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；

	//len指明buf的长度；

	//flags一般为0；

	return 0;
}

int main()
{
	read_all_words();
	read_all_player();
	read_all_test_maker();

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //WSAStartup返回0表示设置初始化成功
		return 0;

	//创建套接字
	//AF_INET表示IPv4，SOCK_STREAM数据传输方式，IPPROTO_TCP传输协议;
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("套接字创建失败");
		WSACleanup();
		return 0;
	}
	//1）WORD是微软SDK中的无符号16位整形数;WSADATA是一个结构体；

	//（2）MAKEWORD(a,b)是一个宏，这里用来指定使用的Winsock版本；

	//（3）WSAStartup，即WSA(Windows Sockets Asynchronous，Windows异步套接字)的启动命令；

	//	 WSAStartup必须是应用程序或DLL调用的第一个Windows Sockets函数。

	//     它允许应用程序或DLL指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节。

	//	应用程序或DLL只能在一次成功的WSAStartup()调用之后才能调用进一步的Windows Sockets API函数。

//	(4）函数socket()，socket()函数用于根据指定的地址族、数据类型和协议来分配一个套接口的描述字及其所用的资源；

	//	若无错误发生，socket()返回引用新套接口的描述字。否则的话，返回INVALID_SOCKET错误。



	//绑定IP和端口

		//配置监听地址和端口
	sockaddr_in addrListen;
	addrListen.sin_family = AF_INET;     //指定IP格式
	addrListen.sin_port = htons(8888);   //绑定端口号
	addrListen.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  //表示任何IP   service.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(listenSocket, (SOCKADDR*)& addrListen, sizeof(addrListen)) == SOCKET_ERROR)  //(SOCKADDR*)
	{
		printf("绑定失败");
		closesocket(listenSocket);
		return 0;
	}
	//（1）sockaddr_in是一个数据结构；用做bind、connect、recvfrom、sendto等函数的参数，指明地址信息。

	//  （2）bind()函数int bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);

	//		bind()函数通过给一个套接字接口分配一个地址来建立捆绑。！



	//开始监听

	if (listen(listenSocket, 5) == SOCKET_ERROR)
	{
		printf("监听出错");
		closesocket(listenSocket);
		return 0;
	}
	//int listen( int sockfd, int backlog);

	//sockfd：用于标识一个已捆绑未连接套接口的描述字。

	//backlog：等待连接队列的最大长度。


	//等待连接，连接后建立一个新的套接字
	printf("等待连接...\n");

	//pthread_t tids[NUM_THREADS];
	//int time = 0;
	while (1)
	{

		SOCKET *revSocket = new SOCKET;  //对应此时所建立连接的套接字的句柄
		revSocket = (SOCKET*)malloc(sizeof(SOCKET));
		sockaddr_in remoteAddr;   //接收连接到服务器上的地址信息
		int remoteAddrLen = sizeof(remoteAddr);
		*revSocket = accept(listenSocket, (SOCKADDR*)& remoteAddr, &remoteAddrLen);  //等待客户端接入，直到有客户端连接上来为止
		if (*revSocket == INVALID_SOCKET)
		{
			printf("客户端发出请求，服务器接收请求失败：%d \n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 0;
		}
		else
		{
			printf("客服端与服务器建立连接成功：%s \n", inet_ntoa(remoteAddr.sin_addr));
		}

		//1）首先定义一个新的套接字，注意该套接字是与之前的不同，数据传输时，使用本套接字。

		//（2）SOCKET accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

		//    函数从等待连接队列中抽取第一个连接，创建一个同类的新的套接口并返回句柄;

		//    sockfd：套接字描述符，该套接口在listen()后监听连接；

		//    addr：（可选）指针，指向一缓冲区，其中接收为通讯层所知的连接实体的地址。Addr参数的实际格式由套接口创建时所产生的地址族确定。

		 //   addrlen：（可选）指针，输入参数，配合addr一起使用，指向存有addr地址长度的整型数。

		//int ret = pthread_create(&tids[time++], NULL, servers, NULL);
		CreateThread(NULL, 0, &ServerThread, revSocket, 0, NULL);
	}
	
	closesocket(listenSocket);

	WSACleanup();

	//int send( SOCKET s,  const char FAR *buf,  int len,   int flags ); 
	//含义基本同recv()函数。

	//关闭套接字，关闭加载的套接字库

	return 0;
}


