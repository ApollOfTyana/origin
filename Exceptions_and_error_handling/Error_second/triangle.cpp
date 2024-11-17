#include "triangle.h"

void ArbitraryTriangle::print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
};

void RightTriangle:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
};

void IsoscelesTriangle:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
};

void EquilateralTriangle:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
};
