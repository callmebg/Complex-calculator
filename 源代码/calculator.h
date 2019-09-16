#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "element.h"
#include <string>
#include <stack>
#include <vector> 
using namespace std;


class calculator
{
    //static const int MAX_NUM = 10086;
    //假设最多100086个操作数或操作符

private:
    //各运算符优先级
    static const int priority[6];

    //原始字符串
    string original_string;

    //下标[0,element_num)middel_order_expression[MAX_NUM];	//中序表达式
    vector<Element> all_element;

    //先序表达式
    vector<Element> preorder_expression;

    //有多少个元素
    int element_num;
    //先序表达式有多少个元素
    int p_o_e_num;


    //转换过程所需的栈
	stack<Element> mystack;
	
    //该计算式的答案
    Number ans;

    //得到先序表达式
    void get_p_o_e();

    //得到以i为开头的数字，处理完成后i指向数字最后一位,bool == true => 正數
    Number get_num(int &i, string &,bool);

public:
    //默认构造函数
    calculator();

    //接受一个计算表达式并保存为中序表达式,如果表达式有语法错误，则返回false
    bool set(string);

    //打印计算表达式(0 为原字符串，1为中序, 2为前序)
    string all_string(int);

    //开始计算
    void calculate();

    //得到答案 0直角坐标 1 极坐标
    string ans_string(int );

    //清除上次运算
    void clear();

    //将元素转换成字符串
    string element_to_string(Element);

    //比较元素的优先级
	bool Greater_than_equal_to_or_equal_to(Element , Element );
};

#endif // !CALCULATOR_H

