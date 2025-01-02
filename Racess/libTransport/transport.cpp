#include "transport.h"

    double Transport:: get_race_time()
    {
        return long_rest.get_value_two_dim_array(0,count_rest-1);
    }
    DynamicMassive Transport:: create_rest_way(){return DynamicMassive();};
    double Transport:: calculate_time_for_distance(int spead) { return 0.0; };


// /////////////////////////////////////GroundTransport////////////////////////////////////////////

    double GroundTransport::get_speed() const { return speed; };  
    double GroundTransport:: calculate_time_for_distance(int spead) {return distance/spead; };


    DynamicMassive Camel:: create_rest_way()
    {
        DynamicMassive long_rest;
        double time_only_way = calculate_time_for_distance(get_speed());
        count_rest = static_cast<int>(time_only_way/time_to_rest);
        long_rest = DynamicMassive(1,count_rest);
        
        int i=-1;
        
        while((i+2)*(get_speed()*time_to_rest)<distance)
        {
            i++;

            if(i==0)
            {
                long_rest.set_value_two_dim_array(0,i,time_only_way+5.0);
            }
            else
            {  
                double last_time=long_rest.get_value_two_dim_array(0,i-1);
                long_rest.set_value_two_dim_array(0,i,last_time+8.0);
            }
        };

        long_rest.set_value_two_dim_array(0,count_rest-1,long_rest.get_value_two_dim_array(0,i));

        return long_rest;
    };

    DynamicMassive CamelSpeed:: create_rest_way()
    {
        DynamicMassive long_rest;
        double time_only_way = calculate_time_for_distance(get_speed());
        count_rest = static_cast<int>(time_only_way/time_to_rest);
        long_rest = DynamicMassive(1,count_rest);
        
        int i=-1;
        
        while((i+2)*(get_speed()*time_to_rest)<distance)
        {
            i++;

            if(i==0)
            {
                long_rest.set_value_two_dim_array(0,i,time_only_way+5.0);

            }
            else if(i==1)
            {   
                double last_time=long_rest.get_value_two_dim_array(0,i-1);
                long_rest.set_value_two_dim_array(0,i,last_time+6.5);
            }
            else
            {   
                double last_time=long_rest.get_value_two_dim_array(0,i-1);
                long_rest.set_value_two_dim_array(0,i,last_time+8.0);
            }
        };

        long_rest.set_value_two_dim_array(0,count_rest-1,long_rest.get_value_two_dim_array(0,i));

        return long_rest;
    };

    DynamicMassive Boots:: create_rest_way()
    {
        DynamicMassive long_rest;
        double time_only_way = calculate_time_for_distance(get_speed());
        count_rest = static_cast<int>(time_only_way/time_to_rest);
        long_rest = DynamicMassive(1,count_rest);
        
        int i=-1;
        
        while((i+2)*(get_speed()*time_to_rest)<distance)
        {
            i++;

            if(i==0)
            {
                long_rest.set_value_two_dim_array(0,i,time_only_way+10.0);
            }
            else
            {   
                double last_time=long_rest.get_value_two_dim_array(0,i-1);
                long_rest.set_value_two_dim_array(0,i,last_time+5.0);
            }
        };
        
        long_rest.set_value_two_dim_array(0,count_rest-1,long_rest.get_value_two_dim_array(0,i));

        return long_rest;
    };

    DynamicMassive Kentavr:: create_rest_way()
    {
        DynamicMassive long_rest;
        double time_only_way = calculate_time_for_distance(get_speed());
        count_rest = static_cast<int>(time_only_way/time_to_rest);
        long_rest = DynamicMassive(1,count_rest);
        
        int i=-1;
        
        while((i+2)*(get_speed()*time_to_rest)<distance)
        {
            i++;

            if(i==0)
            {
                long_rest.set_value_two_dim_array(0,i,time_only_way+2.0);
            }
            else
            {   
                double last_time=long_rest.get_value_two_dim_array(0,i-1);
                long_rest.set_value_two_dim_array(0,i,last_time+2.0);
            }
        };

        long_rest.set_value_two_dim_array(0,count_rest-1,long_rest.get_value_two_dim_array(0,i));

        return long_rest;
    };


// /////////////////////////////////////AirTransport////////////////////////////////////////////

    double AirTransport::get_speed() const { return speed; };  
    DynamicMassive AirTransport:: create_rest_way()
    {
        DynamicMassive long_rest;
        double time_only_way = calculate_time_for_distance(get_speed());
        count_rest = 1;
        long_rest = DynamicMassive(1,1);
        long_rest.set_value_two_dim_array(0,0,time_only_way);

        return long_rest;
    };
    double AirTransport:: calculate_time_for_distance(int spead)
    { 
        return (distance*distance_factor)/spead; 
    };

       
    double CarpetPlane:: calculateDistanceReductionFactor(int dist)
    {
        distance=dist;

        if (dist < 1000) return 1.0;
        else if (dist < 5000) return 0.97;
        else if (dist < 10000) return 0.9;
        else return 0.95;
    };
   
    double Eegl:: calculateDistanceReductionFactor(int dist) {
        
        distance=dist;
        
        return 0.94;
    };
    
    double Metla:: calculateDistanceReductionFactor(int dist) {
        
        distance=dist;

        if(dist<1000)
        {
            return 1;
        }
        else
        {   
            return 1-(trunc(round(((dist/1000))*10)/10)/100);
        }
    };
