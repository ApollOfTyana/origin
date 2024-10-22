#include <iomanip>
#include <iostream>
#include <fstream>

using  namespace std;


class Counter{
    private:
    int schet=0;

    public:

    void up()
    {
        schet++;
    };
    void dwn()
    {
        schet--;
    };
    int get()
    {
        return schet;
    };
    string end()
    {
        cout << "До свидания!" << endl;
        return "end";
    };

    Counter()
    {
       schet=0; 
    };
    Counter(int schet)
    {
        this->schet = schet;
    };
};

int cycleConter(Counter *obj){

    char command;
    string endOrGo;

    while(endOrGo!="end")
    {
        cout << "Введите команду ('+', '-', '=' или 'x'):  " ;
        cin >> command;
        if(command == '+')
        {
            obj->up();
        }
        else if(command == '-')
        {
            obj->dwn();
        }
        else if(command == '=')
        {
            cout << obj->get() << endl;
        }
        else if(command == 'x')
        {
            endOrGo = obj->end();
        }
        else
            ;
    }

    return 1;

};

int main(int argc, char** argv){

    string chose;

    cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    cin >> chose;
    if(chose == "да")
    {
        cout << "Введите начальное значение счётчика: ";
        int schet;
        cin >> schet;

        Counter c(schet);

        cycleConter(&c);
    }
    else if(chose == "нет")
    {
        Counter c;
        cycleConter(&c);
    }
    else
        ;

  return 0;
}