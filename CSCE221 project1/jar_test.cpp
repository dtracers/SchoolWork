#include "marble.h"
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include "vector_jar.h"
#include "llist_jar.h"
#include <iostream>

jar::jar& fill_the_jar(jar::jar& da_jar) {
    for (int i=0; i<4; i++) {
        Marble* m=new Marble();
        da_jar.add(*m);
    }
    return da_jar;
}

void print_jar(jar::jar& da_jar) {
    for (int i=0; i<da_jar.marble_number(); i++) {
        cout<<"Marble: Color = "<<da_jar.get_marble(i)<<endl;
    }
    cout<<"End of jar\n";
}
jar::jar& fill_the_jar(jar::jar& da_jar,istream& in) {
	cout<<"do you want to add at marble (Y/N)"<<endl;
	string in2;
	in>>in2;
	while(in2=="Y"){
		cout<<"enter marble"<<endl;
		Marble m;
		in>>m;
		da_jar.add(m);
		cout<<"do you want to add at marble (Y/N)"<<endl;
		in>>in2;
	}
    return da_jar;
}
jar::jar& do_stuff(int method,int type,jar::jar& m1,jar::jar&m2) {
	jar::jar* da_jar;
	if(type==0)
	{
		da_jar=new vector_jar();
	}
	if(type==1)
	{
		da_jar=new llist_jar();
	}
	jar::jar& da_jar_2=*da_jar;
	switch(method)
	{
		case 0:cout<<"merging\n";da_jar_2.merge(m1,m2);break;
		case 1:cout<<"intersect\n";da_jar_2.intersect(m1,m2);break;
		case 2:cout<<"difference\n";da_jar_2.difference(m1,m2);break;
	}
    return da_jar_2;
}
/*
int main() {
	srand(time(0));
    vector_jar jar1;
    llist_jar jar2;
    fill_the_jar(jar1);
    fill_the_jar(jar2);
    print_jar(jar1);
    print_jar(jar2);
    fill_the_jar(jar1,cin);
    print_jar(jar1);
    fill_the_jar(jar2,cin);
    print_jar(jar2);
    for(int k=0;k<3;k++)
    {
    	for(int q=0;q<2;q++)
    	{
    		jar& jar_temp=do_stuff(k,q,jar1,jar2);
    		print_jar(jar_temp);
    	}
    }
}
*/
