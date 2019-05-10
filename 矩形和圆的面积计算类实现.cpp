 #include<iostream>
 #include<stdlib.h>
 using namespace std;

 class shape
 {
public:
    shape()
 		{
 		    cout<<"shape构造函数"<<endl;
 		}
 		~shape()
 		{
 		     cout<<"shape析构函数"<<endl;
 		}
 		float area(int a)
 		{
                return 3.14*a*a;
 		}
 		float area(int a,int b)
 		{
 		    return a*b;
 		}
 };

 class rectangle:public shape   //矩形
 {
    private:
        float length,wide;
 	public:
 		rectangle(int a,int b)
 		{
 			length=a;
 			wide=b;
 		    cout<<"rectangle构造函数"<<endl;
		}
 		~rectangle()
 		{
 		    cout<<"rectangle析构函数"<<endl;
 		}
 };

class square:public rectangle    //正方形
{
private:
     float side;
public:
    square(float a):rectangle(a,a)
    {
        side=a;
        cout<<"square构造函数"<<endl;
    }
    ~square()
    {
        cout<<"square析构函数"<<endl;
    }
};

class circle:public shape
{
    private:
        float radius;
	public:
		circle(float r)
		{
			radius=r;
			 cout<<"circle构造函数"<<endl;
		}
		~circle()
		{
		     cout<<"circle析构函数"<<endl;
		}
};

int main()
{
    float res;
    float length,wide;
    cout<<"请输入长和宽："<<endl;
    cin>>length>>wide;
    rectangle b(length,wide);
    res=b.area(length,wide);
    cout<<"矩形的面积为"<<res<<endl;


    float radius;
    cout<<"请输入圆的半径："<<endl;
    cin>>radius;
    circle c(radius);
    res=c.area(radius);
    cout<<"圆形的面积为"<<res<<endl;


    float side;
    cout<<"请输入边长"<<endl;
    cin>>side;
    square d(side);
    res=d.area(side,side);
    cout<<"正方形面积为"<<res<<endl;

    system("pause");

    return 0;
}
