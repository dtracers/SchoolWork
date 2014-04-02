/*  Jordan Donais UIN: 620003643
    August 31, 2011
    marble.h file with declarations 
    Lab Project 2
*/  

#ifndef MARBLE_H_ 
#define MARBLE_H_
#include <iostream> 
#include <sstream>
using namespace std;
          class Marble { 

	        public: 

	             class Bad_input {}; // exception class
	             enum Color {red, blue, yellow, green}; 
	             enum Size {small, medium, large}; 
	             static void write_to_file(const Marble& m1, const Marble& m2); // handles file writing
          	private: 

             		Color color; 
             		Size size; 

            		 // internal functions 

             		Color random_color(); 
             		Size random_size(); 
          	public: 

             		// constructors 
             		// write 4 constructors here: 
             		Marble(); // -- random color and size 
		            Marble(Color c); // -- given color, random size 
			        Marble(Size s); // -- random color, given size 
             		Marble(Color c, Size s); // -- given color and size 

             		Color get_color() const;   
             		Size get_size() const;
                    string get_color_text() const;
                    string get_size_text() const; 
             		void set_color(Color c);
             		void set_size(Size s);

};

	// helper functions
	bool operator==(const Marble& m1, const Marble& m2);      
	ostream& operator<<(ostream& os, const Marble& m); 
	istream& operator>>(istream& is, Marble& m);
	istream& operator>>(istream& is, Marble::Color& col);
	istream& operator>>(istream& is, Marble::Size& siz);
	#endif // end of the file marble.h  

