/*
 * Schedulable.cpp
 *
 *  Created on: Mar 17, 2012
 *      Author: gigemjt
 */

#include "Schedulable.h"

Schedulable::Schedulable(const char _name[], Scheduler * _sched):Task(_name)
{
	block_semaphore=new Semaphore(0);
	sched=_sched;
	// TODO Auto-generated constructor stub

}
void Schedulable::CarrierForRun()
{
//	cout<<"carring the run"<<endl;
	sched->Start(this);//needs to add task to the queue
	Task::CarrierForRun();

}
int Schedulable::Start()
{
	int e=Task::Start();
}

Schedulable::~Schedulable()
{
	//delete b
	// TODO Auto-generated destructor stub
}

int Schedulable::Block()
{
//	cerr<<"blocking!"<<endl;
	return block_semaphore->P();
}

int Schedulable::Unblock()
{
//	cout<<"unblocking!"<<endl;
	return block_semaphore->V();
}
