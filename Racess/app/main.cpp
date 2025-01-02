#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "race.h"

#ifdef _WIN32
  #include <Windows.h>
#endif

int main()
{
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif
  
  int game = 1;
  while(game==1)
  {
    Race r;
  
    r.startRace();

    std::cout << "\n1. Провести еще одну гонку\n2. Выйти\nВыберите действие:";
    std::cin >> game;
  }
  return 0;

}

