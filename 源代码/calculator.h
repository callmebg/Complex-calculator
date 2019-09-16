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
    //�������100086���������������

private:
    //����������ȼ�
    static const int priority[6];

    //ԭʼ�ַ���
    string original_string;

    //�±�[0,element_num)middel_order_expression[MAX_NUM];	//������ʽ
    vector<Element> all_element;

    //������ʽ
    vector<Element> preorder_expression;

    //�ж��ٸ�Ԫ��
    int element_num;
    //������ʽ�ж��ٸ�Ԫ��
    int p_o_e_num;


    //ת�����������ջ
	stack<Element> mystack;
	
    //�ü���ʽ�Ĵ�
    Number ans;

    //�õ�������ʽ
    void get_p_o_e();

    //�õ���iΪ��ͷ�����֣�������ɺ�iָ���������һλ,bool == true => ����
    Number get_num(int &i, string &,bool);

public:
    //Ĭ�Ϲ��캯��
    calculator();

    //����һ��������ʽ������Ϊ������ʽ,������ʽ���﷨�����򷵻�false
    bool set(string);

    //��ӡ������ʽ(0 Ϊԭ�ַ�����1Ϊ����, 2Ϊǰ��)
    string all_string(int);

    //��ʼ����
    void calculate();

    //�õ��� 0ֱ������ 1 ������
    string ans_string(int );

    //����ϴ�����
    void clear();

    //��Ԫ��ת�����ַ���
    string element_to_string(Element);

    //�Ƚ�Ԫ�ص����ȼ�
	bool Greater_than_equal_to_or_equal_to(Element , Element );
};

#endif // !CALCULATOR_H

