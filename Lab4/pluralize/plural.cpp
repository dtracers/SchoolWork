/*
 * plural.cpp
 *
 *  Created on: Oct 12, 2010
 *      Author: gigemjt
 */

#include<iostream>
#include<vector>
#include<map>
using namespace std;
string pluralize(string g);
map<string,string> addmap();

int main()
{
	while(!cin.fail())
	{
		string g;
		cin>>g;
	//	cout<<g<<"the word in is"<<endl;
		cout<<pluralize(g)<<endl;
	}
	return 0;
}

string pluralize(string g)
{
	map<string,string> irregular=addmap();
	//cout<<"made it that far"<<endl;
	string g2=irregular[g];
	//cout<<g2<<" the words"<<endl;
	if(g2!="")
	{
		return g2;
	}else
	{
		irregular.erase(g);
		int index=g.find_last_of("h|s");
		if(index==g.size()-1)
		{
			if((index=g.substr(0,g.size()-1).find_last_of("c|s"))==g.size()-2)
				return g+"es";
			else
				return g+"s";
		}else if((index=g.find_last_of("(y)"))!=-1&&index==g.size()-1)
		{
			return g.substr(0,index)+"ies";
		}else if((index=g.find_last_of("(x)"))!=-1&&index==g.size()-1)
		{
			return g+"es";
		}else
		{
			return g+"s";
		}
	}
}
map<string,string> addmap()
{
	map<string,string> irregular;
	irregular.insert(pair<string,string>("mouse","mice"));
	irregular.insert(pair<string,string>("deer","deer"));
	irregular.insert(pair<string,string>("knife","knives"));
	irregular.insert(pair<string,string>("timpano","timpani"));
	irregular.insert(pair<string,string>("calf","calves"));
	irregular.insert(pair<string,string>("aircraft","aircraft"));
	irregular.insert(pair<string,string>("child","children"));
	irregular.insert(pair<string,string>("axis","axes"));
	irregular.insert(pair<string,string>("man","men"));
	irregular.insert(pair<string,string>("boy","boys"));
	irregular.insert(pair<string,string>("stand-by","stand-bys"));
	irregular.insert(pair<string,string>("money","monies"));
	irregular.insert(pair<string,string>("goose","geese"));
	return irregular;
}
