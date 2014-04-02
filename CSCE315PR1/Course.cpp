/*
 * Course.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */
#include "Course.h"


Course::Course() {

}

/**
 * returns the course number
 */
int Course::get_course_number() const
{
    return course_number;
}

/**
 * returns the course title
 */
string Course::get_course_title() const
{
    return course_title;
}

/**
 * returns the max enrollment
 */
int Course::get_max_enrollment() const
{
    return max_enrollment;
}

/**
 * returns the list of the students enrolled
 */
list<Student*> Course::get_students_enrolled() const
{
    return students_enrolled;
}

/**
 * returns the list of the students on the waitlist
 */
list<Student*> Course::get_students_waiting() const
{
    return students_waiting;
}



/**
 * sets the course number
 */
void Course::set_course_number(int course_number)
{
    this->course_number = course_number;
}

/**
 * set the course title
 */
void Course::set_course_title(string course_title)
{
    this->course_title = course_title;
}

/**
 * sets the max enrollment
 */
void Course::set_max_enrollment(int max_enrollment)
{
    this->max_enrollment = max_enrollment;
}

/**
 * this will enroll a student
 * if the class is full it will add a student to the waitlist
 * otherwise it will add the student to the course
 * (the student will also add the course to its list of courses)
 */
bool Course::enroll_student(Student* student)
{
	if(has_space())
	{
		this->students_enrolled.push_back(student);
		student->add_course(this);
		return true;
	}else
	{
		add_student_waitlist(student);
		return false;
	}
}

/**
 * This will add a student to the wait list of the course
 * (the student will also add the course to its wait list)
 */
void Course::add_student_waitlist(Student* student)
{
    this->students_waiting.push_back(student);
    student->add_waitlist_course(this);
}



/**
 * This will remove the student from the course
 * if there is now room and there are people on the wait list
 * it will add them to the course
 * (the student will also remove the course from its list)
 */
Student* Course::remove_student_from_course(Student* student)
{
	this->students_enrolled.remove(student);
	student->remove_course(this);
	if(has_space()&&this->students_waiting.size()>0)
	{
		Student* next_student=remove_student_from_waitlist(students_waiting.front());
		this->enroll_student(next_student);
	}
	return student;
}

/**
 * This will remove the student from the waitlist
 * (the student will also remove the course from its list)
 */
Student* Course::remove_student_from_waitlist(Student* student)
{
	this->students_waiting.remove(student);
	student->remove_waitlist_course(this);
	return student;
}


/**
 * this will return true if there is at least 1 spot available false otherwise
 */
bool Course::has_space()
{
	int left_over=this->get_max_enrollment()-this->students_enrolled.size();
	if(left_over>0)
		return true;
	return false;
}


/**
 * this will print the course info in this format:
 *
 *	<Course Title>	<Course Number>	<Max enrollment #>	<current enrollment #>	<# in waitlist>
 *
 *	if the given bool is false then it will not print the top line
 */
vector<string> Course::print_course_info()
{
	vector<string> info;
	info.push_back(get_course_title()+"  ");
	info.push_back(int_to_string(get_course_number())+"  ");
	info.push_back(int_to_string(get_max_enrollment())+"  ");
	info.push_back(int_to_string(get_students_enrolled().size())+"  ");
	info.push_back(int_to_string(get_students_waiting().size())+"  ");
	return info;
}

/**
 * This will return the labels in this format
 * Course Title		Course Number	Max Enrollment		Current enrollment		amount in waitlist
 */
vector<string> Course::print_course_labels()
{
	vector<string> labels;
	labels.push_back("Course Title  ");
	labels.push_back("Course Number  ");
	labels.push_back("Max Enrollment  ");
	labels.push_back("Current enrollment  ");
	labels.push_back("amount in waitlist  ");
	return labels;
}

/*
 * it converts an int to a string
 */
string Course::int_to_string(int t)
{
	stringstream bottom;
	bottom<<t;
	string temp_string;
	bottom>>temp_string;
	return temp_string;
}

Course::~Course() {
	// TODO Auto-generated destructor stub
}
