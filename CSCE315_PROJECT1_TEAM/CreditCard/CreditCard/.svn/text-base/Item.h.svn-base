#ifndef _ITEM_H_
#define _ITEM_H_

#include "Time.h"
#include "Date.h"
#include "ItemBase.h"
#include <string>
#include <vector>

using namespace std;

template<class T>
class Item: public ItemBase {
private:
	T data;
public:
	//Item(ItemBase::Type dataType);
	Item(T newData, ItemBase::Type dataType);
	T GetData();
	T SetData(T newData);
	//void SetIsNull(bool null);
	void SetType(ItemBase::Type type);
	//void PrintData();
};

template<class T>
T Item<T>::GetData() {
	return data;
}

template<class T>
T Item<T>::SetData(T newData) {
	data = newData;

	if (isNull) {
		isNull = false;
	}
}

/*template<class T>
 Item<T>::Item(ItemBase::Type dataType) {
 SetIsNull(true);
 SetType(dataType);
 }*/

template<class T>
Item<T>::Item(T newData, ItemBase::Type dataType) {
	//SetIsNull(false);
	SetType(dataType);
	data = newData;
}

/*template<class T>
 void Item<T>::SetIsNull(bool null) {
 isNull = null;
 }*/

template<class T>
void Item<T>::SetType(ItemBase::Type type) {
	itemType = type;
}

/*
 template<class T>
 void Item<T>::PrintData() {
 cout<<data<<'\t';
 }*/

#endif
