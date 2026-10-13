#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "capacitor.h"

int main(){
    //Values given on canvas page
    double deltaTime = 1e-10;               // Time step (s)
    int num_steps = 5e-6 / deltaTime;       // 50000 steps
    double R = 1000.0;                      // R = 1000.0 ohm
    double C = 100e-12;                     // C = 100.0 pF
    double I_const = 0.01;                  // I(0) = 10.0 mA
    double V_const = 10.0;                  // V(0) = 10.0 V
  
    /*Constant Current*/
    Capacitor cc;
    cc.time = new double[num_steps + 1];
    cc.voltage = new double[num_steps + 1];
    cc.current = new double[num_steps + 1];
    cc.C = C;
    //initial conditions (index 0)
    cc.time[0] = 0.0; 
    cc.voltage[0] = 0.0;            //possible bug? supposed to be capped around 10V
    cc.current[0] = I_const;            


    /*Constant Voltage*/
    Capacitor cv;
    cv.time = new double[num_steps + 1];
    cv.voltage = new double[num_steps + 1];
    cv.current = new double[num_steps + 1];
    cv.C = C;
    //initial conditions (index 0)
    cv.time[0] = 0.0; 
    cv.voltage[0] = V_const;  
    cv.current[0] = (V_const / R);
   
    //iterate through timesteps
    for (int t = 0; t < num_steps; t++) {
        int current_step = t + 1;

        /* constant current */
        cc.time[current_step] = (current_step) * deltaTime;
        cc.current[current_step] = I_const; //remains constant

        //V(t+1) = V(t) + (I(t) * dt) * (1 / C)
        cc.voltage[current_step] = cc.voltage[t] + ((cc.current[t]) * (deltaTime) * (1.0 / cc.C)); 


        /* constant voltage*/
        cv.time[current_step] = (t + 1) * deltaTime;
        cv.voltage[current_step] = V_const; //remains constant

        //I(t+1) = I(t) - (I(t) / (R * C)) * dt
        cv.current[current_step] = cv.current[t] - ((cv.current[t] / (R * cv.C)) * deltaTime);
    }

    //formatting header output
    std::cout << std::left 
              << std::setw(10) << "Step" << " | "
              << std::setw(15) << "V" << std::setw(15) << "Const I" << " | "
              << std::setw(15) << "Const V" << std::setw(15) << "I" << "\n";
    std::cout << std::string(80, '-') << "\n";

    //std::cout << std::scientific << std::setprecision(2);

    // Output results every 200 timesteps
    for (int t = 0; t <= num_steps; t += 200){
        std::cout << std::left << std::setw(10) << t << " | "
                  << std::setw(15) << cc.voltage[t] << std::setw(15) << cc.current[t] << " | "
                  << std::setw(15) << cv.voltage[t] << std::setw(15) << cv.current[t] << "\n";
    }

    //clean up memory
    delete[] cc.time;
    delete[] cc.voltage;
    delete[] cc.current;

    delete[] cv.time;
    delete[] cv.voltage;
    delete[] cv.current;

    return 0;
}