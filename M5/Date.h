// TODO: add file header comments here
//Milestone 1
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/06/2019

#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace ama {
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;
	const int min_year = 2019; //minimum year acceptable for a valid date
	const int max_year = 2028; //maximum year acceptable for a valid date

	class Date {
		int year; //a four digit int between min_year and max_year
		int month; //a value between 1 and 12 inclusive
		int day; //a value between 1 and number of days in a month
		int errorCodeStatus; //Error code which identifies the validation of the date

		void status(int newStatus);
		int mdays(int year, int month) const;
		bool yearRange(int) const; //validates year restrictions
		bool monthRange(int) const; //validates month restrictions
		bool dayRange(int, int, int) const; //validates day restrictions
		
	public:
    //sets to safe empty sate
		Date();
    //recieves parameters, validates them, stores private variable's values into them
		Date(int, int, int);

    //returns status of error object
		int status() const;
    //clears error object's value
		void clearError();
    //returns true/fase if date is valid
		bool isGood() const;

    //operators validating if date value matches/doesnt match rhs
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

    //validates values and adds newDay to day object
		Date& operator+=(int days);
		Date& operator++();
		Date& operator++(int);
		Date& operator+(int days);

		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;
	};

	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);
}

#endif