 #include<iostream>
 #include<stdlib.h>
 using namespace std;

 class shape  //������
 {
 	public:
 		shape()
 		{}
 		~shape()
 		{}
 		virtual float area()=0��  //�麯��
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
    cout<<"�����볤�Ϳ�"<<endl;
    cin>>length>>wide;
    rectangle b(length,wide);
    res=b.area();
    cout<<"���ε����Ϊ"<<res<<endl;

    float radius;
    cout<<"������Բ�İ뾶��"<<endl;
    cin>>radius;
    circle c(radius);
    res=c.area();
    cout<<"Բ�ε����Ϊ"<<res<<endl;

    float side;
    cout<<"�����������εı߳���"<<endl;
    cin>>side;
    square d(side);
    res=d.area();
    cout<<"�����ε����Ϊ"<<res<<endl;
    system("pause");

    return 0;
}
