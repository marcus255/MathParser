#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include "TChar.h"
#include "TList.h"
#include "TParser.h"

#define RADIAN_CONSTANT 0.0174532925199433
#define RECURSIVE       1
#define DIJKSTRA        2

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

    void on_Dijkstra_Button_clicked();

    void on_Recursive_Button_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
