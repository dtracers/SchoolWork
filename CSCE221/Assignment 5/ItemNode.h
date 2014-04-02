/*
 * ItemNode.h
 *
 *  Created on: Nov 10, 2011
 *      Author: gigemjt
 */

#ifndef ITEMNODE_H_
#define ITEMNODE_H_
/*
 * Item.h
 *
 *  Created on: Nov 7, 2011
 *      Author: gigemjt
 */
#include "Item.h"
using namespace std;
template<typename T> class ItemNode;

template<typename T>
class ItemNode : Item<T>
{
public:
//	template<typename T>
	ItemNode<T>(T o,int p,int k,ItemNode<T>* n):Item<T>(o,p,k)
	{
		next=n;
	}
//	template<typename T>
	ItemNode<T>(T o,int k,ItemNode<T>* n):Item<T>(o,k)
	{
		next=n;
	}
private:
	ItemNode<T>* next;
	ItemNode<T>* previous;
};


#endif /* ITEMNODE_H_ */
