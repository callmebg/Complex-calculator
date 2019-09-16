#ifndef ELEMENT_H
#define ELEMENT_H
//从 0 开始定义 分别为： 左括号、右括号、加、减、乘、除
enum operation_type { left_parentheses, right_parentheses, add, subtraction, multiplication, division};
//两种元素类型，数字和操作
enum element_type {number, operation};

class Number
{
private:
    //复数的实部和虚部
    double a, b;
public:
	/*element_type get_basic_type()
	{
		return element_type(element_type::number);
	}*/
    //读写a
	double get_a();
	void set_a(double);

    //读写b
	double get_b();
	void set_b(double);

    //构造函数
	Number(double, double);
	Number();
};

class Operation
{
private:
	operation_type type;
public:
	/*element_type get_basic_type()
	{
		return element_type(element_type::operation);
	}*/
    //读写操作类型
	operation_type get_type();
	void set_type(operation_type);
	void set_type(int);

    //构造函数
	Operation(int = 0);
	Operation(operation_type);
};

//Element 继承自 Number Operation
class Element: public Number, public Operation
{
private:
    //false 表示这个是数字，true 表示这个是操作
	element_type basic_type;

public:
    //读写基本类型
	element_type get_basic_type();
	void set_basic_type(element_type);
	
	Element(double,double);
	Element(operation_type);

	Element(Number);
	Element(Operation);
};


#endif
