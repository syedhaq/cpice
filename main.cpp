#include <iostream>
#include <vector>
#include "spiceob.h"
#include <cmath>
#include "writeModel.hpp"
#include "functions.h"

int main(int argc, char *argv[]){
    std::vector<double>init;
    init.push_back(2);
    spiceob A(1,1,5,init);

    std::vector< std::vector<double> > finalv;


    init.clear();
    init.push_back(0);
    init.push_back(0);
    
    
    //task 3:
    cout<<"Task 4:\n";
    cout<<"Simulation for 1ns step size with 100 steps\n";
    A=*new spiceob(2,1*pow(10,-9),100,init);
    
    finalv=A.bwdEuler();

    cout<<"\nForward Euler Method\n";
    for(int i=0;i<100;i++){
        cout << "step "<<i<<" value: "<< finalv[1][i] <<endl;
    }
    
    writeModel("backwardEulerTask3_1ns.txt",finalv,"hor");
    
    /*
    finalv=A.trapEuler();
    
    cout<<"\nTrapazoid Euler Method\n";
    for(int i=0;i<100;i++){
        cout << "step "<<i<<" value: "<< finalv[1][i] <<endl;
    }

    vector< vector<double> >test=A.rk34Nt();



    A=*new spiceob(2,1*pow(10,-6),40*pow(10,-6),init);

    writeModel("RK34NTTask4_1ns.txt",test,"vert");

    cout<<"\nRK34 Method With Time adaptation\n";
    test=A.rk34T(pow(10,-1),pow(10,-9.0));

    for (int i=0;i<test.size();i++){
        //cout<<"Time:"<<test[i][2]<<test[i][1]<<endl;

    }
    
    writeModel("forwardEulerTask4_0.2ns.txt",finalv,"hor");
    
    finalv=A.trapEuler();
    
    cout<<"\nTrapazoid Euler Method\n";
    for(int i=0;i<100;i++){
        cout << "step "<<i<<" value: "<< finalv[1][i] <<endl;    }
  
    writeModel("trapazoidEulerTask4_0.2ns.txt",finalv,"hor");
    
    cout<<"\nRK34 Method Without Time adaptation\n";
    test=A.rk34Nt();
    
    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][0] << endl;
    
    writeModel("RK34NTTask4_0.2ns.txt",test,"vert");
    
    A=*new spiceob(2,0.2*pow(10,-9),100*pow(10,-9),init);
    
    cout<<"\nRK34 Method With Time adaptation\n";
    test=A.rk34T(pow(10,-1.0),pow(10,-6.0));
    
    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][0] << endl;
    
    writeModel("RK34TTask4_0.2ns.txt",test,"vert");
    */
    return 0;
}

