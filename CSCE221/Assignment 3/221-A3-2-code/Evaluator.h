#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Equation_Parser.h"
//#include "LinkedList.h"
//#include "LinkedStack.h"
#include "RuntimeException.h"

class Evaluator {
public:
  // user-defined exceptions
  class DivisionByZeroException : public RuntimeException {
    public:
      DivisionByZeroException() : RuntimeException("Division by zero") {}
  };     
private:
  map<string,Equation_Parser*> * operations;
	/* declare member variables;
	may include a string postfix queue and a double value stack */
	LinkedStack<Element>* list;
	/* declare utility functions */
	double getValue(Element num1,Element num2,Element op);
public:
	  Evaluator(Equation_Parser* par,map<string,Equation_Parser*>* op) {list=par->getList();operations=op;}
	  Evaluator(LinkedStack<Element>* par,map<string,Equation_Parser*>* op) {list=par;operations=op;}// constructor
	double getValue(); // returns the result of expression evaluation

};

#endif
