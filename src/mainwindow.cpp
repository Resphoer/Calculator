#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <cmath>
#include<string>
#include<vector>
#include<sstream>
#include<string.h>
using namespace std;
stack<char> hep;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_left,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_right,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_sqrt,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_fen,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_multiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    connect(ui->pushButton_dot,SIGNAL(released()),this,SLOT(on_pushbutton_dot_released()));
    connect(ui->pushButton_equals,SIGNAL(released()),this,SLOT(on_pushbutton_equals_released()));
    connect(ui->pushButton_clear,SIGNAL(released()),this,SLOT(on_pushbutton_clear_released()));

    connect(ui->pushButton_back,SIGNAL(released()),this,SLOT(on_back_pressed()));

    hep.push('=');
    setWindowTitle("myCalculator");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_back_pressed(){
    QString s=ui->label->text();
    s=s.left(s.size()-1);
    ui->label->setText(s);
}

void MainWindow::digit_pressed(){
    QPushButton * button = (QPushButton*) sender();
    ui->label->setText(ui->label->text()+button->text());
}

void MainWindow::on_pushbutton_dot_released(){
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::on_pushbutton_clear_released(){
    ui->label->setText("");
    ui->label_2->setText("0");
    Clear();
}

void MainWindow::on_pushbutton_equals_released(){
    string tar=ui->label->text().toStdString()+"=";
    char ch,ch1,op;
    int i=0;
    string fac;
    ch=tar[i];
    i++;
    while(!hep.empty()){
        if(isdigit(ch)||ch=='.'){
        while(isdigit(ch)||ch=='.') {
            fac.push_back(ch);ch=tar[i++];
        }
        fac.push_back('s');
        }
        else{
            ch1=hep.top();
            if(isp(ch1)<icp(ch)){
                hep.push(ch);ch=tar[i++];
            }
            else if(isp(ch1)>icp(ch)){
                op=hep.top();
                hep.pop();
                fac.push_back(op);
            }
            else{
                op=hep.top();
                hep.pop();
                if(op=='(') ch=tar[i++];
            }
        }
    }
    char lg;
        int j=0,sz=fac.size();
        lg=fac[j];
        while(j<sz&&lg!='='){
            if(lg=='s'){
                j++;
                lg=fac[j];
            }
            else if(lg=='+'||lg=='-'||lg=='/'||lg=='*'){
                 DoOperator(lg);j++;lg=fac[j];}
            else{
                string r;
                while(isdigit(lg)||lg=='.'){
                    r.push_back(lg);
                    j++;
                    lg=fac[j];
                }
                ans.push(help(r));
            }
        }
     if(!ans.empty()) ui->label_2->setText(QString::number(ans.top(),'g',15));
}

void MainWindow::unary_operation_pressed()
{
    QPushButton* button = (QPushButton *) sender();
    double labelnumber;
    QString input;

    if(button->text() == "+/-")
    {
        labelnumber = (ui->label->text()).toDouble();
        labelnumber *= -1;
        input = QString::number(labelnumber,'g',15);
        ui->label->setText(input);
    }

    else if(button->text() == "%")
    {
        labelnumber = (ui->label->text()).toDouble();
        labelnumber *= 0.01;
        input = QString::number(labelnumber,'g',15);
        ui->label->setText(input);
    }

    else if(button->text() == "sqrt"){
        labelnumber = (ui->label->text()).toDouble();
        labelnumber = sqrt(labelnumber);
        input = QString::number(labelnumber,'g',15);
        ui->label->setText(input);
    }

    else if(button->text() == "1/x"){
        labelnumber = (ui->label->text()).toDouble();
        labelnumber = 1/labelnumber;
        input = QString::number(labelnumber,'g',15);
        ui->label->setText(input);
    }

}

void MainWindow::binary_operation_pressed(){
    QPushButton* button = (QPushButton*) sender();
    if(button->text()=="×") ui->label->setText(ui->label->text()+"*");
    else if(button->text()=="÷") ui->label->setText(ui->label->text()+"/");
    else ui->label->setText(ui->label->text()+button->text());
}

int MainWindow::isp(char ch){
    switch(ch){
            case '(':return 1;
            case '*':case '/':case '%':
                return 5;
            case '+':case '-':
                return 3;
            case ')':return 6;
            case '=':return 0;
        }
}

int MainWindow::icp(char ch){
    switch(ch){
            case '(':return 6;
            case '*':case '/':case '%':
                return 4;
            case '+':case '-':
                return 2;
            case ')':return 1;
            case '=':return 0;
        }
}


double MainWindow::help(string a){
    double v;
    stringstream ss;
    ss<<a;
    ss>>v;
    return v;
}

void MainWindow::DoOperator(char op){
    double left,right,value;
        bool result;
        result=Get2Operands(left,right);
        if(result==true){
            switch(op){
                case '+':value=left+right;ans.push(value);break;
                case '-':value=left-right;ans.push(value);break;
                case '*':value=left*right;ans.push(value);break;
                case '/':if(right==0.0){
                    ui->label->setText("不能除以0！");
                    Clear();
                }
                else {value=left/right;ans.push(value);}
                break;
            }
        }
        else Clear();
}

void MainWindow::Clear(){
    hep.push('=');
    stack<double>().swap(ans);
}

bool MainWindow::Get2Operands(double& left,double& right){
    if(ans.empty()){
            ui->label->setText("缺少右操作数！");
            return false;
        }
        right=ans.top();
        ans.pop();
        if(ans.empty()){
            ui->label->setText("缺少左操作数！");
            return false;
        }
        left=ans.top();
        ans.pop();
        return true;
}


