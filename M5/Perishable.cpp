// TODO: add file header comments here
//Milestone 5
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/25/2019

#include <iostream>
#include <iomanip>

#include "Perishable.h"


using namespace std;

namespace ama{
	//A default constructor. calls one-parameter constructor
	//from the base, and pass 'P' for the record tag
	Perishable::Perishable() : Product('P'){}

	std::ostream& Perishable::write(std::ostream& os, int writeMode) const{
		//override for the write() function from the base class
		Product::write(os, writeMode);		
		
		//validates date
		if(date.isGood() && !isEmpty()){
			if(writeMode == write_human){
				//Write Human Formatting
				os << setw(max_length_label) << right << "Expiry Date: " << date << endl;
			}else if(writeMode == write_table){
				//Write Table Formatting					
				os << " " << date << " |";
			}else if(writeMode == write_condensed){
				//Write Condensed Formatting		
				os << "," << date;
			}
		}		
		return os;
	}
	
	std::istream& Perishable::read(std::istream& in, bool interractive){
        in.clear();
        //override for the read() function from the base class
		Product::read(in, interractive);
        
		//If bool is true/false function does or doesn't interact with the user 
        if(interractive){
			cout << setw(max_length_label) << right << "Expiry date (YYYY/MM/DD): ";						
			in >> date;
			if(date.status() != no_error){
				in.setstate(std::ios::failbit);
				if(date.status() == error_year){
					message("Invalid Year in Date Entry\n");
				}else if(date.status() == error_mon){
					message("Invalid Month in Date Entry\n");
				}else if(date.status() == error_day){
					message("Invalid Day in Date Entry\n");
				}else{	
					message("Invalid Date Entry\n");
				}
			}			
		}else{			
			date.read(in);
			in.ignore(2000,'\n');			
		}
		return in;
	}
}