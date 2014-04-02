/*
 * TreeNode.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: gigemjt
 */
#include <queue>
#include<iostream>
using namespace std;
class TreeNode
{
private:
	int value;
	int cost;
	int post;//its position in a left to right format
	TreeNode* left;
	TreeNode* right;
	int height_left;//the max height of the left side
	int height_right;//the max height of the right side
	int max_height;
	void delete_node(TreeNode* n,TreeNode* w,int wobble)
	{
		if(n->is_leaf())
		{
			if(w->get_left()==n)
			{
				w->set_left(NULL,0);
			}else
			{
				w->set_right(NULL,0);
			}
		}else
		{
			TreeNode* kid=n->get_only_kid();
			if(kid==NULL)
			{
				if(wobble>=0)
				{
					kid=n->get_left();
				}else if(wobble<0)
				{
					kid=n->get_left();
				}
				if(wobble==0)
				{
					wobble=1;
				}
			}else
			{
				wobble=0;
			}
			n->value=kid->value;
			delete_node(kid,n,-wobble);
		}
	}
	int add(TreeNode* n,int cost)
	{
		if(n==this)
		{
			n->set_cost(cost);
			cerr<<"yes this is an error";
			return -1;
		}
	//	cerr<<"i made it past my fake return"<<endl;
		TreeNode* cont=NULL;
		if(n->get_value()<value)
		{
			if(left==NULL)
			{
				set_left(n,cost+1);
			}else
				height_left=left->add(n,cost+1);
		}else
		{
			if(right==NULL)
			{
				set_right(n,cost+1);
			}else
				height_right=right->add(n,cost+1);
		}
		if(height_left>height_right)
		{
			max_height=height_left;
		}else
		{
			max_height=height_right;
		}
		return max_height+1;
	}
public :
	TreeNode(int v)
	{
		value=v;
		cost=0;
		left=NULL;
		right=NULL;
	}
	void add(TreeNode* n)
	{
		max_height=add(n,0);
	}
	void level_order_traversal(int key)//assuming they are in order
	{
		queue<TreeNode*> level;
		level.push(this);
		int currentlevel=cost;
		int currentpos=0;
		while(!level.empty())
		{
			TreeNode* current=level.front();
			level.pop();
			if(current->cost!=currentlevel)
			{
				currentpos=0;
			}
			current->Process_node(key);
			TreeNode* child=current->left;
			if(child!=NULL)
			{
				level.push(child);
				child->post=currentpos;
			}
			currentpos+=1;
			child=current->right;
			if(child!=NULL)
			{
				level.push(child);
				child->post=currentpos;
			}
		}
	}
	void pre_order_traversal(int key,int depth=0)
	{
		Process_node(key);
		if(left!=NULL)
		{
			left->pre_order_traversal(key,depth);
		}
		if(right!=NULL)
		{
			right->pre_order_traversal(key,depth);
		}
	}
	void post_order_traversal(int key,int depth=0)
	{
		if(left!=NULL)
		{
			left->post_order_traversal(key,depth);
		}
		if(right!=NULL)
		{
			right->post_order_traversal(key,depth);
		}
		Process_node(key);
	}
	void in_order_traversal(int key,int depth=0)
	{
		if(left!=NULL)
		{
			left->in_order_traversal(key,depth);
		}
		Process_node(key);
		if(right!=NULL)
		{
			right->in_order_traversal(key,depth);
		}
	}
	void Process_node(int action,int depth=0)
	{
		switch(action)
		{
			default:
			case 0:cout<<"Key: "<<value<<" SearchCost = "<<cost<<endl;break;
			case 1:cost=depth;break;
		}
	}
	int get_value()
	{
		return value;
	}
	int get_cost()
	{
		return cost;
	}
	void set_left(TreeNode* l,int cost)
	{
		left=l;
		if(l!=NULL)
		{
			l->max_height=l->height_left=l->height_right=0;
			l->set_cost(cost);
		}
	}
	void set_right(TreeNode* r,int cost)
	{
		right=r;
		if(r!=NULL)
		{
			r->max_height=r->height_left=r->height_right=0;
			r->set_cost(cost);
		}
	}
	void set_cost(int k)
	{
		cost=k;
	}
	TreeNode* get_left()
	{
		return left;
	}
	TreeNode* get_right()
	{
		return right;
	}
	bool is_leaf()
	{
		return left==NULL&&right==NULL;
	}
	int get_added_cost()
	{
		int total=get_cost();
		if(right!=NULL)
		{
			total+=right->get_added_cost();
		}
		if(left!=NULL)
		{
			total+=left->get_added_cost();
		}
		return total;
	}
	void delete_node(int value)
	{
		TreeNode* n=get_node(value);
		TreeNode* w=get_parent_of(n);
		delete_node(n,w,0);
	}
	TreeNode* get_parent_of(TreeNode* kiddy)
	{
		if(left==kiddy||right==kiddy)
		{
			return this;
		}
		if(kiddy->get_value()<value)
		{
			if(left!=NULL)
			{
				return left->get_parent_of(kiddy);
			}
		}
		else
		{
			if(right!=NULL)
			{
				return right->get_parent_of(kiddy);
			}
		}
		return NULL;
	}
	TreeNode* get_parent_of(int value)
	{
		TreeNode* kiddy=get_node(value);
		return get_parent_of(kiddy);
	}
	TreeNode* get_node(int value)
	{
		if(value==get_value())
		{
			return this;
		}
		else if(value<get_value())
		{
			if(left==NULL)
				return NULL;
			return left->get_node(value);
		}else
		{
			if(right==NULL)
				return NULL;
			return right->get_node(value);
		}
	}
	TreeNode* get_only_kid()//returns null unless it has one kid
	{
		if(is_leaf())
			return NULL;
		if(right!=NULL&&left!=NULL)
			return NULL;
		if(right!=NULL)
			return right;
		return left;
	}
	int get_height()
	{
		return max_height+1;
	}
	int get_number_nodes()
	{
		int total=1;
		if(right!=NULL)
		{
			total+=right->get_number_nodes();
		}
		if(left!=NULL)
		{
			total+=left->get_number_nodes();
		}
		return total;
	}
	TreeNode* get_right_most_node()
	{
		TreeNode* prev;
		TreeNode* n=get_right();
		while(n!=NULL)
		{
			prev=n;
			n=n->get_right();
		}
		return prev;
	}
	TreeNode* get_left_most_node()
	{
		TreeNode* prev;
		TreeNode* n=get_left();
		while(n!=NULL)
		{
			prev=n;
			n=n->get_left();
		}
		return prev;
	}
	double get_average_cost()
	{
		double d=((double)get_added_cost()/(double)get_number_nodes());
		return d;
	}
};
