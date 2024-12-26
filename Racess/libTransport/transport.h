#pragma once

#include <string>
#include <cmath>

#include "massive.h"

class Transport {
    
    public:
        ~Transport()
        {
            long_rest.delete_two_dim_array(1,count_rest);
        };
        
    std::string nameTransport = "non";
    std::string typeTransport = "non";
    
    int count_rest;
    int distance;

    virtual double get_speed() const = 0;
    double get_race_time();
    
    protected:
        virtual DynamicMassive create_rest_way();
        DynamicMassive long_rest;
        virtual double calculate_time_for_distance(int spead);
};

// /////////////////////////////////////GroundTransport////////////////////////////////////////////

class GroundTransport : public Transport{
    public:
        GroundTransport(int speeD, int time_Rest) : time_to_rest(time_Rest), speed(speeD) {};
        double get_speed() const override;  

    protected:
        int speed;
        int time_to_rest;
        double calculate_time_for_distance(int spead) override;
};

class Camel : public GroundTransport {
    public:
        Camel(int dist) : GroundTransport(10,30){
            distance = dist;
            nameTransport = "Верблюд";
            typeTransport = "Ground";
            long_rest = create_rest_way();
        };
    
    private:
        DynamicMassive create_rest_way() override;
};
class CamelSpeed : public GroundTransport {
    public:
        CamelSpeed(int dist) : GroundTransport(40,10){
            distance = dist;
            nameTransport = "Верблюд-быстроход";
            typeTransport = "Ground";
            long_rest = create_rest_way();
        };
    
    private:
        DynamicMassive create_rest_way() override;
};
class Boots : public GroundTransport {
    public:
        Boots(int dist) : GroundTransport(6,60){
            distance = dist;
            nameTransport = "Ботинки-вездеходы";
            typeTransport = "Ground";
            long_rest = create_rest_way();
        };
    
    private:
        DynamicMassive create_rest_way() override;
};
class Kentavr : public GroundTransport {
    public:
        Kentavr(int dist) : GroundTransport(15,8){
            distance = dist;
            nameTransport = "Кентавр";
            typeTransport = "Ground";
            long_rest = create_rest_way();
        };
    
    private:
        DynamicMassive create_rest_way() override;
};

// /////////////////////////////////////AirTransport////////////////////////////////////////////
class AirTransport : public Transport{
    public:
        AirTransport(int speeD, double distance_Factor) : distance_factor(distance_Factor), speed(speeD) {};

        double get_speed() const override;
    
    protected:
        int speed;
        double distance_factor;

        DynamicMassive create_rest_way() override;
        double calculate_time_for_distance(int spead) override;

        virtual double calculateDistanceReductionFactor() = 0; 
};

class CarpetPlane : public AirTransport {
    public:
        CarpetPlane(int dist) : AirTransport(10, calculateDistanceReductionFactor()){
            distance = dist;
            nameTransport = "Ковер-самолет";
            typeTransport = "Air";
            long_rest = create_rest_way();
        }
    private:        
        double calculateDistanceReductionFactor() override;
};
class Eegl : public AirTransport {
    public:
        Eegl(int dist) : AirTransport(8, calculateDistanceReductionFactor()){
            distance = dist;
            nameTransport = "Орел";
            typeTransport = "Air";
            long_rest = create_rest_way();
        }
    private:        
        double calculateDistanceReductionFactor() override;
};
class Metla : public AirTransport {
    public:
        Metla(int dist) : AirTransport(20, calculateDistanceReductionFactor()){
            distance = dist;
            nameTransport = "Метла";
            typeTransport = "Air";
            long_rest = create_rest_way();
        }
    private:        
        double calculateDistanceReductionFactor() override;
};