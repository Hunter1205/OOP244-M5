// TODO: add file header comments here
//Milestone 5
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/25/2019

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "AmaApp.h"

using namespace std;

namespace ama{
	// custom constructor that sets the members to a safe empty state, copies the filename, and loads the records from the file.
	AmaApp::AmaApp(const char* file){	
		//Custom Constructor
		strcpy(m_filename, file);
		for(int i = 0; i < 99; i++){
			m_products[i] = nullptr;
		}
		m_noOfProducts = 0;
		loadProductRecords();	
	}

	AmaApp::~AmaApp(){
		//deallocates all dynamic instances stored in the m_products array
		for(int i = 0; i < 99; i++){
			delete m_products[i];
			m_products[i] = nullptr;
		}
	}


	void AmaApp::pause() const{
		//Waits for user to hit Enter
		cout << "Press Enter to continue...";
		cout << endl;
		cin.ignore(2000,'\n');
	}

	int AmaApp::menu() const{
		int option;
        //displays the option menu, and waits for the user to select an option
        cout << "Disaster Aid Supply Management Program" << endl;
        cout << "--------------------------------------" << endl;
        cout << "1- List products" << endl;
        cout << "2- Search product" << endl;
        cout << "3- Add non-perishable product" << endl;
        cout << "4- Add perishable product" << endl;
        cout << "5- Add to product quantity" << endl;
        cout << "6- Delete product" << endl;
        cout << "7- Sort products" << endl;
        cout << "0- Exit program" << endl;
        cout << "> ";
        cin >> option;
        cin.ignore(2000,'\n');

        if(option >= 0 && option <= 7){
			return option;
		}else{
			return -1;
		}
	}

	void AmaApp::loadProductRecords(){
		int index = 0; //set reading index to zero
		char tag;

		for(int i = 0; i < 100; i++){
			//delete all products from the array (if any)
			if(m_products[i] != nullptr){
				delete m_products[i];
			}
		}
		//Open the file for reading
		fstream input(m_filename, ios::in);

		//if the file is open
		if(input){		
			do{
				//read one char character to identify type of Product
				input >> tag;
				if(input){
					//creates an instance		
					iProduct* prod = createInstance(tag);

					if(prod != nullptr){
						//store the product in the array at the read index					
						m_products[index] = prod;				
						//skip the comma
						input.get();
						//read the product from the file (non-interractive mode)				
						prod->read(input, false);	
						//increment the read index					
						index++;
					}
				}
			}while(input); //until reading fails loop
			m_noOfProducts = index;			
			input.close();
		}else{
			//if no file, creates and closes empty file
			fstream fout(m_filename, ios::out);
			fout.close();
		}
	}

	void AmaApp::saveProductRecords() const{
		ofstream output(m_filename, ios::out);
		if(output){
            //Loops through the m_products array up to m_noOfProducts
			for(int i = 0; i < m_noOfProducts; i++){
				if(m_products[i] != nullptr){
                    //stores each of them in file
				    m_products[i]->write(output, write_condensed);
                    //after each record, adds end line into the file
					output << endl;
                }
			}
		}
		output.close();
	}

	void AmaApp::listProducts() const{
		double total = 0;
		
        cout << "------------------------------------------------------------------------------------------------" << endl
			<< "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl
			<< "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
		
		//loops through the m_products array up to m_noOfProducts
        for(int i = 0; i < m_noOfProducts; i++){
			if(m_products[i] != nullptr){	
				cout << "|";
				cout.width(4);
				cout << i + 1 << " |";
				//inserts content of current product, calls iProduct::write()
				m_products[i]->write(cout, write_table);
				cout << endl;
				//calculates the total cost of the products in a double value using the operator +=
				total += *m_products[i];
			}
		}

        //Prints total cost of Product
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|";
		cout.width(82);
		cout << "Total cost of support ($): |";
		cout.width(11);
		cout.setf(ios::right);
		cout.precision(2);
		cout << total << " |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;		
	}

