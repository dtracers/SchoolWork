/*
 * CSCE221HW3PR1.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: gigemjt
 */
#include "LinkedList.h"
ListNode* getRandomNode(LinkedList l);
void swap_node(LinkedList l,ListNode* x,ListNode* y);
int main()
{
	LinkedList l;
	for(int k=0;k<10;k++)
	{
		char c='A'+k;
		l.insertFirst(c);
	}
	cout<<""<<endl;
	cout<<l<<endl;
	ListNode* one=getRandomNode(l);
	ListNode* two=getRandomNode(l);
	cout<<one->getElem()<<endl;
	cout<<two->getElem()<<endl;
	swap_node(l,one,two);
	cout<<l<<endl;
}
ListNode* getRandomNode(LinkedList l)
{
	int number=rand()%l.size();
	ListNode* current=l.getHead();
	for(int k=0;k<number;k++)
	{
		current=current->getNext();
	}
	return current;
}
void swap_node(LinkedList l,ListNode* x,ListNode* y)
{
	if(x==y)
		return;
	cerr<<"here"<<endl;
	bool x_first=false;
	ListNode* previous;
	ListNode* start=l.getHead();
	cerr<<"here2"<<endl;
	while(start!=x&&start!=y&&start!=NULL)
	{
		previous=start;
		start=start->getNext();
	}
	cerr<<"here3"<<endl;
	ListNode* earliest=previous;
	if(start==x)
	{
		x_first=true;
	}
	//x_first=true;
	cerr<<"here4 "<<x_first<<endl;
	start=start->getNext();
	previous=start;
	while(start!=x&&start!=y&&start!=NULL)
	{
		previous=start;
		start=start->getNext();
	}
	cerr<<"here5"<<endl;
	ListNode* second_earliest=previous;
	if(!x_first)
	{
		ListNode* temp=earliest;
		earliest=second_earliest;
		second_earliest=temp;
	}
	//cerr<<"here6"<<endl;
	ListNode* y_next=y->getNext();
	//cerr<<"here7"<<endl;
	earliest->setNext(y);
	//cerr<<"here8"<<endl;
	y->setNext(x->getNext());
	//cerr<<"here9"<<endl;
	second_earliest->setNext(x);
	//cerr<<"here10"<<endl;
	x->setNext(y_next);
}
