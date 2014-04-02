/*
 * main.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: gigemjt
 */
#include<iostream>
#include<fstream>
#include"TreeNode.cpp"
#include <sstream>

TreeNode* create_tree(string name);

int main()
{
	int test=0;
	if(test==0)
	{
		cout<<"File NAME"<<endl;
		string name;
		cin>>name;
		TreeNode* x=NULL;
		x=create_tree(name);
		while(true)
		{
			cout<<"select option\n0:Exit\n1:new tree:"<<endl;
			cout<<"2:in order traversal\n3:post order traversal"<<endl;
			cout<<"4:pre order traversal\n5:level order traversal"<<endl;
			cout<<"6:delete node\n7:insert new node"<<endl;
			cout<<"8:print height\n9:print height from value"<<endl;
			cout<<"10:print number of nodes\n11:print average search cost"<<endl;
			int opt;
			cin>>opt;
			switch(opt)
			{
				case 0:return 0;
				case 1:
				{
					cout<<"File NAME"<<endl;
					cin>>name;
					x=create_tree(name);
				}break;
				case 2:
				{
					x->in_order_traversal(0,0);
				}break;
				case 3:
				{
					x->post_order_traversal(0,0);
				}break;
				case 4:
				{
					x->pre_order_traversal(0,0);
				}break;
				case 5:
				{
					x->level_order_traversal(0);
				}break;
				case 6:
				{
					int n;
					cout<<"enter value"<<endl;
					cin>>n;
					x->delete_node(n);
				}break;
				case 7:
				{
					int n;
					cout<<"enter value"<<endl;
					cin>>n;
					x->add(new TreeNode(n));
				}break;
				case 8:
				{
					cout<<"The maximum height is "<<x->get_height()<<endl;
				}break;
				case 9:
				{
					int n;
					cout<<"enter value"<<endl;
					cin>>n;
					TreeNode* m=x->get_node(n);
					cout<<"the maximum height from "<<n<<" "<<m->get_height()<<endl;
				}break;
				case 10:
				{
					cout<<"The number of nodes are "<<x->get_number_nodes()<<endl;
				}break;
				case 11:
				{
					double d=((double)x->get_added_cost()/(double)x->get_number_nodes());
					cout<<"Average cost is "<<d<<endl;
				}break;
			}
			//x->in_order_traversal(0,0);
			//cout<<"the program will now exit"<<endl;

		}
	}else
	{
		ofstream out("Test.txt",ofstream::out);
		for(int k=1;k<=12;k++)
		{
			cout<<"starting "<<k<<endl;
			string name="";
			stringstream m;
			m<<k;
			m>>name;
			name;
			TreeNode* p=NULL;
			TreeNode* l=NULL;
			TreeNode* r=NULL;
			cout<<"name is"<<endl;
			p=create_tree(name+"p");
			l=create_tree(name+"l");
			r=create_tree(name+"r");
			out<<""<<p->get_number_nodes()<<"\t"<<p->get_average_cost()<<"\t";
			out<<""<<r->get_number_nodes()<<"\t"<<r->get_average_cost()<<"\t";
			out<<""<<l->get_number_nodes()<<"\t"<<l->get_average_cost()<<endl;
			cout<<"done with "<<k<<endl;
		}
	}
}
TreeNode* create_tree(string name)
{
	ifstream file(name.c_str(),ifstream::in);
	int d;
	TreeNode* x=NULL;
	while(!file.eof())
	{
		int d;
		file>>d;
		if(!file.eof())
		{
			TreeNode* temp=new TreeNode(d);
		//	cerr<<"adding "<<d<<endl;
			if(x==NULL)
			{
				x=temp;
			}else
			{
				x->add(temp);
			}
		}
	}
	return x;
}
