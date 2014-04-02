#include "Evaluator.h"
#include <sstream>
#include <math.h>
using namespace std;


//this might be harder than i thought
double Evaluator::getValue() {
	while(!list->isEmpty())
	{
		Element s=list->pop();
		cerr<<"List "<<*list<<endl;
		cerr<<"popped value "<<s<<endl;
		double r_value=0;
		if(s.is_operand())
		{
			if(s.is_cool_operand())
			{
				if(s.get_cool_operand()=="cos")
				{
					return cos(getValue());
				}
			}else
			{
				double d2=getValue(),d1=getValue();
				switch(s.get_operand())
				{
					case '+': r_value=d1+d2;break;
					case '-': r_value=d1-d2;break;
					case '*': r_value=d1*d2;break;
					case '/': r_value=d1/d2;break;
					case '^': r_value=pow(d1,d2);break;
				}
			}
		}else if(s.is_equation())
		{
			Evaluator* temp=new Evaluator(s.get_equation(),operations);
			return temp->getValue();
		}else
		{
			map<string,Equation_Parser*>::iterator it;
			it=operations->find(s.get_value());
			if(it!=operations->end())
			{
				Evaluator* temp=new Evaluator((*operations)[s.get_value()],operations);
				return temp->getValue();
			}else
			{
				stringstream s2(s.get_value());
				double d=0;
				s2>>d;
				r_value=d;
			}
		}
		return r_value;
	}
}
