#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#define n 20 //graph for n*n
#define rn 7 //random max
#define rectl 1000000//rect length
#define o 1
int nu=5;
int pout[5]={3,5,4,2,1};//���w��X 
#define precise_answer 1 
int graph[n][n];//graph�۾F�x�} 
int inspect[n];
int p[1000];//���j�Ȧs�ΰ}�C 
int path[rectl][n+1],path_=0;//�Ҧ��i����|�A���ڥ�-1��ܵ���
float compare[rectl][6];
int compare_;
int answer=0;//�̦h���X�ӤH���\ 
int thou=0;

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
			if(graph[k][t]<10)
			{
				cout<<" ";
			}
			cout<<graph[k][t];
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

void output(void)
{
	for(int k=0;k<compare_;k++)
	{
		for(int t=0;t<3;t++)
		{
			cout<<compare[k][t]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void findpath(int point,int form)//point=A,B,C....;form=p[0,1,2...]
{
//	for(int k=0;k<form;k++)
//	{
//		cout<<p[k]<<",";
//	}
//	cout<<endl;

	if(point==p[0])//�O�_�s�Jpath 
	{
		//�s�J 
		
		for(int k=0;k<form;k++)
		{
			path[path_][k]=p[k];
		}
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

int sequence(int a[],int total)//1=min,2=max,3=length,4=average,5=standard
{
	compare_=path_;
	for(int k=0;k<path_;k++)
	{
		compare[k][0]=k;
	}
	//�R��compare�����Y�q��0
	for(int k=0;k<compare_;k++)
	{
		int u=compare[k][0];
		int r=0;
		int t;
		for(t=0;path[u][t+1]!=-1;t++)
		{
			if(graph[path[u][t]][path[u][t+1]]==0)
			{
				r=1;
				break;
			}
		}
		if(graph[path[u][t]][path[u][0]]==0)
		{
			r=1;
		}
		////
		if(r==1)
		{
			compare_--;
			compare[k][0]=compare[compare_][0];
			k--;
		}
	}
	
	//compare���p�G�S���F��F 
	if(compare_==0)
	{
		if(total>answer)
		{
			answer=total;
		}
		return 0;
	}
	
	//�p��U�ƭ� 
//	cout<<"A."<<endl;
	for(int k=0;k<compare_;k++)
	{
		int mini=15,maxi=0,length;
		float average=0,standard=0;
		int u=compare[k][0];
		int t;
		for(t=0;path[u][t+1]!=-1;t++)
		{
			int w=graph[path[u][t]][path[u][t+1]];
			if(w>maxi)
			{
				maxi=w;
			}
			if(w<mini)
			{
				mini=w;
			}
			average=average+w;
			standard=standard+w*w;
		}
		int w=graph[path[u][t]][path[u][0]];
		if(w>maxi)
		{
			maxi=w;
		}
		if(w<mini)
		{
			mini=w;
		}
		average=average+w;
		standard=standard+w*w;
		t++;
		////
		average=average*1.0;
		average=average/t;
		////
		standard=standard*1.0;
		standard=standard/t-average*average;
		standard=sqrt(standard);
		////
		length=t;
		
		////�s�J
		compare[k][1]=mini;
		compare[k][2]=maxi;
		compare[k][3]=length;
		compare[k][4]=average;
		compare[k][5]=standard;
		
//		cout<<compare[k][0]<<endl;
//		cout<<"max="<<compare[k][1]<<endl;
//		cout<<"min="<<compare[k][2]<<endl;
//		cout<<"length="<<compare[k][3]<<endl;
//		cout<<"average="<<compare[k][4]<<endl;
//		cout<<"standard="<<compare[k][5]<<endl;
	}
//	system("pause");
	//�}�l���
	for(int i=0;i<nu;i++)
	{
		int u=a[i];
		float num;
	 	if(u!=5)
	 	{
	 		num=0;
	 		for(int k=0;k<compare_;k++)
		 	{
		 		if(compare[k][u]>num)
		 		{
		 			num=compare[k][u];
				}
			}
		}
	 	else
	 	{
	 		num=999;
	 		for(int k=0;k<compare_;k++)
		 	{
		 		if(compare[k][u]<num)
		 		{
		 			num=compare[k][u];
				}
			}
		}
//		cout<<"num"<<num<<endl;
		////
		for(int k=0;k<compare_;k++)
	 	{
	 		if(num!=compare[k][u])
	 		{
	 			compare_--;
	 			for(int t=0;t<6;t++)
	 			{
	 				compare[k][t]=compare[compare_][t];
				}
				k--;
			}
		}
	 	//�秹�����G
		if(compare_==1)
		{
			break;
		} 
	}
//	cout<<"B."<<endl;
//	for(int k=0;k<compare_;k++)
//	{
//		cout<<compare[k][0]<<endl;
//		cout<<"max="<<compare[k][1]<<endl;
//		cout<<"min="<<compare[k][2]<<endl;
//		cout<<"length="<<compare[k][3]<<endl;
//		cout<<"average="<<compare[k][4]<<endl;
//		cout<<"standard="<<compare[k][5]<<endl;
//	}
//	system("pause");
	///
	int copycom[compare_];
	int copycom_=compare_;
	for(int k=0;k<compare_;k++)
	{
		copycom[k]=compare[k][0];
//		cout<<copycom[k]<<",";
	}
//	cout<<endl<<endl;

	//
	for(int k=0;k<copycom_;k++)
	{
		int u=copycom[k];
		int t;
		for(t=0;path[u][t+1]!=-1;t++)
		{
			graph[path[u][t]][path[u][t+1]]--;
		}
		graph[path[u][t]][path[u][0]]--;
		sequence(a,total+t+1);
		for(int i=0;i<t;i++)
		{
			graph[path[u][i]][path[u][i+1]]++;
		}
		graph[path[u][t]][path[u][0]]++;
	}
}

int revolve(int a[],int r)//��ƦC 
{
	if(r==1)
	{
		for(int k=0;k<nu;k++)
		{
			cout<<(char)(a[k]+64);
		}
		cout<<endl;
		int s=clock();
		for(int k=0;k<o;k++)
		{
			sequence(a,0);
		}
		cout<<"�Ӯ�"<<clock()-s<<"/"<<o<<"ms"<<endl;
		cout<<"�G��Ȭ�"<<answer<<endl<<endl; 
		
//		system("pause");
		answer=0;
		return 0;
	}
	for(int k=0;k<r;k++)
	{
		int u=a[0];
		for(int t=0;t<r-1;t++)
		{
			a[t]=a[t+1];
		}
		a[r-1]=u;
		revolve(a,r-1);
	}
}

int srevolve(int num[],int kk,int num_)//���զX 
{
	if(num_==nu)
	{
//		for(int k=0;k<nu;k++)
//		{
//			cout<<num[k];
//		}
//		cout<<endl;
		revolve(num,nu); 
		return 0;
	}
	for(int k=kk;k<5;k++)
	{
		num[num_]=k+1;
		srevolve(num,k+1,num_+1);
	}
}

int pointout(int a[])
{
	for(int k=0;k<nu;k++)
	{
		cout<<(char)(a[k]+64);
	}
	cout<<endl;
	int s=clock();
	for(int k=0;k<o;k++)
	{
		sequence(a,0);
	}
	cout<<"�Ӯ�"<<clock()-s<<"/"<<o<<" ms"<<endl;
	cout<<"�G��Ѭ�"<<(float)(answer*1.0/precise_answer)<<endl;
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
		} 
	}
	
	//�H�����͹�
	random(rn);//�i���w���|�̤j�� 
	
	//��J���͹�
//	input(); 

	
	//2.��X�Ҧ��Φ��j������
	
	cout<<"------------------------\n";
	
	//�}�l���j 
	for(int k=0;k<n;k++)
	{
		p[0]=-1;
		inspect[k]=-1;
		findpath(k,0);
		inspect[k]=1;
	} 
	
	///��X�Ҧ��j�� 
//	for(int k=0;k<path_;k++)
//	{
//		if(k<10)
//		{
//			cout<<" ";
//		}
//		cout<<k<<". ";
//		for(int t=0;path[k][t]!=-1;t++)
//		{
//			cout<<path[k][t]<<",";
//		}
//		cout<<path[k][0];
//		cout<<endl;
//	}
	cout<<"�@��"<<path_<<"�Ӱj��"<<endl;
	
	//3.���Ǥ�� 
	
	cout<<"------------------------\n";
	
	//����ƦC
//	for(int k=3;k<=5;k++)
//	{
//		nu=k;
//		int num[nu];
//		srevolve(num,0,0); 
//	}
	
	//���w��J 
	pointout(pout);
	
}
