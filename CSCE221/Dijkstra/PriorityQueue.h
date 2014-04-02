/*
 * PriorityQueue.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
#include"Item.h"
#include<vector>
#include<map>
#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

template<typename T> class PriorityQueue;

template<typename T>
class PriorityQueue
{
protected:
	vector<Item<T>* > list_key;
	map<T,Item<T>* > list_element;
private:

public:
	//template<typename T>
	virtual vector<Item<T>* > get_list_key()
	{
		return list_key;
	}
	//template<typename T>
	virtual map<T,Item<T>* > get_list_element()
	{
		return list_element;
	}
	virtual void set_key(int loc,int key)
	{

	}
	virtual void set_key(T loc,int key)
	{

	}
	//template<typename T>
	virtual void insert(T o,int key)
	{
		insertItem(o,key);
	}
	int get_size() const
	{
		return list_key.size();
	}
	virtual void insertItem(T o,int key)
	{

	}
	virtual T removeMin()
	{
		return NULL;
	}
	virtual void create_queue()
	{

	}
	virtual T remove_at(int t)
	{
		return NULL;
	}
	virtual T remove_item(T t)
	{
		return NULL;
	}
	virtual Item<T>* min()
	{
		return NULL;
	}

};

#endif /* PRIORITYQUEUE_H_ */
