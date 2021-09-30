#include<iostream>
#include<ctime> 
#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include<cmath>
using namespace std;

#define score_multiple 10000
#define employed_multiple 10000

#pragma GCC optimize(2)
#pragma GCC optimize(3)

//profile
int school_q, **school;
int people_q, **people;

//path & answer
vector <short> path_answer_temp;

//path
vector< vector<short> > path; 
short path_confirmed[1000]={0};

//answer
vector< vector<short> > answer; 
short answer_block=0;
set <string> answer_set;

//filter
vector< vector<int> > compare;
vector <short> filter;

//layer
short leap=1;

//vocation or recruitment
vector< vector<int> > vocation(1); 
vector< vector<int> > employed(1);//amswer_X

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

void findpath(int point)//point=A,B,C....
{
	
	if(path_answer_temp.empty())//避免錯誤 
	{
		
	}
	else if(point==path_answer_temp[0])//是否存入path 
	{
		path.push_back(path_answer_temp);
		return;
	}
	path_answer_temp.push_back(point);
	for(int k=0;k<school_q;k++)
	{
		if(school[point][k]>0 && path_confirmed[k]<=0)
		{
			path_confirmed[k]++;
			findpath(k);
			path_confirmed[k]--;
		}
	}
	path_answer_temp.erase(path_answer_temp.end()-1);
	return;
}

void search_path()
{
	for(int k=0;k<school_q;k++)
	{
		path_confirmed[k]=-1;
		findpath(k);
		path_confirmed[k]=1;
	} 
	for(int k=0;k<school_q;k++)
	{
		path_confirmed[k]=0;
	}
}

void complete_way_recursion(int total,int th)//th=選哪個迴圈
{
	int u=0;//避免重複放置 
	for(int k=th;k<path.size();k++)
	{
		int t,r=0;
		//檢驗是否無法繼續扣 
		for(t=0;t<path[k].size()-1;t++)
		{
			if(school[path[k][t]][path[k][t+1]]==0)
			{
				r=1;
				break;
			}
		}
		if(school[path[k][t]][path[k][0]]==0)
		{
			r=1;
		}
		/////////////////////
		
		//不給過，決定是否存入max 
		if(r==1)
		{
			if(u==1)
			{
				continue;
			}
			  
			if(total>answer_block)
			{
				answer.erase(answer.begin(),answer.end());
				answer.push_back(path_answer_temp);
				answer_block=total;
			}
			else if(total==answer_block)
			{
				answer.push_back(path_answer_temp);
			}
			u=1;
			continue;
		}
		//通過的放入p 
		path_answer_temp.push_back(k);
		u=0;
		//通過的開始扣款
		for(int i=0;i<t;i++)
		{
			school[path[k][i]][path[k][i+1]]--;
		}
		school[path[k][t]][path[k][0]]--;
		
		//進入遞迴
		complete_way_recursion(total+t+1,k); 
		
		//拿出p
		path_answer_temp.erase(path_answer_temp.end()-1); 
		//要記得還款 
		for(int i=0;i<t;i++)
		{
			school[path[k][i]][path[k][i+1]]++;
		}
		school[path[k][t]][path[k][0]]++;
	}
	return;
}

void complete_way()
{
	complete_way_recursion(0,0);
	return;
}

