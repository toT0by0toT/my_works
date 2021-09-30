#include<iostream>
#include<ctime> 
#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include<cmath>
using namespace std;

#define score_multiple 1000
#define employed_multiple 1000

#pragma GCC optimize(2)
#pragma GCC optimize(3)

//profile
int school_q, **school;
int people_q, **people;

//answer
vector< vector<short> > answer; 
short answer_block=0;
vector <short> answer_temp;

//riot
vector <vector<int> > riot_able_recruit;
int *out_in_school;

//vocation or recruitment
vector< vector<int> > vocation(1); 
vector< vector<int> > employed(1);

//success recruitment
vector< vector<int> > answer_X;
int answer_X_prev=0;
int answer_X_final=0;

bool sort_compare(int a, int b)
{
	return a>b;
}

void graph_reset()
{
	for(int k=0;k<school_q;k++)
	{
		for(int t=0;t<school_q;t++)
		{
			school[k][t]=0;
		}
	}
}

void riot_way_recursion(int total,int th)
{
	if(th==riot_able_recruit.size())
	{
		for(int k=0;k<school_q;k++)
		{
			if(out_in_school[k]!=0)
			{
				return;
			}
		}
		if(total>answer_block)
		{
			answer_block=total;
			answer.clear();
			answer.push_back(answer_temp);
		}
		else if(total==answer_block)
		{
			answer.push_back(answer_temp);
		}
		return;
	}
	for(int k=0;k<=riot_able_recruit[th][2];k++)
	{
		answer_temp.push_back(k);
		
		out_in_school[riot_able_recruit[th][0]]-=k;
		out_in_school[riot_able_recruit[th][1]]+=k;
		riot_way_recursion(total+k,th+1);
		out_in_school[riot_able_recruit[th][0]]+=k;
		out_in_school[riot_able_recruit[th][1]]-=k;
		
		answer_temp.erase(answer_temp.end()-1);
	}
}

void riot_way()
{
	vector <int> riot_able_recruit_temp(3,0);
	for(int k=0;k<school_q;k++)
	{
		for(int t=0;t<school_q;t++)
		{
			if(school[k][t]!=-1)
			{
				riot_able_recruit_temp[0]=k;
				riot_able_recruit_temp[1]=t;
				riot_able_recruit_temp[2]=school[k][t];
				riot_able_recruit.push_back(riot_able_recruit_temp);
			}
		} 
	}
	riot_way_recursion(0,0);
}

void translate_ans_to_voc(int i)
{
	if(answer.empty())
	{
		vocation.push_back(vocation[0]);
		employed.push_back(employed[0]);
	}
	
	graph_reset();
	vector <int> ans_voc;
	vector <int> emp_voc;
	for(int k=0;k<answer.size();k++)
	{
		//answer to graph
		for(int t=0;t<answer[k].size();t++)
		{
			int out=riot_able_recruit[t][0];
			int in=riot_able_recruit[t][1];
			int data=answer[k][t];
			school[out][in]=data;
		}
		
		//copy vocation[0] to ans_voc
		ans_voc.assign(vocation[0].begin(),vocation[0].end());
		//ans_voc = vocation + score*score_multiple
		for(int t=0;t<ans_voc.size();t++)
		{
			int u=ans_voc[t];
			ans_voc[t]=u+people[u][0]*score_multiple;
		}
		
		//copy employed[0] to emp_voc
		emp_voc.assign(employed[0].begin(),employed[0].end());
		
		//sort ans_voc
		sort(ans_voc.begin(),ans_voc.end(),sort_compare);
		for(int t=0;t<ans_voc.size();t++)
		{
			ans_voc[t]=ans_voc[t]%score_multiple;
		}
		//graph decrease
		int r=answer_block;
		for(int t=0;r!=0;t++)
		{
			int a=people[ans_voc[t]][1],b=people[ans_voc[t]][i];
			if(school[a][b]>=1)
			{
				school[a][b]--;
				
				//emp_voc = employed * employed_multiple + i
				emp_voc.push_back(ans_voc[t]*employed_multiple+i);
				
				ans_voc.erase(ans_voc.begin()+t);
				t--;
				r--;
			}
		}
		//put ans_voc into vocation
		vocation.push_back(ans_voc);
		ans_voc.clear();
		
		//put emp_voc into employed
		employed.push_back(emp_voc);
		emp_voc.clear();
	}
	return;
}

