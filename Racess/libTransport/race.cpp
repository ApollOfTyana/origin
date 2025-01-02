#include "race.h"

    void Race:: startRace()
    {
        seting_race();

        output_result();
    };
    
    std::string Race:: get_name_transports(){ return in_race; };
        
    void Race:: set_distance(int dist)
    {
        if(dist > 0)
            Tr->distance = dist ;
        else
            std::cout << "\nДистанция должна быть положительной!\n" << std::endl;
    };

    int Race:: get_distance(){ return Tr->distance; };

    void Race:: set_type_race(int type)
    {
        if(type >= 1 && type <= 3)
            type_race = type ;
        else
            std::cout << "\nВыберите что-то одно из трех вариантов!\n" << std::endl;
    };
    
    int Race:: get_type_race(){ return type_race; };

    int Race:: get_count_transport(){ return count_transport; };
        
    Transport* Race:: create_array(int size)
    {
        Transport *mass = static_cast<Transport *>(calloc(size, sizeof(Transport)));

        return mass;
    };
    
//Result structur manipulation
    Result** Race::create_ResultArray(int rows, int cols)
{
    Result** mass = static_cast<Result**>(calloc(rows, sizeof(Result*)));
    for (int i = 0; i < rows; i++)
    {
        mass[i] = static_cast<Result*>(calloc(cols, sizeof(Result)));
    }
    this->rows = rows;
    this->cols = cols;
    this->result_race = mass;
    return mass;
}
    
    Result Race::get_value_ResultArray(int row, int col)
    {
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            return result_race[row][col];
        }
        else
        {
            return {"", 0.0}; // Возвращаем пустую структуру, если индексы выходят за пределы массива
        }
    };
    
    void Race::set_value_ResultArray(int row, int col, Result value)
    {
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            result_race[row][col] = value;
        }
    }
