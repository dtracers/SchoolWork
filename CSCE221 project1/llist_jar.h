#include "jar.h"
#include <list>

class llist_jar : public jar {
    public: // functions
        void add(const Marble& m);
        bool is_in_jar(const Marble& m);
        void remove(const Marble& m);
        Marble::Marble remove_any();
        void clear();
        int marble_number() const;
        int marble_nsize(Marble::Size s) const;
        int marble_ncolor(Marble::Color c) const;
        bool is_empty() const;
        void copy_jar(const jar& jar);
        void merge(const jar& jar1, const jar& jar2);
        void intersect(const jar& jar1, const jar& jar2);
        void difference(const jar& jar1, const jar& jar2);
        //list<Marble::Marble>::iterator return_the_marble(const Marble& m);
        Marble::Marble get_marble(int i) const;
        bool do_match(const jar& jar1, const jar& jar2, int k);
    private:
        list<Marble::Marble> my_marbles;
};
