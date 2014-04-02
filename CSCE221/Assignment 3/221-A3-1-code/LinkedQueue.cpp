//LinkedQueue.cpp

#include "LinkedQueue.h"

// assignment operator
/**
 * Big-O(n)
 */
LinkedQueue& LinkedQueue::operator=(const LinkedQueue& queue)
{
	this->ll=queue.ll;
  /* Complete this function */
  return *this;
}

// accessor function

char LinkedQueue::first( ) const throw(QueueEmptyException)
{ 
  /* Complete this function 
   * if the queue is empty, throw an QueueEmptyException
   */
	if(isEmpty())
	{
		throw QueueEmptyException();
	}
  return ll.first();
}

// update functions

char LinkedQueue::dequeue( ) throw(QueueEmptyException)
{
  /* Complete this function 
   * if the queue is empty, throw an QueueEmptyException
   */
	if(isEmpty())
	{
		throw QueueEmptyException();
	}
	return ll.removeFirst();
}
/**
 * Big-O(n)
 */
ostream& operator<<(ostream& out, const LinkedQueue& queue)
{
	out<<queue.ll;
  /* Complete this function;
  * This function outputs each element in the queue from first to last;
  * The elements are delimited by spaces.
  */
  return out;
}
