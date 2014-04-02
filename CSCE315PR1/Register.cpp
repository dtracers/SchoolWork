/*
 * Register.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: gigemjt
 */

#include "Register.h"


Register::Register() {
	// TODO Auto-generated constructor stub
}

/**
 * returns all the courses
 */
map<int,Course*> Register:: get_courses() const
{
    return courses;
}

/**
 * returns all the students
 */
map<int,Student*> Register::get_students() const
{
    return students;
}

/**
 * this will return a student with the given number
 */
Student* Register::get_student(int num)
{
	return students[num];
}

/**
 * this will return a course with the given number
 */
Course* Register::get_course(int num)
{
	return courses[num];
}
/**
 * adds a new course in the map with the course number
 */
void Register::add_course(Course* c)
{
    courses[c->get_course_number()]=c;
}

/**
 * adds a new student in the map with the student number
 */
void Register::add_student(Student* s)
{
    students[s->get_student_number()]=s;
}

/**
 * this will add the given student to the given course
 * returns true if enrolled
 * returns false if put on waitlist
 */
bool Register::enroll_student_in_course(int course_num,int student_num)
{
	return get_course(course_num)->enroll_student(get_student(student_num));
}

/**
 * this will remove the given student from the given course
 */
void Register::remove_student_from_course(int course_num,int student_num)
{
	get_course(course_num)->remove_student_from_course(get_student(student_num));
}

/**
 *
 */
void Register::print_student_report(int student_num)
{
	//a course class for static methods
	Course course;
	//creates the student
	Student* s=this->get_student(student_num);
	vector<vector<string> > un_formatted;

	//prints the course info first
	un_formatted.push_back(s->print_student_labels());
	un_formatted.push_back(s->print_student_info());
	cout<<format(un_formatted,s->print_student_labels().size());
	//empties the list
	un_formatted=*(new vector<vector<string> >());;

	un_formatted.push_back(course.print_course_labels());

	//creates the iterator
	list<Course*>::iterator it;
	list<Course*> course_list=s->get_courses_in();
	bool nobody_in_class=true;
	if(course_list.size()>0)
	{
		//adds the students enrolled to the unformatted so it can be formatted;
		for ( it=course_list.begin() ; it != course_list.end(); it++ )
		{
			Course* c=*it;
			un_formatted.push_back(c->print_course_info());
		}
		//formats them then prints out the newly formated input
		cout<<"\nCourses the student is enrolled in\n";
		format(un_formatted,course.print_course_labels().size());
		//3=number of labels
		nobody_in_class=false;
	}
	//empties the list
	un_formatted=*(new vector<vector<string> >());;

	un_formatted.push_back(course.print_course_labels());

	//repeats above but with the waitlist
	course_list=s->get_courses_waitlist();
	if(course_list.size()>0)
	{
		//adds the students enrolled to the unformatted so it can be formatted;
		for ( it=course_list.begin() ; it != course_list.end(); it++ )
		{
			Course* c=*it;
			un_formatted.push_back(c->print_course_info());
		}
		cout<<"\nCourses that the student is on the waitlist for\n";
		format(un_formatted,course.print_course_labels().size());
		//3=number of labels
		nobody_in_class=false;
	}
	//empties the list
	un_formatted=*(new vector<vector<string> >());;
}

/**
 *
 */
void Register::print_course_report(int course_num)
{
	//a student class for static methods
	Student stud;
	//creates the course
	Course* c=this->get_course(course_num);
	vector<vector<string> > un_formatted;

	//prints the course info first
	un_formatted.push_back(c->print_course_labels());
	un_formatted.push_back(c->print_course_info());
	format(un_formatted,c->print_course_labels().size());
	//empties the list
	un_formatted=*(new vector<vector<string> >());;

	un_formatted.push_back(stud.print_student_labels());

	//creates the iterator
	list<Student*>::iterator it;
	list<Student*> student_list=c->get_students_enrolled();
	bool nobody_in_class=true;
	if(student_list.size()>0)
	{

		//adds the students enrolled to the unformatted so it can be formatted;
		for ( it=student_list.begin() ; it != student_list.end(); it++ )
		{
			Student* s=*it;
			un_formatted.push_back(s->print_student_info());
		}
		//formats them then prints out the newly formated input
		cout<<"\nStudents enrolled in this class\n";
		format(un_formatted,3);
		//3=number of labels
		nobody_in_class=false;
	}
	//empties the list
	un_formatted=*(new vector<vector<string> >());

	un_formatted.push_back(stud.print_student_labels());

	//repeats above but with the waitlist
	student_list=c->get_students_waiting();
	if(student_list.size()>0)
	{
		//adds the students enrolled to the unformatted so it can be formatted;
		for ( it=student_list.begin() ; it != student_list.end(); it++ )
		{
			Student* s=*it;
			un_formatted.push_back(s->print_student_info());
		}
		cout<<"\nStudents that are on the wait list for this class\n";
		format(un_formatted,3);
		//3=number of labels
		nobody_in_class=false;
	}
	if(nobody_in_class)
	{
		cout<<"Nobody is registered for this class\n";
	}
	//empties the list
	un_formatted=*(new vector<vector<string> >());
}

/**
 * This will format all given strings so they all have the same spacing
 * it uses the other string
 * list will hold multiple lines of strings
 * each line should hold the exact same number strings
 * line_length is the number of strings in any one line
 */
string Register::format(vector<vector<string> > list,int line_length)
{
	vector<string> output;
	for(int k=0;k<line_length;k++)
	{
		int longest_word=-1;
		//this will find the length of the longest word
		for(int q=0;q<list.size();q++)
		{
			int word_length=list[q][k].size();
			if(word_length>longest_word)
			{
				longest_word=word_length;
			}
			//that way it doesn't make extraneous lines
			if(k==0)
			output.push_back("");
		}
		for(int q=0;q<list.size();q++)
		{
			//this will add spaces to the end of the word till they are all the same length
			string word=list[q][k];
			while(word.size()<=longest_word)
			{
				word+=" ";
			}
			output[q]=output[q]+word;
		}
	}
	string out_str="";
	for(int k=0;k<output.size();k++)
	{
//		out_str=output[k]+"\n";
		cout<<output[k]<<"\n";
	}
	return out_str;
}


Register::~Register() {
	// TODO Auto-generated destructor stub
}
