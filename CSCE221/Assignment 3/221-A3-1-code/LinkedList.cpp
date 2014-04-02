//LinkedList.cpp



#include <iostream>
#include "LinkedList.h"
using namespace std;
// assignment operator

/**
 * Big-O(n)
 */
LinkedList& LinkedList::operator=(const LinkedList& ll)
{
//	this->head=ll.head;
//	this->tail=ll.tail;
//	this->Size=ll.Size;
	this->removeAll();
	ListNode* front=ll.head;
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

int LinkedList::size() const {
	/* complete this function
	* This function returns the length of the linked list
	* (How many nodes there are in the linked list)
	*/
	return Size;
}

// accessor function

char LinkedList::first() const throw(EmptyLinkedListException)
{
	/* Complete this function;
	* If the linked list is empty, throw an EmptyLinkedListException
	*/
	if(isEmpty())
		throw EmptyLinkedListException();
	return head->getElem();
}

// update functions

void LinkedList::insertFirst(char newobj)
{
	ListNode* n=new ListNode(newobj,head);
	if(isEmpty())
	{
		n->next=tail;
	}
	head=n;
	Size+=1;
  /* complete this function */
}

void LinkedList::insertLast(char newobj)
{
	ListNode* n=new ListNode(newobj,NULL);
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

void LinkedList::insertAfter(char newobj, ListNode *node)
    throw(InvalidPointerException)
{
	bool isLast;
	ListNode* next=node->getNext();
	isLast=(next==tail);
	ListNode* n=new ListNode(newobj,next);
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

char LinkedList::removeFirst() throw(EmptyLinkedListException)
{
	if(isEmpty())
			throw EmptyLinkedListException();
	ListNode* old=head;
	char value=old->getElem();
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
/**
 * Big-O(n)
 */
char LinkedList::remove(ListNode *node)
    throw(InvalidPointerException)
{
	ListNode* first=head;
	ListNode* previous=NULL;
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
	char value=node->getElem();
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

void LinkedList::removeAll()
{
  /* Complete this function;
   * This function removes all the nodes in the linked list
   */
	while(!isEmpty())
	{
		removeFirst();
	}
}
/**
 * Big-O(n)
 */
ostream& operator<<(ostream & out, const LinkedList& ll)
{
	if(!ll.isEmpty())
	{
		ListNode* first=ll.head;
		ListNode* next;
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
