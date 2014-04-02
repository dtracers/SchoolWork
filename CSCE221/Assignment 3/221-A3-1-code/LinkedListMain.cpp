// main function



#include <iostream>
#include "LinkedList.h"
using namespace std;
/*
int main()
{
  LinkedList ll;
  LinkedList ll_copy;
  
  //===== insertion =====
  
  cerr << "ll = ";
  cerr << ll << endl;
  cerr << "length of the list = " << ll.size() << endl << endl;
  //cerr << "first element = " << ll.first() << endl << endl; // throws exception
    
  //ll.insertAfter(7,ll.getHead()); // throws exception
  ll.insertFirst('A');
//  cerr<<ll<<endl;
  ll.insertAfter('N',ll.getHead());
//  cerr<<ll<<endl;
  ll.insertFirst('R');
//  cerr<<ll<<endl;
  ll.insertFirst('O');
//  cerr<<ll<<endl;
  ll.insertLast('G');
//  cerr<<ll<<endl;
  ll.insertLast('E');
//  cerr<<ll<<endl;
  
  cerr << "After inserting 6 elements to ll, ll = ";
  cerr << ll << endl;
  cerr << "length of the list = " << ll.size() << endl;
  cerr << "first element = " << ll.first() << endl << endl; 
  
  //===== assignment operator =====
    
  ll_copy = ll;
  cerr << "Assigning ll to ll_copy, ll_copy = ";
  cerr << ll_copy << endl;
  cerr << "length of the list = " << ll_copy.size() << endl;
  cerr << "first element = " << ll_copy.first() << endl << endl;
  
  //===== copy constructor =====
  
  LinkedList ll_copy2(ll);
  cerr << "Copying ll to ll_copy2, ll_copy2 = ";
  cerr << ll_copy2 << endl;
  cerr << "length of the list = " << ll_copy2.size() << endl;
  cerr << "first element = " << ll_copy2.first() << endl << endl;  

  //===== remove(), removeFirst() =====
  
  ll.remove(ll.getHead());
  ll.remove(ll.getTail());

  cerr << "After removing the first and the last elements from ll, ll = ";
  cerr << ll << endl;
  cerr << "length of the list = " << ll.size() << endl;
  cerr << "first element = " << ll.first() << endl << endl;
  
  ll.removeFirst();
  ll.removeFirst();
  ll.removeFirst();
  ll.removeFirst();
  //ll.removeFirst(); // throws exception
  //ll.remove(ll.getHead()); // throws exception

  cerr << "After removing the rest 4 elements from ll, ll = ";
  cerr << ll << endl;
  cerr << "length of the list = " << ll.size() << endl;
  //cerr << "first element = " << ll.first() << endl << endl; // throws exception
  if (ll.isEmpty())
    cerr << "list is empty." << endl;
  cerr << endl;
  
  //===== removeAll() =====
  
  ll_copy.removeAll();
  cerr << "After removing all elements, ll_copy = ";
  cerr << ll_copy << endl;
  cerr << "length of the list = " << ll_copy.size() << endl;
  if (ll_copy.isEmpty())
    cerr << "list is empty." << endl;
  cerr << endl;
  
  //===== Insertion sort on linked list =====
  
  cerr << "The copy of ll, ll_copy2 = ";
  cerr << ll_copy2 << endl;
  cerr << "length of the list = " << ll_copy2.size() << endl;
  cerr << "first element = " << ll_copy2.first() << endl << endl;
  
  cerr << "Sorts ll_copy2: " << endl;
  
  // "node" points to the second node
  ListNode *node = ll_copy2.getHead()->getNext();
  while (node != NULL) {
    cerr << endl << "Inserting the node " << node->getElem();
    
    // Searches between the head and "node" for "p"
    // of which "p" is >= "node"
    ListNode *p = ll_copy2.getHead();
    ListNode *prev = NULL;
    while (p != node && p->getElem() < node->getElem()) {
      prev = p;
      p = p->getNext();
    }
    
    if (p == node) {
      cerr << " at the original position" << endl;
      node = node->getNext();
      cerr << "ll_copy2 remains unchanged = " << ll_copy2 << endl;
    } else {
      cerr << " before " << p->getElem();
      if (prev!=NULL) {
        cerr << " after " << prev->getElem();
        // Inserts "node" after "p"
        ll_copy2.insertAfter(node->getElem(),prev);
      } else
        ll_copy2.insertFirst(node->getElem());
      cerr << endl;
      
      cerr << "After insertion, ll_copy2 = ";
      cerr << ll_copy2 << endl;
      
      // Removes original "node" and advances "node"
      ListNode *tmpNode = node;
      node = node->getNext();
      cerr << "Removing the node " << tmpNode->getElem();
      ll_copy2.remove(tmpNode);
      cerr << ", ll_copy2 = " << ll_copy2 << endl;
    }
  } 
  
  cerr << endl;
  cerr << "After applying insertion sort, ll_copy2 = ";
  cerr << ll_copy2 << endl;
  cerr << "length of the list = " << ll_copy2.size() << endl;
  cerr << "first element = " << ll_copy2.first() << endl << endl;
  
  return 0;
}
*/
