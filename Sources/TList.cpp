// TList.cpp
#include "TList.h"
#include <QString>

TElem::TElem() : next(0){}
TElem::~TElem() { delete next; }

TList::TList() : firstElemPtr(0) {}
TList::~TList(){}

void TList::copyList(TList * copy)
{
    TList copy_list;
    TChar temp;
    while(!this->isEmpty())
    {
        temp = this->pop();
        copy_list.push(temp);
        copy->push(temp);
    }
    while(!copy_list.isEmpty())
        this->push(copy_list.pop());
}

TChar TList::getTop(void)
{
	TChar top_char = this->pop();
	this->push(top_char);
	return top_char;
}

bool TList::isEmpty(void)
{
	return firstElemPtr ? false : true;
}

void TList::reverseList()
{
	TList reversed_list;
	while (!this->isEmpty())
		reversed_list.push(this->pop());
	*this = reversed_list;
}

void TList::push(TChar x)
{
	TElem *newElemPtr = new TElem;
	newElemPtr->value = x;
	if (firstElemPtr == 0)
		firstElemPtr = newElemPtr;
	else
	{
		TElem *tempElemPtr = firstElemPtr;
		while (tempElemPtr->next)
			tempElemPtr = tempElemPtr->next;
		tempElemPtr->next = newElemPtr;
		newElemPtr->next = 0;
	}
}

TChar TList::pop()
{
	TChar temp;
	if (firstElemPtr)
	{
		TElem *tempElemPtr = firstElemPtr;
		TElem *prevElemPtr = tempElemPtr;
		while (tempElemPtr->next)
		{
			prevElemPtr = tempElemPtr;
			tempElemPtr = tempElemPtr->next;
		}
		if (prevElemPtr == tempElemPtr)
			firstElemPtr = 0;
		temp = tempElemPtr->value;
		prevElemPtr->next = 0;
		delete tempElemPtr;
	}
	else
        return temp; // returns TChar with default values, if the stack is empty
	return temp;
}

void TList::build(int x, char * char_ptr, QString * err_ptr)
{
    char temp;
    QString temp_double = "";
    QString trio = "";
    int i = 0;
    if (*char_ptr == DOT || *char_ptr == COMMA) // if an error occurs, no more conditions are examines
        err_ptr->append("Invalid character at the beginning of expression!\n");
    else
    {
        while(i < x)
        {
            temp = *(char_ptr + i);
            if ((temp > 47 && temp < 58) || temp == DOT)
            {
                while ((temp > 47 && temp < 58) || temp == DOT)
                {
                    temp_double.append(temp);
                    i++;
                    temp = *(char_ptr + i);
                }
                TChar single1;
                single1.number = temp_double.toDouble();
                temp_double = "";
                this->push(single1);
            }
            else if ((temp != DOT) && (temp != COMMA) && (temp > 39 && temp < 48))
            {
                TChar single2;
                single2.operand = temp;
                if (temp == L_BR)
                    single2.priorit = 0;
                else if (temp == ADD || temp == SUBTR || temp == R_BR)
                    single2.priorit = 1;
                else if (temp == MULTIP || temp == DIV)
                    single2.priorit = 2;
                else
                    single2.priorit = -1;
                this->push(single2);
                i++;
            }

            else if(temp == COMMA) // for future use, as a function arguments separator
            {
                err_ptr->append("Unknown character detected!\n");
                break;
            }

            else // (temp < 40 || temp > 57)
            {
                TChar single3;
                trio = "";
                if (i < (x - 2)) // to avoid taking chars out of array bounds
                {
                    trio.append(*(char_ptr + i));     // combining string from 3 consecutive char's
                    trio.append(*(char_ptr + i + 1));
                    trio.append(*(char_ptr + i + 2));
                }
                // skip three more elements in char array...
                i+=3;
                if (trio == SIN)              // checking if there is some function in 'trio' string
                    single3.funct_name = SIN;
                else if (trio == COS)
                    single3.funct_name = COS;
                else if (trio == TAN)
                    single3.funct_name = TAN;
                else if (trio == CTG)
                    single3.funct_name = CTG;
                else if (trio == POW)
                    single3.funct_name = POW;
                else if (trio == SQR)
                    single3.funct_name = SQR;
                else if (trio == EXP)
                    single3.funct_name = EXP;
                else
                {
                    err_ptr->append("Unknown character or string detected!\n");
                    break;
                }
                this->push(single3);
            }
        }
        if (*(char_ptr + i - 1) == DOT || *(char_ptr + i - 1) == COMMA)
            err_ptr->append("Invalid character at the end of expression!\n");
    }
}
