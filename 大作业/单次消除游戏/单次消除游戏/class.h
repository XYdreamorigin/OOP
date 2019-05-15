#pragma once
#include <cstdio>
#include<string>
#include<vector>
using namespace std;

/*建立了对于player类和test_maker类的顺序容器，
  所以这两个类必须支持赋值操作operator=,
  对象实例还必须支持拷贝构造                 */





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
class player:public user
{
private:
	int rank = 0; //闯关者已经闯过的关卡数
	
protected:
	double play_start=0, play_end=0;   //计时器开始和结束
public:
	int show_rank() { return rank; }
	
	void sign_in();//闯关者注册
	void sign_up();//闯关者登陆
	player();//构造函数，初始化
	player(const player& a);  //拷贝构造函数，顺序容器的约束，详情见class.h
	player(string in_name, string in_passwords, int in_experience, int in_level, int in_rank);//为了读取文件时直接赋值，不然就得建立一个game类，造成了浪费
	player& operator=(const player& a);//赋值运算符重载

	void upgrade(vector<player>::iterator it); //闯关者升级

	//bool comp_name(const player& a, const player& b); //自定义比较用户名的函数
};

class test_maker:public user
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

	void upgrade(vector<test_maker>::iterator it); //出题者玩家升级

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

	void read_all_words();  //文件读取所有单词
	void read_all_player(); //文件读取所有闯关者
	void read_all_test_maker();  //文件读取所有出题者


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

	void write_in_player(); //将闯关者的信息写入文件

	void write_in_test_maker();//将出题者的信息写入文件

	static bool comp_string(string a, string b) { return a.length()< b.length(); } //比较字符串长度

	//定义比较函数为了之后能进行排序，排行榜需要排序，对容器内的内容排序
	static bool comp_rank_player(player a,player b) { return a.show_rank() > b.show_rank(); }//自定义比较用户通过关卡数 闯关者 降序
	static bool comp_name_player(player a,player b) { return a.show_name() < b.show_name(); } //自定义比较用户名的函数  闯关者 升序
	static bool comp_experience_player(player a,player b) { return a.show_experience() > b.show_experience(); } //自定义经验值比较函数  闯关者 降序
	static bool comp_level_player(player a,player& b) { return a.show_level() > b.show_level(); } // 自定义等级比较函数  闯关者 降序
	/*为什么加static ? 不加的话会报错说sort默认两个参数却给了三个。
	原因是 成员函数第一个参数默认是this指针， 所以这两个函数其实是3个参数
	  加static   静态函数就没有this指针   */


	//定义比较函数为了之后能进行排序，排行榜需要排序，对容器内的内容排序
	static bool comp_test_num_test_maker(test_maker a, test_maker b) { return a.show_test_num() > b.show_test_num(); } //自定义比较用户出题数目 出题者  降序
	static bool comp_name_test_maker(test_maker a, test_maker b) { return a.show_name() < b.show_name(); } //自定义比较用户名的函数  出题者  升序
	static bool comp_experience_test_maker(test_maker a, test_maker b) { return a.show_experience() > b.show_experience(); } //自定义经验值比较函数  出题者 降序
	static bool comp_level_test_maker(test_maker a,test_maker b) { return a.show_level()> b.show_level(); } // 自定义等级比较函数   出题者 降序
};