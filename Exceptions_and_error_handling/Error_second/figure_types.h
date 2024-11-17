#pragma once

#include "figure_base.h"
#include "fig_errorCheck.h"

class Triangle: public Figure {
  public:
  Triangle(): Figure("Треугольник",3){ };
  
  private:
    string check_triangle_base(int check_deg_accum, int check_count_side) const
    { 
      if (check_deg_accum==1 and check_count_side==1)
        return "OK";
      else if (check_deg_accum==0 and check_count_side==0)
        return "Ошибка создания фигуры. Причина: сумма углов не равна 180 и колличество сторон не равно 3";
      else if (check_deg_accum==0 or check_count_side==0)
      {
        if (check_deg_accum==0)
          return "Ошибка создания фигуры. Причина: сумма углов не равна 180";
        else if (check_count_side==0)
          return "Ошибка создания фигуры. Причина: колличество сторон не равно 3";
        else
          ;
      }
      else
        ;
    };

  protected:
  Triangle(float aLen, float bLen, float cLen, float Adeg, float Bdeg, float Cdeg){
    degAccum= Adeg + Bdeg + Cdeg;
    set_countSides((int)(aLen>0) + (int)(bLen>0) + (int)(cLen>0));
    check_count_side = get_countSides() == 3;
    check_deg_accum = degAccum == 180.0;

    if(check_triangle_base(check_deg_accum,check_count_side)!="OK")
    {
      throw FigureErrorCheck(check_triangle_base(check_deg_accum,check_count_side));
    }
  };
};

class Quadrangle: public Figure {
  public:
  Quadrangle(): Figure("Четырёхугольник",4){ };
  
  private:
    string check_quadrangle_base(int check_deg_accum, int check_count_side) const
    { 
      if (check_deg_accum==1 and check_count_side==1)
        return "OK";
      else if (check_deg_accum==0 and check_count_side==0)
        return "Ошибка создания фигуры. Причина: сумма углов не равна 360 и колличество сторон не равно 4";
      else if (check_deg_accum==0 or check_count_side==0)
      {
        if (check_deg_accum==0)
          return "Ошибка создания фигуры. Причина: сумма углов не равна 360";
        else if (check_count_side==0)
          return "Ошибка создания фигуры. Причина: колличество сторон не равно 4";
        else
          ;
      }
      else
        ;
    };

  protected:
  Quadrangle(float aLen, float bLen, float cLen, float dLen, float Adeg, float Bdeg, float Cdeg, float Ddeg)
  {
    degAccum = Adeg + Bdeg + Cdeg + Ddeg;
    set_countSides((int)(aLen>0) + (int)(bLen>0) + (int)(cLen>0) + (int)(dLen>0));

    check_count_side = get_countSides() == 4;
    check_deg_accum = degAccum == 360.0;

    if(check_quadrangle_base(check_deg_accum,check_count_side)!="OK")
    {
      throw FigureErrorCheck(check_quadrangle_base(check_deg_accum,check_count_side));
    }

  };
};