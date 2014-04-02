#include "Column.h"

//Column constructor- checks validity of type given
Column::Column(string type)
{
	varcharMaxLength = 100;
	isPrimary = false;
	
	if(type =="int" || type == "float" || type == "date" || type == "time"){
		colType = type;
	}
	else{
		string number = "";
		int newLength;
		colType = "varchar";
		for (int i = 0; i < type.length(); i++) {
			if(type[i] == '('){
				i++;
				while(type[i] != ')'){
					number += type[i];
					i++;
				}
				break;
			}
		}

		if( (number.size() > 0) && (type.compare(0,7,"varchar") == 0) ){
			newLength =  atoi(number.c_str());
		
			if(newLength <= 0){
				throw DatabaseException(31);
			}
			else if(newLength > varcharMaxLength){
				throw DatabaseException(32);
			}
			else{
				varcharMaxLength = newLength;
			}
		}
		else{
			throw DatabaseException(30);
		}		
	}
}

Column::~Column()
{

}

//Checks if the given value is valid
bool Column::valExists(string val) {
	const char * valC = val.c_str();

	if(colType == "int") {

		//atoi returns 0 if not successful
		int intVal = 0;
		if(atoi(valC) != 0) {
			intVal = atoi(valC);
		} else {
			throw DatabaseException(33, val + " not a valid integer.");
		}

		for(int i = 0; i < intList.size(); i++) {
			if(intList[i] == intVal) {

				return true;
			}
		}
	}
	else if(colType == "float") {
		//atoi returns 0.0 if not successful
		float floatVal = 0.0;
		
		if(atof(valC) != 0.0) {
			floatVal = atof(valC);
		} else {
			throw DatabaseException(34, val + " not a valid float.");
		}

		for(int i = 0; i < floatList.size(); i++) {
			if(floatList[i] == floatVal) {

				return true;
			}
		}
	}
	else if(colType == "varchar") {
		if(val.size() > varcharMaxLength) {
			throw DatabaseException(35, val.size() + " is greater than " + varcharMaxLength + '.');
		}

		for(int i = 0; i < varcharList.size(); i++) {
			if(varcharList[i].compare(val) == 0) {

				return true;
			}
		}
	}
	else if(colType == "date") {
		//Allowed format: mm/dd/yyyy

		if(val.size() != 10 || !isdigit(val[0]) ||
			!isdigit(val[1]) || !isdigit(val[2]) || !isdigit(val[3]) || val[4] != '/' ||
			!isdigit(val[5]) || !isdigit(val[6]) || val[7] != '/' || !isdigit(val[8]) ||
			!isdigit(val[9])) {
			throw DatabaseException(40, val + " is not a valid date. Accepted format is YYYY/MM/DD.");
		}

		int year = atoi(val.substr(0, 4).c_str());
		int month = atoi(val.substr(5, 2).c_str());
		int day = atoi(val.substr(8, 2).c_str());

		Date * newDate = new Date(year, month, day);

		for(int i = 0; i < dateList.size(); i++) {
			if(dateList[i] == newDate) {

				delete newDate;
				return true;
			}
		}

	}
	else if(colType == "time") {

		if(val.size() != 8 || !isdigit(val[0]) || !isdigit(val[1]) || val[2] != ':' ||
			!isdigit(val[3]) || !isdigit(val[4]) || val[5] != ':' || !isdigit(val[6]) ||
			!isdigit(val[7])) {
			throw DatabaseException(41, val + " is not a valid time. Accepted format is HH:MM:SS.");
		}

		int hr = atoi(val.substr(0, 4).c_str());
		int min = atoi(val.substr(5, 2).c_str());
		int sec = atoi(val.substr(8, 2).c_str());

		Time * newTime = new Time(hr, min, sec);

		for(int i = 0; i < timeList.size(); i++) {
			if(timeList[i] == newTime) {

				delete newTime;
				return true;
			}
		}
	}

	return false;
}

