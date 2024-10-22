#include <iomanip>
#include <iostream>
#include <fstream>

using  namespace std;

struct address{
    string city;
    string street;
    int build;
    int appartament;
    int index;
};

struct address create_address();
int info_address(address *obj);

int main(int argc, char** argv){

  struct address address_1;
  address_1 = create_address();
  info_address(&address_1);

  return 0;
}

int info_address(address *obj){
    cout << '\n' ;
    cout << "Город: ";
    cout << obj->city<< "\n";
    cout << "Улица: ";
    cout << obj->street<< "\n";
    cout << "Номер дома: ";
    cout << obj->build<< "\n";
    cout << "Номер квартиры: ";
    cout << obj->appartament<< "\n";
    cout << "Индекс: ";
    cout << obj->index << "\n\n";

    return 1;
}
struct address create_address(){
    struct address a;
    cout << "\nВведите название города: ";
    cin >> a.city;
    cout << "Введите название улицы: ";
    cin >> a.street;
    cout << "Введите номер дома: ";
    cin >> a.build;
    cout << "Введите номер квартиры: ";
    cin >> a.appartament;
    cout << "Введите индекс: ";
    cin >> a.index;

    return a;
}