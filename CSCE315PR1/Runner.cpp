/*
 * Runner.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */
#include "Student.h"
#include "Course.h"
#include "Register.h"
#include <iostream>
#include <fstream>
using namespace std;

/**
 * This will add a student to the course with the given Register
 */
void add_student_to_course(Register* r,istream& ifs)
{
	int course_number;
	ifs>>course_number;
	int student_number;
	ifs>>student_number;
	cout<<"adding student "<<student_number<<" to class "<<course_number<<"\n";
	r->enroll_student_in_course(course_number,student_number);
}

/**
 * This will drop a student from the course with the given Register
 */
void drop_student_from_course(Register* r,istream& ifs)
{
	int course_number;
	ifs>>course_number;
	int student_number;
	ifs>>student_number;
	cout<<"removing student "<<student_number<<" from class "<<course_number<<"\n";
	r->remove_student_from_course(course_number,student_number);
}

/**
 * This will add a student given Register with the given iostream
 */
void change_enrollment(Register* r,istream& ifs)
{
	int number;
	ifs>>number;
	Course* c=r->get_course(number);
	int max_enroll;
	ifs>>max_enroll;
	c->set_max_enrollment(max_enroll);
	cout<<"New max enrollment = "<<max_enroll<<"\n";
}

/**
 * This will add a course to the given Register with the given iostream
 */
void add_course(Register* r,istream& ifs)
{
	Course* s=new Course();
	int number;
	ifs>>number;
	s->set_course_number(number);

	int max_enroll;
	ifs>>max_enroll;
	s->set_max_enrollment(max_enroll);

	string course_title="";
	ifs>>course_title;
	s->set_course_title(course_title);
	r->add_course(s);
	cout<<"Adding Class "<<number<<"\n";
}

/**
 * This will add a student to the given Register with the given iostream
 */
void add_student(Register* r,istream& ifs)
{
	Student* s=new Student();

	int number;
	ifs>>number;
	s->set_student_number(number);

	string first_name="";
	string last_name="";
	ifs>>first_name;
	ifs>>last_name;
	s->set_student_name(first_name+" "+last_name+" ");

	string major="";
	ifs>>major;
	s->set_student_major(major);

	r->add_student(s);
	cout<<"Adding Student "<<number<<"\n";
}

/**
 * This will print the course info of the given Register and the given iostream
 */
void print_course_info(Register* r,istream& ifs)
{
	int number;
	ifs>>number;
	cout<<"\nprinting report for class "<<number<<"\n";
	r->print_course_report(number);
	cout<<"\n";
}

/**
 * This will print the student info of the given Register and the given iostream
 */
void print_student_info(Register* r,istream& ifs)
{
	int number;
	ifs>>number;
	cout<<"\nprinting report for student "<<number<<"\n";
	r->print_student_report(number);
	cout<<"\n";
}

int main()
{
//  ifstream ifs ( "inputdata.txt" , ifstream::in ); //this is for reading from a file
	istream& ifs=cin;
	Register* r=new Register();
	string data="";
	bool done=false;
	while(!ifs.eof()&&!done)
	{
	  cout<<"enter new command. Type \"done\" to quit\n";
	  ifs>>data;
	  //if the length of data is two then it is either PC or PS
	  if(data=="done"||data=="")
	  {
		  done=true;
	  }
	  if(!done)
	  {
		  if(data.length()==2)
		  {
			  switch(data[1])
			  {
				  case 'S':print_student_info(r,ifs);break;

				  case 'C':print_course_info(r,ifs);break;
			  }
		  }else
		  {
			  //
			  switch(data[0])
			  {
				  case 'S':add_student(r,ifs);break;

				  case 'C':add_course(r,ifs);break;

				  case 'L':change_enrollment(r,ifs);break;

				  case 'A':add_student_to_course(r,ifs);break;

				  case 'D':drop_student_from_course(r,ifs);break;
			  }

		  }
		  done=data=="";
	  }
	}
	cout<<"Thank you for accessing my system";
}
