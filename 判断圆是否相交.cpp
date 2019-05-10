#include<iostream>
#include<stdlib.h>
#include<cmath>
using namespace std;

class point
{
	public:
		point()
		{
		    cout<<"point构造函数"<<endl;
		}
		~point()
		{
		    cout<<"point析构函数"<<endl;
		}
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
			cout<<"请输入圆心坐标："<<endl;
			cin>>O.x>>O.y;
			cout<<"请输入圆的半径："<<endl;
			cin>>radius;
		}
		circle()
		{
		    cout<<"circle构造函数"<<endl;
		}
		~circle()
		{
		    cout<<"cirlce析构函数"<<endl;
		}
};

int main()
{
	circle O1,O2;
	float res;
	cout<<"请输入两个圆的信息:"<<endl;
	O1.get();
	O2.get();
	res=O1.O.dis(O1.O,O2.O);
	//cout<<res<<endl;
	if(res>O1.radius+O2.radius||res<abs(O1.radius-O2.radius))
		cout<<"两个圆不相交"<<endl;
	else if(res==O1.radius+O2.radius||res==abs(O1.radius-O2.radius))
		cout<<"两个圆相切"<<endl;
    else
        cout<<"两个圆相交"<<endl;

	system("pause");
	return 0;
 }

