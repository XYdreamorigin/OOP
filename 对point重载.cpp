#include<iostream>
#include<stdlib.h>
using namespace std;

class point
{
private:
    int x;
    int y;
public:

    point()
    {
        cout<<"point���캯��"<<endl;
    }
    ~point()
    {
        cout<<"point��������"<<endl;
    }
    void init(int a,int b)//���캯��
    {
        x=a;
        y=b;
    }
    void output()
    {
        cout<<"("<<x<<","<<y<<")"<<endl;
    }

    point operator ++(int) //p++
    {
        point r=*this;      //�ȼ��ڸ�ֵx=x
        this->x++;
        this->y++;
        return r;
    }
    point operator --(int) //p--
    {
        point r=*this;      //�ȼ��ڸ�ֵx=x
        this->x--;
        this->y--;
        return r;
    }

    point& operator ++() //++p
    {
       x++;
       y++;
       this->x=x;
       this->y=y;
       return *this;
    }
     point& operator --() //--p
    {
        x--;
        y--;
        this->x=x;
        this->y=y;
        return *this;
    }
};

int main()
{
    point a,b;
    int x,y;
    cout<<"������������"<<endl;
    cin>>x>>y;
    a.init(x,y);

    a.output();

    int choose=0;
    while(choose!=5)
    {
        cout<<"��ѡ������:1.p++ 2.p-- 3.++p 4.--p 5.quit"<<endl;
        cin>>choose;
        switch(choose)
        {
        case 1:
            {
                b=a++;
                cout<<"����֮�������Ϊ:"<<endl;
                b.output();
                break;
            }
        case 2:
            {
                b=a--;
                cout<<"����֮�������Ϊ:"<<endl;
                b.output();
                break;
            }
        case 3:
            {
                b=++a;
                cout<<"����֮�������Ϊ:"<<endl;
                b.output();
                break;
            }
        case 4:
            {
                b=--a;
                cout<<"����֮�������Ϊ:"<<endl;
                b.output();
                break;
            }
        }
    }

    system("pause");
    return 0;
}
