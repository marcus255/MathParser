#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include "TChar.h"
#include "TList.h"
#include "TParser.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Calculate();

private slots:
    void on_run_clicked();

    void on_infix_box_editingFinished();

    void on_Radians_Button_clicked();

    void on_Degrees_Button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
