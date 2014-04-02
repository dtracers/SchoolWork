/*  Jordan Donais UIN: 620003643
    August 31, 2011
    marble.cpp file with definitions
    Lab Project 2
*/

#include "marble.h"
#include <time.h>
#include<fstream>

Marble::Color Marble::random_color()
{
	//srand(time(NULL));
    switch (rand()%4) {
    case (0):
        return Marble::red;
        break;
    case (1):
        return Marble::blue;
        break;
    case (2):
        return Marble::yellow;
        break;
    case (3):
        return Marble::green;
        break;
    }
}

//------------------------------------------------------------------------------

Marble::Size Marble::random_size()
{
   // srand(time(NULL));
    switch (rand()%3) {
    case (0):
        return Marble::small;
        break;
    case (1):
        return Marble::medium;
        break;
    case (2):
        return Marble::large;
        break;
    }
}

//------------------------------------------------------------------------------
// Both traits are random
Marble::Marble()
{
    color=random_color();
    size=random_size();    
}

//------------------------------------------------------------------------------

Marble::Marble(Marble::Color c)
{
	color=c;
	size=random_size();
}

//------------------------------------------------------------------------------

Marble::Marble(Marble::Size s)
{
	size=s;
	color=random_color();
}

//------------------------------------------------------------------------------

Marble::Marble(Marble::Color c, Marble::Size s)
{
	color=c;
	size=s;
}

//------------------------------------------------------------------------------

Marble::Color Marble::get_color() const
{
	return color;
}

//------------------------------------------------------------------------------

Marble::Size Marble::get_size() const
{
	return size;
}

//------------------------------------------------------------------------------
// I wanted a string value returned instead of a number for some things
string Marble::get_color_text() const
{
    switch (color) {
    case (0):
        return "red";
        break;
    case (1):
        return "blue";
        break;
    case (2):
        return "yellow";
        break;
    case (3):
        return "green";
        break;
    }
}    

//------------------------------------------------------------------------------

string Marble::get_size_text() const
{
    switch (size) {
    case (0):
        return "small";
        break;
    case (1):
        return "medium";
        break;
    case (2):
        return "large";
        break;
    }
} 

//------------------------------------------------------------------------------

void Marble::set_color(Marble::Color c)
{
	color=c;
}

//------------------------------------------------------------------------------

void Marble::set_size(Marble::Size s)
{
	size=s;
}

//------------------------------------------------------------------------------

// Displays marble information in format (color, size)
ostream& operator<<(ostream& os, const Marble& m)
{
    os<<"("<<m.get_color_text()<<", "<<m.get_size_text()<<")";
    return os;
}

//------------------------------------------------------------------------------

void Marble::write_to_file(const Marble& m1, const Marble& m2)
{
        string out_name="comparisons.txt";
        ofstream out(out_name.c_str());
        out << "You have just compared two marbles with traits ("<<m1.get_color_text()<<", "<<m1.get_size_text()<<") and ("<<m2.get_color_text()<<", "<<m2.get_size_text()<<")\n";
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

istream& operator>>(istream& is, Marble::Color& col)
{
    char eater;
    string check;
    int colo_num;
    while (eater!=',' && eater!='\n' && is>>eater) { // stop if comma is found
        if (eater!=','&&eater!='\n') check+=eater;
    }
    string colo_txt(check);
    stringstream convert(check);
    if (convert>>colo_num) {
        switch (colo_num) {
        case (1):
            col=Marble::red;
            break;
        case (2):
            col=Marble::blue;
            break;
        case (3):
            col=Marble::yellow;
            break;
        case (4):
            col=Marble::green;
            break;
        default:
            throw Marble::Bad_input();
        }
    }
    else {
        if (colo_txt=="r" || colo_txt=="red") { col=Marble::red; return is; }
        if (colo_txt=="b" || colo_txt=="blue") { col=Marble::blue; return is; }
        if (colo_txt=="y" || colo_txt=="yellow") { col=Marble::yellow; return is; }
        if (colo_txt=="g" || colo_txt=="green") { col=Marble::green; return is; }
        throw Marble::Bad_input(); // thrown if input is found to be bad, caller deals with it
    }
    return is;
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Marble::Size& siz)
{
    char eater; 
    string check;
    int siz_num;
    while (/*!is.eof() &&*/ eater!=')' && eater!='\n'&& is>>eater) { // read one character at a time to verify input
        if (eater!=')'&& eater!='\n') check=check+eater; // make a string from the characters
        //cout<<check<<'\n';
    }
    string siz_txt(check);
    stringstream convert(check);
    if (convert>>siz_num) { // see if user put in a number that can be used
        switch (siz_num) {
        case (1):
            siz=Marble::small;
            break;
        case (2):
            siz=Marble::medium;
            break;
        case (3):
            siz=Marble::large;
            break;
        default:
            throw Marble::Bad_input();
        }
    }
    else { // if user put in text for their input
        if (siz_txt=="s" || siz_txt=="small") { siz=Marble::small; return is; }
        if (siz_txt=="m" || siz_txt=="medium") { siz=Marble::medium; return is; }
        if (siz_txt=="l" || siz_txt=="large") { siz=Marble::large; return is; }
        throw Marble::Bad_input();  // thrown if input is found to be bad, caller deals with it
    }
    return is;
}

//------------------------------------------------------------------------------
// Will have Color and Size input operator called
istream& operator>>(istream& is, Marble& m)
{
    char part_1;
    Marble::Color colo;
    Marble::Size sizz;
    is>>part_1;
    if (part_1=='(') { // simple syntax check as bad input is detected elsewhere
    	is>>colo>>sizz;
    }else
    {
    	is.putback(part_1);
    }
    is>>colo>>sizz;
    m.set_color(colo);
    m.set_size(sizz);
    return is;
}

//------------------------------------------------------------------------------

// Compare the elements of two marble objects
bool operator==(const Marble& m1, const Marble& m2)
{
    Marble::write_to_file(m1, m2); // write the traits of the marbles to a file
    //cout<<"Compare: "<<m1<<" vs "<<m2<<'\n';
    if (m1.get_size()!=m2.get_size()) return false;
    if (m1.get_color()!=m2.get_color()) return false;
    return true;
}





