/*
 * Item.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
#include <iostream>
#include <sstream>
#ifndef ITEM_H_
#define ITEM_H_
using namespace std;
template<typename T> class Item;

template<typename T>
class Item
{
public:
//	template<typename T>
	Item<T>(T o,int p,int k)
	{
		obj=o;pos=p;key=k;
	}
//	template<typename T>
	Item<T>(T o,int k)
	{
		obj=o;key=k;
	}
	int get_key()
	{
		return key;
	}
	T get_element()
	{
		return obj;
	}
	int get_position()
	{
		return pos;
	}
	void set_position(int p)
	{
		pos=p;
	}
	void set_key(int k)
	{
		key=k;
	}
	string to_string()
	{
		stringstream m;
		m<<"object is "<<obj<<" position is "<<pos<<" key is "<<key;
		string g;
		m>>g;
		return g;
	}
private:
	T obj;
	int pos;
	int key;
};

#endif /* ITEM_H_ */
