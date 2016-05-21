// TParser.h
#ifndef TPARSER_H
#define TPARSER_H
#include "TChar.h"
#include "TList.h"
#include "QString"

class TParser
{
public:
    int expr_len;
    char * expr_ptr;
    long double score;    // stores final expression result
    QString char_expr;    // stores expression typed by user
    QString string_score; // stores RPN expression
    TList infix_expr;     // stack of TChar elements in original form
    TList rpn_expr;       // stack of TChar's after RPN rearrangement

    void prepare_expr(void);        // basic format conversions
    void parseRpnExpr(void);        // main parsing algorithm
    void rpn(void);                 // infix to postfix algorithm
    void stringRpn(void);           // combines 'string_score' variable
    void validateExpr(QString * err_ptr);   // returns error text if the expression is invalid

    TParser();
    ~TParser();
};

#endif // TParser.h
