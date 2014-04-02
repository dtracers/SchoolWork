/* TEST PROGRAM FOR STEP 2 of MP2 */

#include <iostream>
#include "task.h"
#include "scheduler.h"
#include "schedulable.h"

using namespace std;

class RudderController : public Schedulable {
public:
  RudderController(char _name[], Scheduler * _sched) : 
    Schedulable(_name, _sched) {}

  void Run() {
    cout << "Rudder Controller [" << name << "] running\n" << flush;
    for (int i = 0; i < 100; i++) {
      cout << name << " waiting for next sensor input\n" << flush;
      if (i % 5 == 1) {
	sched->Resume(this);
	sched->Yield();
      }
      cout << name << " issueing rudder control command\n" << flush;
      usleep(10000);
    }
    cout << "Rudder Controller [" << name << "] done!\n" << flush;
  }
};

class AvionicsTask : public Schedulable {
public:
  AvionicsTask(char _name[], Scheduler * _sched) : 
    Schedulable(_name, _sched) {}

  void Run() {
    cout << "Avionics System [" << name << "] running\n" ;
    for (int i = 0; i < 100; i++) {
      cout << name << " waiting for next refresh interval\n" ;
      if (i % 10 == 1) {
	sched->Resume(this);
	sched->Yield();
      }
      cout << name << " refreshing avionics screen\n" ;
      usleep(12000);
    }
    cout << "Avionics System [" << name << "] done!\n" ;
  }
};

int main(int argc, char * argv[]) {

  /* -- CREATE SCHEDULER */
  Scheduler * system_scheduler = new Scheduler("scheduler");

  /* -- CREATE TASKS */
  RudderController task1("rudder control", system_scheduler);
  AvionicsTask     task2("avionics task", system_scheduler);
//  cout<<"before launch"<<endl;
  /* -- LAUNCH TASKS */
  task1.Start(); // cout<<"task one started"<<endl;
  task2.Start();

  cout << "end of launch"<<endl;

  usleep(100000);

  /* -- START SCHEDULING */  cout<<"\n\n\nscheduling started"<<endl;
  system_scheduler->Kick_Off();

  /* -- Have the parent thread get out of the way. */
  Task::GracefullyExitMainThread();
}
