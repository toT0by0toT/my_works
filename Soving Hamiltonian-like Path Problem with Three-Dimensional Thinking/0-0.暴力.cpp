#include<iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

#define n 6 //graph for n*n
#define rn 3 //random max
int graph[n][n];//graph相鄰矩陣 
int fg[n*(n-1)][3],fg_=0;//[n,[n,g
int sn[n]={0};//節點教師數判斷 
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

void violent(int r,int total)
{
	//判斷 
	if(r==fg_)
	{
		for(int k=0;k<n;k++)
		{
			if(sn[k]!=0)
			{
				return;
			}
		}
		if(total>answer)
		{
			answer=total;
		}
		return;
	}
	for(int k=0;k<=fg[r][2];k++)
	{
		sn[fg[r][0]]-=k;
		sn[fg[r][1]]+=k;
		violent(r+1,total+k);
		sn[fg[r][0]]+=k;
		sn[fg[r][1]]-=k;
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
	random(rn);//可指定路徑最大值 
	
	//輸入產生圖
//	input(); 
	
	//2.產生要回溯的graph 
	
	cout<<"------------------------\n";
	
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			if(graph[k][t]!=-1)
			{
				fg[fg_][0]=k;
				fg[fg_][1]=t;
				fg[fg_][2]=graph[k][t];
				fg_++;
			}
		} 
	}
	violent(0,0);
	cout<<"最大值為"<<answer<<endl;
}
