// TODO: add file header comments here
//Milestone 1
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/06/2019

#include <iostream>
#include <cstring>

#include "Date.h"

using namespace std;

namespace ama{
	Date::Date(){
		//Safe Empty State
		year = 0;
		month = 0;
		day = 0;
		errorCodeStatus = no_error;
	}

	Date::Date(int years, int months, int days){
		//validates parameteres and stores the arguments in the attributes
		//along with setting the status to no_error.
		if(yearRange(years)){
			if(monthRange(months)){ 
				if(dayRange(years, months, days)){
					this->year = years;
					this->month = months;
					this->day = days;
					this->errorCodeStatus = no_error;
				}else{
				//If parameters are invalid, set the date object in a safe empty state
				//and set the status to a value that indicates which parameter was invalid
					*this = Date();
					this->errorCodeStatus = error_day;
				}
			}else{
				*this = Date();
				this->errorCodeStatus = error_mon;
			}
		}else{
			*this = Date();
			this->errorCodeStatus = error_year;
		}
	}

	// number of days in month. It was provided.
	int Date::mdays(int year, int mon) const{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::status(int newStatus){
		//sets the status to the value of the parameter.
		errorCodeStatus = newStatus;
	}

	int Date::status() const{
		//returns an integer representing the status of the current object
		return errorCodeStatus;
	}

	void Date::clearError(){
		//clears status of current value and sets it to no_error
		errorCodeStatus = no_error;
	}

	bool Date::yearRange(int years) const{ 
		//validates year is in range of restrictions
		return years >= min_year && years <= max_year;
	}

	bool Date::monthRange(int months) const{ 
		//validates month is in range of restrictions
		return months >= 1 && months <= 12;
	}

	bool Date::dayRange(int years, int months, int days) const{ 
		//validates day is in range of restrictions
		return days >= 1 && days <= mdays(years, months);
	}

	bool Date::isGood() const{
		//returns true/false if date is valid
		return (errorCodeStatus == no_error && yearRange(year) && this->monthRange(month) && this->dayRange(year, month, day));
	}

	bool Date::operator==(const Date& rhs) const{
		//returns true if two date objects match
		return (this->day == rhs.day && this->month == rhs.month && this->year == rhs.year);
	}

	bool Date::operator!=(const Date& rhs) const{
		//returns true if two date objects don't match
		return !(*this == rhs);
	}

	bool Date::operator<(const Date& rhs) const{
		//returns true/false if the current object's date is before the date stored in rhs
		bool laterDate = false;
		if(this->year < rhs.year){ 
			laterDate = true; 
		}else if(this->year == rhs.year){
			if(this->month < rhs.month){ 
				laterDate = true; 
			}else if(this->month == rhs.month){
				if(this->day < rhs.day){ 
					laterDate = true; 
				}
			}
		}
		return laterDate;
	}

	bool Date::operator>(const Date& rhs) const{
		//returns true/false if the current object's date is after the date stored in rhs
		return !(*this < rhs || *this == rhs);
	}

	bool Date::operator<=(const Date& rhs) const{
		//returns true/false if the current object's date is before or equal to the date stored in rhs
		return *this < rhs || *this == rhs;
	}

	bool Date::operator>=(const Date& rhs) const{
		//returns true/false if the current object's date is after or equal to the date stored in rhs
		return *this > rhs || *this == rhs;
	}

	Date& Date::operator+=(int days){
		int addDay = day + days;
		if(!isGood()){
			//if there's error, change to be this error mode
			status(error_invalid_operation);
		}else if(!dayRange(year, month, addDay) || addDay > mdays(year, month)){
			status(error_invalid_operation);
		}else{
			//new number os days will be added to day object
			day = addDay;
		}
		return *this; //return reference of object
	}

	Date& Date::operator++(){
		int addDay = day + 1;
		if(!isGood()){ 
			//if there's error, change to be this error mode
			status(error_invalid_operation);
		}else if(addDay > mdays(year, month)){ 
			//if day exceed the max day, change error status to be this
			status(error_invalid_operation);
		}else{
			//new day will be added to day object
			day = addDay;
		}
		return *this;	//return reference of object

	}

	Date& Date::operator++(int days){
		//current state of object
		Date* copyObj;
		copyObj = new Date();
		*copyObj = *this;
		days = day + 1;

		if(!isGood()){ 
			//if there's error, change to be this error mode
			status(error_invalid_operation);
		}else if(days > mdays(year, month)){ 
			//if day exceed the max day, change error status to be this
			status(error_invalid_operation);
		}else{ 
			//new day will be added to day object
			this->day = this->day + 1; 
		}
		return *copyObj; //return a copy of the instance before updated.
	}

	Date& Date::operator+(int days){
		//current state of object
		Date* tempDate;
		tempDate = new Date();
		*tempDate = *this;

		int addMoreDay = day + days;
		
		if(!isGood()){
			//if there's error, change to be this error mode
			tempDate->status(error_invalid_operation);
		}else if(addMoreDay > mdays(year, month)){
			//if day exceed the max day, change error status to be this
			tempDate->status(error_invalid_operation);
		}else{ 
			tempDate->day = addMoreDay; 
		}
		return *tempDate;
	}

	std::istream& Date::read(std::istream& is){
		char data;
		
		this->clearError();
		is.clear();

		is >> year >> data >> month >> data >> day;

		//validates year, month, day error checks
		if(is.fail()){
			*this = Date();
			status(error_input);
		}else if(!yearRange(year)){
			*this = Date();
			status(error_year);
		}else if(!monthRange(month)){
			*this = Date();
			status(error_mon);
		}else if(!dayRange(year, month, day)){
			*this = Date();
			status(error_day);
		}

		return is;
	}

	std::ostream& Date::write(std::ostream& os) const{
		char data = '/';
		
		os.width(4);
		os.fill('0');
		os << year << data; // year

		//validates if months less than 2 digits
		if(month < 10){
			//adds 0
			os << 0;
		}
		os << month << data;

		//validates if months less than 2 digits
		if(day < 10){
			//adds 0
			os << 0;
		}
		os << day;
		os.fill(' ');
		return os;
	}

	std::istream& operator>>(std::istream& is, Date& d){
		d.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& d){
		d.write(os);
		return os;
	}
}
