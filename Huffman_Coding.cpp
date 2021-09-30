#include<iostream>
#include<string.h>
using namespace std;
int main()
{
	char a[100000];
	gets(a);
	int x=strlen(a);
	int e[26],e_=26;
	for(int k=0;k<26;k++)
	{
		e[k]=0;
	}
	for(int k=0;k<x;k++)
	{
		if(a[k]>=65 && a[k]<=90)
		{
			e[a[k]-65]++;
		}
		else if(a[k]>=97 && a[k]<=122)
		{
			e[a[k]-97]++;
		}
	}
	char p[26][26];
	int p_[26];
	char i[26][26];
	int i_[26];
	for(int k=0;k<26;k++)
	{
		p[k][0]=(char)(k+65);
		p_[k]=1;
		i_[k]=0;
	}
	while(e_!=1)
	{
		int g=e[0],g_=0;
		for(int k=1;k<e_;k++)
		{
			if(e[k]<g)
			{
				g=e[k];
				g_=k;
			}
		}
		int h,h_;
		if(g_==0)
		{
			h=e[1];
			h_=1;
		}
		else
		{
			h=e[0];
			h_=0;
		}
		for(int k=0;k<e_;k++)
		{
			if(k==g_)
			{
			}
			else if(e[k]<h)
			{
				h=e[k];
				h_=k;
			}
		}
		for(int k=0;k<p_[g_];k++)
		{
			i[p[g_][k]-65][i_[p[g_][k]-65]]='0';
			i_[p[g_][k]-65]++;
		}
		for(int k=0;k<p_[h_];k++)
		{
			i[p[h_][k]-65][i_[p[h_][k]-65]]='1';
			i_[p[h_][k]-65]++;
		}
		e[g_]=g+h;
		for(int k=p_[g_];k<p_[g_]+p_[h_];k++)
		{
			p[g_][k]=p[h_][k-p_[g_]];
		}
		p_[g_]=p_[g_]+p_[h_];
		for(int k=h_;k<e_-1;k++)
		{
			e[k]=e[k+1];
			p_[k]=p_[k+1];
			for(int t=0;t<p_[k];t++)
			{
				p[k][t]=p[k+1][t];
			}
		}
		e_--;
	}
	for(int k=0;k<26;k++)
	{
		cout<<(char)(k+65)<<" ";
		for(int t=i_[k]-1;t>=0;t--)
		{
			cout<<i[k][t];
		}
		cout<<endl;
	}
}
