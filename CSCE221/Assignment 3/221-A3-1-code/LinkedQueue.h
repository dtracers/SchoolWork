#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
#include "RuntimeException.h"
#include "LinkedList.h"

class LinkedQueue {
private:
   LinkedList ll;

public:
   // user-defined exceptions
   class QueueEmptyException : public RuntimeException {
   public:
     QueueEmptyException() : RuntimeException("Access to an empty queue") {}
   };

   LinkedQueue() {ll; /* Complete this function */ } // constructor
   ~LinkedQueue() { ll.removeAll();/* Complete this function */ } // destructor
   LinkedQueue(const LinkedQueue& queue) {ll=queue.ll; /* Complete this function */ } // copy constructor
   LinkedQueue& operator=(const LinkedQueue& queue); // assignment operator
   
   // query function
   int size() const {return ll.size(); /* Complete this function */ }
   bool isEmpty() const {return  ll.isEmpty();/* Complete this function */  }
   
   // accessor function
   char first() const throw(QueueEmptyException);
   
   // update functions
   void enqueue(char elem) {ll.insertLast(elem); /* Complete this function */ }
   char dequeue() throw(QueueEmptyException);
   
   friend ostream & operator<<(ostream& out, const LinkedQueue& queue); // overload <<
};

#endif
