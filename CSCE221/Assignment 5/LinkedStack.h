// LinkedStack.h

#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_

#include <iostream>
#include "RuntimeException.h"
#include "LinkedList.h"
#include "LinkedList.cpp"

template<typename T> class LinkedStack;

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedStack<T>& stack);
    
template<typename T>
class LinkedStack
{
	private:
	   LinkedList<T> ll;
public:
	   // user-defined exceptions
	   class StackEmptyException : public RuntimeException {
	   public:
	     StackEmptyException() : RuntimeException("Stack is empty") {}
	   };

	   LinkedStack<T>() {ll; /* Complete this function */ } // constructor
	   ~LinkedStack<T>() { ll.removeAll();/* Complete this function */ } // destructor
	   LinkedStack<T>(const LinkedStack<T>& queue) {ll=queue.ll; /* Complete this function */ } // copy constructor
	   LinkedStack<T>& operator=(const LinkedStack<T>& queue); // assignment operator

	   // query function
	   int size() const {return ll.size(); /* Complete this function */ }
	   bool isEmpty() const {return  ll.isEmpty();/* Complete this function */  }

	   // accessor function
	   T top() const //throw(StackEmptyExcpetion)
	   {
		   if(ll.isEmpty())
		   	{
		   		//throw StackEmptyException();
		   	}
		   	return ll.last();
	   }

	   // update functions
		void push(T elem) {ll.insertLast(elem); /* Complete this function */ }
		T pop() //throw(StackEmptyException)
		{
			if(isEmpty())
			{
				//throw StackEmptyException();
			}
			return ll.removeLast();
		}
   /* declare rest of functions */
      
   friend std::ostream& operator<< <>(std::ostream& out,
                              const LinkedStack<T>& stack); //overload <<
};

/* describe rest of the functions here */

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedStack<T>& stack)
{
	out<<stack.ll;
  /* fill in the function */
   return out;
}

#endif
