#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

class game
{
private:
    int price;
public:
    int judge=0;
    void sand()
    {
        srand((unsigned)time(NULL));
        price=(rand()%(999))+1;
    }
    void guess()
    {
        //cout<<"请输入您猜测的价格"<<endl;
        int temp;
        cin>>temp;
        if(temp<price)
            cout<<"您猜测的价格过低"<<endl;
        else if(temp>price)
            cout<<"您猜测的价格过高"<<endl;
        else
        {
            cout<<"恭喜您猜对了！"<<endl;
            judge=1;
        }


    }
};
int main()
{
    game A;
    A.sand();
    cout<<"请输入您猜测的价格"<<endl;
    while(A.judge==0)
    {
        A.guess();
    }
    system("pause");
    return 0;
}
