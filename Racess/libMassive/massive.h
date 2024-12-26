#pragma once

#include <iomanip>
#include <iostream>

class DynamicMassive{
    public:
        int Rows;
        int Colls;
        DynamicMassive() {};
        DynamicMassive(int rows, int colls) : Rows(rows) , Colls(colls) {
            massive = create_two_dim_array(Rows, Colls);
            fill_two_dim_array_Zero(Rows, Colls);
        };

        void print_two_dim_array();

        void set_value_two_dim_array(int Rows, int Colls, double value);
        double get_value_two_dim_array(int Rows, int Colls);
        void delete_two_dim_array(int Rows, int Colls);
    
    protected:
        double **massive;

    private:
        double **create_two_dim_array(int Rows, int Colls);
        void fill_two_dim_array_Zero(int Rows, int Colls);
};