#pragma once

#include <algorithm>
#include "transport.h"

struct Result
{
    std::string nameTransport;
    double Racetime;
};

class Race {
    public:
        Transport* Tr;

        Race()
        { 
            Tr=create_array(7); 
        };

        ~Race()
        {
            free(Tr);

            for (int r = 0; r < rows; r++)
            {
                free(result_race[r]);
            }
                free(result_race);
        };
        
        void startRace();
        std::string get_name_transports();  
        void set_distance(int dist);
        int get_distance();
        void set_type_race(int type);
        int get_type_race();
        int get_count_transport();
        
        
    private:
        Result** result_race;
        int rows;
        int cols;

        std::string in_race = "";
        std::string count_type;
        int type_race=0;
        int count_transport=0;

        Transport *create_array(int size);
        void set_value_one_dim_array(Transport *mass,Transport* in, int place);          
        void seting_race();
        void preload_race();
        void registrate(Transport* first,int place);
        void registering();
        void output_result();

        Result** create_ResultArray(int rows, int cols);
        Result get_value_ResultArray(int row, int col);
        void set_value_ResultArray(int row, int col, Result value);
};