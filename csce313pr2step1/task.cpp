/*
 * task.cpp
 *
 *  Created on: Mar 13, 2012
 *      Author: gigemjt
 */

#include"task.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<pthread.h>
#include <iostream>
vector<pthread_t*> thread_list;
char * Task::Name()
{
	return name;
}
void* myRun(void* arg)
{
//	printf("RUnning ");
	Task* b=(Task*)arg;
//	printf("pointer address is %p\n",b);
	b->CarrierForRun();
	pthread_exit(NULL);
}

int Task::Start()
{
//	cout<<"starting task!"<<endl;
	pthread_create(&thread_id, NULL, myRun,this);
	thread_list.push_back(&thread_id);
}

void Task::GracefullyExitMainThread()
{
	for(int k=0;k<thread_list.size();k++)
	{
		int error=pthread_join(*(thread_list[k]),NULL);
	}
}
Task::~Task()
{

}
