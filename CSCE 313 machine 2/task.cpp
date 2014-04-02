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


char * Task::Name()
{
	return name;
}
void* myRun(void* arg)
{
	Task* b=(Task*)arg;
	b->Run();
	//Task::Run();
}

void Task::Start()
{
	pthread_create(&thread_id, NULL, myRun,this);
}

void Task::GracefullyExitMainThread()
{

}
Task::~Task()
{

}
