// TList.h
#ifndef TLIST_H
#define TLIST_H
#include "TChar.h"
class TElem
{
public:
	TChar value;
	TElem *next;

public:
	TElem();
	~TElem();
};

class TList
{
public:
	TElem *firstElemPtr;
	void push(TChar x);
    TChar pop();
    bool isEmpty(void);         // returns true when stack is empty, otherwise returns false
    void reverseList(void);     // reverses stack order
    TChar getTop(void);         // returns top stack element, without droping it from stack
    void copyList(TList * copy);
    void build(int x, char * char_ptr, QString *err_ptr); // builds stack of TChar elements from character array

public:
    TList();
    ~TList();
};


#endif // TList.h
