#pragma once

#include "figure_types.h"

class ArbitraryTriangle: public Triangle {
  
  public:
  ArbitraryTriangle(): Triangle(set_len('a',10), set_len('b',20), set_len('c',30), set_deg('a',50), set_deg('b',60), set_deg('c',70))
  {
    nameFigure="Треугольник";
  };
  void print_info() override;
};

class RightTriangle: public Triangle {
  protected:
    bool righttriangle_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  RightTriangle(): Triangle(set_len('a',10), set_len('b',20), set_len('c',30), set_deg('a',50), set_deg('b',90), set_deg('c',90))
  {
    nameFigure="Прямоугольный треугольник";
    check_individual_option = get_deg('c') == 90.0;
    if (!righttriangle_check(check_individual_option)) {
      throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы угол C был равен 90 градусов");
    };
  };

  void print_info() override;

};
class IsoscelesTriangle: public Triangle {
  protected:
    bool isoscelestriangle_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  IsoscelesTriangle(): Triangle(set_len('a',10), set_len('b',20), set_len('c',20), set_deg('a',50), set_deg('b',80), set_deg('c',50))
  {
    nameFigure="Равнобедренный треугольник";
    check_individual_option = get_deg('a') == get_deg('c') && get_len('a') == get_len('c');
    if (!isoscelestriangle_check(check_individual_option)) {
      throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы стороны a и c были равны, углы A и C тоже равны");
    };
  };

  void print_info() override;
};

class EquilateralTriangle: public Triangle {
  protected:
    bool equilateraltriangle_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  EquilateralTriangle(): Triangle(set_len('a',30), set_len('b',30), set_len('c',30), set_deg('a',60), set_deg('b',60), set_deg('c',60))
  {
    nameFigure="Равносторонний треугольник";
    check_individual_option =  (get_len('A') == get_len('b') && get_len('b') == get_len('c')) && (get_deg('A') == 60.0 && get_deg('b') == 60.0 && get_deg('c') == 60.0);
    if (!equilateraltriangle_check(check_individual_option)) {
      throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы все стороны были равны и все углы равны 60 градусов");
    };
  };

  void print_info() override;

};