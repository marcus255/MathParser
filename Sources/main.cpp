// Mathematical Parser, based on Reverse Polish Notation processing
// Author: Marek Trojan, marek255trojan[at]gmail[dot]com
// Electronics and Telecommunications, AGH University of Science and Technology

// example expression:
// 7*cos(3)*(5-6.45*(5+2*pow(3)+8.234)-18/7)*3+sqr(7)-(4.1*exp(4)*6+12)/13*0.2*5

// RPN expression matching this query is:
// 7 cos 3 * 5 6.45 5 2 pow 3 * + 8.234 + * - 18 7 / - * 3 * sqr 7 + 4.1 exp 4 * 6 * 12 + 13 / 0.2 * 5 * -
// (check on: http://scanftree.com/Data_Structure/prefix-postfix-infix-online-converter)

// the result is: 4036.223661 (calculated using excel.exe) (trigonometric functions arguments assumed in radians)

// Program detects some incorect expressions:           Examples:
// - two operators next to each other                   7*/8            67-(34*7+-5)
// - operator at the beginning and at the end           *5/12+9         89*(4-9)+
// - different number of right and left brackets        3+(3*7)-8)      (8-(12+8)
// - unknown chars and strings (functions)              78a8*7-cos(2)   diff(34)*7
// - decimal dot at the beginning and at the end        12+exp(2)+7.    .5-2

// Due to algorithms limitations, some errors are not handled.
// Recursive algorithm requires complete bracketing, i.e. (a+(b*c)). Fails when expression contains unary minus, i.e. (-1+2)
// Dijkstra algorithm in turn, does not support nesting of functions.

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
