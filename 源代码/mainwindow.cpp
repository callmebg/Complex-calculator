#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>
#include "calculator.h"

std::string expression = "";
bool ans_mode = 1;
std::string my_ans = "";
std::string my_anss = "";

int parentheses_num = 0;         //左右括号总数


std::string my_to_string(std::string t);

calculator mycalculator;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->change,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));

    connect(ui->pushButton_angle,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_j,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_multi,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));

    connect(ui->pushButton_change,SIGNAL(clicked()),this,SLOT(ClickChangeAnsButton()));

    connect(ui->pushButton_ac,SIGNAL(clicked()),this,SLOT(ClickACButton()));
    connect(ui->pushButton_delete,SIGNAL(clicked()),this,SLOT(ClickDeleteButton()));
    connect(ui->pushButton_output,SIGNAL(clicked()),this,SLOT(ClickGetAnsButton()));

    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_e,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_left,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_pai,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));
    connect(ui->pushButton_right,SIGNAL(clicked()),this,SLOT(ClickChangeButton()));


    connect(ui->pushButton_about,SIGNAL(clicked()),this,SLOT(ClickAboutButton()));

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClickAboutButton()
{
    QString dlgTitle = "about";
    QString strInfo = "1.There are two ways to express complex numbers.\n 1.1 Cartesian coordinates: a+jb (a and b are real number, j is imaginary number symbol)\n 1.2 Polar coordinates: a<b (a is amplitude, b is phase(unit: °) )\n 2.This program was developed by Wang Congbiao.";
    QMessageBox::about(this, dlgTitle, strInfo);
}

void MainWindow::ClickChangeButton()
{
    // 获取发送信号的对象存放到 QObject 基类对象中
    QObject* obj = sender();
    // 把基类对象强制转换成子类对象
    QPushButton* button = dynamic_cast<QPushButton*>(obj);
    // 获取子类对象文本可以判断出是点了哪个按钮

    std::string last_op = "";   //上一个操作

    std::string t = my_to_string(button->objectName().toStdString());

    //判断当前表达式是不是为空
    if(expression == "")
    {
        //不能开头的字符
        if(t[0] == '+' || t[0] == '*' || t[0] == '/' || t[0] == '.' || t[0] == ')' || t[0] == '<')
        {
            return;
        }
    }
    else
    {
        //保存这次的操作
        last_op = expression[expression.length() - 1];
    }

    //单纯的判断上一个字符不能接啥
    if(last_op[0] >= '0' && last_op[0] <= '9')
    {
        if(t[0] == '(' || t[0] == 'j' || t == "2.718281828459" || t == "3.1415926535898")
        {
            return;
        }
    }
    else if(last_op[0] == '.')
    {
        if(t[0] < '0' || t[0] > '9')
        {
            return;
        }
    }
    else if(last_op[0] == 'j')
    {
        if(t[0] == '-')
        {
            //ok
        }
        else if(t[0] < '0' || t[0] > '9')
        {
            return;
        }

    }
    else if(last_op[0] == '(')
    {
        if(t[0] == '<' || t[0] == '+' || t[0] == '*' || t[0] == '/')
        {
            return;
        }
    }
    else if(last_op[0] == ')')
    {
        if(t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/' || t[0] == ')')
        {
            //ok
        }
        else
        {
            return;
        }
    }
    else if(last_op[0] == '<')
    {
        if(t[0] >= '0' && t[0] <= '9' || t[0] == '-')
        {
            //ok
        }
        else
        {
            return;
        }
    }
    else if(last_op[0] == '+' || last_op[0] == '*' || last_op[0] == '/')
    {
        if(t[0] == '+' || t[0] == '*' || t[0] == '/' || t[0] == '.' || t[0] == ')' || t[0] == '<')
        {
            return;
        }
    }
    else if(last_op[0] == '-')
    {
        if(t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/' || t[0] == '.' || t[0] == ')' || t[0] == '<')
        {
            return;
        }
    }


    //括号要闭合
    if(t[0] == ')')
    {
        if(parentheses_num <= 0) t = "";
        else    parentheses_num--;
    }
    else if(t[0] == '(')
    {
        if(last_op == "j" || last_op == "<")
        {
            t = "";
        }
        else
        {
             parentheses_num++;
        }

    }

    //防止一个数有两个小数点
    if(t[0] == '.')
    {
        int i;
        for(i = expression.length() - 1; i > 0 && expression[i] >= '0' && expression[i] <= '9'; i--);
        if(expression[i] == '.')
        {
            return;
        }
    }

    //构造一个表达式
    expression = expression + t;
    //把表达式放入输入框
    ui->textBrowser_input->setText(QString::fromStdString(expression));
}

void MainWindow::ClickChangeAnsButton()
{
    //改变输出答案的格式
    ans_mode = !ans_mode;

    if(ans_mode)
    {
        //当ans_mode为真时，输出a+jb 直角坐标形式
        ui->label_output->setText(QString::fromStdString(my_ans));
    }
    else
    {
        //当ans_mode为假时，输出a<b 极坐标形式
        ui->label_output->setText(QString::fromStdString(my_anss));
    }
}

void MainWindow::ClickDeleteButton()
{
    //删除最后一个字符
    expression = expression.substr(0, expression.length()-1);
    ui->textBrowser_input->setText(QString::fromStdString(expression));
}

void MainWindow::ClickACButton()
{
    //清除所有字符
    parentheses_num = 0;

    expression = "";
    ui->textBrowser_input->setText(QString::fromStdString(expression));
}

void MainWindow::ClickGetAnsButton()
{
    //如果括号不闭合
    if(parentheses_num != 0)
    {
        ui->label_output->setText(QString::fromStdString("Unclosed parentheses "));
        return;
    }

    //以防万一，先清空计算器
    mycalculator.clear();
    //再传入字符串
    mycalculator.set(expression);
    //开始计算
    mycalculator.calculate();

    //得到答案
    my_ans = mycalculator.ans_string(0);    //直角坐标
    my_anss = mycalculator.ans_string(1);   //极坐标

    //出现语法错误
    if(my_ans == "-nan(ind)+j-nan(ind)")
    {
        my_ans = "Grammatical errors ";
        my_anss = "Grammatical errors ";
    }

    //按照当前指定模式输出
    if(ans_mode)
    {
        ui->label_output->setText(QString::fromStdString(my_ans));
    }
    else
    {
        ui->label_output->setText(QString::fromStdString(my_anss));
    }

    //将本次计算放入历史栏
    ui->textBrowser_history->append(QString::fromStdString(expression));
    ui->textBrowser_history->append( "=  " + QString::fromStdString(my_ans));
}

std::string my_to_string(std::string t)
{
    //按照按钮名字来判断输入
    std::string tans = "";
    if(t == "pushButton_add")    tans = '+';
    else if(t == "pushButton_sub")   tans = '-';
    else if(t == "pushButton_multi")   tans = '*';
    else if(t == "pushButton_div")   tans = '/';
    else if(t == "pushButton_dot")   tans = '.';
    else if(t == "pushButton_e")   tans = "2.718281828459";
    else if(t == "pushButton_left")   tans = '(';
    else if(t == "pushButton_pai")   tans = "3.1415926535898";
    else if(t == "pushButton_right")   tans = ')';
    else if(t == "pushButton_angle")    tans = "<";
    else    tans = t[11];
    return tans;
}