int volunteer_sequence(int i)
{
	//people[0]=score
	//people[1]=original school
	//people[2]=new school
	//people[n]=-1
	int answer_block_max=0;
	int na_size=vocation.size(); 
	for(int k=0;k<na_size;k++)
	{
		//graph generater
		for(int t=0;t<vocation[0].size();t++)
		{
			int u=vocation[0][t]; 
			
			//inspect vocation
			if(people[u][i]==-1)
			{
				vocation[0].erase(vocation[0].begin()+t);
				t--;
				continue;
			}
			
			school[ people[u][1] ][ people[u][i] ]++; 
		}
//		for(int x=0;x<school_q;x++)
//		{
//			for(int y=0;y<school_q;y++)
//			{
//				cout<<school[x][y]<<" ";
//			}
//			cout<<endl;
//		}
//		cout<<endl;
		//inspect if finish
		if(vocation[0].empty())
		{
			vocation.erase(vocation.begin());
			
			if(answer_X_final>answer_X_prev)
			{
				answer_X_prev=answer_X_final;
				answer_X.erase(answer_X.begin(),answer_X.end());
			}
			answer_X.push_back(employed[0]);
			employed.erase(employed.begin());
			continue;
		}
		
		////search for answer_block 
		riot_way();
		
		//put into vocation
		if(answer_block>answer_block_max)
		{
			int n=na_size-k;
			vocation.erase(vocation.begin()+n,vocation.end());
			employed.erase(employed.begin()+n,employed.end());
			translate_ans_to_voc(i);
			answer_block_max=answer_block;
		}
		else if(answer_block==answer_block_max)
		{
			translate_ans_to_voc(i);
		}
		
		//parameter & vector reset
		answer_block=0;
		vocation.erase(vocation.begin());
		employed.erase(employed.begin());
		answer.erase(answer.begin(),answer.end());
		riot_able_recruit.clear();
		
		//graph reset
		graph_reset();
	} 
	answer_X_final+=answer_block_max;
	if(vocation.empty())
		return 0;
	else
		return 1;
}

int main()
{
	////input
	//school data
	cout<<"school quantity: ";
	cin>>school_q;
	school=new int *[school_q];
	for(int k=0;k<school_q;k++)
	{
		school[k]=new int [school_q];
		for(int t=0;t<school_q;t++)
		{
			school[k][t]=0;
		}
	}
	
	//people data
	cout<<"people quantity: ";
	cin>>people_q;
	people=new int *[people_q];
	cout<<"score / original school / volunteer quantity / school 1 / school 2 ....\n";
	for(int k=0;k<people_q;k++)
	{	
		////input people number
		int people_v=people_q,v1=-1;
		while(people_v/10)
		{
			v1++;
			people_v=people_v/10;
		}
		int k_v=k,v2=-1;
		while(k_v/10)
		{
			v2++;
			k_v=k_v/10;
		}
		for(int t=0;t<v1-v2;t++)
		{
			cout<<"0";
		}
		cout<<k<<": ";
		
		//input > score, original school, volunteer quantity, new school--1, ....
		//store > score, original school, new school--1, new school--2, ... , -1
		int score,ori_school,volunteer_q;
		cin>>score>>ori_school>>volunteer_q;
		people[k]=new int [volunteer_q+3];
		people[k][0]=score;
		people[k][1]=ori_school;
		for(int t=2;t<volunteer_q+2;t++)
		{
			cin>>people[k][t];
		}
		people[k][volunteer_q+2]=-1;
	}
	out_in_school=new int [people_q]();
	//people[0]=score
	//people[1]=original school
	//people[2]=new school
	//people[n]=-1
	
	cout<<"-------------------------------\n";
	
	////run
	for(int k=0;k<people_q;k++)
	{
		vocation[0].push_back(k);
	} 
	for(int k=2;;k++)
	{
		cout<<k-1<<":\n";
//		for(int x=0;x<vocation.size();x++)
//		{
//			cout<<x<<".";
//			for(int y=0;y<vocation[x].size();y++)
//			{
//				cout<<vocation[x][y]<<" ";
//			}
//			cout<<endl;
//		}
		//find branch
		if(volunteer_sequence(k)==0)
		{
			break;
		}
	}
	for(int k=0;k<answer_X.size();k++)
	{
//		answer_X = people_th * employed_multiple + people volunteer
		sort(answer_X[k].begin(),answer_X[k].end());
		cout<<k<<":";
		for(int t=0;t<answer_X[k].size();t++)
		{
			cout<<answer_X[k][t]<<" ";
		}
		cout<<endl<<endl;
	}
	cout<<endl;
	cout<<"max seccessful people= "<<answer_X_final<<endl;
	cout<<"there are "<<answer_X.size()<<" times combination";
	delete school,people;
}//strcmp
