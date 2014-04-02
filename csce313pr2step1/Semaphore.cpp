/*
 * Semaphore.cpp
 *
 *  Created on: Mar 17, 2012
 *      Author: gigemjt
 */

#include "Semaphore.h"
#include <iostream>
Semaphore::Semaphore(int val)
{
	value=val;
	pthread_mutex_init(&m, NULL);
}

Semaphore::~Semaphore()
{
	// TODO Auto-generated destructor stub
}

/*if P==0 continue
 * else block thread add one to P
 */
int Semaphore::P()
{
//	printf("semaphore P\n");
	int error = 0;
	error = pthread_mutex_lock(&m);

	value+=1;
	pthread_mutex_unlock(&m);
	while(value>0)
	{
	//	printf("waiting %d\n",value);
		pthread_cond_wait(&c,&m);
	}
//	printf("done unlocking");
	pthread_mutex_unlock(&m);
}
/**
 * signals a blocked thread
 * subtracts one from semaphore
 */
int Semaphore::V()
{
//	printf("semaphore V %d\n",value);
	pthread_mutex_lock(&m);
	pthread_mutex_unlock(&m);
	//if its here then value is not less than zero
	pthread_mutex_lock(&m);
	value--;
	pthread_cond_signal(&c);
	//pthread_cond_broadcast(&c);
	pthread_mutex_unlock(&m);
	//done!!!!
}
