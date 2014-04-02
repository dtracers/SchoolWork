//LinkedList.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "RuntimeException.h"

class LinkedList;

class ListNode {
 private:
   char obj;
   ListNode *next;
   friend class LinkedList;
   
 public:
   ListNode(char e = 0, ListNode *n = NULL) : obj(e), next(n) { }
   char getElem() const { return obj; }
   ListNode * getNext() const { return next; }
};

class LinkedList {
 private:
   ListNode *head, *tail;
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
   
   LinkedList() { Size=0; head=NULL;tail=NULL;/* Complete this function */ } // default constructor
   ~LinkedList() { removeAll();
   if(head!=NULL)delete head;if(tail!=NULL)delete tail;/* Complete this function */ } // destructor
   /**
    * Big-O (n)
    */
   LinkedList(const LinkedList& ll)
   {
	   Size=0; head=NULL;tail=NULL;
	   ListNode* front=ll.head;
	   cerr<<front->getElem();
	   while(front!=NULL)
	   {
		//   cerr<<"Monkeys "<<front->getElem()<<endl;
		   insertLast(front->getElem());

		   front=front->getNext();
	   }
   } // copy constructor
   LinkedList & operator=(const LinkedList & ll); // assignment operator
     
   // query function
   int size() const;
   bool isEmpty() const {return (head==NULL&&tail==NULL)||Size==0;/* Complete this function */ }
   
   // accessor functions
   char first() const throw(EmptyLinkedListException);
   ListNode *getHead() const { return head; }
   ListNode *getTail() const { return tail;/* Complete this function */ }

   // update functions
   void insertFirst(char newobj);
   char removeFirst() throw(EmptyLinkedListException);
   void insertLast(char newobj);
   void insertAfter(char newobj, ListNode *node) throw(InvalidPointerException);
   char remove(ListNode *node) throw(InvalidPointerException);
   void removeAll();
   
   friend ostream & operator<<(ostream& out, const LinkedList &ll); //overload <<
};


#endif
