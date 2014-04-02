/*
 * Course.h
 *
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */
using namespace std;
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include"Student.h"
//class Student;

#ifndef COURSE_H_
#define COURSE_H_
class Course {
private:
	string course_title;
	int course_number;
	int max_enrollment;

	list<Student*> students_enrolled;
	list<Student*> students_waiting;

	string int_to_string(int t);
public:
	Course();
	virtual ~Course();

	/*******************
	//get methods
	********************/
    int get_course_number() const;
    string get_course_title() const;
    int get_max_enrollment() const;
    list<Student*> get_students_enrolled() const;
    list<Student*> get_students_waiting() const;

    /*******************
    //set methods
    ********************/
    void set_course_number(int course_number);
    void set_course_title(string course_title);
    void set_max_enrollment(int max_enrollment);
    //will return false if the student was added to waitlist
    bool enroll_student(Student* student);
    void add_student_waitlist(Student* student);

    /*******************
    //Removing Methods
    ********************/
    Student* remove_student_from_course(Student *);
    Student* remove_student_from_waitlist(Student *);

    //returns true if there is space in the class
    bool has_space();

    /*******************
	//Printing Methods
	********************/
    vector<string> print_course_info();
    vector<string> print_course_labels();
};

#endif /* COURSE_H_ */
