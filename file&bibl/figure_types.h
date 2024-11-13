#pragma once

#include "figure_base.h"

class Triangle: public Figure {
  public:
  Triangle(): Figure("Треугольник",3){ };

  protected:
  Triangle(float aLen, float bLen, float cLen, float Adeg, float Bdeg, float Cdeg){
    degAccum= Adeg + Bdeg + Cdeg;
    set_countSides((int)(aLen>0) + (int)(bLen>0) + (int)(cLen>0));
    check_count_side = get_countSides() == 3;
    check_deg_accum = degAccum == 180.0;
  };
};

class Quadrangle: public Figure {
  public:
  Quadrangle(): Figure("Четырёхугольник",4){ };

  protected:
  Quadrangle(float aLen, float bLen, float cLen, float dLen, float Adeg, float Bdeg, float Cdeg, float Ddeg)
  {
    degAccum = Adeg + Bdeg + Cdeg + Ddeg;
    set_countSides((int)(aLen>0) + (int)(bLen>0) + (int)(cLen>0) + (int)(dLen>0));

    check_count_side = get_countSides() == 4;
    check_deg_accum = degAccum == 360.0;
  };
};