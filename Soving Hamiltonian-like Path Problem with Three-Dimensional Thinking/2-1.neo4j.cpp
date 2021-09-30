#include<iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
#define n 7 //graph for n*n
int graph[n][n];//graph相鄰矩陣 

void input()
{
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			cin>>graph[k][t];
		}
	}
}

void neo4j(void)
{
	cout<<"MATCH (n) DETACH DELETE n\n\n";
	
	cout<<"CREATE (a:Person { name: "<<'"'<<"A"<<'"'<<" })";
	for(int k=1;k<n;k++)
	{
		cout<<",("<<(char)(97+k)<<":Person { name: "<<'"'<<(char)(65+k)<<'"'<<"})";
	}
	for(int k=0;k<n;k++)
	{
		for(int t=0;t<n;t++)
		{
			if(graph[k][t]>0)
			{
				cout<<",("<<(char)(97+k)<<")-[:KNOWS{m:"<<graph[k][t]<<"}]->("<<(char)(97+t)<<")";
			}
		}
	}
	cout<<endl<<endl;
	
	cout<<"MATCH (all:Person)-[:KNOWS]-(friends)\n";
	cout<<"RETURN all,friends";
	cout<<endl;
}

int main()
{
	cout<<"array:\n";
	//1.產生graph 

	//輸入產生圖
	input(); 
	
	cout<<endl<<"javascript:\n";
	
	neo4j();
}
