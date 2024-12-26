#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "race.h"


int main()
{
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

