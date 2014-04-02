/*
 * Semaphore.h
 *
 *  Created on: Mar 17, 2012
 *      Author: gigemjt
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_
/*

    File: semaphore.H



    Author: R. Bettati

            Department of Computer Science

            Texas A&M University

    Date  : 08/02/11



*/



#ifndef _semaphore_H_                   // include file only once

#define _semaphore_H_



/*--------------------------------------------------------------------------*/

/* DEFINES */

/*--------------------------------------------------------------------------*/



/* -- (none) -- */



/*--------------------------------------------------------------------------*/

/* INCLUDES */

/*--------------------------------------------------------------------------*/

#include <iostream>

#include <pthread.h>



/*--------------------------------------------------------------------------*/

/* DATA STRUCTURES */

/*--------------------------------------------------------------------------*/



/* -- (none) -- */



/*--------------------------------------------------------------------------*/

/* FORWARDS */

/*--------------------------------------------------------------------------*/



/* -- (none) -- */



/*--------------------------------------------------------------------------*/

/* CLASS   S e m a p h o r e  */

/*--------------------------------------------------------------------------*/



class Semaphore {

private:

  int             value;

  pthread_mutex_t m;

  pthread_cond_t  c;

public:



  /* -- CONSTRUCTOR/DESTRUCTOR */



  Semaphore(int _val);



  ~Semaphore();



  /* -- SEMAPHORE OPERATIONS */



  int P();

  int V();

};





#endif






#endif /* SEMAPHORE_H_ */
