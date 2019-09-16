#include<cmath>
#include<string>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<cmath>
#include"calculator.h"
#include<algorithm>
using namespace std;

//各个运算的优先级
const int calculator::priority[6] = { 666,666,0,0,1,1 };
const double pai = acos(-1);
const double e = exp(1);

Number calculator::get_num(int &i, string &t, bool sign)
{
    Number tnum;
    double tsum = 0;
    if (t[i] >= '0'&&t[i] <= '9' || t[i] == 'e')
    {
        if(t[i] == 'e')
        {
            tsum = e;
            i++;
        }
        else
        {
            int p1 = 10;	//整数部分的权
            double p2 = 0.1;//小数部分的权
            do
            {
                tsum = tsum * p1 + t[i] - '0';
                i++;
            } while (t[i] >= '0'&&t[i] <= '9');
            if (t[i] == '.')
            {
                i++;
                do
                {
                    tsum = tsum + (t[i] - '0')*p2;
                    p2 *= 0.1;
                    i++;
                } while (t[i] >= '0'&&t[i] <= '9');
            }
        }


        if (!sign)	tsum = -tsum;

        //角度制
        if(t[i] == '<')
        {
            i++;
            double t_tsum = 0;
            int t_sign = 1;
            if(t[i] == '-')
            {
                i++;
                t_sign = -1;
            }

            if(t[i] == 'e')
            {
                t_tsum = e;
                i++;
            }
            else
            {
                int t_p1 = 10;	//整数部分的权
                double t_p2 = 0.1;//小数部分的权
                do
                {
                    t_tsum = t_tsum * t_p1 + t[i] - '0';
                    i++;
                } while (t[i] >= '0'&&t[i] <= '9');
                if (t[i] == '.')
                {
                    i++;
                    do
                    {
                        t_tsum = t_tsum + (t[i] - '0')*t_p2;
                        t_p2 *= 0.1;
                        i++;
                    } while (t[i] >= '0'&&t[i] <= '9');
                }
            }

            tnum.set_a(tsum * cos(t_sign * t_tsum * pai / 180));
            tnum.set_b(tsum * sin(t_sign * t_tsum * pai / 180));
        }
        else
        {
            tnum.set_a(tsum);
        }

        i--;
        //cout << i <<" is "<< all_element[element_num].a << 'j' << all_element[element_num].b << endl;
    }

    //处理虚数
    else
    {
        i++;

        //j 后面跟一个负数
        int t_sign = 1;
        if(t[i] == '-')
        {
            i++;
            t_sign = -1;
        }
        if(t[i] == 'e')
        {
            tsum = e;
            i++;
        }
        else if(t[i] >= '0' && t[i] <= '9')
        {
            int p1 = 10;	//整数部分的权
            double p2 = 0.1;//小数部分的权
            do
            {
                tsum = tsum * p1 + t[i] - '0';
                i++;
            } while (t[i] >= '0'&&t[i] <= '9');
            if (t[i] == '.')
            {
                i++;
                do
                {
                    tsum = tsum + (t[i] - '0')*p2;
                    p2 *= 0.1;
                    i++;
                 } while (t[i] >= '0'&&t[i] <= '9');
            }
        }
        //单独一个j
        else
        {
            tsum = 1;
        }
        if (!sign)	tsum = -tsum;
        tnum.set_b(tsum * t_sign);
        i--;
        //cout << "now b is " << tsum << endl;
        //cout << "now b is " << tnum.get_b() << endl;
    }
    return tnum;
}

bool calculator::set(string t)
{
    original_string = t;
    int amazing = 0;	//括号数
    int tl = int(t.length());
    //cout << tl << endl;
    //依次处理字符
    for (int i = 0; i < tl; i++)
    {
        //处理完一个元素后，i 指向元素末尾
        //大胆地把一个复数拆成一个实数加一个纯虚数

        //负数 （当负号前面是一个操作（非右括号非j）,并且后面是一个数字时，既判定为负数）
        if (t[i] == '-'
                       && (i==0 || (t[i - 1] == '+' || t[i - 1] == '-' || t[i-1] == '*' || t[i-1] == '/' || t[i-1] == '(') )
                       && ((t[i + 1] >= '0' && t[i + 1] <= '9') || t[i + 1] == 'j' || t[i + 1] == 'e')
            )
        {
            i++;
            all_element.push_back(Element(get_num(i, t, false)));
            //cout<<all_element[0].get_a();
        }

        //处理非负实数
        else if ((t[i] >= '0'&&t[i] <= '9') || (t[i] == 'j') || t[i] == 'e')
        {
            all_element.push_back(Element(get_num(i, t, true)));
        }

        //处理其他操作
        else
        {
            int op_type;
            switch (t[i])
            {
            case '(':
                op_type = 0;
                amazing++;
                break;
            /*case '（':
                op_type = 0;
                amazing++;
                break;*/
            case ')':
                op_type = 1;
                amazing++;
                break;
            /*case '）':
                op_type = 1;
                amazing++;
                break;*/
            case '+':
                op_type = 2;
                break;
            case '-':
                op_type = 3;
                break;
            case '*':
                op_type = 4;
                break;
            case '/':
                op_type = 5;
                break;
            default:
                return false;
                break;
            }
            all_element.push_back(Operation(op_type));
            //cout << op_type << endl;
        }

        //显然，现在的元素数量要加一个了
        element_num++;
    }
    p_o_e_num = element_num - amazing;
    //得到中序表达式

    //得到先序表达式
    get_p_o_e();

    //cout << "set is ok" << endl;
    return true;
}

