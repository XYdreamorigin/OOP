 #include<iostream>
 #include<stdlib.h>
 using namespace std;

 class shape
 {
public:
    shape()
 		{
 		    cout<<"shape���캯��"<<endl;
 		}
 		~shape()
 		{
 		     cout<<"shape��������"<<endl;
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

 class rectangle:public shape   //����
 {
    private:
        float length,wide;
 	public:
 		rectangle(int a,int b)
 		{
 			length=a;
 			wide=b;
 		    cout<<"rectangle���캯��"<<endl;
		}
 		~rectangle()
 		{
 		    cout<<"rectangle��������"<<endl;
 		}
 };

class square:public rectangle    //������
{
private:
     float side;
public:
    square(float a):rectangle(a,a)
    {
        side=a;
        cout<<"square���캯��"<<endl;
    }
    ~square()
    {
        cout<<"square��������"<<endl;
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
			 cout<<"circle���캯��"<<endl;
		}
		~circle()
		{
		     cout<<"circle��������"<<endl;
		}
};

int main()
{
    float res;
    float length,wide;
    cout<<"�����볤�Ϳ�"<<endl;
    cin>>length>>wide;
    rectangle b(length,wide);
    res=b.area(length,wide);
    cout<<"���ε����Ϊ"<<res<<endl;


    float radius;
    cout<<"������Բ�İ뾶��"<<endl;
    cin>>radius;
    circle c(radius);
    res=c.area(radius);
    cout<<"Բ�ε����Ϊ"<<res<<endl;


    float side;
    cout<<"������߳�"<<endl;
    cin>>side;
    square d(side);
    res=d.area(side,side);
    cout<<"���������Ϊ"<<res<<endl;

    system("pause");

    return 0;
}
