#include "quadrangle.h"

void ArbitraryQuadrangle::print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
};

void Rectangle:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
};

void Square:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
};

void Parallelogram:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
};

void Rhombus:: print_info()
{
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
};
