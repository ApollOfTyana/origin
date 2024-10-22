#include <iomanip>
#include <iostream>
#include <fstream>

using  namespace std;

class Calculator{
    public:
    double num1;
    double num2;

    bool set_num1(double num1)
    {
        if( num1 != 0)
        {
            this-> num1 = num1; 
            return true;
        }
        else
        {
            cout<< "Неверный ввод!" <<endl;
            return false; 
        }   
    };
    bool set_num2(double num2)
    {
        if( num2 != 0)
        {
            this-> num2 = num2; 
            return true;
        }
        else
        {
            cout<< "Неверный ввод!" <<endl;
            return false; 
        }   
    };

    Calculator()
    {
        do{
            cout<< "Введите num1: " <<endl;
            cin >> num1;
        }while(!set_num1(num1));
        do{
            cout<< "Введите num2: " <<endl;
            cin >> num2;
        }while(!set_num2(num2));

    }


    double add(){
        return num1 + num2;
    };
    double multiply(){
        return num1 * num2;
    };
    double subtract_1_2(){
        return num1 - num2;
    };
    double subtract_2_1(){
        return num2 - num1;
    };
    double devide_1_2(){
        return num1 / num2;
    };
    double devide_2_1(){
        return num2 / num1;
    };

};

int main(int argc, char** argv){

    cout << "\t\t\t\t Задание 1 \n\n";

    while(true)
    {
        Calculator cl;
        cout << "num1 + num2 = " << cl.add() << endl;
        cout << "num1 * num2 = " << cl.multiply() << endl;
        cout << "num1 - num2 = " << cl.subtract_1_2() << endl;
        cout << "num2 - num1 = " << cl.subtract_2_1() << endl;
        cout << "num1 / num2 = " << cl.devide_1_2() << endl;
        cout << "num2 / num1 = " << cl.devide_2_1() << endl;
    }

  return 0;
}