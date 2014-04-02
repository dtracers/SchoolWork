#include "LinkedQueue.h"
#include <iostream>
#include <string>
#include <iterator>
using namespace std;
/*
int main()
{
  LinkedQueue queue;
  LinkedQueue queue_copy;

  //===== enqueue() =====
   
  queue.enqueue('1');
  queue.enqueue('2');
  queue.enqueue('3');
  queue.enqueue('4');
  queue.enqueue('5');
  queue.enqueue('6');

  cerr << "queue = " << queue << endl;
  cerr << "size of queue = " << queue.size() << endl;
  cerr << "first of queue = " << queue.first() << endl << endl;
     
  //===== assignment operator =====
   
  queue_copy = queue;
  cerr << "assigning queue to queue_copy, queue_copy = ";
  cerr << queue_copy << endl;
  cerr << "size of queue_copy = " << queue_copy.size() << endl;
  cerr << "first of queue_copy = " << queue_copy.first() << endl << endl;
   
  //===== copy constructor =====
   
  LinkedQueue queue_copy2(queue);
  cerr << "copy constructor queue = ";
  cerr << queue_copy2 << endl;
  cerr << "size of queue_copy2 = " << queue_copy2.size() << endl;
  cerr << "first of queue_copy2 = " << queue_copy2.first() << endl << endl;
   
  //===== dequeue() =====
   
  while (!queue_copy2.isEmpty()) {
    cerr << queue_copy2.dequeue() << endl;
  }   

  cerr << "dequeueing all elements from queue_copy2, queue_copy2 = ";
  cerr << queue_copy2 << endl;
   
  try {
    queue_copy2.dequeue();
  } catch(RuntimeException &e) {
    cerr << e << endl;
  }
  cerr << endl;
   
  cerr << "original queue:" << endl;
  cerr << queue << endl;

  return 0;
}

*/