// //////////////////////////////////////////////////////////////////////////////////////////////////////            

    void Race:: set_value_one_dim_array(Transport *mass,Transport* in, int place)
    {
        *(mass + place) = *in;
    };
    void Race:: seting_race()
    {
        while(get_type_race()==0)
        {
            int type_race=0;
            std:: cout << "Добро пожаловать в гоночный симулятор!\n 1.Гонка для наземного транспорта\n 2.Гонка для воздушного транспорта\n 3.Гонка для наземного и воздушного транспорта\n Выберите тип гонки:";
            std::cin >> type_race;
            set_type_race(type_race);
        };
        
        while(get_distance()==0)
        {
            int distance=0;
            std::cout << "Укажите длину дистанции (должна быть положительна):";
            std::cin >> distance;
            set_distance(distance); 
        };

        preload_race();
    };

    void Race:: preload_race()
    { 
        int start=false;
        int mainMenu = 1;

        while (!start)
        {               
            if(get_count_transport()<2)
                std::cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства!" << std::endl;
                    
            std::cout<<"1.Зарегистрировать транспорт" << std::endl; 
                    
            if(get_count_transport()>=2)
                std::cout<<"2.Начать гонку" << std::endl;
            
            std::cout<<"Выберите действие: ";
            std::cin >> mainMenu;

            if (mainMenu == 1)
                registering();
            else if (mainMenu == 2)
            {
                for(int tr=0; tr < count_transport; tr++)
                {
                    Tr[tr].get_race_time();
                }
                start = true;
            }
            else
                continue;
        };
    };
            
    void Race:: registrate(Transport* first,int place)
    {
        set_value_one_dim_array(Tr,first, place);
        
        if(in_race=="")
            in_race += first ->nameTransport;
        else
            in_race += " ," + first ->nameTransport;
        
        count_transport++;
    };

    void Race:: registering()
    {
        bool doneRegistering = false; //окончание регистрации
    
        while (!doneRegistering)
        {
            if(get_type_race() == 1)
                std:: cout << "Гонка для наземного транспорта. Расстояние: " << get_distance()<< std::endl;
            else if(get_type_race() == 2)
                std:: cout << "Гонка для воздушного транспорта. Расстояние: " << get_distance()<< std::endl;
            else
                std:: cout << "Гонка для наземного и воздушного транспорта. Расстояние: " << get_distance()<< std::endl;

            if(count_transport>0)
                std:: cout << "Зарегистрированные транспортные средства: " << get_name_transports() << std::endl;

                std:: cout << "1. Ботинки-вездеходы\n";
                std:: cout << "2. Метла\n";
                std:: cout << "3. Верблюд\n";
                std:: cout << "4. Кентавр\n";
                std:: cout << "5. Орел\n";
                std:: cout << "6. Верблюд-быстроход\n";
                std:: cout << "7. Ковер-самолет\n";
                std:: cout << "0. Закончить регистрацию\n";
                std:: cout << "Выберите транспорт или 0 для окончания процесса регистрации:";

                int choice=-1;
                std::cin >> choice;  
                    
                Transport* transport = nullptr;
                
            switch(choice)
            {
                case 0:
                {
                    doneRegistering = true;
                    break;
                }
                case 1: 
                {
                    if(std::count(count_type.begin(),count_type.end(),'1')==0 && get_type_race()!=2)
                    {
                        transport = new Boots(get_distance());
                        registrate(transport,count_transport);
                        
                        count_type+='1';
                        std::cout<< "Ботинки-вездеходы успешно зарегистрированы!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'1')>0)
                        std::cout<< "Ботинки-вездеходы уже зарегистрированы!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                        
                    break;
                }
                case 2:
                {
                    if(std::count(count_type.begin(),count_type.end(),'2')==0 && get_type_race()!=1)
                    {
                        transport = new Metla(get_distance());
                        registrate(transport,count_transport);
                            
                        count_type+='2';
                        std::cout<< "Метла успешно зарегистрирована!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'2')>0)
                        std::cout<< "Метла уже зарегистрирована!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                        
                    break;
                }
                case 3:
                {
                    if(std::count(count_type.begin(),count_type.end(),'3')==0 && get_type_race()!=2)
                    {
                        transport = new Camel(get_distance());
                        registrate(transport,count_transport);
                            
                        count_type+='3';
                        std::cout<< "Верблюд успешно зарегистрирован!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'3')>0)
                        std::cout<< "Верблюд уже зарегистрирован!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                        
                    break;
                }
                case 4:
                {
                    if(std::count(count_type.begin(),count_type.end(),'4')==0 && get_type_race()!=2)
                    {
                        transport = new Kentavr(get_distance());
                        registrate(transport,count_transport);
                            
                        count_type+='4';
                        std::cout<< "Кентавр успешно зарегистрирован!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'4')>0)
                        std::cout<< "Кентавр уже зарегистрирован!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                        
                    break;
                }
                case 5:
                {
                    if(std::count(count_type.begin(),count_type.end(),'5')==0 && get_type_race()!=1)
                    {
                        transport = new Eegl(get_distance());
                        registrate(transport,count_transport);
                            
                        count_type+='5';
                        std::cout<< "Орел успешно зарегистрирован!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'5')>0)
                        std::cout<< "Орел уже зарегистрирован!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                        
                    break;
                }
                case 6:
                {
                    if(std::count(count_type.begin(),count_type.end(),'6')==0 && get_type_race()!=2)
                    {
                        transport = new CamelSpeed(get_distance());
                        registrate(transport,count_transport);
                            
                        count_type+='6';
                        std::cout<< "Верблюд-быстроход успешно зарегистрирован!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'6')>0)
                        std::cout<< "Верблюд-быстроход уже зарегистрирован!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                    
                    break;
                }
                case 7:
                {
                    if(std::count(count_type.begin(),count_type.end(),'7')==0 && get_type_race()!=1)
                    {
                        transport = new CarpetPlane(get_distance());
                        registrate(transport,count_transport);
                            
                        count_type+='7';
                        std::cout<< "Ковер-самолет успешно зарегистрирован!"<< std::endl;
                    }
                    else if(std::count(count_type.begin(),count_type.end(),'7')>0)
                        std::cout<< "Ковер-самолет уже зарегистрирован!"<< std::endl;
                    else 
                        std::cerr << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
                        
                    break;
                };
                default:
                {
                    std::cerr << "Такого транспортного средства нет в списке!" << std::endl;
                        
                    continue;
                }
            }; 
        };
    };

    void Race:: output_result()
    {
        std::cout<<"OK"<<std::endl;
    // Создаем динамический массив для хранения результатов
        result_race=create_ResultArray(count_transport, 1); // Один столбец
                
        for (int id = 0; id < count_transport; ++id)
        {
            Result newResult = {Tr[id].nameTransport, Tr[id].get_race_time()};
            set_value_ResultArray(id, 0, newResult);
        };

        bool swapped;
        do {
            swapped = false;
            
            for (int i = 0; i < count_transport - 1; ++i)
            {
                if (get_value_ResultArray(i,0).Racetime > get_value_ResultArray(i+1,0).Racetime)
                {
                    // Используем собственную функцию обмена
                    Result temp = get_value_ResultArray(i,0);
                    set_value_ResultArray(i, 0, get_value_ResultArray(i+1,0));
                    set_value_ResultArray(i+1, 0, temp);
                    swapped = true;
                }
            };
        } while (swapped);
        std::cout << "Результат гонки:\n";

        for (int id = 0; id < count_transport; ++id)
        {
            std::cout << id+1 << ". " << get_value_ResultArray(id,0).nameTransport << ". Время: " << get_value_ResultArray(id,0).Racetime << std::endl;
        };

    };
