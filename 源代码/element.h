#ifndef ELEMENT_H
#define ELEMENT_H
//�� 0 ��ʼ���� �ֱ�Ϊ�� �����š������š��ӡ������ˡ���
enum operation_type { left_parentheses, right_parentheses, add, subtraction, multiplication, division};
//����Ԫ�����ͣ����ֺͲ���
enum element_type {number, operation};

class Number
{
private:
    //������ʵ�����鲿
    double a, b;
public:
	/*element_type get_basic_type()
	{
		return element_type(element_type::number);
	}*/
    //��дa
	double get_a();
	void set_a(double);

    //��дb
	double get_b();
	void set_b(double);

    //���캯��
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
    //��д��������
	operation_type get_type();
	void set_type(operation_type);
	void set_type(int);

    //���캯��
	Operation(int = 0);
	Operation(operation_type);
};

//Element �̳��� Number Operation
class Element: public Number, public Operation
{
private:
    //false ��ʾ��������֣�true ��ʾ����ǲ���
	element_type basic_type;

public:
    //��д��������
	element_type get_basic_type();
	void set_basic_type(element_type);
	
	Element(double,double);
	Element(operation_type);

	Element(Number);
	Element(Operation);
};


#endif
