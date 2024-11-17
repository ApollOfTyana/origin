#include <iostream>
#include <stdexcept>

int len_strRusEng(const std::string& str)
{
    int count = 0;
    for (auto i = str.begin(); i != str.end(); ++i)
    {
        if ((*i & 0xC0) != 0x80)
            ++count;
    }
    return count;
}

int function(const std::string& str, int forbidden_length)
{
  if (len_strRusEng(str) == forbidden_length)
    throw std::runtime_error("Error::lengthLimit_sttring");
  
  return static_cast<int>(len_strRusEng(str));
}

int main()
{
  int forbidden_length = 0;
  
  std::cout << "Введите запретную длину: ";
  std::cin >> forbidden_length;

  while (true)
  {
    std::string input;
    std::cout << "Введите слово: ";
    std::cin >> input;
    
    try
    {
      int len = function(input, forbidden_length);
      
      std::cout << "Длина слова \"" << input << "\" равна " << len << std::endl;
    }
    catch (const std::runtime_error& error)
    {
      if (error.what() == std::string("Error::lengthLimit_sttring"))
      std::cout << "Вы ввели слово запретной длины! До свидания\n";
      break;
    }
  }
    return 0;
}