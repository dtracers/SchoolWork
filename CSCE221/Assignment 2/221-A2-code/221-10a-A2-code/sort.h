//============================================================================
// Name        : sort.h
// Author      : 
// Date        :
// Copyright   : 
// Description : Sort interface and various sorting algorithms in C++
//============================================================================
#include<sstream>
#include<iostream>
#ifndef SORT_H_
#define SORT_H_

using namespace std;

class Sort {
protected:
   int Comp[5]; // number of comparisons performed in sort function
public:
   virtual void sort(int A[], int size) = 0;    // main entry point
   bool testIfSorted(int A[], int size);        // returns false if not sorted
                                                // true otherwise
   string getNumCmps()
   {
	   string g="";
	   for(int k=0;k<5;k++)
	   {
		   string g2="";
		   stringstream s;
		   s<<Comp[k];
		   s>>g2;
		   g+=g2+" , ";
	   }
	   return g;
   }        // returns # of comparisons
   void add_to_compare()
   {
	   int k=0;
	   Comp[k]++;
	   while(Comp[k]<0&&k<5)
	   {
		   Comp[k]=0;
		   Comp[k+1]++;
		//   cerr<<Comp[k+1];
		   k+=1;
	   }
   }
};

class SelectionSort:public Sort {	// SelectionSort class
public:
  void sort(int A[], int size);		// main entry point
};

class InsertionSort:public Sort {	// InsertionSort class
public:
  void sort(int A[], int size);		// main entry point
};

class BubbleSort:public Sort {		// BubbleSort class
public:
  void sort(int A[], int size);		// main entry point
};

class ShellSort:public Sort {		// ShellSort class
public:
  void sort(int A[], int size);		// main entry point
};

class RadixSort:public Sort {		// RadixSort class
public:
  void sort(int A[], int size);		// main entry point
};

#endif //SORT_H_
