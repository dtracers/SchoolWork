/*
#include <iostream>
using namespace std;
#include "task.h"




class RudderController : public Task {

public:

  RudderController(char _name[]) : Task(_name) {}



  void Run() {

	  cerr<<"running"<<endl;
    cout << "Rudder Controller [" << name << "] running\n" << endl;

    for (int i = 0; i < 10; i++) {

      cout << name << " waiting for next sensor input\n" << endl;

      usleep(1000000);

      cout << name << " issueing rudder control command\n" << endl;

      usleep(10000);

    }

  }

};



class AvionicsTask : public Task {

public:

  AvionicsTask(char _name[]) : Task(_name) {}



  void Run() {

    cout << "Avionics System [" << name << "] running\n" << endl;

    for (int i = 0; i < 10; i++) {

      cout << name << " waiting for next refresh interval\n" << endl;

      usleep(700000);

      cout << name << " refreshing avionics screen\n" << endl;

      usleep(12000);

    }

  }

};





int main(int argc, char * argv[]) {



  /* -- CREATE TASKS */
/*
  RudderController task1("rudder control");

  AvionicsTask     task2("avionics task");



  /* -- LAUNCH TASKS */
/*
  task1.Start();

  task2.Start();



  Task::GracefullyExitMainThread();

}

*/
