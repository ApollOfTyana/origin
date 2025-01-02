#include <string>
#include "massive.h"

void DynamicMassive:: print_two_dim_array() {
    std::cout << "Таблица умножения: " << std::endl;
    for (int r = 0; r < Rows; r++) {
        for (int c = 0; c < Colls; c++) {
            int otstup = (int)(std::to_string(*(*(massive + (Rows - 1)) + (c))).length());
            c != 0 ? std::cout << std::setw(otstup) << *(*(massive + r) + c)
            : std::cout << std::setw(2) << *(*(massive + r) + c);
            };
            std::cout << '\n';
    };
}
void DynamicMassive:: fill_two_dim_array_Zero(int Rows, int Colls) {
    for (int r = 0; r < Rows; r++) {
        for (int c = 0; c < Colls; c++) {
            *(*(massive + r) + c) = 0;
        }
    };
};
void DynamicMassive:: set_value_two_dim_array(int Rows, int Colls, double value) {
    *(*(massive + Rows) + Colls) = value;
};
double DynamicMassive:: get_value_two_dim_array(int Row, int Coll) {
    return  *(*(massive + Row) + Coll);
};

double **DynamicMassive:: create_two_dim_array(int Rows, int Colls) {
    double **mass = static_cast<double **>(calloc(Rows, sizeof(double *)));
    for (int i = 0; i < Rows; i++) {
        *(mass + i) = static_cast<double *>(calloc(Colls, sizeof(double)));
    }
    return mass;
};
void DynamicMassive:: delete_two_dim_array(int Rows, int Colls) {
    for (int r = 0; r < Rows; r++) {
        free(massive[r]);
    }
    free(massive);
};
