
#include<iostream>

#include <vector>

using namespace std;
const int inf = 65535;
const int n = 15;
int L[n][n] = {inf,11,30,10,28,6,31,2,2,8,12,9,23,7,21,
			   11,inf,22,20,6,7,23,23,22,11,7,23,9,12,12,
			   30,22,inf,2,2,23,23,32,30,29,27,10,24,14,13,
			   6,20,2,inf,3,24,25,29,28,37,25,11,28,9,9,
			   28,8,6,6,inf,22,21,30,30,29,27,17,24,7,7,
   			   4,4,23,24,22,inf,1,41,40,2,22,39,23,3,24,
   			   31,23,23,25,21,1,inf,40,40,23,22,39,20,25,25,
   			   2,23,32,29,30,41,40,inf,2,22,19,22,25,22,21,
   			   2,22,30,28,30,40,40,2,inf,22,20,21,24,20,21,
   			   4,11,29,37,29,3,23,22,22,inf,2,30,2,5,23,
   			   6,4,27,25,27,22,22,19,20,2,inf,28,3,19,19,
   			   4,22,10,11,17,39,39,22,21,30,28,inf,32,4,11,
   			   23,9,24,28,24,23,20,25,24,2,3,32,inf,23,22,			
   			   4,5,14,9,7,8,25,22,20,2,19,3,23,inf,1,
   			   21,23,13,9,7,24,25,21,21,23,19,11,22,1,inf 
                 };               //存储图中的路径
int dis[n][n];        //存储源点到各个顶点的最短路径

vector<int> path[n][n];

int main()
{
	for (int i = 0; i < n; i++)              //初始化
	{
		for (int j = 0; j < n; j++)
		{
			dis[i][j] = L[i][j];
			path[i][j].push_back(i+1);
		    path[i][j].push_back(j+1);
		}
	}
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
	   {
		for (int j = 0; j < n; j++)
		{
				//dis[i] = min(dis[i],dis[j] + L[j][i]);
			if (dis[k][i] > dis[k][j] + L[j][i])               //求源点到节点的最短路径，利用现有的L矩阵
			{
				dis[k][i] = dis[k][j] + L[j][i];
				path[k][i].clear();                         //保存并更新路径
				path[k][i].insert(path[k][i].end(), path[k][j].begin(),path[k][j].end());
				path[k][i].push_back(i+1);
			}
		}
		for (int m = 0; m < i; m++)              //更新节点最短路径
		{
			for(int j = 0; j < n; j++)
			{
				if (dis[k][m] > dis[k][j] + L[j][m])
				{
					dis[k][m] = dis[k][j] + L[j][m];
					path[k][m].clear();                     //保存并更新路径
					path[k][m].insert(path[k][m].end(), path[k][j].begin(), path[k][j].end());
					path[k][m].push_back(m + 1);
				}
			}
		}
	}
	}
/*	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			cout<<L[k][i]<<"  ";
		}
		cout<<endl;
	}
*/	
	
	vector<int>::iterator ite;
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
	{
	
		cout << "源点"<<k<<"到"<<i<<"的最短路径长度：" << dis[k][i]<<endl<<"Path：";
	    for (ite = path[k][i].begin(); ite !=path[k][i].end();++ite) {
		    if (ite == path[k][i].begin())
			    cout << *ite-1;
		    else
			    cout << "->"<< *ite-1 ;
	}
	    cout << endl;
	}
	}
	return 0;
}


