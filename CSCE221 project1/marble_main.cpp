/*  Jordan Donais UIN: 620003643
    August 31, 2011
    marble_main.cpp file with user interface and testing facilities
    Lab Project 2
*/

#include "marble.h"
#include <string>
#include <vector>
#include <sstream>
#include "vector_jar.h"
#include "llist_jar.h"
/*
int main()
{
    // vector used to make the loop "work"
    vector<Marble> m;
    m.push_back(Marble (Marble::yellow));
    cout<<"Marble"<<m[m.size()-1]<<" was created.\n";
    m.push_back(Marble (Marble::medium));
    cout<<"Marble"<<m[m.size()-1]<<" was created.\n";
    m.push_back(Marble (Marble::yellow, Marble::large));
    cout<<"Marble"<<m[m.size()-1]<<" was created.\n";
    m.push_back(Marble ());
    cout<<"Marble"<<m[m.size()-1]<<" was created.\n";
    // ugly global variables
    int more_marbles=2;
    int clear=1;
    string garbage_check="";
    Marble::Color user_color;
    Marble::Size user_size;
    Marble da_Marble;
    // keep bad input from being entered
    while (more_marbles!=0 && more_marbles!=1) {
    try {
    cout<<m.size()<<" marbles have already been made, would you like to make more?\n0 for no, 1 for yes.\n";
    getline(cin,garbage_check);
    stringstream convert(garbage_check);
    if ( !(convert >> more_marbles) || more_marbles<0 || more_marbles>1 ) throw Marble::Bad_input(); // exception class to be thrown
    } catch (Marble::Bad_input) { 
            cout<<"Invalid input, please try again.\n";
        }
    }
    // allows user to make as many marbles as they want
    while (more_marbles) {
        cout<<"Please make a new marble with the following format: (color, size)\nColor choices are red, blue, yellow, and green.\nSize choices are small, medium, and large.\n";
        while (clear) {
            try {
            cin>>da_Marble;
            clear = 0;
            } catch (Marble::Bad_input) { 
                cout<<"Invalid input, please try again.\n";
                getline(cin,garbage_check); 
            }
        }
        m.push_back(da_Marble);
        cout<<"Your input was: Marble"<<m[m.size()-1]<<'\n';
        getline(cin,garbage_check);
        more_marbles=2;
        while (more_marbles!=0 && more_marbles!=1) {
        try {
        cout<<m.size()<<" marbles have already been made, would you like to make more?\n0 for no, 1 for yes.\n";
        getline(cin,garbage_check);
        stringstream convert(garbage_check);
        clear = 1;
        if ( !(convert >> more_marbles) || more_marbles<0 || more_marbles>1 ) throw Marble::Bad_input();
        } catch (Marble::Bad_input) { 
                cout<<"Invalid input, please try again.\n";
            }
        }
    }
    // variables to control the following loops
    int compare = 1;
    int get_marble_1=0;
    int get_marble_2=0;
    if (more_marbles!=0) getline(cin,garbage_check);
    while (compare) { // compare is either 0 (false) or 1 (true)
        compare=2;
        // loop will only end when valid input is detected
        while (get_marble_1 < 1 || get_marble_1 > m.size()+1) {
            cout<<"Enter the first marble you would like to compare: 1, 2, 3, 4, etc....\n";
            // check for bad input such as a string and spaces
            getline(cin,garbage_check);
            stringstream convert(garbage_check);
            if ( !(convert >> get_marble_1) ) get_marble_1=m.size()+1;
            if (get_marble_1==m.size()+1) {
                cout<<"Invalid input, please try again.\n";
                get_marble_1=0;
            }
        }
        // vector starts at 0, but for user simplicity, options start at 1
        get_marble_1-=1;
        while (get_marble_2 < 1 || get_marble_2 > m.size()+1) {
            cout<<"Enter the second marble you would like to compare: 1, 2, 3, 4, etc....\n";
            getline(cin,garbage_check);
            stringstream convert(garbage_check);
            if ( !(convert >> get_marble_2) ) get_marble_2=m.size()+1;
            if (get_marble_2==m.size()+1) {
                cout<<"Invalid input, please try again.\n";
                get_marble_2=0;
            }
        }
        get_marble_2-=1;
        // compare the two marbles
        if (m[get_marble_1]==m[get_marble_2]) {
            cout<<"The two marbles were equal. \n";
        }
        else {
            cout<<"The two marbles were not equal. \n";
        }
        // as requested in section 3 part 2
        while (compare!=0 && compare!=1) {
            cout<<"Do you wish to continue? 0 for no, 1 for yes.\n";
            getline(cin,garbage_check);
            stringstream convert(garbage_check);
            if ( !(convert >> compare) ) {
                cout<<"Invalid input, please try again.\n";
                compare=2;
            }
        }
        // reset values
        get_marble_1=0;
        get_marble_2=0;
    }

};

*/
