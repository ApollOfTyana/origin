#include <iomanip>
#include <iostream>
#include <fstream>

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
  
  int &get_countSides() {return countSide; }
  void set_countSides(int cs) { countSide = cs; }
  
  const string &get_nameFigure() const { return nameFigure; }
  
  
  virtual void print_info()
  {
    cout << '\n' << get_nameFigure() << ":\n" << check_obj() << "Количество сторон: " << get_countSides() <<'\n';    
  }

  string check_obj(){
    
    string result;
    bool checker = check_count_side == check_deg_accum == check_individual_option;
    checker == 1 ? result.append("Правильная\n") : result.append("Неправильная\n");

    return result;
  };

  private:
  int countSide;
  
  protected:
  string nameFigure;
  float len_a,len_b,len_c,len_d;
  float deg_A, deg_B, deg_C, deg_D;
  float degAccum;
  
  float degErr=1;
  float lenErr=1;

  bool check_count_side;
  bool check_deg_accum;
  bool check_individual_option;

  Figure(string name_figure,int count_side): countSide(count_side), nameFigure(name_figure)
  {
    check_count_side = 1;
    check_deg_accum = 1;
    check_individual_option = 1;
  };

  float &get_len(const char side)
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

  float &get_deg(const char side)
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
  
  float &set_len(const char side, float len)
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

  float &set_deg(const char side, float deg)
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

};

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

class ArbitraryTriangle: public Triangle {
  public:
  ArbitraryTriangle(): Triangle(set_len('a',10), set_len('b',20), set_len('c',30), set_deg('a',50), set_deg('b',60), set_deg('c',70))
  {
    nameFigure="Треугольник";
  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
  };
};
class RightTriangle: public Triangle {
  public:
  RightTriangle(): Triangle(set_len('a',10), set_len('b',20), set_len('c',30), set_deg('a',50), set_deg('b',90), set_deg('c',90))
  {
    nameFigure="Прямоугольный треугольник";
    check_individual_option = get_deg('c') == 90.0;
  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
  };

};
class IsoscelesTriangle: public Triangle {
  public:
  IsoscelesTriangle(): Triangle(set_len('a',10), set_len('b',20), set_len('c',20), set_deg('a',50), set_deg('b',80), set_deg('c',50))
  {
    nameFigure="Равнобедренный треугольник";
    check_individual_option = get_deg('a') == get_deg('c') && get_len('a') == get_len('c');
  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
  };
};
class EquilateralTriangle: public Triangle {
  public:
  EquilateralTriangle(): Triangle(set_len('a',30), set_len('b',30), set_len('c',30), set_deg('a',60), set_deg('b',60), set_deg('c',60))
  {
    nameFigure="Равносторонний треугольник";
    check_individual_option =  (get_len('A') == get_len('b') && get_len('b') == get_len('c')) && (get_deg('A') == 60.0 && get_deg('b') == 60.0 && get_deg('c') == 60.0);
  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c')<< '\n' <<endl;
  }
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

class ArbitraryQuadrangle: public Quadrangle {
  public:
  ArbitraryQuadrangle(): Quadrangle(set_len('a',10), set_len('b',20), set_len('c',30), set_len('d',40), set_deg('a',50), set_deg('b',60), set_deg('c',70), set_deg('d',80))
  {
    nameFigure="Четырёхугольник";
  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
  };
};
class Rectangle: public Quadrangle {
  public:
  Rectangle(): Quadrangle(set_len('a',10), set_len('b',20), set_len('c',10), set_len('d',20), set_deg('a',90), set_deg('b',90), set_deg('c',90), set_deg('d',90))
  {
    nameFigure="Прямоугольник";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('D')) && (get_deg('A')==90.0 && get_deg('B')==get_deg('A') && get_deg('C')==get_deg('A') && get_deg('D')==get_deg('A'));
  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
  }
};
class Square: public Quadrangle {
  public:
  Square(): Quadrangle(set_len('a',10), set_len('b',10), set_len('c',10), set_len('d',10), set_deg('a',90), set_deg('b',90), set_deg('c',90), set_deg('d',90))
  {
    nameFigure="Квадрат";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('A') && get_len('C') == get_len('A') && get_len('D') == get_len('A') ) && (get_deg('A')==90.0 && get_deg('B')==get_deg('A') && get_deg('C')==get_deg('A') && get_deg('D')==get_deg('A'));

  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
  }
};
class Parallelogram: public Quadrangle {
  public:
  Parallelogram(): Quadrangle(set_len('a',20), set_len('b',30), set_len('c',20), set_len('d',30), set_deg('a',100), set_deg('b',80), set_deg('c',100), set_deg('d',80))
  {
    nameFigure="Параллелограмм";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('D')) && (get_deg('A') == get_deg('C') && get_deg('B') == get_deg('D'));

  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
  }
};
class Rhombus: public Quadrangle {
  public:
  Rhombus(): Quadrangle(set_len('a',30), set_len('b',30), set_len('c',30), set_len('d',30), set_deg('a',100), set_deg('b',80), set_deg('c',100), set_deg('d',80))
  {
    nameFigure="Ромб";
    check_individual_option = (get_len('A') == get_len('C') && get_len('B') == get_len('A') && get_len('C') == get_len('A') && get_len('D') == get_len('A')) && (get_deg('A') == get_deg('C') && get_deg('B') == get_deg('D'));

  };

  void print_info() override
  {
    Figure:: print_info();
    cout << "Стороны: a=" << get_len('A') << " b=" << get_len('b') << " c=" << get_len('c') << " d=" << get_len('d')<<endl;
    cout << "Углы: A=" << get_deg('A') << " B=" << get_deg('b') << " C=" << get_deg('c') << " D=" << get_deg('d')<< '\n' <<endl;
  }
};

int main(int argc, char** argv){

    Figure fi;
    fi.print_info();
    
    Triangle tr;
    tr.print_info();
    Quadrangle qa;
    qa.print_info();
    
    ArbitraryTriangle at;
    at.print_info();
    RightTriangle rt;
    rt.print_info();
    IsoscelesTriangle it;
    it.print_info();
    EquilateralTriangle et;
    et.print_info();

    ArbitraryQuadrangle aq;
    aq.print_info();
    Rectangle re;
    re.print_info();
    Square sq;
    sq.print_info();
    Parallelogram p;
    p.print_info();
    Rhombus ro;
    ro.print_info();

    return 0;
}

