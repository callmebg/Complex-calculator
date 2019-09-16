#include"element.h"
#include<iostream>

double Number::get_a()
{
    return a;
}

void Number::set_a(double t)
{
    a = t;
}

double Number::get_b()
{
    return b;
}

void Number::set_b(double t)
{
    b = t;
}

Number::Number(double aa, double bb)
{
    a = aa;
    b = bb;
}

Number::Number()
{
    a = 0;
    b = 0;
    //std::cout << "what the fuck" << std::endl;
}

operation_type Operation::get_type()
{
    return type;
}

void Operation::set_type(operation_type t)
{
    type = t;
}
void Operation::set_type(int t)
{
    type = operation_type(t);
}

Operation::Operation(int t)
{
    set_type(t);
}
Operation::Operation(operation_type t)
{
    set_type(t);
}

element_type Element::get_basic_type()
{
    return basic_type;
}
void Element::set_basic_type(element_type t)
{
    basic_type = t;
}

Element:: Element(double aa, double bb):Number(aa, bb)
{
    set_basic_type(element_type::number);
}
Element:: Element(operation_type t):Operation(t)
{
    set_basic_type(element_type::operation);
}

Element:: Element(Number t):Number(t.get_a(), t.get_b())
{
    set_basic_type(element_type::number);
}
Element:: Element(Operation t):Operation(t.get_type())
{
    set_basic_type(element_type::operation);
}
