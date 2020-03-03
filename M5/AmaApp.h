// TODO: add file header comments here
//Milestone 5
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/25/2019

#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H

#include "iProduct.h"
#include "Utilities.h"

namespace ama{
	class AmaApp{
        char m_filename[256]; //Holds the name of the text file used to store the product information
        iProduct* m_products[100]; //array of iProduct pointers
        int m_noOfProducts; //Number of products (perishable or non perishable)

        //Waits for user to hit Enter, ignores other keys pressed
        void pause() const;
        //displays the option menu, waits for the user to select an option
        int menu() const;
        //If file exits, Opens the data file for reading
        //If file doesnt exits, creates and closes empty file
        void loadProductRecords();
        //Loops through the m_products array
        //up to m_noOfProducts and stores each of them in a file
        void saveProductRecords() const;
        //Prints title, loops through the m_products array up to m_noOfProducts
        //prints a bar, and list of Product information
        void listProducts() const;
        //Updates the quantity on hand for iProduct
        void addQty(iProduct* product);
        //adds a new product at the end of the array
        void addProduct(char tag);
        //Loops through the m_products 
        //array up to m_noOfProducts and checks each of them for
        //the same SKU as the incoming argument
        iProduct* find(const char* sku) const;

    public:
        //Custom Constructor
        AmaApp(const char*);
        //Deconstructor
        ~AmaApp();
        //Display the menu, receive the user’s selection
        //does the action requested
        int run();
	};
}
#endif