	void AmaApp::addQty(iProduct* product){
		int num;
		product->write(cout, write_human);
		cout << endl << endl << "Please enter the number of purchased items: ";
		cin >> num;
		if(!cin.fail()){
			//validates amount is less or equal than the amount required
            if(num <= (product->qtyNeeded() - product->qtyAvailable())){
                //Updates the quantity on hand for an iProduct
				*product += num;
				saveProductRecords();
			}else{
				//returns message if amount is less or equal than the amount required
				cout << "Too many items; only " << (product->qtyNeeded() - product->qtyAvailable()) << " is needed. Please return the extra " << (num - (product->qtyNeeded() - product->qtyAvailable())) << " items." << endl;
				*product += (product->qtyNeeded() - product->qtyAvailable());
			}
			//returns message product qty was updated
            cout << endl << "Updated!" << endl;
		}else{
			//If int can't be read, clears the stream error, prints error message
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid quantity value!" << endl;
		}
	}

void AmaApp::addProduct(char tag){
		if(m_noOfProducts < 99){		
			m_products[m_noOfProducts] = createInstance(tag);

			if(m_products[m_noOfProducts] != nullptr){
				cin >> *m_products[m_noOfProducts];
				
				if(cin.fail()){
					//clears error from input stream, displays product
					cin.clear();
					cin.ignore(2000, '\n');

					cout << endl << *m_products[m_noOfProducts];

					delete m_products[m_noOfProducts];
					m_products[m_noOfProducts] = nullptr;
				}else{
					//add a new product at the end of the array
					m_noOfProducts++;
					saveProductRecords();
					cout << endl << "Success!" << endl;
				}
			}	
		}
	}

	iProduct* AmaApp::find(const char* sku) const{
		bool found = false;
		iProduct* iProd = nullptr;

		//Loops through the m_products array up to m_noOfProducts 
        //checks each of them for the same SKU as the incoming argument
        //using the operator == implemented by the Product class
		for(int i = 0; i < m_noOfProducts && !found; i++){
			if(*m_products[i] == sku){
				//If a match is found, returns the address of the found Product
				found = true;
				iProd = m_products[i];
			}	
		}
		return iProd;
	}


	int AmaApp::run(){
		int option;
		iProduct* temp = nullptr;
		char sku[max_length_sku] = { '\0' };
		
		do{
			//Displays menu
			option = menu();
            //receives user’s selection
			switch(option){
				case 1:
					//lists product information
					listProducts();
					cout << endl;
					pause();
					break;
				case 2:
					//searches and displays the product information if found
					cout << "Please enter the product SKU: ";
					cin.get(sku, max_length_sku-1, '\n');
					if (char(cin.get()) == '\n'){
						temp = find(sku);
						if (temp != nullptr){
							cout << endl;
							temp->write(cout, write_human);
							temp = nullptr;
							cout << endl;
						}else{
							//displays error message if not found
							cout << endl << "No such product!" << endl;
						}
					}else{
						//displays error message if not found
						cout << endl << "Invalid SKU!" << endl;
					}
					pause();
					break;
				case 3:
					//adds non-perishable product to system and loads product
					addProduct('N');
					loadProductRecords();
					cout << endl;
					break;
				case 4:
					//adds perishable product to system perishable and loads product
					addProduct('P');
					loadProductRecords();
					cout << endl;
					break;
				case 5:
					//searches and adds product qty if found
					cout << "Please enter the product SKU: ";
					cin.get(sku, max_length_sku-1, '\n');
					if(char(cin.get()) == '\n'){
						temp = find(sku);
						if(temp != nullptr){
							cout << endl;
							addQty(temp);
						}else{
							//displays error message if not found
							cout << endl << "No such product!" << endl;
						}
					}else{
						//displays error message if not found
						cout << endl << "Invalid SKU!" << endl;
					}
					cout << endl;
					break;
				case 0:
					cout << "Goodbye!" << endl;
					break;
				default:
					//displays error message if invalid selection of options
					cout << "~~~Invalid selection, try again!~~~" << endl;
					pause();
					break;
			}
		}while(option != 0);

		return 0; 
	}
}