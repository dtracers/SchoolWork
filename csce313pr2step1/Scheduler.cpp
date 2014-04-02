/*
 * Scheduler.cpp
 *
 *  Created on: Mar 17, 2012
 *      Author: gigemjt
 */

#include "Scheduler.h"
#include "Schedulable.h"
Scheduler::Scheduler(char _name[])
{
	strncpy(name, _name, MAX_NAME_LEN);
	scheduler_mutex=new Semaphore(-1);
}

Scheduler::~Scheduler()
{

	// TODO Auto-generated destructor stub
}

int Scheduler::Kick_Off( )
{
//	printf("I am kicking off");
//	cerr<<"dequieing"<<endl;

	Schedulable* newTask=this->dequeue();
//	cerr<<"done dequieing"<<endl;
	scheduler_mutex->P();
//	cerr<<"new task is now current task in kickoff";
	current_task=newTask;
	scheduler_mutex->V();
	current_task->Unblock();
//	cerr<<"done kicking off!";
}

int Scheduler::Resume(Schedulable* _task)
{
//	cerr<<"resuming!";
//	cerr<<"resuming task "<<_task<<endl;
	enqueue(_task);
	//_task->Unblock();//probably do other stuff
}

int Scheduler::Start(Schedulable* _task)
{
//	cout<<"enquing "<<_task<<endl;
	enqueue(_task);
//	cerr<<"Task is blocked"<<endl;
	_task -> Block();
//	return _task->Start();
}

int Scheduler::Yield()
{
//	cerr<<"yielding task"<<endl;
	scheduler_mutex->P();
	Schedulable* oldtask=current_task;
	scheduler_mutex->V();
	if(ready_queue.size() > 0)
	{
//		cerr<<"queue size"<<ready_queue.size()<<endl;
		Schedulable* newTask=this->dequeue();
		scheduler_mutex->P();
		current_task=newTask;
		scheduler_mutex->V();
	}else
	{
		cerr<<"ready size is zero"<<endl;
	}
	current_task -> Unblock();
	if(oldtask!=NULL)
	{
		oldtask->Block();
	}
}

int Scheduler::enqueue(Schedulable* _task)
{
	scheduler_mutex->P();
	this->ready_queue.push_back(_task);
	scheduler_mutex->V();
}
Schedulable* Scheduler::dequeue()
{

	Schedulable* sched=NULL;
	if(ready_queue.size() > 0)
	{
		scheduler_mutex->P();
		sched=this->ready_queue.front();
		this->ready_queue.pop_front();
		scheduler_mutex->V();
	}else
	{
	}
	return sched;
}
