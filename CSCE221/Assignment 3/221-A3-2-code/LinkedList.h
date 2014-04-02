// LinkedList.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "RuntimeException.h"
#include <iostream>

template<typename T> class LinkedList;

template<typename T>
std::ostream& operator<<(std::ostream&, const LinkedList<T>&);

template<typename T>
class ListNode {
	private:
	T obj;
	ListNode<T> *next;
	friend class LinkedList<T>;

public:
	ListNode<T>(T e = 0, ListNode<T> *n = NULL) : obj(e), next(n) { }
	T getElem() const { return obj; }
	ListNode<T> * getNext() const { return next; }
	void setNext(ListNode<T> * n) { next=n; }
};
  /* fill in the class */
  

template<typename T>
class LinkedList {
 private:
   ListNode<T> *head, *tail;
   int Size;
   
 public:
   // user-defined exceptions
   class EmptyLinkedListException : public RuntimeException {
    public:
     EmptyLinkedListException() : RuntimeException("Empty linked list") {}
   };
   class InvalidPointerException : public RuntimeException {
    public:
     InvalidPointerException() : RuntimeException("Attempt to use null pointer") {}
   };   
   LinkedList<T>() { Size=0; head=NULL;tail=NULL;/* Complete this function */ } // default constructor
   ~LinkedList<T>() { removeAll();
   if(head!=NULL)delete head;if(tail!=NULL)delete tail;/* Complete this function */ } // destructor
   LinkedList<T>(const LinkedList<T>& ll)
   {
	   Size=0; head=NULL;tail=NULL;
	   ListNode<T>* front=ll.head;
	  // cerr<<front->getElem();
	   while(front!=NULL)
	   {
		//   cerr<<"Monkeys "<<front->getElem()<<endl;
		   insertLast(front->getElem());

		   front=front->getNext();
	   }
   } // copy constructor
   LinkedList<T> & operator=(const LinkedList<T> & ll); // assignment operator
     
   // query function
   int size() const;
   bool isEmpty() const {return Size==0;/* Complete this function */ }
   
   // accessor functions
   T first() const throw(EmptyLinkedListException);
   T last() const throw(EmptyLinkedListException);
   ListNode<T> *getHead() const { return head; }
   ListNode<T> *getTail() const { return tail;/* Complete this function */ }

   // update functions
   void insertFirst(T newobj);
   T removeFirst() throw(EmptyLinkedListException);
   void insertLast(T newobj);
   T removeLast();
   void insertAfter(T newobj, ListNode<T> *node) throw(InvalidPointerException);
   T remove(ListNode<T> *node) throw(InvalidPointerException);
   void removeAll();
   
   friend std::ostream & operator<< <>(std::ostream& out, const LinkedList<T> &ll); //overload <<
};
#endif
/*
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll) // copy constructor
{

}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll) // assignment operator
{

   return *this;
}
*/
/* describe rest of the functions here */
/*
template<typename T>
std::ostream& operator<<(std::ostream & out, const LinkedList<T>& ll) //overload <<
{

   return out;
}

#endif
*/
