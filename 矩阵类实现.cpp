#include<iostream>
#include<stdlib.h>
using namespace std;
#define row 2
#define col 2
class matrix
{
	public:
	    int **array;
		matrix()
		{
			cout<<"456566"<<endl;
			array = new int *[row];
     	    for (int i = 0;i < row; ++i)
     	    {
                array[i] = new int[col];
            }
		}
		~matrix()
		{
			cout<<"4566"<<endl;
			for(int i = 0 ; i < row ; i ++ )
                delete []array[i] ;
            delete []array ;
		}
		void input()
		{
   	        cout<<"请输入矩阵的元素"<<endl;
     		for(int i=0;i<row;i++)
     		{
          		for(int j=0;j<col;j++)
          		cin>>array[i][j];
     		}
     		//return array;
		}
		void output()
		{
     		for(int i=0;i<row;i++)
         	for(int j=0;j<col;j++)
         	{
             	cout<<array[i][j];
             	if(j==col-1)
             	cout<<endl;
             	else
             	cout<<' ';
         	}
		}
		void add(matrix a,matrix b)
		{
    		for(int i=0;i<row;i++)
    		{
         		for(int j=0;j<col;j++)
         		{
                	this->array[i][j] =a.array[i][j]+b.array[i][j];
          		}
    		}

		}
		void sub(matrix a,matrix b)
		{
    		for(int i=0;i<row;i++)
    		{
         		for(int j=0;j<col;j++)
         		{
                	this->array[i][j] = a.array[i][j]-b.array[i][j];
          		}
    		}
		}

 };
int main()
{
	matrix A1,A2,A3;

	A1.input();
	A2.input();
	cout<<"A1矩阵为："<<endl;
	A1.output();
	cout<<"A2矩阵为："<<endl;
	A2.output();

	A3.add(A1,A2);
	cout<<"两个矩阵相加为："<<endl;
	A3.output();

	A3.sub(A1,A2);
	cout<<"两个矩阵相减为："<<endl;
	A3.output();

//	A2.output();
	system("pause");
	return 0;
}















