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
        //cout<<"���������²�ļ۸�"<<endl;
        int temp;
        cin>>temp;
        if(temp<price)
            cout<<"���²�ļ۸����"<<endl;
        else if(temp>price)
            cout<<"���²�ļ۸����"<<endl;
        else
        {
            cout<<"��ϲ���¶��ˣ�"<<endl;
            judge=1;
        }


    }
};
int main()
{
    game A;
    A.sand();
    cout<<"���������²�ļ۸�"<<endl;
    while(A.judge==0)
    {
        A.guess();
    }
    system("pause");
    return 0;
}
