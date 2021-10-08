#include<cmath>
#include<iostream>
using namespace std;
int decare(int a[],int b[],int t)
{
	for(int k=0;k<t;k++)
	{
		a[k]=b[k];
	}
}
int decpow(int a[],int total[],int s)
{
	int x=0;
	for(int k=s-1;k>=0;k--)
	{
		for(int t=s-1;t>=0;t--)
		{
			total[k+t]=total[k+t]+a[k]*a[t]+x;
			if(total[k+t]>=10)
			{
				x=total[k+t]/10;
				total[k+t]=total[k+t]%10;
			}
			else
			{
				x=0;
			}
			if(t==0 && x!=0)
			{
				total[k+t-1]=total[k+t-1]+x;
			}
		}
		x=0;
	}
}
int decadd(int a[],int b[],int s)
{
	int x=0;
	for(int k=s-1;k>=0;k--)
	{
		a[k]=a[k]+b[k]+x;
		if(a[k]>=10)
		{
			x=a[k]/10;
			a[k]=a[k]%10;
		}
		else
		{
			x=0;
		}
	}
}
int dive(int a[],int x,int y)
{
	int t=0;
	for(t=0;t<10000;t++)
	{
		a[t]=x/y;
		x=x%y;
		if(x==0)
		{
			break;
		}
		x=x*10;
	}
	return t+1;
}
int main()
{
	int t,p,i=2;
	for(int h=20;h>0;h--)
	{
		p=pow(2,i);
		i++;
		int n[10000]={0},g[10000]={0},q[10000]={0};
		t=dive(n,2,p);
		int total[2*t-1]={0};
		decare(g,n,t);
		for(;g[0]<2 || g[1]==0;decadd(g,n,t))
		{
			decare(q,n,t);
			for(;q[0]<2 || q[1]==0;decadd(q,n,t))
			{
				int gtal[2*t-1]={0},qtal[2*t-1]={0},ntal[2*t-1]={0};
				decpow(g,gtal,t);
				decpow(q,qtal,t);
				decadd(gtal,qtal,2*t-1);
				if(gtal[0]<4)
				{
					decpow(n,ntal,t);
					decadd(total,ntal,2*t-1);
				}
			}
		}
		for(int k=0;k<2*t-1;k++)
		{
			cout<<total[k];
		}
		cout<<endl;
	}
	return 0;
}
