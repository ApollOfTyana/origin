#include "math_operation.h"

double accum(double First, double Second)
{
    return First+Second;
};
double subtraction(double First, double Second)
{
    return First-Second;
};
double division(double First, double Second)
{
    return First/Second;
};

double multiplication(double First, double Second)
{
    return First*Second;
};

double exp(double First, double exp)
{
    double result = First;

    double schet = 1;
    if(exp > 1)
    {
        while(schet < exp)
        {
            result = result*First;
            schet ++;
        }
    }
    else if(exp == 0)
    {
        result = 1;
    }
    else if(exp == 1)
    {
        return First;
    }
    else
        return 0;

    return result;
};
