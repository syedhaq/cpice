#include <iostream>
#include <vector>
#include "spiceob.h"
#include <cmath>
#include "writeModel.hpp"

int main(int argc, char *argv[]){
    std::vector<double>init;
    init.push_back(2);
    spiceob A(1,1,5,init);

    std::vector< std::vector<double> > finalv;
    
    /*
    finalv=A.fwdEuler();

    cout<<"\nForward Euler Method\n";
    for(int i=0;i<5;i++){
        cout << "step "<<i<<" value: "<< finalv[0][i] <<endl;
    }
    
    finalv=A.trapEuler();
    
    cout<<"\nTrapazoid Euler Method\n";
    for(int i=0;i<5;i++){
        cout << "step "<<i<<" value: "<< finalv[0][i] <<endl;
    }
    
    cout<<"\nRK34 Method Without Time adaptation\n";
    vector< vector<double> >test=A.rk34Nt();
    
    
    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][0] <<endl;
    
    A=*new spiceob(1,1,5.0,init);
    
    cout<<"\nRK34 Method With Time adaptation\n";
    test=A.rk34T(pow(10,-1.0),pow(10,-6.0));
    
    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][0] <<endl;
    */
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

    writeModel("trapazoidEulerTask4_1ns.txt",finalv,"hor");
    
    cout<<"\nRK34 Method Without Time adaptation\n";
    vector< vector<double> >test=A.rk34Nt();


    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][1] <<endl;

    A=*new spiceob(2,1*pow(10,-9),100*pow(10,-9),init);
    
    writeModel("RK34NTTask4_1ns.txt",test,"vert");
    
    cout<<"\nRK34 Method With Time adaptation\n";
    test=A.rk34T(pow(10,-1.0),pow(10,-6.0));

    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][1] <<endl;
    
    writeModel("RK34TTask4_1ns.txt",test,"vert");
    
    
    cout<<"Simulation for 0.2ns step size with 500 steps\n";
    A=*new spiceob(2,0.2*pow(10,-9),500,init);
    
    finalv=A.fwdEuler();
    
    cout<<"\nForward Euler Method\n";
    for(int i=0;i<100;i++){
        cout << "step "<<i<<" value: "<< finalv[1][i] <<endl;
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

