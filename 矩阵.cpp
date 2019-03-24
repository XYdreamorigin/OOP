#include<iostream>
using namespace std;
#define a 2 
#define b 2 

int** input(int**);
void output(int**);	
int ** add(int **,int **,int **);
int ** sub(int **,int **,int **);

 
int main(void)
{
    int **A1,**A2,**A3;   
    A1=input(A1);
    output(A1);
    A2=input(A2);
    output(A2);
    A3=add(A1,A2,A3);
    cout<<"相加的结果为"<<endl; 
    output(A3);
    cout<<"相减的结果为"<<endl; 
    output(sub(A1,A2,A3));
    
    
    for(int i = 0 ; i < a ; i ++ )
    delete []A1[i] ; 
    delete []A1 ; 
    
    for(int i = 0 ; i < a ; i ++ )
    delete []A2[i] ; 
    delete []A2 ; 
    
    for(int i = 0 ; i < a ; i ++ )
    delete []A3[i] ; 
    delete []A3 ; 
    system("pause");
    return 0;
}
int ** input(int **array)
{
     array = new int *[a];
     for (int i = 0;i < a; ++i)
     {
         array[i] = new int[b];
     }
     cout<<"请输入矩阵的元素"<<endl;
     for(int i=0;i<a;i++)
     {
          for(int j=0;j<b;j++)
          cin>>array[i][j];
     }
     return array;    
} 
void output(int **array2)
{    
     for(int i=0;i<a;i++)
         for(int j=0;j<b;j++)
         {
             cout<<array2[i][j];
             if(j==b-1)
             cout<<endl;
             else
             cout<<' ';
         }
     
}
int ** add(int **array1,int **array2,int **array3)
{
    array3 = new int *[a];
     for (int i = 0;i < a; ++i)
     {
         array3[i] = new int[b];
     }
    for(int i=0;i<a;i++)
    {
          for(int j=0;j<b;j++)
          {
                array3[i][j] = array1[i][j]+array2[i][j];
          }
                  
    }
    return array3;
}
     
int ** sub(int **array1,int **array2,int **array3)
{
    for(int i=0;i<a;i++)
    {
          for(int j=0;j<b;j++)
          {
                array3[i][j] = array1[i][j]-array2[i][j];
          }
                  
    }
    return array3;
}
