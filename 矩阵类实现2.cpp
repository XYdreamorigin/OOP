#include<iostream>
#include<stdlib.h>
using namespace std;
//#define lines 2
//#define row 2
class matrix
{
private:
      int lines;
      int rows;

public:
	  int **array;


        matrix()//Ĭ�Ϲ��캯������������
        {
           // cout<<"Ĭ�Ϲ���"<<endl;
            //cout<<"��������������������:"<<endl;
            cin>>lines>>rows;


			array = new int *[lines];
     	    for (int i = 0;i < lines; ++i)
     	    {
                array[i] = new int[rows];
            }

        }*
		matrix(int a,int b)//�������Ĺ��캯��
		{
		    //cout<<"�����������к���"<<endl;
		    //cin>>lines>>row;
		    this->lines=a;
		    this->rows=b;
			cout<<"����������"<<endl;
			array = new int *[a];
     	    for (int i = 0;i < a; ++i)
     	    {
                array[i] = new int[b];
            }
		}

		matrix(matrix &A)//�������캯��
		{
            cout<<"�������캯��"<<endl;

		    array=new int *[A.lines];
		    for(int i=0;i<A.lines;i++)
                array[i]=new int [A.rows];

            this->lines=A.lines;
            this->rows=A.rows;
		}


		~matrix()//��������
		{
			cout<<"��������"<<endl;
			for(int i = 0 ; i < lines ; i ++ )
                delete []array[i] ;
            delete []array ;
		}

		void input()
		{

   	        cout<<"������һ��"<<lines<<"��"<<rows<<"�еľ���Ԫ��"<<endl;
     		for(int i=0;i<lines;i++)
     		{
          		for(int j=0;j<rows;j++)
          		cin>>this->array[i][j];
     		}
     		//return array;
		}
		void output()
		{
     		for(int i=0;i<lines;i++)
                for(int j=0;j<rows;j++)
                {
                    cout<<array[i][j];
                    if(j==rows-1)
                    cout<<endl;
                    else
                    cout<<' ';
                }
		}
		void add(matrix &a,matrix &b)
		{
    		for(int i=0;i<lines;i++)
    		{
         		for(int j=0;j<rows;j++)
         		{
                	this->array[i][j] =a.array[i][j]+b.array[i][j];
          		}
    		}

		}
		void sub(matrix &a,matrix &b)
		{
    		for(int i=0;i<lines;i++)
    		{
         		for(int j=0;j<rows;j++)
         		{
                	this->array[i][j] = a.array[i][j]-b.array[i][j];
          		}
    		}
		}

 };
int main()
{
    int temp_line,temp_row;
    cout<<"��������������������"<<endl;
    cin>>temp_line>>temp_row;

    cout<<temp_line<<temp_row<<endl;


	matrix A1(temp_line,temp_row);
	matrix A2=A1;//��������
	matrix A3=A1;

	A1.input();
	A2.input();
	cout<<"A1����Ϊ��"<<endl;
	A1.output();
	cout<<"A2����Ϊ��"<<endl;
	A2.output();

	A3.add(A1,A2);
	cout<<"�����������Ϊ��"<<endl;
	A3.output();

	A3.sub(A1,A2);
	cout<<"�����������Ϊ��"<<endl;
	A3.output();

    matrix *pA1,*pA2,*pA3;
    cout<<"��������������������"<<endl;
    cin>>temp_line>>temp_row;

    cout<<temp_line<<temp_row<<endl;

	pA1=new matrix(temp_line,temp_row);
	pA2=new matrix(temp_line,temp_row);
	pA3=new matrix(temp_line,temp_row);

	pA1->input();
	cout<<"A1����Ϊ��"<<endl;
	pA1->output();

	pA2->input();
	cout<<"A2����Ϊ��"<<endl;
	pA2->output();

	pA1->output();

	pA3->add(*pA1,*pA2);
	cout<<"�����������Ϊ��"<<endl;
	pA3->output();

	pA3->sub(*pA1,*pA2);
	cout<<"�����������Ϊ��"<<endl;
	pA3->output();

	delete pA1;
	delete pA2;
	delete pA3;

	system("pause");
	return 0;
}















