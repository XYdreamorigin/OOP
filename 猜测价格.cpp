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
	public://���г�Ա����
   	 	int input;
    
	public://���г�Ա����
    	Input(int x=0)
		{//���캯��
        	input=x;
    	}
    	void getinput()
		{//�õ��û������룬�ԷǷ������������
        	while(1)
			{
            	cout<<"���������µļ۸�(1-1000)��"<<endl;
            	cin>>input;   //cin����ǿ������ת����ֻ����������ͻ���ã������ַ�����Ը���� 
            	//cout<<input<<endl;
            	if (input>0&&input<1001) 
				{//����Ϸ�
                	cin.clear();
                	cin.ignore(1024,'\n');//����������
                	break;
            	}
            cout<<"����Ƿ���������1-1000�������"<<endl;
            cin.clear();
            cin.ignore(1024,'\n');//����������
        	}
    	}
    	~Input(){}
};

class Price 
{
	private://˽�г�Ա����
    	int price;
    
	public://���г�Ա����
    	Price()
		{//���캯��
        	srand((unsigned)time(NULL));
        	price=rand()%1000+1;//������ɼ۸�
        	cout<<"�漴���ɵļ۸�Ϊ��"<<price<<endl;//���������ɵļ۸�
    	}
    	int IsRight(Input x)
		{//�ж����µ����Ƿ���ȷ
        	if(x.input==price)
			{
            	cout<<"�¶�����"<<endl;
            	return RIGHT;
        	}
        	if(x.input<price)
			{
            	cout<<"���¼�ֵƫ�ͣ�����������"<<endl;
            	return SMALL;
        	}
        	if(x.input>price)
			{
            	cout<<"���¼�ֵƫ��"<<endl;
            	return BIG;
        	}
        	cout<<"������ִ���"<<endl;
        	return ERROR;
    	}
    	~Price(){}
};

/*������*/

int main() 
{
    Input guess(0);//��������
    Price real;
    guess.getinput();//�õ�����
    while (real.IsRight(guess)!=RIGHT) {
        guess.getinput();
    }
    return 0;
}




