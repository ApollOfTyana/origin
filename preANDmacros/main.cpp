#include <iomanip>
#include <iostream>
#include <fstream>

#define MODE 1

#define SUB(a,b) ((a)-(b))

#ifndef MODE
#error Check MODE ::: it's true?
#endif

int add_input();

using  namespace std;

int main(int argc, char** argv){
  #if MODE == 1
  cout << "Работаю в боевом режиме" << endl;
  add_input();
  #elif MODE == 0
  cout << "Работаю в режиме тренировки" << endl;
  //some func
  #elif MODE > 1 or MODE < 0
  cout << "Неизвестный режим. Завершение работы." << endl;  
  #endif
  
  cout << SUB(6,5) << endl;
  cout << SUB(6,5) * 2 << endl;
  cout << SUB(6,5+2) * 2 << endl;
  
  return 0;
}

int add_input()
{
  double a=0;
  double b=0;

  cout<< "Введите число 1: ";
  cin >> a;
  cout<< "Введите число 2: ";
  cin >> b;

  cout << "Результат сложения: " << a + b << endl;
  
  return 1;
};
