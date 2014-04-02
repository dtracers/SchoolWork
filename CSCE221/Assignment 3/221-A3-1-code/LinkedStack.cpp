// LinkedStack.cpp

#ifndef LINKEDLISTSTACK_CPP
#define LINKEDLISTSTACK_CPP

#include "LinkedStack.h"

// assignmnet operator
/**
 * Big-O(n)
 */
LinkedStack& LinkedStack::operator=(const LinkedStack& stack) 
{
	this->ll=stack.ll;
  /* Complete this function */
  return *this;
}

// query function

char LinkedStack::top() const throw(StackEmptyException)
{
  /* Complete this function 
   * if the stack is empty, throw an StackEmptyException
   */
	if(ll.isEmpty())
	{
		throw StackEmptyException();
	}
	return ll.first();
 // return 0;
}

// update function

char LinkedStack::pop() throw(StackEmptyException)
{
  /* Complete this function 
   * if the stack is empty, throw an StackEmptyException
   */
	if(isEmpty())
	{
		throw StackEmptyException();
	}
	return ll.removeFirst();
//	return 0;
}
/**
 * Big-O(n)
 */
ostream& operator<<(std::ostream& out, const LinkedStack& stack)
{
	out<<stack.ll;
  /* Complete this function;
  * This function outputs each element in the stack from top to bottom;
  * The elements are delimited by spaces.
  */
  return out;
}


#endif 
