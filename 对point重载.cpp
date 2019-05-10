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
        cout<<"point构造函数"<<endl;
    }
    ~point()
    {
        cout<<"point析构函数"<<endl;
    }
    void init(int a,int b)//构造函数
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
        point r=*this;      //先加在赋值x=x
        this->x++;
        this->y++;
        return r;
    }
    point operator --(int) //p--
    {
        point r=*this;      //先加在赋值x=x
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
    cout<<"请输入点的坐标"<<endl;
    cin>>x>>y;
    a.init(x,y);

    a.output();

    int choose=0;
    while(choose!=5)
    {
        cout<<"请选择运算:1.p++ 2.p-- 3.++p 4.--p 5.quit"<<endl;
        cin>>choose;
        switch(choose)
        {
        case 1:
            {
                b=a++;
                cout<<"运算之后的坐标为:"<<endl;
                b.output();
                break;
            }
        case 2:
            {
                b=a--;
                cout<<"运算之后的坐标为:"<<endl;
                b.output();
                break;
            }
        case 3:
            {
                b=++a;
                cout<<"运算之后的坐标为:"<<endl;
                b.output();
                break;
            }
        case 4:
            {
                b=--a;
                cout<<"运算之后的坐标为:"<<endl;
                b.output();
                break;
            }
        }
    }

    system("pause");
    return 0;
}
