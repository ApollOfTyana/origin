#include <iostream>

#include "triangle.h"
#include "quadrangle.h"

using namespace std;

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
};