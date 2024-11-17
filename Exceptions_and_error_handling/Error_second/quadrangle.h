#pragma once

#include "figure_types.h"

class ArbitraryQuadrangle: public Quadrangle {
  public:
  ArbitraryQuadrangle(): Quadrangle(set_len('a',10), set_len('b',20), set_len('c',30), set_len('d',40), set_deg('a',90), set_deg('b',90), set_deg('c',90), set_deg('d',90))
  {
    nameFigure="Четырёхугольник";
  };

  void print_info() override;
};

class Rectangle: public Quadrangle {
  protected:
    bool rectangle_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  Rectangle(): Quadrangle(set_len('a',10), set_len('b',20), set_len('c',10), set_len('d',20), set_deg('a',90), set_deg('b',90), set_deg('c',90), set_deg('d',90))
  {
    nameFigure="Прямоугольник";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('D')) && (get_deg('A')==90.0 && get_deg('B')==get_deg('A') && get_deg('C')==get_deg('A') && get_deg('D')==get_deg('A'));
    if (!rectangle_check(check_individual_option)) {
            throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы стороны a,c и b,d  были попарно равны, и все углы равны 90 градусов");
    };
  };

  void print_info() override;
};
class Square: public Quadrangle {
  protected:
    bool square_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  Square(): Quadrangle(set_len('a',10), set_len('b',10), set_len('c',10), set_len('d',10), set_deg('a',90), set_deg('b',90), set_deg('c',90), set_deg('d',90))
  {
    nameFigure="Квадрат";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('A') && get_len('C') == get_len('A') && get_len('D') == get_len('A') ) && (get_deg('A')==90.0 && get_deg('B')==get_deg('A') && get_deg('C')==get_deg('A') && get_deg('D')==get_deg('A'));
    if (!square_check(check_individual_option)) {
      throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы все стороны были равны и все углы равны 90 градусов");
    };
  };

  void print_info() override;
};

class Parallelogram: public Quadrangle {
  protected:
    bool parallelogram_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  Parallelogram(): Quadrangle(set_len('a',20), set_len('b',30), set_len('c',20), set_len('d',30), set_deg('a',100), set_deg('b',80), set_deg('c',100), set_deg('d',80))
  {
    nameFigure="Параллелограмм";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('D')) && (get_deg('A') == get_deg('C') && get_deg('B') == get_deg('D'));
    if (!parallelogram_check(check_individual_option)) {
      throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы все стороны a,c и b,d были попарно равны,а также углы A,C и B,D попарно равны");
    };
  };

  void print_info() override;

};
class Rhombus: public Quadrangle {
  protected:
    bool rhombus_check(int check_individual_option) const
    {
      if (check_individual_option==0) {
        return false;
      }
      return true;
    };

  public:
  Rhombus(): Quadrangle(set_len('a',30), set_len('b',30), set_len('c',20), set_len('d',30), set_deg('a',100), set_deg('b',80), set_deg('c',100), set_deg('d',80))
  {
    nameFigure="Ромб";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('A') && get_len('C') == get_len('A') && get_len('D') == get_len('A')) && (get_deg('A') == get_deg('C') && get_deg('B') == get_deg('D'));
    if (!rhombus_check(check_individual_option)) {
      throw FigureErrorCheck("Ошибка создания фигуры. Проверьте чтобы все стороны были равны и углы A,C и B,D попарно равны");
    };
  };

  void print_info() override;
};