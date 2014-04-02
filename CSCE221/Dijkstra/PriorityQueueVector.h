/*
 * PriorityQueue.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
#include "PriorityQueue.h"
#ifndef PRIORITYQUEUEVECTOR_H_
#define PRIORITYQUEUEVECTOR_H_

template<typename T> class PriorityQueue;

template<typename T>
class PriorityQueueVector:public PriorityQueue<T>
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
protected:
public:
//	int insert;
	int remove;
//	int extract;
	virtual void set_key(T loc,int key)
		{
			Item<T>* item=this->list_element[loc];
			int pos=item->get_position();
		//	cerr<<"starting position"<<pos<<endl;
			item->set_key(key);
		//	create_queue_down_moose(pos);
		//	cerr<<"middle postion is "<<pos<<endl;
		//	create_queue_up(pos);
		//	cerr<<"final position is "<<item->get_position()<<endl;
		}
		void set_key_at(int loc,int key)
		{
			insert++;
			Item<T>* item=this->list_key[loc];
			int pos=item->get_position();
			item->set_key(key);
	//		create_queue_down_moose(pos/2);
		}
	//template<typename T>
	virtual void insert(T o,int key)
	{
		insertItem(o,key);

	}
	virtual void insertItem(T o,int key)
	{
	//	insert++;
		Item<T>* adding=new Item<T>(o,key);
		this->list_key.push_back(adding);
		adding->set_position(this->list_key.size()-1);
		this->list_element[o]=adding;
	}
	virtual T removeMin()
	{
		vector<Item<T>* > list=this->list_key;
		int key=-1;
		int index=0;
		for(int k=0;k<list.size();k++)
		{
			Item<T>* item=list[k];
			if(key==-1)
			{
				key=item->get_key();
				index=k;
			}
			if(key>item->get_key())
			{
				remove++;
				index=k;
				key=item->get_key();
			}
		}
		Item<T>* remove=list[index];
		swap(index,this->list_key.size()-1);
		this->list_key.pop_back();
		return remove->get_element();
	}
	virtual void create_queue()
	{

	}
	virtual T remove_at(int t)
	{
		return NULL;
	}
	Item<T>* min()
	{
		return this->list_key[0];
	}

};

#endif /* PRIORITYQUEUE_H_ */
