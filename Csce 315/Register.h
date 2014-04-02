/*
 * Register.h
 *
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */

#ifndef REGISTER_H_
#define REGISTER_H_
#include"Course.h"
#include<map>
#include<iostream>
class Register {
private:
	map<int,Course*> courses;
	map<int,Student*> students;
public:
	Register();
	virtual ~Register();
    map<int,Course*> get_courses() const;
    map<int,Student*> get_students() const;
    Student* get_student(int num);
    Course* get_course(int num);
    void add_course(Course* c);
    void add_student(Student* s);
    bool enroll_student_in_course(int course_num,int student_num);
    void remove_student_from_course(int course_num,int student_num);
    void print_student_report(int student_num);
    void print_course_report(int course_num);
    string format(vector<vector<string> > list,int line_length);
};

#endif /* REGISTER_H_ */
