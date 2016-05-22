// TParser.cpp
#include "TParser.h"

TParser::TParser(){}
TParser::~TParser(){}

void TParser::prepare_expr(void)
{
    this->expr_len = this->char_expr.length();
    char * c_ptr = new char[this->char_expr.length()];
    for (int i = 0; i < this->char_expr.length(); i++)
        *(c_ptr + i) = this->char_expr[i].toLatin1();
    this->expr_ptr = c_ptr;
}

void TParser::validateExpr(QString *err_ptr)
{
    int l_br = 0, r_br = 0;
    TList * expr = new TList;
    this->infix_expr.copyList(expr);
    TChar single;
    char is_operator = 0, is_near = 0;
    TChar first_one = expr->getTop();

    if ((first_one.operand != 0) && (first_one.operand != L_BR)) // if an error occurs, no more conditions are examines
        err_ptr->append("Invalid character at the beggining of expression!\n");
    else
    {
        while (!expr->isEmpty())
        {
            if (is_operator > 1)
                is_near = 1;

            single = expr->pop();
            if (single.operand != 0)
            {
                if (single.operand == L_BR)
                    l_br++;
                else if (single.operand == R_BR)
                    r_br++;
                else
                    is_operator++;
            }
            else
                is_operator = 0;
        }

        if (l_br != r_br)
            err_ptr->append("Left and right brackets dont match!\n");
        else if (is_near)
            err_ptr->append("Two or more operators next to each other detected!\n");
        else if ((single.operand != 0) && (single.operand != R_BR))
            err_ptr->append("Invalid character at the end of expression!\n");
    }
}

void TParser::rpn()
{   // http://pl.wikipedia.org/wiki/Odwrotna_notacja_polska#Algorytm_konwersji_z_notacji_infiksowej_do_ONP
    TList op_stack;
    TChar topChar, temp_char;
    while (!this->infix_expr.isEmpty())
    {
        topChar = this->infix_expr.pop();
        if (topChar.operand == 0)           // digits and decimal dot
            this->rpn_expr.push(topChar);
        else
        {
            if (topChar.operand == L_BR)
                op_stack.push(topChar);
            else if (topChar.operand == R_BR)
            {
                temp_char = op_stack.pop();
                while (temp_char.operand != L_BR)
                {
                    this->rpn_expr.push(temp_char);
                    temp_char = op_stack.pop();
                }
            }
            else                            // operators: +, -, *, /
            {
                if (op_stack.isEmpty())
                    op_stack.push(topChar);
                else
                {
                    temp_char = op_stack.getTop();
                    if (topChar.priorit > temp_char.priorit)
                        op_stack.push(topChar);
                    else
                    {
                        while (temp_char.priorit >= topChar.priorit)
                        {
                            this->rpn_expr.push(temp_char);
                            op_stack.pop();
                            if (!op_stack.isEmpty())
                                temp_char = op_stack.getTop();
                            else
                                break;
                        }
                        op_stack.push(topChar);
                    }
                }
            }
        }
    }
    while (!op_stack.isEmpty())
        this->rpn_expr.push(op_stack.pop());
}

// https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska#Algorytm_konwersji_z_notacji_infiksowej_do_ONP_.28rekurencyjny.29
int TParser::recursiveRPN(void)
{
    int error = NO_ERROR;
    TChar a, c;
    c = this->infix_expr.pop();
    if (c.operand == L_BR || c.funct_name != "")
    {
        if (c.funct_name != "")
        {
            this->infix_expr.pop(); // pop a bracket, function name already indicated that there is nested expression
            this->rpn_expr.push(c); // push a function on the stack
        }
        error = this->recursiveRPN();
        if (error)
            return error;
        a = this->infix_expr.pop();
        if (a.operand == 0 || a.operand == L_BR || a.operand == R_BR)
            return NO_OPERAND_ERROR;
        error = this->recursiveRPN();
        if (error)
            return error;
        if(this->infix_expr.pop().operand != R_BR)
            return NO_R_BR_ERROR;
        this->rpn_expr.push(a);
    }
  /*  else if (c.funct_name != "")
    {
    //    char bracket = this->infix_expr.pop().operand;
    //    if (bracket != L_BR)
    //        return NO_L_BR_ERROR;
        this->rpn_expr.push(c);
        error = this->recursiveRPN();
    }*/
    else
    {
        this->rpn_expr.push(c);
    }
    return error;
}

void TParser::parseRpnExpr(void)
{   // http://pl.wikipedia.org/wiki/Odwrotna_notacja_polska#Algorytm_obliczenia_warto.C5.9Bci_wyra.C5.BCenia_ONP
    TChar top_char, a_char, b_char, f_char;
    TList op_stack, rpn_copy;
    while (!this->rpn_expr.isEmpty())
    {
        top_char = this->rpn_expr.pop();
        rpn_copy.push(top_char);
        if (top_char.operand == 0 && top_char.funct_name == "")  // number
            op_stack.push(top_char);
        else if (top_char.funct_name != "")                      // one argument functions: sin(), cos(), etc.
        {
            f_char = this->rpn_expr.pop();
            rpn_copy.push(f_char);
            op_stack.push(top_char.funct(f_char));
        }
        else                                                   // two argument operators: +, -, *, /
        {
            a_char = op_stack.pop();
            b_char = op_stack.pop();
            op_stack.push(top_char.operation(a_char, b_char));
        }
    }
    this->score = op_stack.pop().number;
    rpn_copy.reverseList();
    this->rpn_expr = rpn_copy;
}

void TParser::stringRpn(void)
{
    QString rpn = "";
    TChar temp_char;
    while (!this->rpn_expr.isEmpty())
    {
        temp_char = this->rpn_expr.pop();
        if (temp_char.operand == 0 && temp_char.funct_name == "")
            rpn.append(QString::number(temp_char.number, 'g', 10)); // concatenating number...
        else if (temp_char.funct_name != "")                        // ...to string after type conversion
            rpn.append(temp_char.funct_name);
        else
            rpn.append(temp_char.operand);
        rpn.append(' ');
    }
    this->string_score = rpn;
}
