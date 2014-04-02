// LinkedListStack.h

#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_

#include <iostream>
#include "RuntimeException.h"
#include "LinkedList.h"

class LinkedStack
{
private:
   LinkedList ll;
public:
   // user-defined exceptions
   class StackEmptyException : public RuntimeException {
   public:
     StackEmptyException() : RuntimeException("Stack is empty") {}
   };
   
   LinkedStack() { /* Complete this function */ } // default constructor
   ~LinkedStack() { ll.removeAll();/* Complete this function */ } // destructor
   LinkedStack(const LinkedStack& stack) {ll=stack.ll; /* Complete this function */ } // copy constructor
   LinkedStack& operator=(const LinkedStack& stack); // assignmnet operator
   
   // query functions
   bool isEmpty() {return ll.isEmpty(); /* Complete this function */ }
   int size() const { return ll.size();/* Complete this function */ }
   
   // accessor function
   char top() const throw(StackEmptyException);
   
   // update functions
   void push(const char elem) {ll.insertFirst(elem); /* Complete this function */ }
   char pop() throw(StackEmptyException);
   
   friend ostream& operator<<(std::ostream& out,
                              const LinkedStack& stack); //overload <<
};


#endif
