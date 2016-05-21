#include "mainwindow.h"
#include "ui_mainwindow.h"

double rad_deg = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_run_clicked()
{
    Calculate();
}

void MainWindow::on_infix_box_editingFinished()
{
    Calculate();
}

void MainWindow::Calculate()
{
    TParser expr1;
    expr1.char_expr = ui->infix_box->text();
    expr1.prepare_expr();
    QString * err_ptr = new QString("");
    expr1.infix_expr.build(expr1.expr_len, expr1.expr_ptr, err_ptr);

    if((*err_ptr) == "") // if an error while 'build' function occurs, no more function executes
        expr1.validateExpr(err_ptr);
    if ((*err_ptr) == "") // parsing is performed only if there is no error detected
    {
        expr1.infix_expr.reverseList();
        if(!expr1.recursiveRPN())
        {
            ui->error_box->setText("Error: recursiveRPN returned non-zero value.");
        }
        //expr1.rpn();
        expr1.rpn_expr.reverseList();
        expr1.parseRpnExpr();
        expr1.stringRpn();

        ui->rpn_box->setText(expr1.string_score);
        ui->result_box->setText(QString::number(expr1.score, 'g', 10));
        ui->error_box->setText("No errors.");
    }
    else
    {
        ui->rpn_box->setText("Error");
        ui->result_box->setText("Error");
        ui->error_box->setText(*err_ptr);
    }
}

void MainWindow::on_Radians_Button_clicked()
{
    rad_deg = 1;
}

void MainWindow::on_Degrees_Button_clicked()
{
    rad_deg = 0.0174532925199433;
}
