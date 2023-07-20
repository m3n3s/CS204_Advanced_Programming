#include <iostream>

// MEHMET ENES BATTAL - HW5

using namespace std;

class IntegerSet
{
	public:
		IntegerSet(); // Default constructer
		IntegerSet(int); // Constructer with set size
		IntegerSet(const IntegerSet &); // Deep copy constructer
		~IntegerSet(); // Destructor

		IntegerSet operator+(int);
		IntegerSet operator+(const IntegerSet &) const;
		IntegerSet operator*(IntegerSet) const;
		const IntegerSet & operator=(const IntegerSet &);
		const IntegerSet & operator+=(const IntegerSet &);
		bool operator<=(IntegerSet) const;

		int getSize() const; // Returns the size of the set
		int* getPtr() const; // Returns the pointer to the set
		bool inSet(int) const; // Return true if given parameter is in the set
		
	private:
		int size;
		int* setPtr;
};

// FREE FUNCTIONS

ostream & operator <<(ostream &output, const IntegerSet &set);
bool operator!=(IntegerSet lhs, IntegerSet rhs);
bool operator<=(int lhs, IntegerSet rhs);