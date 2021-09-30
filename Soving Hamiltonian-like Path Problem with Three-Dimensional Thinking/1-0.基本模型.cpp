#include<iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

#define n 8 //graph for n*n
int graph[n][n];//graph�۾F�x�} 
int route[n][n];//�P�_�O�_���L 
int p[100000];//���j�Ȧs�ΰ}�C 
int path[1000000][(n-1)*(n-2)+3],path_=0;//�Ҧ��i����|�A���ڥ�-1��ܵ���
int maxpath[1000000][100],maxpath_=0;
int answer=0;//�̦h���X�ӤH���\ 

void random(int range)
{
	//�e�m�@�~ 
	srand(time(NULL));
	int g1[n],g2[n];
	for(int k=0;k<n;k++)
	{
		g1[k]=0;
		g2[k]=0;
	}
	
	//�إ߶üƹ� 
	while(1)
	{
		//���Ͷü� 
		int r1=rand()%n;
		int r2=rand()%n;
		while(r2==r1)
		{
			r2=rand()%n;
		}
		graph[r1][r2]=rand()%range+1;
		g1[r1]=1;
		g2[r2]=1;
		
		//A~Z�˧_�@�i�@�X 
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
	
	//��X�� 
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

int findpath(int point,int form)//point=A,B,C....;form=p[0,1,2...]
{
//	for(int k=0;k<form;k++)
//	{
//		cout<<p[k]<<",";
//	}
//	cout<<endl;
	
	if(point==p[0])//�O�_�s�Jpath 
	{
		//����O�_�j������ (�i²���A��}�Y) 
		for(int k=0;k<path_;k++)//��path_�ӭn�� 
		{
			int x=0;
			for(;path[k][x]!=-1;x++)//�ӼƬO�_�@�� 
			{
			}
			if(x!=form)
			{
				continue;
			}
			int s=0;
			//�ӼƬۦP�A�}�l�ոհj��
			for(int t=0;t<form;t++) //�ݭnform���A�մ�p�ӹ�� 
			{
				//�մ�p 
				int r=p[0];
				for(int i=0;i<form-1;i++)
				{
					p[i]=p[i+1];
				}
				p[form-1]=r;
				
				//���
				r=0;
				if(s==1)
				{
					continue;
				} 
				for(int i=0;i<form;i++)
				{
					if(path[k][i]!=p[i])
					{
						r=1;
						break;
					}
				}
				if(r==0)
				{
					s=1;
				}
			}
			//�O�_����
			if(s==1)
			{
				return 0;
			}
		}//*/
		
		//�s�J 
		
		for(int k=0;k<form;k++)
		{
//			cout<<p[k]<<",";
			path[path_][k]=p[k];
		}
//		cout<<endl;
		path[path_][form]=-1;
		path_++;
		return 0;
	}
	p[form]=point;
	for(int k=0;k<n;k++)
	{
//		for(int i=0;i<form;i++)
//		{
//			cout<<"      ";
//		}
//		cout<<point<<"-"<<k;
		if(graph[point][k]>0 && route[point][k]==0)
		{
//			cout<<"(O)"<<endl;
			route[point][k]=1;
			findpath(k,form+1);
			route[point][k]=0;
		}
		else
		{
//			cout<<"(X)"<<endl;
		}
	}
	return 0;
}

int pathout()
{
	for(int k=0;k<path_;k++)
	{
		if(k<10)
		{
			cout<<" ";
		}
		cout<<k+1<<". ";
		for(int t=0;path[k][t]!=-1;t++)
		{
			cout<<(char)(path[k][t]+65)<<",";
		}
		cout<<(char)(path[k][0]+65);
		cout<<endl;
	}
}

int findmax(int total,int th,int form)//th=����Ӱj��; 
{
	int u=0;
	for(int k=th;k<path_;k++)
	{
		int t,r=0;
		
		//����O�_�L�k�~�� 
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
		
		//�����L�A�M�w�O�_�s�Jmax 
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
		
		//�q�L����Jp 
		p[form]=k;
		u=0;
		
		//�q�L���}�l����
		for(int i=0;i<t;i++)
		{
			graph[path[k][i]][path[k][i+1]]--;
		}
		graph[path[k][t]][path[k][0]]--;
		
		//�i�J���j
		findmax(total+t+1,k,form+1); 
		
		//�n�O�o�ٴ� 
		for(int i=0;i<t;i++)
		{
			graph[path[k][i]][path[k][i+1]]++;
		}
		graph[path[k][t]][path[k][0]]++;
	}
}

int ansout()
{
	for(int k=0;k<maxpath_;k++)
	{
		cout<<k+1<<". ";
		for(int t=0;maxpath[k][t]!=-1;t++)
		{
			cout<<maxpath[k][t]<<",";
		}
		cout<<endl;
	} 
}

int main()
{
	//1.����graph 

	//�U���k-1
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			graph[k][t]=-1;
			route[k][t]=0;
		} 
	}
	 
	
	//�H�����͹�
	random(5);//�i���w���|�̤j�� 
	
	//��J���͹�
//	input(); 
	
	//2.��X�Ҧ��Φ��j������
	
	cout<<"------------------------\n";
	
	//�}�l��j��
	for(int k=0;k<n;k++)
	{
		p[0]=-1;
		findpath(k,0);
	} 
	
	//��X�Ҧ��j�� 
	pathout();
	
	cout<<"�@��"<<path_<<"�Ӱj��"<<endl;
	
	//3.�ոճ̨βզX
	
	cout<<"------------------------\n";
	
	//�}�l���j
	findmax(0,0,0);
	
	//��X�̤j�Ȥ��Ҧ���
	ansout();
	
	cout<<"�@��"<<maxpath_<<"�ӳ̤j���k"<<endl;
	cout<<"�̤j�Ȭ�"<<answer;
}
