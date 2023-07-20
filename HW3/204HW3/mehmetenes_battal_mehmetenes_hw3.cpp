#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "CardList.h"

using namespace std;

// MEHMET ENES BATTAL - HW3

void menu()
{
	cout << endl;
	cout << "1) Upload Card(s) from a File" << endl;
	cout << "2) Display List Chronological " << endl;
	cout << "3) Display List Reverse Chronological" << endl;
	cout << "4) Card Search" << endl;
	cout << "5) Bulk Delete" << endl;
	cout << "6) Exit" << endl; 
	cout << "Please choose option from the menu: ";
}

void uploadCards(CardList & myList)
{
	string filename, line;
	ifstream input;

	do
	{
		cout << "Please enter file name: ";
		cin >> filename;

		input.open(filename);

		if (input.fail())
		{
			cout << "Cannot find a file named " << filename << endl;
			return;
		}

	}while(input.fail());
	
	while( !input.eof())
	{
		getline(input, line);

		int month, year;
		string cardNo;
		stringstream  ss(line);

		while(ss >> cardNo >> month >> year)  
		{
			myList.insertCard(cardNo, month, year);
		}
	}

	input.close();
}

bool cardNoCheck(string n)
{
	if(n.length() != 16)
		return false;
	for(int i=0 ; i<n.length(); i++)
	{
		if(!(n[i]>= '0' && n[i] <= '9'))
			return false;
	}
	return true;
}

void cardSearch(CardList myList)
{
	cout << "Please enter the credit card number: ";
	string search ;
	cin >> search;

	if(cardNoCheck(search))
		myList.cardSearch(search);
	else
		cout << "Invalid format!" << endl; 
}

void bulkDelete(CardList & myList)
{
	cout << "Please enter month and year: ";
	int m, y;

	if(cin >> m)
	{
		if(cin >> y)
		{
			if(0 < m && m < 13)
			{
				myList.bulkDelete(m, y);
			}
			else
				cout << "Invalid format!" << endl;
		}
		else
		{
			cout << "Invalid format!" << endl;
			cin.clear();
			
			string s1;
			getline(cin,s1);
			
		}
	}

	else
	{
		cout << "Invalid format!" << endl;
		cin.clear();
		
		string s1;
		getline(cin,s1);

	}

}

int main()
{
	CardList myList;
	string choice = "";

	do
	{
		menu();
		cin >> choice;

		if( choice == "1")
			uploadCards(myList);
		
		else if(choice == "2")
			myList.displayListChronological();

		else if(choice == "3")
			myList.displayListReverseChronological();
		
		else if(choice == "4")
			cardSearch(myList);

		else if(choice == "5")
			bulkDelete(myList);

		else if(choice == "6")
			myList.deleteAll();
			
		else
		{
			cout << "Invalid operation! " << endl;
			string s1;
			getline(cin,s1);
		}

	} while(choice != "6");

	cout << "Terminating!!!" << endl;

	return 0;
}