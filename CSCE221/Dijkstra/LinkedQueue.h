// LinkedQueue.h

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
#include "RuntimeException.h"
#include "LinkedList.h"

template<typename T> class LinkedQueue;

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedQueue<T>& queue);

template<typename T>
class LinkedQueue {
private:
   /* declare member variables here */

public:
   // user-defined exceptions
   class QueueEmptyException : public RuntimeException {
   public:
     QueueEmptyException() : RuntimeException("Access to an empty queue") {}
   };

   /* declare rest of functions */
   
   friend std::ostream& operator<< <>(std::ostream& out, const LinkedQueue<T>& queue); // overload <<
};

/* describe rest of the functions here */

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedQueue<T>& queue)
{
  /* fill in the function */
   return out;
}

#endif
