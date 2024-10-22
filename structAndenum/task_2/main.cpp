#include <iomanip>
#include <iostream>
#include <fstream>

using  namespace std;

struct schet{
    int number;
    string name;
    double balance;
};

struct schet signUp();
int update_balance(schet *obj);
int info_schet(schet *obj);

int main(int argc, char** argv){

  struct schet user_1;
  user_1 = signUp();
  update_balance(&user_1);
  info_schet(&user_1);

  return 0;
}

struct schet signUp(){
    struct schet a;
    cout << "Введите номер счета: ";
    cin >> a.number;
    cout << "Введите имя владельца: ";
    cin >> a.name; 
    cout << "Введите баланс: ";
    cin >> a.balance;

    return a;
}        
int update_balance(schet *obj){
    
    cout << "Введите новый баланс: ";
    cin >> obj->balance;

    return 1;
};

int info_schet(schet *obj){
    cout << "Ваш счет: " << obj->name << ", " << obj->number << ", " << obj->balance << endl;
    
    return 1;
}
