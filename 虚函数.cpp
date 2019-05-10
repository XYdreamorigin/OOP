 #include<iostream>
 #include<stdlib.h>
 using namespace std;

 class shape  //抽象类
 {
 	public:
 		shape()
 		{}
 		~shape()
 		{}
 		virtual float area()=0；  //虚函数
 };

 class rectangle:public shape
 {
 private:
    float length,wide;
 	public:
 		rectangle(float a,float b)
 		{
 			length=a;
 			wide=b;
		}
 		~rectangle()
 		{}

 		float area()
 		{
 		    return length*wide;
 		}
 };

class square:public rectangle
{
    private:
    float side;
 	public:
 		square(float a):rectangle(a,a)
 		{
 			side=a;
		}
		~square()
		{}
};

class circle:public shape
{
    private:
    float radius;
	public:
		circle(float r)
		{
			radius=r;
		}
		~circle()
		{}
		float area()
		{
		     return 3.14*radius*radius;
		}
};

int main()
{
    float res;
    float length,wide;
    cout<<"请输入长和宽："<<endl;
    cin>>length>>wide;
    rectangle b(length,wide);
    res=b.area();
    cout<<"矩形的面积为"<<res<<endl;

    float radius;
    cout<<"请输入圆的半径："<<endl;
    cin>>radius;
    circle c(radius);
    res=c.area();
    cout<<"圆形的面积为"<<res<<endl;

    float side;
    cout<<"请输入正方形的边长："<<endl;
    cin>>side;
    square d(side);
    res=d.area();
    cout<<"正方形的面积为"<<res<<endl;
    system("pause");

    return 0;
}
