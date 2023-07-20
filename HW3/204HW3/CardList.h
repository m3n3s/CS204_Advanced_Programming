#include <string>
using namespace std;

struct creditCardNode
{
	string creditCardNo;  
	creditCardNode * next;
	//default constructor
	creditCardNode::creditCardNode ()
		:creditCardNo(0), next(NULL)
	{}
	//constructor
	creditCardNode::creditCardNode (string m, creditCardNode *n)
		:creditCardNo(m), next(n)
	{}	
};

struct expirationNode 
{  
	int month, year;  
	creditCardNode * cHead;  
	expirationNode * next;  
	expirationNode * prev; 
	
	//default constructor
	expirationNode::expirationNode ()
		:month(0), year(0), next(NULL), prev(NULL), cHead(NULL)
	{}
	//constructor
	expirationNode::expirationNode (int m, int y, expirationNode *n, expirationNode *p, creditCardNode *c)
		:month(m), year(y), next(n), prev(p), cHead(c)
	{}	
};

class CardList  
{ 
	public:  
		CardList(); //default constructor that creates an empty list  
		void insertCard (string creditCardNo, int month, int year);    //inserts a new card to the structure in sorted fashion  
		void displayListChronological ();  //displays entire structure in chronological order  
		void displayListReverseChronological ();  //displays entire structure in reverse chronological order  
		void cardSearch (string creditCardNo);  //displays all of the occurrences of the given card number  
		void bulkDelete (int month, int year);  //deletes all nodes up to and including given expiration date  
		void deleteAll (); //deletes the entire structure 
	private:  
		expirationNode * head;  
		expirationNode * tail; 
 
// any helper functions you see necessary 
};