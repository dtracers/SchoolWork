//LinkedList<T>.cpp



#include <iostream>
#include "LinkedList.h"
using namespace std;
// assignment operator

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
{
//	this->head=ll.head;
//	this->tail=ll.tail;
//	this->Size=ll.Size;
	this->removeAll();
	ListNode<T>* front=ll.head;
	cerr<<front->getElem();
	while(front!=NULL)
	{
	//   cerr<<"Monkeys "<<front->getElem()<<endl;
	   insertLast(front->getElem());

	   front=front->getNext();
	}
  /* complete this function */
  return *this;
}

// query function
template<typename T>
int LinkedList<T>::size() const {
	/* complete this function
	* This function returns the length of the linked list
	* (How many nodes there are in the linked list)
	*/
	return Size;
}

// accessor function
template<typename T>
T LinkedList<T>::first() const throw(LinkedList::EmptyLinkedListException)
{
	/* Complete this function;
	* If the linked list is empty, throw an EmptyLinkedListException
	*/
	if(isEmpty())
		throw EmptyLinkedListException();
	return head->getElem();
}
template<typename T>
T LinkedList<T>::last() const throw(LinkedList::EmptyLinkedListException)
{
	/* Complete this function;
	* If the linked list is empty, throw an EmptyLinkedListException
	*/
	if(isEmpty())
		throw EmptyLinkedListException();
	return tail->getElem();
}

// update functions
template<typename T>
void LinkedList<T>::insertFirst(T newobj)
{
	ListNode<T>* n=new ListNode<T>(newobj,head);
	if(isEmpty())
	{
		n->next=tail;
	}
	head=n;
	Size+=1;
  /* complete this function */
}
template<typename T>
void LinkedList<T>::insertLast(T newobj)
{
	ListNode<T>* n=new ListNode<T>(newobj,NULL);
	if(isEmpty())
	{
		head=n;
	}else
	{
		tail->next=n;
	}
	tail=n;
	Size+=1;
}
template<typename T>
T LinkedList<T>::removeLast()
{
	ListNode<T>* current=head;
	ListNode<T>* prev=current;
	while(current!=tail)
	{
		prev=current;
		current=current->getNext();
	}
	T obj=tail->getElem();
	prev->setNext(NULL);
	delete current;
	tail=prev;
	return obj;
}
template<typename T>
void LinkedList<T>::insertAfter(T newobj, ListNode<T> *node)
    throw(LinkedList::InvalidPointerException)
{
	bool isLast;
	ListNode<T>* next=node->getNext();
	isLast=(next==tail);
	ListNode<T>* n=new ListNode<T>(newobj,next);
	node->next=n;
	if(isLast)
	{
		tail=n;
	}
	Size+=1;
  /* BONUS QUESTION: complete this function
   * This function inserts a new node with element 'newobj' 
   * after the node pointed by the pointer 'node'.
   * Modify the head and tail pointers when needed.
   * If the pointer "node" is NULL, throw an InvalidPointerException
   */
}
template<typename T>
T LinkedList<T>::removeFirst() throw(LinkedList::EmptyLinkedListException)
{
	if(isEmpty())
			throw EmptyLinkedListException();
	ListNode<T>* old=head;
	T value=old->getElem();
	head=old->getNext();
  /* Complete this function;
   * If the linked list is empty, throw an EmptyLinkedListException
   */
	Size-=1;
	if(old!=NULL)
	delete old;
	if(Size==0)
	{
		tail=NULL;
		head=NULL;
	}
	return value;
}
template<typename T>
T LinkedList<T>::remove(ListNode<T> *node)
    throw(LinkedList::InvalidPointerException)
{
	ListNode<T>* first=head;
	ListNode<T>* previous=NULL;
	if(first==node)
	{
		head=first->getNext();
	}else
	{
		while(first!=NULL&&first!=node)
		{
			previous=first;
			first=first->getNext();
		}
		if(first==NULL)
		{
			tail=previous;
			previous->next=NULL;
		}else
		{
			previous->next=node->getNext();
		}
	}
	T value=node->getElem();
	if(node!=NULL)
		delete node;
		Size-=1;
  /* BONUS QUESTION: Complete this function;
   * This function removes the linked list node pointed by the given pointer "node".
   * You should change the link before the specified "node"; 
   * connect the previous node to the next node;
   * modify the head and tail pointers when needed.
   *
   * If the pointer "node" is NULL, throw an InvalidPointerException;
   * If the pointer "node" does not point to a node in the linked list,
   * throw an InvalidPointerException
   */
  return value;
}
template<typename T>
void LinkedList<T>::removeAll()
{
  /* Complete this function;
   * This function removes all the nodes in the linked list
   */
	while(!isEmpty())
	{
		removeFirst();
	}
}
template<typename T>
ostream& operator<<(ostream & out, const LinkedList<T>& ll)
{
	if(!ll.isEmpty())
	{
		ListNode<T>* first=ll.head;
		ListNode<T>* next;
		do
		{
			out<<first->getElem()<<" ";
			next=first->getNext();
			first=next;
		}while(next!=NULL);
	//	out<<endl;
		/* Complete this function;
		* This function outputs each element in the linked list in order;
		* The elements are delimited by spaces.
		*/
	}else
	{
		out<<"The list is currently empty";
	}
  return out;
}
