/*
 * PriorityQueueHeap.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
#include"PriorityQueue.h"
#ifndef PRIORITYQUEUEHEAP_H_
#define PRIORITYQUEUEHEAP_H_

/*
 * PriorityQueue.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
template<typename T> class PriorityQueueHeap;

template<typename T>
class PriorityQueueHeap:public PriorityQueue<T>
{
private:

	void swap(int loc1,int loc2)
	{
		//vector<Item<T>* > list=this->this->list_key;
		Item<T>* first=this->list_key[loc1];
		Item<T>* second=this->list_key[loc2];
		this->list_key[loc2]=first;
		this->list_key[loc1]=second;
		first->set_position(loc2);
		second->set_position(loc1);

	//	first->
	}
	void create_queue_down_moose(int pos)
	{
		if(pos>=this->list_key.size())
			return;
		Item<T>* parent=this->list_key[pos];

		int left=2*pos;
		int right=2*pos+1;
		if(pos==0)
		{
			left=1;
			right=2;
		}
//		cerr<<"left "<<left<<"right "<<right<<endl;
		if(right>=this->list_key.size())
			return;
//		cerr<<"left key "<<this->list_key[left]->get_key()<<" right key "<<this->list_key[right]->get_key()<<endl;
		int max_pos=(this->list_key[left]->get_key()>
		this->list_key[right]->get_key())?left:right;

		int min_pos=(this->list_key[left]->get_key()<=
				this->list_key[right]->get_key())?left:right;
		int comp_pos=max_pos;
//		cerr<<"max_pos is "<<max_pos<<endl;
//		cerr<<"min_pos is "<<min_pos<<endl;
		//if the left is greater than the right
		//then the right is the min number of the two
		if(parent->get_key()>this->list_key[comp_pos]->get_key())
		{
//			cerr<<"changing position "<<pos<<endl;
			swap(pos,comp_pos);
			create_queue_down_moose(comp_pos);
			//create_queue_up(pos);
		}
	//	create_queue_down_moose(left);
	//	create_queue_down_moose(right);
	}
	void create_queue_up(int pos)
	{
		if(pos<0)
			return;
		int parent_pos=(pos)/2;
		if(parent_pos==pos)
			return;
		if(this->list_key[parent_pos]->get_key()<this->list_key[pos]->get_key())
		{
			swap(pos,parent_pos);
			create_queue_up(parent_pos);
		}
	}

public:
	virtual void set_key(T loc,int key)
	{
		Item<T>* item=this->list_element[loc];
		int pos=item->get_position();
		cerr<<"starting position"<<pos<<endl;
		item->set_key(key);
		create_queue_down_moose(pos);
		cerr<<"middle postion is "<<pos<<endl;
		create_queue_up(pos);
		cerr<<"final position is "<<item->get_position()<<endl;
	}
	void set_key_at(int loc,int key)
	{
		Item<T>* item=this->list_key[loc];
		int pos=item->get_position();
		item->set_key(key);
		create_queue_down_moose(pos/2);
	}
	//template<typename T>
	void insertItem(T o,int key)
	{
		Item<T>* adding=new Item<T>(o,key);
		this->list_key.push_back(adding);
		adding->set_position(this->list_key.size()-1);
	//	cerr<<"current size "<<this->list_key.size()<<endl;
		//this->get_list_element().push_back(adding);
		this->PriorityQueue<T>::list_element[o]=adding;
		create_queue_up(this->list_key.size()-1);
		//this->list_key[0]=adding;
		//this->list_key.push_pack();
	}
	T removeMin()
	{
	//	cerr<<"removing0"<<endl;
		vector<Item<T>* > list=this->list_key;
	//	cerr<<"removing0.5 "<<list.size()<<endl;
		Item<T>* remove=list[0];
	//	cerr<<"removing1"<<endl;
		swap(0,this->list_key.size()-1);
	//	cerr<<"removing2"<<endl;
		//this->list_key[0]=this->list_key[this->list_key.size()-1];
		this->list_key.pop_back();
	//	cerr<<"removing3"<<endl;
	//	cerr<<"precreating queue?"<<endl;
		create_queue_down_moose(0);
	//	cerr<<"removing4"<<endl;
	//	cerr<<"creating queue?"<<endl;
		return remove->get_element();
	}
	T remove_item(T loc)
	{
		Item<T>* element=this->get_list_element()[loc];
		Item<T>* min=this->list_key[0];
		swap(0,element->get_position());
		T g=removeMin();
		create_queue_up(min->get_position());
		return g;
	}
	void create_queue()
	{
		create_queue_down_moose(0);
	}
	void print list()
	{
		vector<Item<T>* > list=this->list_key;
		for(int k=0;k<list.size;k++)
		{

		}
	}
	Item<T>* min()
	{
		return this->list_key[0];
	}
};


#endif /* PRIORITYQUEUEHEAP_H_ */
