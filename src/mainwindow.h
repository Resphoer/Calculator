#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <stack>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int isp(char);
    int icp(char);
    void DoOperator(char op);
    bool Get2Operands(double& left,double& right);
    void Clear();
    double help(string);
private:
    Ui::MainWindow *ui;
    stack<double> ans;
private slots:
    void digit_pressed();
    void on_pushbutton_dot_released();
    void on_pushbutton_clear_released();
    void on_pushbutton_equals_released();
    void binary_operation_pressed();
    void unary_operation_pressed();
    void on_back_pressed();
};
#endif // MAINWINDOW_H
