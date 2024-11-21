#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;

    if (denominator_ == 0)
      throw std::runtime_error("Нулевой знаменатель!");
	}
  bool operator==(Fraction other){ return method_mleq(&this->numerator_,&this->denominator_,&other.numerator_,&other.denominator_,1) == method_mleq(&this->numerator_,&this->denominator_,&other.numerator_,&other.denominator_,2); }
  bool operator!=(Fraction other){ return !(*this == other); };

  bool operator>(Fraction other){ return method_mleq(&this->numerator_,&this->denominator_,&other.numerator_,&other.denominator_,1) > method_mleq(&this->numerator_,&this->denominator_,&other.numerator_,&other.denominator_,2); }
  bool operator<(Fraction other){ return other > *this; }

  bool operator>=(Fraction other){ return !(*this < other); }
  bool operator<=(Fraction other){ return !(*this > other); }

  Fraction operator+(Fraction other){
    return Fraction(this->numerator_ * o_z(&this->numerator_, &this->denominator_, &other, 1) + other.numerator_ * o_z(&this->numerator_, &this->denominator_, &other, 2),
     o_z(&this->numerator_, &this->denominator_, &other, 1) * o_z(&this->numerator_, &this->denominator_, &other, 2));} 

  Fraction operator-(Fraction other){
    return Fraction(this->numerator_ * o_z(&this->numerator_, &this->denominator_, &other, 1) - other.numerator_ * o_z(&this->numerator_, &this->denominator_, &other, 2),
     o_z(&this->numerator_, &this->denominator_, &other, 1) * o_z(&this->numerator_, &this->denominator_, &other, 2));} 

  Fraction operator*(Fraction other){
    return Fraction((this->numerator_ * other.numerator_) / n_o_d(this->numerator_ * other.numerator_,this->denominator_ * other.denominator_),
     (this->denominator_ * other.denominator_)/ n_o_d(this->numerator_ * other.numerator_,this->denominator_ * other.denominator_));} 

  Fraction operator/(Fraction other){
    if (other.numerator_ == 0)
      throw std::runtime_error("Деление на ноль!");
    return Fraction((this->numerator_ * other.denominator_) / n_o_d(this->numerator_ * other.denominator_,this->denominator_ * other.numerator_),
     (this->denominator_ * other.numerator_)/n_o_d(this->numerator_ * other.denominator_,this->denominator_ * other.numerator_));} 
  
  Fraction operator-()
  {
        return Fraction(-numerator_, denominator_);
  }
  
  Fraction& operator++() { numerator_+= denominator_; return *this;};
  Fraction operator++(int)
  {
    Fraction temp = *this;
    ++(*this);
    return temp;
  };
  Fraction& operator--() { numerator_-= denominator_; return *this;};
  Fraction operator--(int)
  {
    Fraction temp = *this;
    --(*this);
    return temp;
  };

  int method_mleq(int *num1, int *denom1, int *num2, int *denom2, int whatReturn)
  {
    int  first = *num1 * *denom2;
    int  second = *denom1 * *num2;

    if (whatReturn == 1)
      return first;
    if (whatReturn == 2)
      return second;
  };

  int n_o_k(int denom1,int denom2) // наименьшее общее кратное
  {
    return abs(denom1 * denom2);
  }
  int o_z(int *num, int *denom, Fraction *other, int whatReturn)//приведение дробей к общему знаменателю
  {
    int on_what_mult_first = n_o_k(*denom,other->denominator_)/ *denom;
    int on_what_mult_second = n_o_k(*denom,other->denominator_)/ other->denominator_;
  
    if (whatReturn == 1)
      return on_what_mult_first;//first;
    if (whatReturn == 2)
      return on_what_mult_second;//second;
  };
  int n_o_d(int num, int denom)// наибольший общий делитель
    {
        while (denom != 0)
        {
            int temp = denom;
            denom = num % denom;
            num = temp;
        }
        return num;
    }
  
  friend std::ostream& operator<<(std::ostream& output, const Fraction& frac);
};

std::ostream& operator<<(std::ostream& output, const Fraction& frac)
{
    output << frac.numerator_ << "/" << frac.denominator_;
    return output;
};

int main()
{
	 try
   {
    int nume_1, deno_1, nume_2, deno_2;

      std::cout << "Введите числитель дроби 1: ";
      std::cin >> nume_1;
      std::cout << "Введите знаменатель дроби 1: ";
      std::cin >> deno_1;
      std::cout << "Введите числитель дроби 2: ";
      std::cin >> nume_2;
      std::cout << "Введите знаменатель дроби 2: ";
      std::cin >> deno_2;

      Fraction f1(nume_1, deno_1);
      Fraction f2(nume_2, deno_2);

      std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
      std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
      std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
      std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
      std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
      std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';

      std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;
      std::cout << f1 << " - " << f2 << " = " << f1 - f2 << std::endl;
      std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl;
      std::cout << f1 << " / " << f2 << " = " << f1 / f2 << std::endl;
      std::cout << "++" << f1 << " * " << f2 << " = " << ++f1 * f2 << std::endl;
      std::cout << "Значение дроби 1: " << f1 << std::endl;
      std::cout << f1 << "-- * " << f2 << " = " << f1-- * f2 << std::endl;
      std::cout << "Значение дроби 1: " << f1 << std::endl;

  }
  catch(const std::exception& e)
  {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  };

	return 0;
}