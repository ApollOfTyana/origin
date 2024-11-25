#include <iostream>
#include <stdexcept>


#include "extended_array.h"
#include "test.h"

int main()
{
  ExtArray<int> v0{};
  ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
  ExtArray<int> v2{ 0, 1, 1, 0, 0, 1, 0, 1 };

  std::cout <<"\n\t\t\tTRUE\n" <<std::endl;

  MyTestClass istina;
  istina.RunOneTest([&](){istina.test_ArrayEmpty(v0);},"Array test:\\'Empty'\\");
  istina.RunOneTest([&](){istina.test_ArrayMean(v1,1.125);},"Array test: \\'Mean'\\");                        
  std::pair<int,int> diap;
  diap.first=1;                                                                                    
  diap.second=5;
  istina.RunOneTest([&](){istina.test_ArrayMean(v1,diap,1.4);},"Array test: \\'Mean in diapason'\\");         
  istina.RunOneTest([&](){istina.test_ArrayTypeBoolInt(v2,4);},"Array test:\\'Type data,Content,Count'\\");  

  std::cout <<"\n\t\t\tERRORS\n" <<std::endl;
  
  MyTestClass loj;
  loj.RunOneTest([&](){loj.test_ArrayEmpty(v1);},"Array test:\\'Empty'\\");
  loj.RunOneTest([&](){loj.test_ArrayMean(v1,4);},"Array test: \\'Mean'\\");                            //значение 4 установлено как якобы TRUE результат
  diap.first=-1;                                                                                        //начальный диапазон указан нарочно менее 0
  diap.second=5;
  loj.RunOneTest([&](){loj.test_ArrayMean(v1,diap,4);},"Array test: \\'Mean in diapason'\\");          //значение 4 установлено как якобы TRUE результат
  diap.first=1;                                                                                        //начальный диапазон указан верно,чтобы показать другие возможные ошибки
  diap.second=5;
  loj.RunOneTest([&](){loj.test_ArrayMean(v1,diap,4);},"Array test: \\'Mean in diapason'\\");          //значение 4 установлено как якобы TRUE результат
  loj.RunOneTest([&](){loj.test_ArrayTypeBoolInt(v2,5);},"Array test:\\'Type data,Content,Count'\\");  //значение 4 установлено как якобы TRUE результат

  return 0;
}