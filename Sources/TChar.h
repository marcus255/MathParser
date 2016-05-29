// TChar.h
#ifndef	TCHAR_H
#define TCHAR_H

#include <QString>
                    // ASCII codes:
#define L_BR   40   // (
#define R_BR   41   // )
#define MULTIP 42   // *
#define ADD    43   // +
#define COMMA  44   // ,
#define SUBTR  45   // -
#define DOT    46   // .
#define DIV    47   // /

#define SIN "sin"
#define COS "cos"
#define TAN "tan"
#define CTG "ctg"
#define POW "pow"
#define SQR "sqr"
#define EXP "exp"

extern double rad_deg;   // global variable to switch between radians and degrees

class TChar
{
public:
    char operand;        // stores operator characters
    char priorit;        // stores operator priorities
    long double number;  // stores numbers combined from digits and decimal dot
    QString funct_name;  // stores list of functions acronyms ("sin", "cos", etc.)
    TChar operation(TChar a, TChar b);  // perform two argument arithmetic operation (adding, multiplication, etc.)
    TChar funct(TChar arg);             // perform one argument arithmetic operation (sin(), cos(), etc.)

public:
    TChar(void);
    ~TChar(void);
};

#endif // TChar.h
