#include <iomanip>
#include <iostream>
#include <fstream>

using  namespace std;

enum class month{
  January=1,
  February=2,
  March=3,
  April=4,
  May=5,
  June=6,
  July=7,
  August=8,
  September=9,
  October=10,
  November=11,
  December=12
};

int main(int argc, char** argv){
  
  cout << "\t\t\t Задание 1 \n";

  int chooses=1;
  string output="";
  while(chooses != 0)
  {
    cout<<"Введите номер месяца: ";
    cin >> chooses;
    month choose= static_cast<month>(chooses);
    switch(static_cast<int>(choose))
    {
        case 1: 
            std::cout << "Январь" << "\n";
            break;
        case 2: 
            std::cout << "Февраль" << "\n";
            break;
        case 3: 
            std::cout << "Март" << "\n";
            break;
        case 4: 
            std::cout << "Апрель" << "\n";
            break;
        case 5: 
            std::cout << "Май" << "\n";
            break;
        case 6: 
            std::cout << "Июнь" << "\n";
            break;
        case 7: 
            std::cout << "Июль" << "\n";
            break;
        case 8: 
            std::cout << "Август" << "\n";
            break;
        case 9: 
            std::cout << "Сентябрь" << "\n";
            break;
        case 10: 
            std::cout << "Октябрь" << "\n";
            break;
        case 11: 
            std::cout << "Ноябрь" << "\n";
            break;
        case 12: 
            std::cout << "Декабрь" << "\n";
            break;
        default: 
            chooses!=0 ? output="Неправильный номер!\n" : output="";
            cout << output;
            break;
    }
  }
  cout<<"До свидания"<<endl;

  return 0;
}