//Add a row to the table
void Column::addRow(string val) {

	const char * valC = val.c_str();

	if(colType == "int") {

		//atoi returns 0 if not successful
		if(val.compare("0") == 0) {
			intList.push_back(0);
		} else if(atoi(valC) != 0) {
			intList.push_back(atoi(valC));
		} else {
			throw DatabaseException(33, val + " not a valid integer.");
		}
	}
	else if(colType == "float") {
		//atoi returns 0.0 if not successful
		if(val.compare("0.0") == 0.0) {
			floatList.push_back(0.0);
		} else if(atof(valC) != 0.0) {
			floatList.push_back(atof(valC));
		} else {
			throw DatabaseException(34, val + " not a valid float.");
		}
	}
	else if(colType == "varchar") {
		if(val.size() > varcharMaxLength) {
			throw DatabaseException(35, val.size() + " is greater than " + varcharMaxLength + '.');
		}

		varcharList.push_back(val);
	}
	else if(colType == "date") {
		//Allowed format: mm/dd/yyyy

		if(val.size() != 10 || !isdigit(val[0]) ||
			!isdigit(val[1]) || !isdigit(val[2]) || !isdigit(val[3]) || val[4] != '/' ||
			!isdigit(val[5]) || !isdigit(val[6]) || val[7] != '/' || !isdigit(val[8]) ||
			!isdigit(val[9])) {
			throw DatabaseException(40, val + " is not a valid date. Accepted format is YYYY/MM/DD.");
		}

		int year = atoi(val.substr(0, 4).c_str());
		int month = atoi(val.substr(5, 2).c_str());
		int day = atoi(val.substr(8, 2).c_str());

		dateList.push_back(new Date(year, month, day));
	}
	else if(colType == "time") {

		if(val.size() != 8 || !isdigit(val[0]) || !isdigit(val[1]) || val[2] != ':' ||
			!isdigit(val[3]) || !isdigit(val[4]) || val[5] != ':' || !isdigit(val[6]) ||
			!isdigit(val[7])) {
			throw DatabaseException(41, val + " is not a valid time. Accepted format is HH:MM:SS.");
		}

		int hr = atoi(val.substr(0, 2).c_str());
		int min = atoi(val.substr(3, 2).c_str());
		int sec = atoi(val.substr(6, 2).c_str());
		timeList.push_back(new Time(hr, min, sec));
	}

	//delete valC;
}

//print the data in a column
string Column::printDataList(){
	string s = "";
	ostringstream stringForConversion; 
	
	if(colType == "int") {
		for(int i = 0; i < intList.size(); i++){
			stringForConversion.str("");
			stringForConversion << intList[i];
			s += ", " + stringForConversion.str();
		}
	}
	else if(colType == "float") {
		for(int i = 0; i < floatList.size(); i++){
			stringForConversion.str("");
			stringForConversion << floatList[i];
			s += ", " + stringForConversion.str();
		}
	}
	else if(colType == "varchar") {
		for(int i = 0; i < varcharList.size(); i++){
			stringForConversion.str("");
			stringForConversion << varcharList[i];
			s += ", " + stringForConversion.str();
		}
	}
	else if(colType == "date") {
		for(int i = 0; i < dateList.size(); i++){
			stringForConversion.str("");
			stringForConversion << dateList[i];
			s += ", " + stringForConversion.str();
		}
	}
	else if(colType == "time") {
		for(int i = 0; i < timeList.size(); i++){
			stringForConversion.str("");
			stringForConversion << timeList[i];
			s += ", " + stringForConversion.str();
		}
	}
	return s;
}

//Count number of rows in table
int Column::rowCount() {
	if(colType == "int") {
		return intList.size();
	}
	else if(colType == "float") {
		return floatList.size();
	}
	else if(colType == "varchar") {
		return varcharList.size();
	}
	else if(colType == "date") {
		return dateList.size();
	}
	else if(colType == "time") {
		return timeList.size();
	}
	return -1;
}


string Column::getValueAtRowIndex(int rowIndex) {
	if(rowIndex > rowCount()) {
		throw DatabaseException(23, rowIndex + " is greater than " + rowCount() + '.');
	} else if(rowIndex < 0) {
		throw DatabaseException(23, rowIndex + " must be greater than 0.");
	}

	if(colType == "int") {
		stringstream ss;
		ss << intList[rowIndex];
		return ss.str();
	}
	else if(colType == "float") {
		stringstream ss;
		ss << floatList[rowIndex];
		return ss.str();
	}
	else if(colType == "varchar") {
		return varcharList[rowIndex];
	}
	else if(colType == "date") {
		return dateList[rowIndex]->toString();
	}
	else if(colType == "time") {
		return timeList[rowIndex]->toString();
	}
	return "";
}
