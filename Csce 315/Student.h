/*
 * Student.h
 * This class will represent a student.
 * It will have a name, a number,
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */
using namespace std;
#include <list>
#include <string>
#include <sstream>
#include <vector>
class Course;

#ifndef STUDENT_H_
#define STUDENT_H_
class Student {
private:
	string student_major;
	string student_name;
	int student_number;

	list<Course*> courses_in;
	list<Course*> courses_waiting;

	string int_to_string(int t);
public:
	Student();
	virtual ~Student();

	/*******************
	//get methods
	********************/
    list<Course*> get_courses_in() const;
    list<Course*> get_courses_waitlist() const;
    string get_student_name() const;
    string get_student_major() const;
    int get_student_number() const;

    /*******************
	//set methods
	********************/
    void add_course(Course* c);
    void add_waitlist_course(Course* wait);
    void set_student_name(string student_name);
    void set_student_major(string student_major);
    void set_student_number(int student_number);

    /*******************
	//Removing Methods
	********************/
    Course* remove_course(Course* c);
    Course* remove_waitlist_course(Course* c);

    /*******************
	//Printing Methods
	********************/
    vector<string> print_student_info();
    vector<string> print_student_labels();
};

#endif /* STUDENT_H_ */
