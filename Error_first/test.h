#pragma once

// ANSI Escape Sequences for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#include <cassert>
#include <sstream>

#include "extended_array.h"

class MyTestClass
{
    public:

        template <typename  ExtArray>
        void test_ArrayEmpty(ExtArray& v1) {
            AssertArray_Empty(v1, 0);
        };

        template <typename  ExtArray,typename B, typename C>
        void test_ArrayMean(ExtArray& v1, B& diap, C true_value) {
            AssertArray_Mean(v1,true_value,diap);
        }
        template <typename  ExtArray,typename B>
        void test_ArrayMean(ExtArray& v1, B true_value) {
            AssertArray_Mean(v1, true_value);
        }
        
        template <typename ExtArray,typename B>
        void test_ArrayTypeBoolInt(ExtArray& v1, B true_count_value) {
            AssertArray_typeBoolInt(v1, true_count_value);
        }


        template <typename TestFunc>
        void RunOneTest(TestFunc tfunc, const std::string& test_name) {
            try
            {
                tfunc();
                std::cerr << BLUE << "###" << RESET << CYAN << test_name << RESET << GREEN <<" (√) •–––––>  " << RESET << WHITE << "OK" << RESET << std::endl;
            }
            catch (std::runtime_error& e)
            {
                std::cerr << BLUE << "###" << RESET << CYAN << test_name << RESET << RED << " (Error) •–––––> " << WHITE << e.what() << RESET << std::endl;
            }
        }

    private:

        template <typename T, typename U>
        void AssertArray_Empty(T& array, const U& value){
            if (array.size() > value) {
                std::ostringstream err;
                err << "Размер массива = " << array.size();
                throw std::runtime_error(err.str());
            }
            
        }
        
        template <typename T, typename U>
        void AssertArray_Mean(T& array_mean, const U& true_mean){
            if (array_mean.mean() != true_mean) {
                std::ostringstream err;
                err << "Cреднее арифметическое для указанного массива возвращено не верно: " << array_mean.mean() << " ≠ " << true_mean;
                throw std::runtime_error(err.str());
            }
        }
        
        template <typename T, typename U, typename D>
        void AssertArray_Mean(T& array_mean, const U& true_mean, const D& diap){
            std::string error_type="msg from outside";
            try
            {
                if(array_mean.mean(diap.first,diap.second))
                {
                    if (array_mean.mean(diap.first,diap.second) != true_mean) {
                        std::ostringstream err;
                        err << "Cреднее арифметическое для указанного диапазона" << "[" << diap.first<<"," << diap.second<<"] " 
                        << "массива возвращено не верно: " << array_mean.mean(diap.first,diap.second) << " ≠ " << true_mean;
                        throw std::runtime_error(err.str());
                    }
                }
                else
                {
                    error_type = "msg from inside";
                }
            }
            catch(const std::exception& e)
            {
                if(error_type=="msg from inside")
                    std::cerr << RED << "\t\t\t(Error) •–––––> " << WHITE << e.what() << RESET << std::endl;
                else
                    throw std::runtime_error(e.what());
            }
            
        }

        template <typename T, typename U>
        void AssertArray_typeBoolInt(T& array, const U& value){
            std::string error_type="msg from outside";
            try
            {
                if(array.checkSum())
                {
                    if (array.checkSum() != value) {
                        std::ostringstream err;
                        err << "Количество элементов, установленных в значение 1(true) возвращено не верно: " << array.checkSum() << " ≠ " << value;
                        throw std::runtime_error(err.str());
                    }
                }
                else
                {
                    error_type = "msg from inside";
                }
            }
            catch(const std::exception& e)
            {
                if(error_type=="msg from inside")
                    std::cerr << RED << "\t\t\t(Error) •–––––> " << WHITE << e.what() << RESET << std::endl;
                else
                    throw std::runtime_error(e.what());
            }
        }

};