string calculator::element_to_string(Element t)
{
    if (t.get_basic_type() == element_type::operation)
    {
        string op_type;
        switch (t.get_type())
        {
        case 0:
            op_type = '(';
            break;
        case 1:
            op_type = ')';
            break;
        case 2:
            op_type = '+';
            break;
        case 3:
            op_type = '-';
            break;
        case 4:
            op_type = '*';
            break;
        case 5:
            op_type = '/';
            break;
        default:
            cout << "what? " << t.get_type() << endl;
            break;
        }
        return op_type;
    }
    //未实现精度问题
    string tans = "";

    if (t.get_a() != 0)
    {
        tans += to_string(t.get_a());
        if (t.get_b() != 0)
        {
            if(t.get_b() < 0)
            {
                tans += "-j";
                tans += to_string(-t.get_b());
            }
            else
            {
                tans += "+j";
                tans += to_string(t.get_b());
            }
        }
    }
    else
    {
        if (t.get_b() != 0)
        {
            if(t.get_b() < 0)
            {
                tans += "-j";
                tans += to_string(-t.get_b());
            }
            else
            {
                tans += "+j";
                tans += to_string(t.get_b());
            }
        }
        else
        {
            tans = "0";
        }
    }
    //cout << "be " <<tans << endl;
    return tans;
}

string calculator::all_string(int choice)
{
    if (choice == 0)	return original_string;
    else if (choice == 1)
    {
        string ans = "";
        for (std::vector<Element>::iterator it = all_element.begin(); it != all_element.end(); it++)
        {
            ans += element_to_string(*it);
        }
        return ans;
    }
    else
    {
        string ans = "";
        for (std::vector<Element>::iterator it = preorder_expression.begin(); it != preorder_expression.end(); it++)
        {
            ans += element_to_string(*it);
        }
        return ans;
    }
}

void calculator::calculate()
{
    //计算会改变前序表达式和所有元素，所以在计算完在查看元素或表达式就会得到错误结果
    for (int i = p_o_e_num - 1; i >= 0; i--)
    {
        double ttt;
        double a1, a2, b1, b2;

        if (preorder_expression[i].get_basic_type() == element_type::operation)
        {
            preorder_expression[i].set_basic_type(element_type::number);	//这个操作的结果存在这
            //下面的式子写的长了一点
            switch (preorder_expression[i].get_type())
            {
            case 2:				// +
                a1 = mystack.top().get_a();
                b1 = mystack.top().get_b();
                mystack.pop();
                a2 = mystack.top().get_a();
                b2 = mystack.top().get_b();
                mystack.pop();

                preorder_expression[i].set_a(a1 + a2);
                preorder_expression[i].set_b(b1 + b2);
                break;
            case 3:				// -
                a1 = mystack.top().get_a();
                b1 = mystack.top().get_b();
                mystack.pop();
                a2 = mystack.top().get_a();
                b2 = mystack.top().get_b();
                mystack.pop();

                preorder_expression[i].set_a(a1 - a2);
                preorder_expression[i].set_b(b1 - b2);
                break;
            case 4:				// *
                a1 = mystack.top().get_a();
                b1 = mystack.top().get_b();
                mystack.pop();
                a2 = mystack.top().get_a();
                b2 = mystack.top().get_b();
                mystack.pop();

                preorder_expression[i].set_a(a1 * a2 - b1 * b2);
                preorder_expression[i].set_b(b1 * a2 + a1 * b2);

                break;
            case 5:				// /
                a1 = mystack.top().get_a();
                b1 = mystack.top().get_b();
                mystack.pop();
                a2 = mystack.top().get_a();
                b2 = mystack.top().get_b();
                mystack.pop();

                ttt = a2 * a2 + b2 * b2;

                preorder_expression[i].set_a((a1 * a2 + b1 * b2) / ttt);
                preorder_expression[i].set_b((b1 * a2 - a1 * b2) / ttt);

                break;
            default:
                //cout << "见鬼了" << endl;
                return;
                break;
            }
        }
        mystack.push(preorder_expression[i]);
        /*
        look look stack
        cout << stack_num << endl;
        cout << all_element[stack[3]].a << " + j " << all_element[stack[3]].b << endl;
        cout << all_element[stack[2]].a << " + j " << all_element[stack[2]].b << endl;
        cout << all_element[stack[1]].a << " + j " << all_element[stack[1]].b << endl;
        */
    }

    ans = preorder_expression[0];
}

