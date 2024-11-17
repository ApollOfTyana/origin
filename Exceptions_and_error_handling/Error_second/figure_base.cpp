#include "figure_base.h"


int& Figure:: get_countSides() {return countSide; };
void Figure:: set_countSides(int cs) { countSide = cs; };
  
const std::string & Figure:: get_nameFigure() const { return nameFigure; };
 
void Figure:: print_info()
{
    cout << '\n' << get_nameFigure() << ":\n" << check_obj() << "Количество сторон: " << get_countSides() <<'\n';    
};

std::string Figure:: check_obj()
{
    std::string result;
    bool checker = check_count_side == check_deg_accum == check_individual_option;
    checker == 1 ? result.append("Правильная\n") : result.append("Неправильная\n");
    
    return result;
};

float & Figure:: get_len(const char side)
{
    switch(tolower(side))
    {
      case 'a':
        return len_a;
        break;
      case 'b':
        return len_b;
        break;
      case 'c':
        return len_c;
        break;
      case 'd':
        return len_d;
        break;
      default: 
        std::cout << "side is undefined" << "\n";
        return lenErr;
        break;
    }
};
float & Figure::set_len(const char side, float len)
{
    switch(tolower(side))
    {
      case 'a':
        len_a=len;
        return len_a;
        break;
      case 'b':
        len_b=len;
        return len_a;
        break;
      case 'c':
        len_c=len;
        return len_a;
        break;
      case 'd':
        len_d=len;
        return len_d;
        break;
      default: 
        std::cout << "side is undefined" << "\n";
        return lenErr;
        break;
    }
};

float & Figure:: get_deg(const char side)
  {
    switch(tolower(side))
    {
      case 'a':
        return deg_A;
        break;
      case 'b':
        return deg_B;
        break;
      case 'c':
        return deg_C;
        break;
      case 'd':
        return deg_D;
        break;
      default:
        std::cout << "side is undefined" << "\n";
        return degErr; 
        break;
    }
};
float & Figure::set_deg(const char side, float deg)
{
    switch(tolower(side))
    {
      case 'a':
        deg_A=deg;
        return deg_A;
        break;
      case 'b':
        deg_B=deg;
        return deg_B;
        break;
      case 'c':
        deg_C=deg;
        return deg_C;
        break;
      case 'd':
        deg_D=deg;
        return deg_D;
        break;
      default: 
        std::cout << "side is undefined" << "\n";
        return degErr;
        break;
    }
};
