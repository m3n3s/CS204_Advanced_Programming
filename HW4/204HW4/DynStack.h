/* Begin: code taken from DynIntStack.h and updated */ 

struct StackNode
{
	int rowNum;
	int colNum;
	StackNode* next;
};

class DynStack
{
private:
	StackNode* top;

public:
	DynStack(void);
	~DynStack();
	void push(int x, int y);
	void pop(int &numX, int &numY);
	bool isEmpty(void);
};

/* End: code taken from DynIntStack.h and updated */ 