calculator::calculator(void)
{
    clear();
}

string calculator::ans_string(int t)
{
    string tans = "";
    if (t == 0)
    {
        tans = element_to_string(ans);
        return tans;
    }
    else
    {
        tans += to_string(sqrt(ans.get_a()*ans.get_a() + ans.get_b()*ans.get_b()));
        tans += " <";
        tans += to_string(atan2(ans.get_b(), ans.get_a()) * 180 / acos(-1));
        tans += "°";
    }
    return tans;

    //角度制
    //cout << "角度制为： " << sqrt(ans.a*ans.a + ans.b*ans.b);
    //cout << '<' << atan2(ans.b, ans.a) * 180 / acos(-1) << endl;
}

void calculator::clear()
{
    original_string = "";
    element_num = 0;
    p_o_e_num = 0;
    ans = Number(0, 0);
    all_element.clear();
    preorder_expression.clear();
    while (!mystack.empty())
        mystack.pop();
}

void calculator::get_p_o_e()
{
    //cout << "there is g_p_o_e begin" << endl;
    /*
    Code highlighting produced by Actipro CodeHighlighter (freeware)
    http://www.CodeHighlighter.com/-->
    中序表达式转前序表达式步骤
    1、反转输入字符串，如“2*3/(2-1)+3*(4-1)” 反转后为“ )1-4(*3+)1-2(/3*2”，
    2、从字符串中取出下一个字符
        2.1.如果是操作数，则直接输出
        2.2.如果是“)”，压入栈中
        2.3.如果是运算符但不是“(”，“)”,则不断循环进行以下处理
            2.3.1.如果栈为空，则此运算符进栈，结束此步骤
            2.3.2.如果栈顶是“)”,则此运算符进栈，结束此步骤
            2.3.2.如果此运算符与栈顶优先级相同或者更高，此运算符进栈，结束此步骤
            2.3.4.否则，运算符连续出栈，直到满足上述三个条件之一，然后此运算符进栈
        2.4、如果是“(”，则运算符连续出栈，直到遇见“)”为止,将“)”出栈且丢弃之
    3、如果还有更多的字符串，则转到第2步
    4、不在有未处理的字符串了，输出栈中剩余元素
    5、再次反转字符串得到最终结果
    */
    int t = 0;	//放先序表达式的位置
    for (int i = element_num - 1; i >= 0; i--)
    {
        //cout << "hfkjdsahfkjdashf" <<int(all_element[i].get_basic_type()) << endl;
        if (all_element[i].get_basic_type() == element_type::number)
        {
            //cout << "this is a num" << endl;
            preorder_expression.push_back(all_element[i]);
            t++;
        }
        else if (all_element[i].get_type() == 1)	// ）
        {
            mystack.push(all_element[i]);
        }
        else if (all_element[i].get_type() != 0)
        {
            while (1)
            {
                if (mystack.empty())
                {
                    mystack.push(all_element[i]);
                    break;
                }
                else if (mystack.top().get_type() == 1)
                {
                    mystack.push(all_element[i]);
                    break;
                }
                else if (Greater_than_equal_to_or_equal_to(all_element[i], mystack.top()))
                {
                    mystack.push(all_element[i]);
                    break;
                }
                else
                {
                    preorder_expression.push_back(mystack.top());
                    mystack.pop();
                    t++;
                }
            }
        }
        else
        {
            while (!mystack.empty() && mystack.top().get_type() != operation_type::right_parentheses)
            {
                preorder_expression.push_back(mystack.top());
                mystack.pop();
                t++;	//原本是preorder_expression【t】，现在没用了
            }
            mystack.pop();
        }
    }
    while (!mystack.empty())
    {
        preorder_expression.push_back(mystack.top());
        mystack.pop();
        t++;
    }
    /*int temp;
    for (int i = 0; i <= (p_o_e_num - 1) / 2; i++)
    {
        temp = preorder_expression[i];
        preorder_expression[i] = preorder_expression[p_o_e_num - 1 - i];
        preorder_expression[p_o_e_num - 1 - i] = temp;
    }*/

    reverse(preorder_expression.begin(), preorder_expression.end());
}

bool calculator::Greater_than_equal_to_or_equal_to(Element a, Element b)
{
    if (a.get_basic_type() == element_type::number)
    {
        return sqrt(a.get_a()*a.get_a() + a.get_b()*a.get_b()) >= sqrt(b.get_a()*b.get_a() + b.get_b()*b.get_b());
    }
    else
    {
        return priority[a.get_type()] >= priority[b.get_type()];
    }
}