void filter_way_recursion(int total,vector <short> path_select)//a[]=哪種篩選法 
{
//	for(int k=0;k<path_select.size();k++)
//	{
//		cout<<path_select[k]<<" ";
//	}
//	cout<<endl;
	vector <int> recu_temp;
	//store which is able to recurse
	for(int k=0;k<path_select.size();k++)
	{
		int r=0;
		int u=path_select[k];
		int t;
		for(t=0;t<path[u].size()-1;t++)
		{
			if(school[path[u][t]][path[u][t+1]]==0)
			{
				r=1;
				break;
			}
		}
		if(school[path[u][t]][path[u][0]]==0)
		{
			r=1;
		}
		////
		if(r==0)
		{
			recu_temp.push_back(u);
			for(int i=0;i<5;i++)
			{
				recu_temp.push_back(0);
			}
			compare.push_back(recu_temp);
			recu_temp.clear();
		}
		else
		{
			path_select.erase(path_select.begin()+k);
			k--;
		}
	}
	//compare中如果沒有東西了 
	if(compare.empty())
	{
//		cout<<total<<endl;
		if(total>answer_block)
		{
			answer.clear();
			answer.push_back(path_answer_temp);
			answer_block=total;
		}
		else if(total==answer_block)
		{
			answer.push_back(path_answer_temp);
		}
		return;
	}
	//計算各數值 
//	cout<<"A."<<endl;
	for(int k=0;k<compare.size();k++)
	{
		int u=compare[k][0];
		int t,s;
		int mini=20,maxi=0;
		compare[k][3]=path[u].size();
		float average=0.0,standard=0.0;
		for(t=0;t<path[u].size()-1;t++)
		{
			s=school[path[u][t]][path[u][t+1]];
			if(s<mini)
				mini=s;
			if(s>maxi)
				maxi=s;
			average+=s*1.0;
		}
		s=school[path[u][t]][path[u][0]];
		if(s<mini)
			mini=s;
		if(s>maxi)
			maxi=s;
		compare[k][1]=mini;
		compare[k][2]=maxi;
		average+=s*1.0;
		average=average*1.0/compare[k][3];
		compare[k][4]=average*1000000;
		for(t=0;t<path[u].size()-1;t++)
		{
			float r=school[path[u][t]][path[u][t+1]]*1.0;
			standard+=(r-average)*(r-average);
		}
		float r=school[path[u][t]][path[u][0]]*1.0;
		standard+=(r-average)*(r-average);
		standard=standard/compare[k][3];
		standard=sqrt(standard);
		compare[k][5]=standard*1000000;
		
//		cout<<compare[k][0]<<endl;
//		cout<<"min="<<compare[k][1]<<endl;
//		cout<<"max="<<compare[k][2]<<endl;
//		cout<<"length="<<compare[k][3]<<endl;
//		cout<<"average="<<compare[k][4]<<endl;
//		cout<<"standard="<<compare[k][5]<<endl;
	}
	//開始比較
	for(int i=0;i<filter.size();i++)
	{
		int u=filter[i];
		int m;
		if(u!=5)
		{
			m=compare[0][u];
			for(int k=0;k<compare.size();k++)
			{
				if(compare[k][u]>m)
				{
					m=compare[k][u];
					compare.erase(compare.begin(),compare.begin()+k);
					k=0;
				}
				else if(compare[k][u]<m)
				{
					compare.erase(compare.begin()+k);
					k--;
				}
			}
		}
		else
		{
			m=compare[0][u];
			for(int k=0;k<compare.size();k++)
			{
				if(compare[k][u]<m)
				{
					m=compare[k][u];
					compare.erase(compare.begin(),compare.begin()+k);
					k=0;
				}
				else if(compare[k][u]>m)
				{
					compare.erase(compare.begin()+k);
					k--;
				}
			}
			
		}
	 	//驗完收成果
		if(compare.size()==1)
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
	for(int k=0;k<compare.size();k++)
	{
//		cout<<compare[k][0]<<endl;
		recu_temp.push_back(compare[k][0]);
	}
//	for(int k=0;k<recu_temp.size();k++)
//	{
//		cout<<recu_temp[k]<<" ";
//	}
//	cout<<endl;
//	system("pause");
	compare.clear();

	for(int k=0;k<recu_temp.size();k++)
	{
		int u=recu_temp[k];
		path_answer_temp.push_back(u);
		int t;
		for(t=0;t<path[u].size()-1;t++)
		{
			school[path[u][t]][path[u][t+1]]--;
		}
		school[path[u][t]][path[u][0]]--;
		
//		cout<<"path_select:\n";
//		for(int i=0;i<path_select.size();i++)
//		{
//			cout<<path_select[i]<<" "; 
//		}
//		cout<<endl;
		filter_way_recursion(total+t+1,path_select);
		
		path_answer_temp.erase(path_answer_temp.end()-1);
		for(int i=0;i<t;i++)
		{
			school[path[u][i]][path[u][i+1]]++;
		}
		school[path[u][t]][path[u][0]]++;
	}
	return;
}

void filter_way()
{
	//recursion
	vector <short> path_select;
	for(short k=0;k<path.size();k++)
	{
		path_select.push_back(k);
	}
	filter_way_recursion(0,path_select);
	
	//remove answer which is same
//	for(int k=0;k<answer.size();k++)
//	{
//		for(int t=0;t<answer[k].size();t++)
//		{
//			cout<<answer[k][t]<<" ";
//		}
//		cout<<endl;
//	}
//	set <string> answer_set;
//	for(int k=0;k<answer.size();k++)
//	{
//		string answer_set_temp;
//		for(int t=0;t<answer[k].size();t++)
//		{
//			string r;
//			int u=answer[k][t];
//			while(u!=0)
//			{
//				int s=u%10;
//				r=(char)(s+48)+r;
//				u=u/10;
//			}
//			answer_set_temp+=r;
//		}
//		answer_set.insert(answer_set_temp);
//	}
//	for(set <string>::iterator it=answer_set.begin(); it!=answer_set.end();it++) 
//	{
//		cout << (*it) <<endl;
//	}
	
	return;
}

void layer_way_recursion(int total,int th)
{
	int u=0;//避免重複放置 
	for(int k=th;k<path.size();k++)
	{
		int t,r=0;
		//檢驗是否無法繼續扣 
		for(t=0;t<path[k].size()-1;t++)
		{
			if(school[path[k][t]][path[k][t+1]]==0)
			{
				r=1;
				break;
			}
		}
		if(school[path[k][t]][path[k][0]]==0)
		{
			r=1;
		}
		/////////////////////
		
		//不給過，決定是否存入max 
		if(r==1)
		{
			if(u==1)
			{
				continue;
			}
			  
			if(total>answer_block)
			{
				answer.clear();
				answer.push_back(path_answer_temp);
				answer_block=total;
			}
			else if(total==answer_block)
			{
				answer.push_back(path_answer_temp);
			}
			u=1;
			continue;
		}
		//calculate for path minimum
		int path_min=1000;
		for(int i=0;i<t;i++)
		{
			if(school[path[k][i]][path[k][i+1]]<path_min)
			{
				path_min=school[path[k][i]][path[k][i+1]];
			}
		}
		if(school[path[k][t]][path[k][0]]<path_min)
		{
			path_min=school[path[k][t]][path[k][0]];
		}
		//calculate for cut
		short cut=((path_min-1)/leap)+1;
		//通過的放入p 
		for(int i=0;i<cut;i++)
		{
			path_answer_temp.push_back(k);
		}
		//通過的開始扣款
		for(int i=0;i<t;i++)
		{
			school[path[k][i]][path[k][i+1]]-=cut;
		}
		school[path[k][t]][path[k][0]]-=cut;
		
		//進入遞迴
		layer_way_recursion(total+cut*(t+1),k);
		
		//拿出p
		for(int i=0;i<cut;i++)
		{
			path_answer_temp.erase(path_answer_temp.end()-1); 
		}
		
		//要記得還款 
		for(int i=0;i<t;i++)
		{
			school[path[k][i]][path[k][i+1]]+=cut;
		}
		school[path[k][t]][path[k][0]]+=cut;
	}
	return;
}

void layer_way()
{
	layer_way_recursion(0,0);
	return;
}

void ans_set_and_to_graph_1d()
{
	string answer_set_temp;
	for(int k=0;k<answer.size();k++)
	{
		graph_reset();
		for(int t=0;t<answer[k].size();t++)
		{
			int u=answer[k][t];
			int i;
			for(i=0;i<path[u].size()-1;i++)
			{
				school[path[u][i]][path[u][i+1]]++;
			}
			school[path[u][i]][path[u][0]]++;
		}
		for(int i=0;i<school_q;i++)
		{
			for(int j=0;j<school_q;j++)
			{
				int u=school[i][j];
				string a;
				while(u)
				{
					int s=u%10;
					a=(char)(s+48)+a;
					u=u/10;
				}
				answer_set_temp=answer_set_temp+a+" ";
			}
		}
		answer_set.insert(answer_set_temp);
		answer_set_temp.clear();
	}
}

void translate_ans_emp_to_voc(int i)
{	
	if(answer.empty())
	{
		vocation.push_back(vocation[0]);
		employed.push_back(employed[0]);
	}
	ans_set_and_to_graph_1d();
	vector <int> ans_voc;
	vector <int> emp_voc;
	vector<string> answer_vec(answer_set.begin(),answer_set.end());
	string answer_vec_temp;
	for(int k=0;k<answer_vec.size();k++)
	{
		//convert answer_set to graph 2d
		graph_reset();
		int seq=0,var=0;
		answer_vec_temp=answer_vec[k];
		for(int t=0;t<answer_vec_temp.size();t++)
		{
			char a=answer_vec_temp[t];
			if(a==' ')
			{
				school[seq/school_q][seq%school_q]=var;
				seq++;
				var=0;
			}
			else
			{
				var=var*10;
				var=var+(int)(a-48);
			}
		}
//		for(int x=0;x<school_q;x++)
//		{
//			for(int y=0;y<school_q;y++)
//			{
//				cout<<school[x][y]<<" ";
//			}
//			cout<<endl;
//		}
//		system("pause");
		
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
		ans_voc.erase(ans_voc.begin(),ans_voc.end());
		
		//put emp_voc into employed
		employed.push_back(emp_voc);
		emp_voc.erase(emp_voc.begin(),emp_voc.end());
	}
	//clear answer_set
	answer_set.clear();
	return;
}

int volunteer_sequence(int i,short algo_vari)
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
				answer_X.clear();
			}
			answer_X.push_back(employed[0]);
			employed.erase(employed.begin());
			continue;
		}
		
		int sl=clock();
		////search for answer_block 
		search_path();
		//	
		if(algo_vari==1)
			complete_way();
		else if(algo_vari==2)
			filter_way();
		else
			layer_way();

		//put into vocation
		if(answer_block>answer_block_max)
		{
			int n=na_size-k;
			vocation.erase(vocation.begin()+n,vocation.end());
			employed.erase(employed.begin()+n,employed.end());
			
			translate_ans_emp_to_voc(i);
			
			answer_block_max=answer_block;
		}
		else if(answer_block==answer_block_max)
		{
			translate_ans_emp_to_voc(i);
		}
		//parameter & vector reset
		answer_block=0;
		vocation.erase(vocation.begin());
		employed.erase(employed.begin());
		path.clear();
		answer.clear();
		
		//graph reset
		graph_reset();
	} 
	answer_X_final+=answer_block_max;
	cout<<answer_X_final<<endl;
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
	short algo_vari;
	cout<<endl;
	cout<<"   algorithm   |  accurate rate  |   time   \n";
	cout<<"-------------- | --------------- | ---------\n";
	cout<<"1.complete way |       100%      |   long   \n";
	cout<<"2.filter   way |      88~92%     |   short  \n";
	cout<<"3.layer    way |      99~100%    |  medium  \n";
	cout<<endl<<"which: ";
	cin>>algo_vari;
	cout<<endl;
	////start
	//people[0]=score
	//people[1]=original school
	//people[2]=new school
	//people[n]=-1
	if(algo_vari==1)
	{
		
	}
	else if(algo_vari==2)
	{
		cout<<"  filter |  accurate rate  |   time   \n";
		cout<<"---------| --------------- | ---------\n";
		cout<<"0.  cba  |      92.23%     |  longer  \n";
		cout<<"1.  acb  |      92.12%     |          \n";
		cout<<"2.  acd  |      91.86%     |          \n";
		cout<<"3. acbed |      91.73%     |    to    \n";
		cout<<"4. acdbe |      91.60%     |          \n";
		cout<<"5. becad |      90.91%     |          \n";
		cout<<"6.  cbad |      90.71%     |    to    \n";
		cout<<"7. cbade |      90.58%     |          \n";
		cout<<"8. cbdea |      90.38%     |          \n";
		cout<<"9. cedab |      89.02%     |  faster  \n";
		cout<<endl<<"which: ";
		int filter_th;
		cin>>filter_th;
		int a[10][6]={{3,2,1,-1},{1,3,2,-1},{1,3,4,-1},{1,3,2,5,4,-1},{1,3,4,2,5,-1},
		{2,5,3,1,4,-1},{3,2,1,4,-1},{3,2,1,4,5,-1},{3,2,4,5,1,-1},{3,5,4,1,2,-1}};
		for(int k=0;a[filter_th][k]!=-1;k++)
		{
			filter.push_back(a[filter_th][k]);
		}
	}
	else if(algo_vari==3)
	{
		cout<<"according to rn1 to decide layer\n";
		cout<<"(layer up, accuracy up, time longer)\n";
		cout<<"leap: ";
		cin>>leap;
	}
	
	cout<<"-------------------------------\n";
	
	////run
	for(int k=0;k<people_q;k++)
	{
		vocation[0].push_back(k);
	} 
	for(int k=2;;k++)
	{
		cout<<k-1<<":"<<endl;
//		for(int x=0;x<vocation.size();x++)
//		{
//			cout<<"  ";
//			cout<<x<<". ";
//			for(int y=0;y<vocation[x].size();y++)
//			{
//				cout<<vocation[x][y]<<" ";
//			}
//			cout<<endl;
//		}
//		cout<<endl;
		//find branch
		if(volunteer_sequence(k,algo_vari)==0)
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
