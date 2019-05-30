#include<iostream>
using namespace std;

class father
{
	public:
	int a,b;
	father(int a,int b)
	{
		this->a=a;
		this->b=b;
		cout<<a<<b<<endl;
	}
};

class son:public father
{
	public:
	int c;
	int d;
	son(int c,int d	,int a,int b):father(a,b)
	{
		this->c=c;
		this->d=d;
		cout<<c<<d<<endl;
	}

};

int main()
{
	son A(3,4,1,6);
	cout<<A.a<<A.b<<A.c<<A.d<<endl;
    return 0;
}
