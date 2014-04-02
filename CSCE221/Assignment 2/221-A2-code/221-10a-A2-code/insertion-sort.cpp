//============================================================================
// Name        : insertion-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"

void
InsertionSort::sort(int A[], int size) {
    int tmp;
    for (int k = 1; k < size; k++ ) {
        tmp = A[k];
        int j = k;
        for( ; j > 0 && (add_to_compare(), tmp < A[j-1]); j--)
        A[j] = A[j-1];
        A[j] = tmp;
    }
}
