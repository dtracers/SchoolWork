/*
 * Student.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */

#include "Student.h"


Student::Student() {

}

/**
 * This will return a list of the courses that
 * the student is currently enrolled in
 */
list<Course*> Student::get_courses_in() const
{
    return courses_in;
}

/**
 * This will return a list of the courses that
 * the student is currently on the waitlist for
 */
list<Course*> Student::get_courses_waitlist() const
{
    return courses_waiting;
}

/**
 * returns the student name
 */
string Student::get_student_name() const
{
    return student_name;
}

/**
 * returns the student's major
 */
string Student::get_student_major() const
{
    return student_major;
}

/**
 * returns the student number
 */
int Student::get_student_number() const
{
    return student_number;
}

/**
 * This will remove a Course the the student is enrolled in
 */
Course* Student::remove_course(Course* c)
{
	this->courses_in.remove(c);
	return c;
}

/**
 * This will remove a Course the the student is enrolled in
 */
Course* Student::remove_waitlist_course(Course* c)
{
	this->courses_waiting.remove(c);
	return c;
}

/**
 * this will add a course that a student is enrolled in
 */
void Student::add_course(Course* c)
{
    this->courses_in.push_back(c);
}

/**
 * this will add a course that the student is in the waitlist on
 */
void Student::add_waitlist_course(Course* wait)
{
	this->courses_waiting.push_back(wait);
}

/**
 * sets the student's name
 */
void Student::set_student_name(string student_name)
{
    this->student_name = student_name;
}

/**
 * sets the student's major
 */
void Student::set_student_major(string student_major)
{
    this->student_major = student_major;
}

/**
 * sets the student's number
 */
void Student::set_student_number(int student_number)
{
    this->student_number = student_number;
}

/**
 * this will print the student info in this format:
 *
 * Name				Number				Major
 * <Student name>	<Student number>	<Student major>
 */
vector<string> Student::print_student_info()
{
	vector<string> info;
	info.push_back(get_student_name()+"  ");
	info.push_back(int_to_string(get_student_number())+"  ");
	info.push_back(get_student_major()+"  ");
	return info;
}

/**
 * This will return the labels in this format
 * Course Title		Course Number	Max Enrollment		Current enrollment		amount in waitlist
 */
vector<string> Student::print_student_labels()
{
	vector<string> labels;
	labels.push_back("Name  ");
	labels.push_back("Number  ");
	labels.push_back("Major  ");
	return labels;
}

/*
 * it converts an int to a string
 */
string Student::int_to_string(int t)
{
	stringstream bottom;
	bottom<<t;
	string temp_string;
	bottom>>temp_string;
	return temp_string;
}

Student::~Student() {

}
