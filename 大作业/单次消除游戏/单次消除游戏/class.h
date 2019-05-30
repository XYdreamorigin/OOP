#pragma once
#include <cstdio>
#include<string>
#include<vector>
using namespace std;

/*�����˶���player���test_maker���˳��������
  ���������������֧�ָ�ֵ����operator=,
  ����ʵ��������֧�ֿ�������                 */





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
class player:public user
{
private:
	int rank = 0; //�������Ѿ������Ĺؿ���
	
protected:
	double play_start=0, play_end=0;   //��ʱ����ʼ�ͽ���
public:
	int show_rank() { return rank; }
	
	void sign_in();//������ע��
	void sign_up();//�����ߵ�½
	player();//���캯������ʼ��
	player(const player& a);  //�������캯����˳��������Լ���������class.h
	player(string in_name, string in_passwords, int in_experience, int in_level, int in_rank);//Ϊ�˶�ȡ�ļ�ʱֱ�Ӹ�ֵ����Ȼ�͵ý���һ��game�࣬������˷�
	player& operator=(const player& a);//��ֵ���������

	void upgrade(vector<player>::iterator it); //����������

	//bool comp_name(const player& a, const player& b); //�Զ���Ƚ��û����ĺ���
};

class test_maker:public user
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

	void upgrade(vector<test_maker>::iterator it); //�������������

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

	void read_all_words();  //�ļ���ȡ���е���
	void read_all_player(); //�ļ���ȡ���д�����
	void read_all_test_maker();  //�ļ���ȡ���г�����


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

	void write_in_player(); //�������ߵ���Ϣд���ļ�

	void write_in_test_maker();//�������ߵ���Ϣд���ļ�

	static bool comp_string(string a, string b) { return a.length()< b.length(); } //�Ƚ��ַ�������

	//����ȽϺ���Ϊ��֮���ܽ����������а���Ҫ���򣬶������ڵ���������
	static bool comp_rank_player(player a,player b) { return a.show_rank() > b.show_rank(); }//�Զ���Ƚ��û�ͨ���ؿ��� ������ ����
	static bool comp_name_player(player a,player b) { return a.show_name() < b.show_name(); } //�Զ���Ƚ��û����ĺ���  ������ ����
	static bool comp_experience_player(player a,player b) { return a.show_experience() > b.show_experience(); } //�Զ��徭��ֵ�ȽϺ���  ������ ����
	static bool comp_level_player(player a,player& b) { return a.show_level() > b.show_level(); } // �Զ���ȼ��ȽϺ���  ������ ����
	/*Ϊʲô��static ? ���ӵĻ��ᱨ��˵sortĬ����������ȴ����������
	ԭ���� ��Ա������һ������Ĭ����thisָ�룬 ����������������ʵ��3������
	  ��static   ��̬������û��thisָ��   */


	//����ȽϺ���Ϊ��֮���ܽ����������а���Ҫ���򣬶������ڵ���������
	static bool comp_test_num_test_maker(test_maker a, test_maker b) { return a.show_test_num() > b.show_test_num(); } //�Զ���Ƚ��û�������Ŀ ������  ����
	static bool comp_name_test_maker(test_maker a, test_maker b) { return a.show_name() < b.show_name(); } //�Զ���Ƚ��û����ĺ���  ������  ����
	static bool comp_experience_test_maker(test_maker a, test_maker b) { return a.show_experience() > b.show_experience(); } //�Զ��徭��ֵ�ȽϺ���  ������ ����
	static bool comp_level_test_maker(test_maker a,test_maker b) { return a.show_level()> b.show_level(); } // �Զ���ȼ��ȽϺ���   ������ ����
};