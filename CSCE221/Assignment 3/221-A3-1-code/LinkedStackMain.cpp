// main function



#include <iostream>
#include "LinkedStack.h"
using namespace std;

int main()
{
   LinkedStack stack;
   LinkedStack stack_copy;

   //===== push() =====
   
   stack.push('O');
   stack.push('R');
   stack.push('A');
   stack.push('N');
   stack.push('G');
   stack.push('E');

   cerr << "stack = " << stack << endl;
   cerr << "size of stack = " << stack.size() << endl;
   cerr << "top of stack = " << stack.top() << endl << endl;
     
   //===== assignment operator =====
   
   stack_copy = stack;
   cerr << "assigning stack to stack_copy, stack_copy = ";
   cerr << stack_copy << endl;
   cerr << "size of stack_copy = " << stack_copy.size() << endl;
   cerr << "top of stack_copy = " << stack_copy.top() << endl << endl;
   
   //===== copy constructor =====
   
   LinkedStack stack_copy2(stack);
   cerr << "copy constructor stack = ";
   cerr << stack_copy2 << endl;
   cerr << "size of stack_copy2 = " << stack_copy2.size() << endl;
   cerr << "top of stack_copy2 = " << stack_copy2.top() << endl << endl;
   
   //===== pop() =====
   
   while (!stack_copy2.isEmpty()) {
     cerr << stack_copy2.pop() << endl;
   }   

   cerr << "popping all elements from stack_copy2, stack_copy2 = ";
   cerr << stack_copy2 << endl;
   
   try {
     stack_copy2.pop();
   } catch(RuntimeException &e) {
     cerr << e << endl;
   }
   cerr << endl;
   
   cerr << "original stack:" << endl;
   cerr << stack << endl;
   
   return 0;
}

