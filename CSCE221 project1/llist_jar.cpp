#include "llist_jar.h"
#include <iostream>
#include <time.h>
#include <list>

using namespace std;

void llist_jar::add(const Marble& m) {
    llist_jar::my_marbles.push_back(m);
}

//------------------------------------------------------------------------------

bool llist_jar::is_in_jar(const Marble& m) {
    list<Marble::Marble>::iterator it;
    for (it=llist_jar::my_marbles.begin(); it!=llist_jar::my_marbles.end(); it++)
        if (*it==m)
            return true;
    return false;
}

//------------------------------------------------------------------------------

void llist_jar::remove(const Marble& m) {
    llist_jar::my_marbles.remove(m);
}

//------------------------------------------------------------------------------

Marble::Marble llist_jar::get_marble(int i) const {
    list<Marble::Marble>::const_iterator jj;
    jj=llist_jar::my_marbles.begin();
    for(int k=0;k<i;k++)
    {
    	jj++;
    }
    return *jj;
    //return llist_jar::my_marbles.begin()+i;
  //  return -1;
}

//------------------------------------------------------------------------------

Marble::Marble llist_jar::remove_any() {
//    srand(time(NULL));
    int r_marble = (rand()%llist_jar::my_marbles.size());
    Marble m=llist_jar::get_marble(r_marble);
    llist_jar::my_marbles.remove(m);
    return m;
}

//------------------------------------------------------------------------------

void llist_jar::clear() {
    llist_jar::my_marbles.clear();
}

//------------------------------------------------------------------------------

int llist_jar::marble_number() const {
    return llist_jar::my_marbles.size();
}

//------------------------------------------------------------------------------

int llist_jar::marble_nsize(Marble::Size s) const {
    int count=0;
    Marble::Marble temp_marble;
    for (int i=0; i<llist_jar::my_marbles.size(); i++) {
        temp_marble=llist_jar::get_marble(i);
        if (temp_marble.get_size()==s) {
            count++;
        }
    }
    return count;
}

//------------------------------------------------------------------------------

int llist_jar::marble_ncolor(Marble::Color c) const {
    int count=0;
    Marble::Marble temp_marble;
    for (int i=0; i<llist_jar::my_marbles.size(); i++) {
        temp_marble=llist_jar::get_marble(i);
        if (temp_marble.get_color()==c) {
            count++;
        }
    }
    return count;
}

//------------------------------------------------------------------------------

bool llist_jar::is_empty() const {
    if (llist_jar::my_marbles.size()==0) 
        return true;
    return false;
}

//------------------------------------------------------------------------------

bool llist_jar::do_match(const jar& jar1, const jar& jar2, int k) {
        for (int j=0; j<jar2.marble_number(); j++) {
            if (jar1.get_marble(k)==jar2.get_marble(j)) {
                return true;
            }
        }
    return false;
}

//------------------------------------------------------------------------------
        
void llist_jar::copy_jar(const jar& jar) {
    llist_jar::clear();
    for (int i=0; i<jar.marble_number()-1; i++)
        llist_jar::my_marbles.push_back(jar.get_marble(i));
}

//------------------------------------------------------------------------------

void llist_jar::merge(const jar& jar1, const jar& jar2) {
    llist_jar::clear();
    for (int i=0; i<jar1.marble_number(); i++)
        llist_jar::my_marbles.push_back(jar1.get_marble(i));
    for (int i = 0; i < jar2.marble_number(); i++)
        llist_jar::my_marbles.push_back(jar2.get_marble(i));
}

//------------------------------------------------------------------------------

void llist_jar::intersect(const jar& jar1, const jar& jar2) {
    llist_jar::clear();
    for (int i=0; i<jar1.marble_number(); i++) {
        if (llist_jar::do_match(jar1, jar2, i))
            llist_jar::my_marbles.push_back(jar1.get_marble(i));
    } 
}

//------------------------------------------------------------------------------

void llist_jar::difference(const jar& jar1, const jar& jar2) {
    llist_jar::clear();
    for (int i=0; i<jar1.marble_number(); i++) {
        if (!(llist_jar::do_match(jar1, jar2, i)))
            llist_jar::my_marbles.push_back(jar1.get_marble(i));
    } 
}

//------------------------------------------------------------------------------
