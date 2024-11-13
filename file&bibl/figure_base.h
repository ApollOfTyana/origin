#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using  namespace std;

class Figure{
  public:
  Figure(){
    nameFigure = "Фигура";
    countSide = 0;
    degAccum = 0;
    check_count_side = 1;
    check_deg_accum = 1;
    check_individual_option = 1;
  };
  
  int &get_countSides();
  void set_countSides(int cs);
  
  const std::string &get_nameFigure() const;
  
  virtual void print_info();

  std::string check_obj();

  private:
  int countSide;
  
  protected:
  std::string nameFigure;
  float len_a,len_b,len_c,len_d;
  float deg_A, deg_B, deg_C, deg_D;
  float degAccum;
  
  float degErr=1;
  float lenErr=1;

  bool check_count_side;
  bool check_deg_accum;
  bool check_individual_option;

  Figure(std::string name_figure,int count_side): countSide(count_side), nameFigure(name_figure)
  {
    check_count_side = 1;
    check_deg_accum = 1;
    check_individual_option = 1;
  };

  float &get_len(const char side);
  float &set_len(const char side, float len);

  float &get_deg(const char side);  
  float &set_deg(const char side, float deg);

};