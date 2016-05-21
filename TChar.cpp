// TChar.cpp
#include "TChar.h"
#include <math.h>

TChar::TChar() : operand(0), priorit(-1), number(0.0), funct_name(""){}
TChar::~TChar(){}

TChar TChar::operation(TChar a, TChar b)
{
	TChar score;
	switch (this->operand)
	{
	case ADD:
		score.number = b.number + a.number;
		break;
	case SUBTR:
		score.number = b.number - a.number;
		break;
	case MULTIP:
		score.number = b.number * a.number;
		break;
	case DIV:
		score.number = b.number / a.number;
		break;
	default:
		score.number = 0.0;
		break;
	}
	return score;
}

TChar TChar::funct(TChar arg)
{
    TChar score;
    if (this->funct_name == SIN)
        score.number = sin(arg.number * rad_deg);
    else if (this->funct_name == COS)
        score.number = cos(arg.number * rad_deg);
    else if (this->funct_name == TAN)
        score.number = tan(arg.number * rad_deg);
    else if (this->funct_name == CTG)
        score.number = 1/(tan(arg.number * rad_deg));
    else if (this->funct_name == POW)
        score.number = pow(arg.number,2.0);
    else if (this->funct_name == SQR)
        score.number = sqrt(arg.number);
    else if (this->funct_name == EXP)
        score.number = exp(arg.number);
    else
    {
        // argument error
        score.number = 0;
    }
    return score;
}
