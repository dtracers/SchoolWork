#include "Time.h"
#include <sstream>

Time::Time(int hr, int min, int sec){
	if(!isTime(hr, min, sec))
		throw DatabaseException(41, hr + ':' + min + ':' + sec + " is not a valid time.");

	hour = hr;
	minute = min;
	second = sec;
}

Time::~Time()
{

}

string Time::toString(){
	stringstream h;
	h << getHours();
	stringstream m;
	m << getMinutes();
	stringstream s;
	s << getSeconds();
	
	string output = "";
	output += h.str();
	output += ':';
	output += m.str();
	output += ':';
	output += s.str();
	return output;
}

//Checks if the hour, minutes, and seconds are valid
bool isTime(int hour, int minute, int second){
	if ((hour > 0 && hour < 24) && (minute > 0 && minute < 60) && (second > 0 && second < 60)){
		return true;
	}
	else{
		return false;
	}	
}

//Operator overloads for ==, !=, <, >, <=, >=, <<, >>
bool operator==(const Time& time1, const Time& time2){
	if( (time1.getHours() == time2.getHours()) 
		&& (time1.getMinutes() == time2.getMinutes()) 
		&& (time1.getSeconds() == time2.getSeconds()) ){
		return true;
	}
	else{
		return false;
	}
}

bool operator!=(const Time& time1, const Time& time2){
	return !(time1==time2);
}

bool operator<(Time& time1, Time& time2){
	int hour1=time1.getHours();
	int minute1=time1.getMinutes();
	int second1=time1.getSeconds();
	int hour2=time2.getHours();
	int minute2=time2.getMinutes();
	int second2=time2.getSeconds();
	
	if(hour1<hour2){
		return true;
	}
	else if(hour1>hour2){
		return false;
	}
	else if(minute1<minute2){
		return true;
	}
	else if(minute1>minute2){
		return false;
	}
	else if(second1<second2){
		return true;
	}
	else if(second1>second2){
		return false;
	}
	else{
		return false;
	}
}

bool operator>(Time& time1, Time& time2){
	int hour1=time1.getHours();
	int minute1=time1.getMinutes();
	int second1=time1.getSeconds();
	int hour2=time2.getHours();
	int minute2=time2.getMinutes();
	int second2=time2.getSeconds();
	
	if(hour1>hour2){
		return true;
	}
	else if(hour1<hour2){
		return false;
	}
	else if(minute1>minute2){
		return true;
	}
	else if(minute1<minute2){
		return false;
	}
	else if(second1>second2){
		return true;
	}
	else if(second1<second2){
		return false;
	}
	else{
		return false;
	}
}

bool operator<=(Time& time1, Time& time2){
	if( (time1 < time2) || (time1 == time2) ){
		return true;
	}
	else{
		return false;
	}
}

bool operator>=(Time& time1, Time& time2){
	if( (time1 > time2) || (time1 == time2) ){
		return true;
	}
	else{
		return false;
	}
}

ostream& operator<<(ostream& os, Time& time){
	return os<<time.getHours()<<":"<<time.getMinutes()<<":"<<time.getSeconds();
}

istream& operator>>(istream & is, Time& t){
	int h;
	int m;
	int s;
	char ch1, ch2;
	is >> h >> ch1 >> m >> ch2 >> s;
	if(!is)return is;
	if(ch1!=':' || ch2!=':'){
		is.clear(ios_base::failbit);
		return is;
	}
	t = Time(h,m,s);
	return is;
}
