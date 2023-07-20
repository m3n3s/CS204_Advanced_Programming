#include <iostream>
#include <string>
#include "CardList.h"

using namespace std;

CardList::CardList()
{
	head = NULL;
	tail = NULL;
}

void CardList::insertCard (string creditCardNo, int month, int year)
{
	// THIS FUNCTION SHOULD INSERT THE CARD IN THE CORRECT PLACE (IN A SORTED FASHION)
	// SO IT NEEDS TO ITERATE THROUGH EXPIRATION DATES AND IF NO SUCH DATE IS FOUND, IT SHOULD CREATE A NEW ONE
	// IF SUCH A DATE IS FOUND, IT SHOULD ITERATE THROUGH THE CARDS IN IT AND PLACE THE CARD IN THE CORRECT PLACE

	if(head == NULL) // List is empty
	{
		head = new expirationNode(month, year, NULL , NULL, NULL);
		head -> cHead = new creditCardNode(creditCardNo, NULL);
		tail = head;
		cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
	}

	else // List is not empty so we have to check for expiration dates
	{
		expirationNode* ptr = head; // loop variable

		while((ptr->next != NULL)&&(ptr->next->year < year || 
			(ptr->next->year == year && ptr->next->month < month)||(ptr->next->year == year && ptr->next->month == month)))
			ptr = ptr->next;
		// moves the pointer to the correct position		
		
		if(ptr->month == month && ptr->year == year) // if there is a node with same expiration date
		{
			// iterate throuhg cards list
			// place it in the correct place(ascending order)			

			creditCardNode* cptr = ptr->cHead; // loop variable

			// it cant be empty since we always add card when the date node is created
			// so no need to check
			while(cptr->next != NULL && cptr ->next->creditCardNo <= creditCardNo)
				cptr = cptr->next;

			if(cptr->creditCardNo == creditCardNo) // if that card was already inserted
				cout << creditCardNo << " " << month << " " << year << ": this card was already inserted" << endl;

			else if(cptr ==  ptr->cHead && cptr->creditCardNo >creditCardNo) // add to beginning
			{
				creditCardNode* temp = new creditCardNode(creditCardNo, cptr);
				ptr->cHead = temp; // edited
				cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node " << endl;
			}			

			else if(cptr->next == NULL && cptr->creditCardNo < creditCardNo) // add card to the end
			{
				creditCardNode* temp = new creditCardNode(creditCardNo, NULL);
				cptr->next = temp;
				cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node " << endl;
			}

			else // add card in the middle
			{
				creditCardNode* temp = new creditCardNode(creditCardNo, cptr->next);
				cptr->next = temp;
				cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node " << endl;
			}
		}

		else // there is no node with that expiration date
		{
			if(ptr == head && (ptr->year > year ||((ptr->year == year)&&(ptr->month > month)))) 
			{	// add to beginning
				expirationNode* temp = new expirationNode(month, year, ptr, NULL, NULL);
				ptr->prev = temp;
				head = temp;
				// created a new date node

				temp->cHead = new creditCardNode(creditCardNo, NULL); // added the credit card no
				cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
			}

			else if(ptr == tail && (ptr->year < year ||((ptr->year == year)&&(ptr->month < month)))) // add to end
			{
				expirationNode* temp = new expirationNode(month, year, NULL, tail, NULL);
				tail->next = temp;
				tail = temp;
				// created a new date node

				temp->cHead = new creditCardNode(creditCardNo, NULL); // added the credit card no
				cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
			}

			else // add to somewhere in the middle
			{
				expirationNode* temp = new expirationNode(month, year, ptr->next, ptr, NULL);
				ptr->next->prev = temp;
				ptr->next = temp;
				// created a new date node

				temp->cHead = new creditCardNode(creditCardNo, NULL); // added the credit card no
				cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
			}
		}
	}
}

void CardList::displayListChronological ()
{
	/* Begin: code taken from DoublyLinkedList.cpp and updated */ 	
	cout << endl;
	expirationNode* ptr = head;
	//List is empty
	if(head == NULL)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		while(ptr != NULL)
		{			
			cout << "Expiration Date: " << ptr->month << " " << ptr->year << endl; 
			creditCardNode* cptr = ptr->cHead;

			int count = 0;
			while(cptr != NULL)
			{
				count++;
				cout << count << ") " << cptr->creditCardNo << endl;;
				cptr = cptr->next;
			}
			cout << "-------------------" << endl;
			ptr = ptr->next;
		}
	}
	/* End: code taken from DoublyLinkedList.cpp and updated*/
}

void CardList::displayListReverseChronological () 
{
	/* Begin: code taken from DoublyLinkedList.cpp and updated */ 	
	cout << endl;
	expirationNode* ptr = tail;
	//List is empty
	if(head == NULL)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		while(ptr != NULL)
		{
			cout << "Expiration Date: " << ptr->month << " " << ptr->year << endl; 

			creditCardNode* cptr = ptr->cHead;
			int count = 0;
			while(cptr != NULL)
			{
				count++;
				cout << count << ") " << cptr->creditCardNo << endl;
				cptr = cptr->next;
			}
			cout << "-------------------" << endl;
			ptr = ptr->prev;
		}
	}
	/* End: code taken from DoublyLinkedList.cpp and updated*/
}

void CardList::cardSearch (string creditCardNo)
{
	expirationNode* ptr = head; // loop variable
	bool found = false;

	while(ptr != NULL)
	{		
		creditCardNode* cptr = ptr->cHead;
	
		while(cptr != NULL)
		{			
			if(cptr->creditCardNo == creditCardNo)
			{
				found = true;
				cout << "There exists a credit card given number " << creditCardNo << " with expiration date: " <<endl;
				cout << ptr->month << " " << ptr->year << endl;
			}
			cptr = cptr->next;
						
		}
		ptr = ptr->next;

	}
	if(!found)
		cout << "There is no credit card with given credit card number: " << creditCardNo << endl;
}

void CardList::bulkDelete (int month, int year)
{
	expirationNode* ptr = head; // loop variable
	
	while(ptr != NULL && (year > ptr->year || (ptr->year == year && ptr->month <= month)))
	{
		// delete the cards
		
		expirationNode* temp = ptr;
		cout << "Node with expiration date " << temp->month << " " << temp->year << "  and the following credit cards have been" << endl;
		cout << "deleted!" << endl;
		
		creditCardNode* cptr = ptr->cHead;
		int count = 0;
		while(cptr != NULL)
		{
			count++;
			creditCardNode* temp = cptr;
			cptr = cptr->next;

			cout << count << ") " << temp->creditCardNo << endl;
			delete temp;
		}
		ptr = ptr->next;
		delete temp;
		head = ptr;	// assign the new head

		if(head != NULL)
			head->prev = NULL; // make sure head does not point to any previous place
	}
	
}

void CardList::deleteAll ()
{
	expirationNode* ptr = head; // loop variable
	
	while(ptr != NULL)
	{
		// delete the cards
		
		expirationNode* temp = ptr;
		creditCardNode* cptr = ptr->cHead;

		int count = 0;
		while(cptr != NULL)
		{
			count++;
			creditCardNode* temp = cptr;
			cptr = cptr->next;

			delete temp;
		}
		ptr = ptr->next;
		delete temp;
		head = ptr;

		if(head != NULL)
			head->prev = NULL;
	}
	cout << "All the nodes have been deleted!" << endl;
}