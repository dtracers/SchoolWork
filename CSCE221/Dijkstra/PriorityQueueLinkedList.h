/*
 * PriorityQueueLinkedList.h
 *
 *  Created on: Nov 9, 2011
 *      Author: gigemjt
 */

#ifndef PRIORITYQUEUELINKEDLIST_H_
#define PRIORITYQUEUELINKEDLIST_H_

/*
 * PriorityQueueHeap.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
#include"PriorityQueue.h"
//#include"LinkedList.h"
#include"ItemNode.h"
#include"Item.h"

/*
 * PriorityQueue.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
template<typename T> class PriorityQueueHeap;

template<typename T>
class PriorityQueueLinkedList:public PriorityQueue<T>
{
private:
	ItemNode<T>* head;
	ItemNode<T>* tail;
	void swap(int loc1,int loc2)
	{
		ItemNode<T>* first=((ItemNode<T>*)this->PriorityQueue<T>::get_list_key()[loc1]);
		ItemNode<T>* second=((ItemNode<T>*)this->PriorityQueue<T>::get_list_key()[loc2]);
		this->PriorityQueue<T>::get_list_key()[loc2]=((Item<T>*)first);
		this->PriorityQueue<T>::get_list_key()[loc1]=((Item<T>*)second);
		((Item<T>*)first)->set_position(loc2);
		((Item<T>*)second)->set_position(loc1);
		swap(first,second);
	}
	/**
	 * This will swap two nodes
	 */
	void swap(ItemNode<T>* node1,ItemNode<T>* node2)
	{
		if(node2!=NULL&&node1!=NULL)
		{
			ItemNode<T>* head_temp;
			ItemNode<T>* tail_temp;
			if(node1==head)
			{
				head_temp=node1;
			}else if(node1==tail)
			{
				tail_temp=node1;
			}
			//if(node2)
		}
	}
	ItemNode<T>* getHead() const { return head; }
	ItemNode<T>* getTail() const { return tail; }
public:
	void set_key(T loc,int key)
	{
		Item<T>* item=this->get_list_element()[loc];
		int pos=item->get_position();
		item->set_key(key);
	}
	void set_key_at(int loc,int key)
	{
		Item<T>* item=this->get_list_key()[loc];
		int pos=item->get_position();
		item->set_key(key);
	//	create_queue_down(pos/2);
	}
	//template<typename T>
	void insertItem(T o,int key)
	{
		Item<T>* adding=new ItemNode<T>(o,key);
		this->get_list_key().push_back(adding);
		this->get_list_element().push_back(adding);
	//	this->PriorityQueue::get_list_element()[o]=adding;
		//create_queue_up(this->get_list_key().size()-1);
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
	//	create_queue_up(min->get_position());
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




#endif /* PRIORITYQUEUELINKEDLIST_H_ */
