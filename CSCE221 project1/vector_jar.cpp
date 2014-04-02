#include "vector_jar.h"
#include <iostream>
#include <time.h>

using namespace std;

void vector_jar::add(const Marble& m) {
    vector_jar::my_marbles.push_back(m);
}

//------------------------------------------------------------------------------

bool vector_jar::is_in_jar(const Marble& m) {
    for (int i=0; i<vector_jar::my_marbles.size(); i++)
        if (vector_jar::my_marbles[i]==m) 
            return true;
    return false;
}

//------------------------------------------------------------------------------

/*int vector_jar::return_same_marble(const Marble& m) {
    for (int i=0; i<vector_jar::my_marbles.size()-1; i++) 
        if (vector_jar::my_marbles[i]==m) 
            return i;
    return 0;
}*/

//------------------------------------------------------------------------------

void vector_jar::remove(const Marble& m) {
    for (int i=0; i<vector_jar::my_marbles.size(); i++) {
        if (vector_jar::my_marbles[i]==m) {
            vector_jar::my_marbles.erase(vector_jar::my_marbles.begin()+i);
        }
    }
    //vector_jar::my_marbles.erase(vector_jar::my_marbles.begin()+vector_jar::return_same_marble(m));
}

//------------------------------------------------------------------------------

Marble::Marble vector_jar::get_marble(int i) const {
    return vector_jar::my_marbles[i];
}

//------------------------------------------------------------------------------

Marble::Marble vector_jar::remove_any() {
   // srand(time(NULL));
	int r_marble = (rand()%vector_jar::marble_number());
	Marble m=vector_jar::get_marble(r_marble);
    vector_jar::my_marbles.erase(vector_jar::my_marbles.begin()+(r_marble));
    return m;
}

//------------------------------------------------------------------------------

void vector_jar::clear() {
    vector_jar::my_marbles.clear();
}

//------------------------------------------------------------------------------

int vector_jar::marble_number() const {
    return vector_jar::my_marbles.size();
}

//------------------------------------------------------------------------------

int vector_jar::marble_nsize(Marble::Size s) const {
    int count=0;
    for (int i=0; i<vector_jar::my_marbles.size(); i++)
        if (vector_jar::my_marbles[i].get_size()==s) 
            count++;
    return count;
}

//------------------------------------------------------------------------------

int vector_jar::marble_ncolor(Marble::Color c) const {
    int count=0;
    for (int i=0; i<vector_jar::my_marbles.size(); i++)
        if (vector_jar::my_marbles[i].get_color()==c) 
            count++;
    return count;
}

//------------------------------------------------------------------------------

bool vector_jar::is_empty() const {
    if (vector_jar::my_marbles.size()==0) 
        return true;
    return false;
}

//------------------------------------------------------------------------------

bool vector_jar::do_match(const jar& jar1, const jar& jar2, int k) {
        for (int j=0; j<jar2.marble_number(); j++) {
            if (jar1.get_marble(k)==jar2.get_marble(j)) {
                return true;
            }
        }
    return false;
}

//------------------------------------------------------------------------------
        
void vector_jar::copy_jar(const jar& jar) {
    vector_jar::clear();
    for (int i=0; i<jar.marble_number(); i++)
        vector_jar::my_marbles.push_back(jar.get_marble(i));
    /*while(!is_empty()) {
        remove_any();
    }
    vector_jar::merge(this, jar);*/
}

//------------------------------------------------------------------------------

void vector_jar::merge(const jar& jar1, const jar& jar2) {
    vector_jar::clear();
    for (int i=0; i<jar1.marble_number(); i++)
        vector_jar::my_marbles.push_back(jar1.get_marble(i));
    for (int i = 0; i < jar2.marble_number(); i++)
        vector_jar::my_marbles.push_back(jar2.get_marble(i));
}

//------------------------------------------------------------------------------

void vector_jar::intersect(const jar& jar1, const jar& jar2) {
    vector_jar::clear();
    /*for (int i=0; i<jar1.marble_number()-1; i++) {
        for (int j=0; j<jar2.marble_number()-1; j++) {
            if (jar1.get_marble(i)==jar2.get_marble(j)) {
                vector_jar::my_marbles.push_back(jar1.get_marble(i));
                j=jar2.marble_number()+1;
            }
        }
    } */
    for (int i=0; i<jar1.marble_number(); i++) {
        if (vector_jar::do_match(jar1, jar2, i))
            vector_jar::my_marbles.push_back(jar1.get_marble(i));
    } 
}

//------------------------------------------------------------------------------

void vector_jar::difference(const jar& jar1, const jar& jar2) {
    vector_jar::clear();
    //vector<bool> matching;
    /* for (int i=0; i<jar1.marble_number()-1; i++) {
        for (int j=0; j<jar2.marble_number()-1; j++) {
            if (!(jar1.get_marble(i)==jar2.get_marble(j))) {
                matching.push_back(true);
            }
            else matching.push_back(false);
        }
    } */
    for (int i=0; i<jar1.marble_number(); i++) {
        if (!(vector_jar::do_match(jar1, jar2, i)))
            vector_jar::my_marbles.push_back(jar1.get_marble(i));
    } 
}

//------------------------------------------------------------------------------
