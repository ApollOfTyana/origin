#include <iostream>
#include "math_operation.h"
#include "counter.h"

#include "triangle.h"
#include "quadrangle.h"

using namespace std;

int main(int argc, char** argv){

    cout << "\t\t\tЗАДАНИЕ №3\n\n" <<endl;
    
    Figure fi;
    fi.print_info();
    
    Triangle tr;
    tr.print_info();
    Quadrangle qa;
    qa.print_info();
    
    ArbitraryTriangle at;
    at.print_info();
    RightTriangle rt;
    rt.print_info();
    IsoscelesTriangle it;
    it.print_info();
    EquilateralTriangle et;
    et.print_info();

    ArbitraryQuadrangle aq;
    aq.print_info();
    Rectangle re;
    re.print_info();
    Square sq;
    sq.print_info();
    Parallelogram p;
    p.print_info();
    Rhombus ro;
    ro.print_info();

    cout << "\t\t\tЗАДАНИЕ №1\n\n" <<endl;
       
    int a = 0;
    int b = 0;

    int chooce=0;

    cout << "Введите первое число:";
    cin >> a;
     cout << "Введите второе число:";
    cin >> b;
    cout << "Выберите операцию(1 - сложение, 2 вычетание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    cin >> chooce;

    switch (chooce)
    {
    case 1:
        cout << a << " плюс " << b << " = " << accum(a,b) << endl;
        break;
    case 2:
        cout << a << " минус " << b << " = " << subtraction(a,b) << endl;
        break;
    case 3:
        cout << a << " умножить на " << b << " = " << multiplication(a,b) << endl;
        break;
    case 4:
        cout << a << " раздеть на " << b << " = " << division(a,b) << endl;
        break;
    case 5:
        cout << a << " в степени " << b << " = " << exp(a,b) << endl;
        break;
    
    default:
        break;
    }

    cout << "\t\t\tЗАДАНИЕ №2\n\n" <<endl;

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::string answer;
    cin >> answer;

    Counter s;
    if (answer == "да") {
        cout << "Введите начальное значение счётчика: ";
        int value;
        cin >> value;
        s = Counter(value);
    }

    char cmd;
    do {
        std::cout << "\nВведите команду ('+', '-', '=' или 'x'): ";
        std::cin >> cmd;

        switch(cmd) {
            case '+':
                s.up();
                break;
            case '-':
                s.dwn();
                break;
            case '=':
                cout << s.getValue() << endl;
                break;
            case 'x':
                cout << "До свидания!" << endl;
                break;
            default:
                cout << "Неверная команда." << std::endl;
                break;
        }
    } while (cmd != 'x');
    
    return 0;
};