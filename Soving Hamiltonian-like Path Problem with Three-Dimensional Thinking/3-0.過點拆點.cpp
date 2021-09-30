#include<iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

#define n 8 //graph for n*n
#define rn 10 //random max
#define rectl 100000//rect length=

int graph[n][n];//graph相鄰矩陣 
int inspect[n]={0};
int p[1000];//遞迴暫存用陣列 
int path[rectl][n+1],path_=0;//所有可行路徑，尾巴用-1表示結束
int maxpath[rectl][100],maxpath_=0;
int answer=0;//最多有幾個人成功 

void random(int range)
{
	//前置作業 
	srand(time(NULL));
	int g1[n],g2[n];
	for(int k=0;k<n;k++)
	{
		g1[k]=0;
		g2[k]=0;
	}
	
	//建立亂數圖 
	while(1)
	{
		//產生亂數 
		int r1=rand()%n;
		int r2=rand()%n;
		while(r2==r1)
		{
			r2=rand()%n;
		}
		graph[r1][r2]=rand()%range+1;
		g1[r1]=1;
		g2[r2]=1;
		
		//A~Z檢否一進一出 
		int s=0;
		for(int k=0;k<n;k++)
		{
			if(g1[k]==0 || g2[k]==0)
			{
				s=1;
				break;
			}
		}
		if(s==0)
		{
			break;
		}
	}
	
	//輸出圖 
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			if(graph[k][t]>0)
			{
				cout<<" ";
			}
			cout<<graph[k][t]<<" ";
		}
		cout<<endl;
	}
}

void input(void)
{
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			cin>>graph[k][t];
		}
	}
}

void findpath(int point,int form)//point=A,B,C....;form=p[0,1,2...]
{
//	for(int k=0;k<form;k++)
//	{
//		cout<<p[k]<<",";
//	}
//	cout<<endl;

	if(point==p[0])//是否存入path 
	{
		//存入 
		
		for(int k=0;k<form;k++)
		{
//			cout<<p[k]<<",";
			path[path_][k]=p[k];
		}
//		cout<<endl;
		path[path_][form]=-1;
		path_++;
		if(path_==rectl)
		{
			cout<<1;
			system("pause");
		}
		
		return;
	}
	
	p[form]=point;
	for(int k=0;k<n;k++)
	{
//		for(int i=0;i<form;i++)
//		{
//			cout<<"      ";
//		}
//		cout<<point<<"-"<<k;
		if(graph[point][k]>0 && inspect[k]<=0)
		{
//			cout<<"(O)"<<endl;
			inspect[k]++;
			findpath(k,form+1);
			inspect[k]--;
		}
		else
		{
//			cout<<"(X)"<<endl;
		}
	}
	return;
}

void pathout()
{
	for(int k=0;k<path_;k++)
	{
		if(k<10)
		{
			cout<<" ";
		}
		cout<<k<<". ";
		for(int t=0;path[k][t]!=-1;t++)
		{
			cout<<path[k][t]<<",";
		}
		cout<<path[k][0];
		cout<<endl;
	}
}

int findmax(int total,int th,int form)//th=選哪個迴圈; 
{
	int u=0;
	for(int k=th;k<path_;k++)
	{
		int t,r=0;
		
		//檢驗是否無法繼續扣 
		for(t=0;path[k][t+1]!=-1;t++)
		{
			if(graph[path[k][t]][path[k][t+1]]==0)
			{
				r=1;
				break;
			}
		}
		if(graph[path[k][t]][path[k][0]]==0)
		{
			r=1;
		}
		
		//不給過，決定是否存入max 
		if(r==1)
		{
			if(total>answer)
			{
				for(int i=0;i<form;i++)
				{
					maxpath[0][i]=p[i];
				}
				maxpath[0][form]=-1;
				maxpath_=1;
				answer=total;
			}
			else if(total==answer)
			{
				if(u==1)
				{
					continue;
				}
				for(int i=0;i<form;i++)
				{
					maxpath[maxpath_][i]=p[i];
				}
				maxpath[maxpath_][form]=-1;
				maxpath_++;
			}
			u=1;
			continue;
		}
		
		//通過的放入p 
		p[form]=k;
		u=0;
		
		//通過的開始扣款
		for(int i=0;i<t;i++)
		{
			graph[path[k][i]][path[k][i+1]]--;
		}
		graph[path[k][t]][path[k][0]]--;
		
		//進入遞迴
		findmax(total+t+1,k,form+1); 
		
		//要記得還款 
		for(int i=0;i<t;i++)
		{
			graph[path[k][i]][path[k][i+1]]++;
		}
		graph[path[k][t]][path[k][0]]++;
	}
}

void ansout()
{
	for(int k=0;k<maxpath_;k++)
	{
		for(int t=0;maxpath[k][t]!=-1;t++)
		{
			cout<<maxpath[k][t]<<",";
		}
		cout<<endl;
	}
}

int main()
{
	//1.產生graph 

	//各格歸-1
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			graph[k][t]=-1;
		} 
	}
	
	//隨機產生圖
//	random(rn);//可指定路徑最大值 
	
	//輸入產生圖
	input(); 

	//2.找出所有形成迴路之解
	
	cout<<"------------------------\n";
	
	//開始遞迴 
	for(int i=0;i<100;i++)
	{
		path_=0;
		for(int k=0;k<n;k++)
		{
			p[0]=-1;
			inspect[k]=-1;
			findpath(k,0);
			inspect[k]=1;
		} 
		for(int k=0;k<n;k++)
		{
			inspect[k]=0;
		}
	}

	//輸出所有迴圈 
	pathout();
	
	cout<<"共有"<<path_<<"個迴圈"<<endl;
	
	//3.試試最佳組合
	
	cout<<"------------------------\n";
	
	//開始遞迴
	
	findmax(0,0,0);
	
	////輸出最大值之所有解
	ansout();

	cout<<"共有"<<maxpath_<<"個最大走法"<<endl;
	cout<<"最大值為"<<answer<<endl;
}
