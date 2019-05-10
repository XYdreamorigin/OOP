#include <iostream>
//#include <ctime>
#include<time.h>
#include<stdlib.h>
using namespace std;


const int SMALL=0;
const int RIGHT=1;
const int BIG=2;
const int ERROR=-1;

class Input 
{
	public://公有成员变量
   	 	int input;
    
	public://公有成员函数
    	Input(int x=0)
		{//构造函数
        	input=x;
    	}
    	void getinput()
		{//得到用户的输入，对非法输入提出警告
        	while(1)
			{
            	cout<<"请输入所猜的价格(1-1000)："<<endl;
            	cin>>input;   //cin不会强制类型转换，只有输入该类型会调用，输入字符会忽略该语句 
            	//cout<<input<<endl;
            	if (input>0&&input<1001) 
				{//输入合法
                	cin.clear();
                	cin.ignore(1024,'\n');//清理输入流
                	break;
            	}
            cout<<"输入非法，请输入1-1000间的整数"<<endl;
            cin.clear();
            cin.ignore(1024,'\n');//清理输入流
        	}
    	}
    	~Input(){}
};

class Price 
{
	private://私有成员变量
    	int price;
    
	public://公有成员函数
    	Price()
		{//构造函数
        	srand((unsigned)time(NULL));
        	price=rand()%1000+1;//随机生成价格
        	cout<<"随即生成的价格为："<<price<<endl;//输出随机生成的价格
    	}
    	int IsRight(Input x)
		{//判断所猜的数是否正确
        	if(x.input==price)
			{
            	cout<<"猜对啦！"<<endl;
            	return RIGHT;
        	}
        	if(x.input<price)
			{
            	cout<<"所猜价值偏低，请重新输入"<<endl;
            	return SMALL;
        	}
        	if(x.input>price)
			{
            	cout<<"所猜价值偏高"<<endl;
            	return BIG;
        	}
        	cout<<"程序出现错误"<<endl;
        	return ERROR;
    	}
    	~Price(){}
};

/*主函数*/

int main() 
{
    Input guess(0);//创建对象
    Price real;
    guess.getinput();//得到输入
    while (real.IsRight(guess)!=RIGHT) {
        guess.getinput();
    }
    return 0;
}




