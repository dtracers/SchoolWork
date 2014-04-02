#ifndef GLOBAL_METHODS_CPP_
#define GLOBAL_METHODS_CPP_
#include"global_parsing_methods.h"
#include<sstream>
#include<iostream>
namespace globalParse {
/**
 * This will get the parts of a string separated by the above and put it into a vector<string>
 */
vector<string> get_separate_statments(string statement, string separator) {
//		cerr<<"the in string is "<<statement<<endl;
	vector<string> sepa;
	int pos = 0;
	int final_index;
	while (pos >= 0 && pos < statement.length()) {
		final_index = pos;
		int next = statement.find(separator, pos);
//			cerr<<"The next next is "<<next<<endl;
		if (next > 0 && pos < statement.length()) {
			string data = statement.substr(pos, next - pos);
//				cerr<<"The part is "<<data<<endl;
			//	data_types_and_their_name(data,table);
			sepa.push_back(data);
			pos = next + 1;
		} else {
			pos = -1;
		}
	}
	if (final_index < statement.length()) {

		string data = statement.substr(final_index,
				statement.length() - final_index);
//			cerr<<"The FINAL part is "<<data<<endl;
		sepa.push_back(data);
	}
	return sepa;
}

/**
 * This will remove all spaces outside of the string
 * but it has to be one word!
 */
string trim(string in) {
	stringstream stream(in);
	stream >> in;
	return in;
}
}
#endif
