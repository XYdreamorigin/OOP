#include<iostream>
#include<cmath>
using namespace std;

class point
{
	public:
		point()
		{}
		~point()
		{}
		float x=0.0;
		float y=0.0;
		float dis(point x1,point y1)
		{
			return sqrt((x1.x-y1.x)*(x1.x-y1.x)+(x1.y-y1.y)*(x1.y-y1.y));
		}
};

class circle
{	
	public:
		float radius;
		point O;
		void get()
		{
			cout<<"������Բ�����꣺"<<endl;
			cin>>O.x>>O.y;
			cout<<"������Բ�İ뾶��"<<endl;
			cin>>radius;
		}
};

int main()
{
	circle O1,O2;
	float res;
	cout<<"����������Բ����Ϣ:"<<endl;
	O1.get();
	O2.get(); 
	res=O1.O.dis(O1.O,O2.O);
	if(res>O1.radius+O2.radius||res<O1.radius-O2.radius)
		cout<<"����Բ���ཻ"<<endl;
	else
		cout<<"����Բ�ཻ"<<endl;
		
	system("pause");
	return 0; 
 } 

