#include <iostream>

#include "triangle.h"
#include "quadrangle.h"

int main()
{
  try
  {
    ArbitraryTriangle at;
    at.print_info();
    ArbitraryQuadrangle aq;
    aq.print_info();
    Rhombus ro;
    ro.print_info();

  }
  catch (const FigureErrorCheck& ex)
  {
    std::cerr << ex.what() << std::endl;
  }
    return 0;
}