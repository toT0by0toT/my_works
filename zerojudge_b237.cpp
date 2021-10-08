#include<iostream>
#include<cstring>
using namespace std;
char g1[251][251];
int g2[250][250][4]={0};//距離，第幾條路，標記點
int p[62500][2],p_=1;
int q[62500][2],q_=1;
int u=0;
int n,m;
int h(int x)
{
	if(x>0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}
int f(int d)
{
//	for(int k=0;k<n;k++)
//	{
//		for(int t=0;t<m;t++)
//		{
//			cout<<g2[k][t][1]<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;
	if(p_==0)
	{
		return 0;
	}
	q_=p_;
	for(int k=0;k<q_;k++)
	{
		q[k][0]=p[k][0];
		q[k][1]=p[k][1];
	}
	p_=0;
	
	for(int k=0;k<q_;k++)
	{
		int x=q[k][0],y=q[k][1];
		int r[4]={0},r_=0;
		if(g1[x][y+1]=='.' && g2[x][y+1][0]==0)
		{
			r_++;
			r[0]=1;
		}
			
		if(g1[x][y-1]=='.' && g2[x][y-1][0]==0)
		{
			r_++;
			r[1]=1;
		}
		if(g1[x+1][y]=='.' && g2[x+1][y][0]==0)
		{
			r_++;
			r[2]=1;
		}
		if(g1[x-1][y]=='.' && g2[x-1][y][0]==0)
		{
			r_++;
			r[3]=1;
		}
			
		if(r_==0)
		{
			continue;
		}
		else if(r_==1)
		{
			if(r[0]==1)
			{
				p[p_][0]=x;
				p[p_][1]=y+1;
				p_++;
				g2[x][y+1][0]=d;
				g2[x][y+1][1]=g2[x][y][1];
				g2[x][y+1][2]=g2[x][y][2];
				g2[x][y+1][3]=g2[x][y][3];
				
			}
			else if(r[1]==1)
			{
				p[p_][0]=x;
				p[p_][1]=y-1;
				p_++;
				g2[x][y-1][0]=d;
				g2[x][y-1][1]=g2[x][y][1];
				g2[x][y-1][2]=g2[x][y][2];
				g2[x][y-1][3]=g2[x][y][3];
			}
			else if(r[2]==1)
			{
				p[p_][0]=x+1;
				p[p_][1]=y;
				p_++;
				g2[x+1][y][0]=d;
				g2[x+1][y][1]=g2[x][y][1];
				g2[x+1][y][2]=g2[x][y][2];
				g2[x+1][y][3]=g2[x][y][3];
			}
			else
			{
				p[p_][0]=x-1;
				p[p_][1]=y;
				p_++;
				g2[x-1][y][0]=d;
				g2[x-1][y][1]=g2[x][y][1];
				g2[x-1][y][2]=g2[x][y][2];
				g2[x-1][y][3]=g2[x][y][3];
			}
		}
		else
		{
			if(r[0]==1)
			{
				p[p_][0]=x;
				p[p_][1]=y+1;
				p_++;
				g2[x][y+1][0]=d;
				u++;
				g2[x][y+1][1]=u;
				g2[x][y+1][2]=x;
				g2[x][y+1][3]=y;
			}
			if(r[1]==1)
			{
				p[p_][0]=x;
				p[p_][1]=y-1;
				p_++;
				g2[x][y-1][0]=d;
				u++;
				g2[x][y-1][1]=u;
				g2[x][y-1][2]=x;
				g2[x][y-1][3]=y;
			}
			if(r[2]==1)
			{
				p[p_][0]=x+1;
				p[p_][1]=y;
				p_++;
				g2[x+1][y][0]=d;
				u++;
				g2[x+1][y][1]=u;
				g2[x+1][y][2]=x;
				g2[x+1][y][3]=y;
			}
			if(r[3]==1)
			{
				p[p_][0]=x-1;
				p[p_][1]=y;
				p_++;
				g2[x-1][y][0]=d;
				u++;
				g2[x-1][y][1]=u;
				g2[x-1][y][2]=x;
				g2[x-1][y][3]=y;
			}
		}
		
	}
	return f(d+1);
}

int main()
{
	int e;
	cin>>n>>m>>e;
	for(int k=0;k<n;k++)
	{
		cin>>g1[k];
	}
	
	int a1,a2;
	for(int k=0;k<n*m;k++)
	{
		int x=k/n,y=k%m;
		if(g1[x][y]=='.')
		{
			a1=x;
			a2=y;
			break;
		}
	}
	g2[a1][a2][0]=1;
	g2[a1][a2][1]=0;
	g2[a1][a2][2]=a1;
	g2[a1][a2][3]=a2;
	p[0][0]=a1;
	p[0][1]=a2;
	f(2);
//	for(int k=0;k<n;k++)
//	{
//		for(int t=0;t<m;t++)
//		{
//			cout<<k<<" "<<t<<" .";
//			for(int i=0;i<4;i++)
//			{
//				cout<<g2[k][t][i]<<" ";
//			}
//			cout<<endl;
//		}
//	}
	int total=0;
	for(int k=0;k<e;k++)
	{
		for(int k=0;k<n;k++)
		{
			for(int t=0;t<m;t++)
			{
				if(g2[k][t][1]<10)
				{
					cout<<" ";
				}
				if(g2[k][t][0]==0)
				{
					cout<<'#'<<" ";
					continue;
				}
				cout<<g2[k][t][1]<<" ";
			}
			cout<<endl;
		}
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
//		for(int k=0;k<n;k++)
//		{
//			for(int t=0;t<m;t++)
//			{
//				if(k==x1 && t==x2)
//				{
//					cout<<" * ";
//				}
//				else if(k==y1 && t==y2)
//				{
//					cout<<" * ";
//				}
//				else if(g1[k][t]=='.')
//				{
//					cout<<" ";
//					cout<<g2[k][t][1];
//					if(g2[k][t][1]<10)
//						cout<<" ";
//				}
//				else 
//				{
//					cout<<" "<<g1[k][t]<<" ";
//				}
//			}
//			cout<<endl;
//		}
//		cout<<endl;
		int as1=x1,as2=x2,ad1=y1,ad2=y2;
		while(1)
		{
			if(g2[as1][as2][1]==g2[ad1][ad2][1])
			{
				total+=g2[x1][x2][0]-g2[as1][as2][0]+g2[y1][y2][0]-g2[ad1][ad2][0]+h(g2[as1][as2][0]-g2[ad1][ad2][0]);
				break;
			}
			else if(g2[as1][as2][2]==g2[ad1][ad2][2] && g2[as1][as2][3]==g2[ad1][ad2][3])
			{
				int sd1=g2[as1][as2][2],sd2=g2[as1][as2][3];
				total+=g2[x1][x2][0]-g2[sd1][sd2][0]+g2[y1][y2][0]-g2[sd1][sd2][0];
				break;
			}
			else
			{
				if(g2[as1][as2][0]>g2[ad1][ad2][0])
				{
					int sd1=g2[as1][as2][2],sd2=g2[as1][as2][3];
					as1=sd1;
					as2=sd2;
				}
				else
				{
					int sd1=g2[ad1][ad2][2],sd2=g2[ad1][ad2][3];
					ad1=sd1;
					ad2=sd2;
				}
			}
		}
	}
	cout<<total;
}
