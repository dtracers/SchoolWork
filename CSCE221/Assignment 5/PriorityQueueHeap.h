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
class PriorityQueueHeap:PriorityQueue<T>
{
private:

	void swap(int loc1,int loc2)
	{
		//vector<Item<T>* > list=this->this->get_list_key();
		Item<T>* first=this->get_list_key()[loc1];
		Item<T>* second=this->get_list_key()[loc2];
		this->get_list_key()[loc2]=first;
		this->get_list_key()[loc1]=second;
		first->set_position(loc2);
		second->set_position(loc1);
	//	first->
	}
	void create_queue_down(int pos)
	{
		Item<T>* parent=this->get_list_key()[pos];
		int left=2*pos;
		int right=2*pos+1;
		if(right>=this->get_list_key().size())
			return;
		int min_pos=(this->get_list_key()[left]->get_key()>this->get_list_key()[right]->get_key())
				?right:left;
		//if the left is greater than the right
		//then the right is the min number of the two
		if(parent->get_key()>this->get_list_key()[min_pos]->get_key())
		{
			swap(pos,min_pos);
			create_queue_up(pos);
		}
		create_queue_down(left);
		create_queue_down(right);
	}
	void create_queue_up(int pos)
	{
		if(pos==0)
			return;
		int parent_pos=(pos)/2;
		if(this->get_list_key()[parent_pos]->get_key()>this->get_list_key()[pos]->get_key())
		{
			swap(pos,parent_pos);
			create_queue_up(parent_pos);
		}
	}

public:
	void set_key(T loc,int key)
	{
		Item<T>* item=this->get_list_element()[loc];
		int pos=item->get_position();
		item->set_key(key);
	//	this->create_queue_down(0);
	//	create_queue_down((int)(pos/2));
	}
	void set_key_at(int loc,int key)
	{
		Item<T>* item=this->get_list_key()[loc];
		int pos=item->get_position();
		item->set_key(key);
		create_queue_down(pos/2);
	}
	//template<typename T>
	void insertItem(T o,int key)
	{
		Item<T>* adding=new Item<T>(o,key);
		this->get_list_key().push_back(adding);
		//this->get_list_element().push_back(adding);
		this->PriorityQueue<T>::get_list_element()[o]=adding;
		create_queue_up(this->get_list_key().size()-1);
		//this->get_list_key()[0]=adding;
		//this->get_list_key().push_pack();
	}
	T removeMin()
	{
		Item<T>* remove=this->get_list_key()[0];
		swap(0,this->get_list_key().size()-1);
		//this->get_list_key()[0]=this->get_list_key()[this->get_list_key().size()-1];
		this->get_list_key().pop_back();
		create_queue();
		return remove->get_element();
	}
	T remove_item(T loc)
	{
		Item<T>* element=this->get_list_element()[loc];
		Item<T>* min=this->get_list_key()[0];
		swap(0,element->get_position());
		T g=removeMin();
		create_queue_up(min->get_position());
		return g;
	}
	void create_queue()
	{
	//	create_queue_down(0);
	}
	Item<T>* min()
	{
		return this->get_list_key()[0];
	}
};


#endif /* PRIORITYQUEUEHEAP_H_ */
