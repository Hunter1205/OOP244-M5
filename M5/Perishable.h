// TODO: add file header comments here
//Milestone 5
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/25/2019

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include <iostream>

#include "Product.h"
#include "Date.h"
#include "ErrorState.h"

namespace ama{
	class Perishable : public Product{
		Date date; //store the expiry date for a perishable product
	public:
		//A default constructor. calls one-parameter constructor 
		//from the base, and pass 'P' for the record tag
		Perishable();
		//override for the read() function from the base class
		std::istream& read(std::istream& in, bool interractive);
		//override for the write() function from the base class
		std::ostream& write(std::ostream& os, int writeMode) const;
	};
}
#endif