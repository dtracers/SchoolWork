#include "marble.h"
#include <list>
#ifndef JAR_H_ 
#define JAR_H_
class jar {
    public: // functions
        virtual void add(const Marble& m)=0;
        virtual bool is_in_jar(const Marble& m)=0;
        virtual void remove(const Marble& m)=0;
        virtual Marble::Marble remove_any()=0;
        virtual void clear()=0;
        virtual int marble_number() const=0;
        virtual int marble_nsize(Marble::Size s) const=0;
        virtual int marble_ncolor(Marble::Color c) const=0;
        virtual bool is_empty() const=0;
        virtual void copy_jar(const jar& jar)=0;
        virtual void merge(const jar& jar1, const jar& jar2)=0;
        virtual void intersect(const jar& jar1, const jar& jar2)=0;
        virtual void difference(const jar& jar1, const jar& jar2)=0;
        //virtual int return_same_marble(const Marble& m)=0;
        virtual Marble::Marble get_marble(int i) const=0;
        virtual bool do_match(const jar& jar1, const jar& jar2, int k)=0;
        //-------
};

    #endif
