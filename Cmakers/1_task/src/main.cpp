#include <iostream>
#include <string>

int input_name(std::string& name)
{
  std::cout << "Введите имя: ";
  std::cin >> name;
  std::cout << "Здравствуйте, " << name << "!" << std::endl;
  return 0;
}

int main()
{
  std::string name;
  input_name(name);
  return 0;
}