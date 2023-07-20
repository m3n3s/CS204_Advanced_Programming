#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// MEHMET ENES BATTAL - HW2

struct node  
{
	int month, year; 
	vector<string> cards; 
	node* next; 

	/* Begin: code taken from linkedList.cpp and updated */ 

	//default constructor
	node::node ()
		:month(0), year(0), next(NULL)
	{}

	//constructor
	node::node (int m, int y, node *n)
		:month(m), year(y), next(n)
	{}	

	/* End: code taken from linkedList.cpp and updated */ 
}; 

int search(node* head, int m, int y)
{
	node* temp = head;
	int nodeIndex = 0;
	while(temp != NULL)
	{
		if(temp -> month == m && temp -> year == y)
			return nodeIndex;
		temp = temp -> next;
		nodeIndex ++;
	}
	return -1;

}

node* getNode(node* head, int n)
{
	/* Begin: code taken from linkedList.cpp and updated */ 
	
	int counter=0;
	node *ptr = head;
	while (ptr != NULL && counter<n-1)
	{ 
		ptr = ptr->next;
		counter++;
	}
	return ptr;

	/* End: code taken from linkedList.cpp and updated */ 
}

void menu()
{
	cout << endl;
	cout << "1)Display List" << endl;
	cout << "2)Card Search via Credit Number" << endl;
	cout << "3)Delete Card with respect to Expiration Date" << endl;
	cout << "4)Exit" << endl << endl; 
	cout << "Please choose option from the menu: ";
}

void displayList(node* head)
{
	node* p = head;

	if(p == NULL)
		cout << "List is empty!" << endl;
		
	while(p != NULL)
	{
		cout << "Expiration Date: ";
		cout << p->month << "  " << p->year <<endl;
		for (int j = 1; j < p ->cards.size() + 1; j++)
		{
			cout << j << ") " << p->cards[j-1] << endl;
		}
		cout << "-------------------" << endl << endl;
		p= p->next;
	}

}

bool cardSearch(node* head)
{
	string num;
	bool valid;

	do
	{	
		valid = true;

		cout << "Please enter the credit card number: ";
		cin >> num;

		if(num.length() != 16)
		{
			cout << "Invalid format!" << endl;
			valid = false;
		}

		else
		{
			for (int j = 0; j < num.length() && valid; j++)
			{
				// every element should be an integer 
				//cout << num[j] << endl;
				if(num[j] < '0' || num[j] > '9')
				{
					cout << "Invalid format!" << endl;
					valid = false;
				}
			}
			
		}

	}while(!valid);
		
	while (head != NULL)
	{
		for(int i = 0; i < head -> cards.size(); i++)
		{
			if(head -> cards[i] == num)
			{
				cout << "There exists a credit card given number " << num << " with" << endl;
				cout << "expiration date: " << head->month << " " << head->year << endl;
				return true;
			}
		}	

		head = head->next;
	}

	cout << "There is no credit card with given credit card number: " << endl;
	cout << num << endl;

	return false;
}

bool deleteCard(node* & head)
{
	int m, y;
	bool valid;

	do
	{		
		valid = true;

		cout << "Please enter month and year: ";
		string line;

		// cin.clear();
		// cin.ignore();

		// neden 33 3 girince olmuyo !!!!!!!!!!
		getline(cin, line);
		stringstream ss(line);

		if(ss >> m >> y && (m > 0 && m < 13) && y >= 0)
			cout << "valid entry" << endl;

		else
		{
			cout << "Invalid Date!" << endl;
			valid = false;
		}

	}while(!valid);
		
	
	node* ptr = head; // loop variable
		
	// THE CASE WHERE TNE FIRST NODE IS DELETED
	if(ptr -> month == m && ptr -> year == y && ptr == head)
	{
		cout << "Node with expiration date " << ptr->month << " " << ptr->year << " and the following credit cards" << endl;
		cout << "have been deleted!" << endl;
		for(int i = 1; i < ptr->cards.size()+1; i++)
		{
			cout << i << ") " << ptr->cards[i] << endl;
		}
		
		head = ptr->next;
		delete ptr;
		return true;
	}

	while (ptr -> next != NULL)
	{
		// THE CASE WHERE THE DELETED NODE IS IN THE MIDDLE OR AT THE END
		
		if(ptr -> next -> month == m && ptr -> next -> year == y)
		{
			node* prev = ptr;
			ptr = ptr -> next;
			
			prev = ptr -> next; 

			cout << "Node with expiration date " << ptr->month << " " << ptr->year << " and the following credit cards" << endl;
			cout << "have been deleted!" << endl;
			for(int i = 1; i < ptr->cards.size()+1; i++)
			{
				cout << i << ") " << ptr->cards[i] << endl;
			}

			delete ptr;

			return true;
		}

		ptr = ptr -> next;
	}

	cout << "There is no node with expiration date " << m << y << ", nothing deleted!" << endl;

	return false;	
}

int main()
{
	string filename, line;
	ifstream input;

	do
	{
		cout << "Please enter file name: ";
		cin >> filename;

		input.open(filename);

		if (input.fail())
			cout << "Cannot find a file named " << filename << endl;

	}while(input.fail());

	node* list = NULL;
	
	while( !input.eof())
	{
		getline(input, line);

		int month, year;
		string cardNo;
		stringstream  ss(line);

		while(ss >> cardNo >> month >> year)  
		{
			int nodeindex = search(list, month, year);

			if(nodeindex != -1) // THERE IS A NODE WITH THIS DATE
			{
				getNode(list, nodeindex)->cards.push_back(cardNo);

				cout << "Node with expiration date "<< month << " " << year << " already exists" << endl;
				cout << "Credit card " << cardNo << " added to node " << month << " " << year << endl; 
				cout << "***************" << endl;
			}
			else // IF THERE IS NO SUCH NODE WITH THIS DATE
			{ 
				/* Begin: code taken from ptrfunc.cpp and updated */ 

				if ((list == NULL) || (year < list -> year) || 
					(year == list -> year && month < list -> month))    
				{  
					// if new node should be first, handle this case
					node* temp = new node(month, year, list);
					temp -> cards.push_back(cardNo);
					list = temp;

					cout << "New node is created with expiration date: " << month << " " << year << endl; 
					cout << "Credit card " << cardNo <<" added to node " << month << " " << year << endl; 
					cout << "***************" << endl;
				}

				else
				{
					node *  ptr = list;   // loop variable

					while ((ptr->next != NULL) && 
						(ptr->next->year < year || (ptr->next->year == year && ptr->next->month < month)))
					{   
						ptr = ptr->next;
					}					
					ptr->next = new node(month, year, ptr->next);
					ptr -> next -> cards.push_back(cardNo);

					cout << "New node is created with expiration date: " << month << " " << year << endl; 
					cout << "Credit card " << cardNo <<" added to node " << month << " " << year << endl; 
					cout << "***************" << endl;
				}

				/* End: code taken from ptrfunc.cpp and updated */ 

			}

		}
	
	}
	// BUTUN SATIRLAR OKUNDU

	int choice = 0;

	do
	{
		// HARF GIRME DURUMUNU HALLET!!!!!

		menu();
		cin >> choice;

		if( choice == 1)
			displayList(list);
		
		else if(choice == 2)
			cardSearch(list);

		else if(choice == 3)
			deleteCard(list);
		
	} while(choice != 4);

	cout << "Terminating!!!";

	return 0;
}