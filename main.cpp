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
    /*
    cout<<"Task 4:\n";
    cout<<"Simulation for 1ns step size with 100 steps\n";
    A=*new spiceob(2,1*pow(10,-9),100,init);
    
    finalv=A.bwdEuler();

    cout<<"\nForward Euler Method\n";
    for(int i=0;i<100;i++){
        cout << "step "<<i<<" value: "<< finalv[1][i] <<endl;
    }
    
    writeModel("backwardEulerTask3_1ns.txt",finalv,"hor");
    
    finalv=A.trapEuler();
    
    cout<<"\nTrapazoid Euler Method\n";
    for(int i=0;i<100;i++){
        cout << "step "<<i<<" value: "<< finalv[1][i] <<endl;
    }

    writeModel("trapazoidEulerTask4_1ns.txt",finalv,"hor");
    */
     
     
    cout<<"\nRK34 Method Without Time adaptation\n";
    vector< vector<double> >test=A.rk34Nt();


    A=*new spiceob(2,1*pow(10,-6),40*pow(10,-6),init);

    writeModel("RK34NTTask4_1ns.txt",test,"vert");

    cout<<"\nRK34 Method With Time adaptation\n";
    test=A.rk34T(pow(10,-1),pow(10,-9.0));

    for (int i=0;i<test.size();i++){
        //cout<<"Time:"<<test[i][2]<<test[i][1]<<endl;

    }

    //Find v2 after 20us and initiate parameter search
    bool found=false;
    int index=0;
    double dh=.000008;
    double par[]={1,pow(10,-8),6*pow(10,-8)};
    vector<double>x1;
    vector<double>x2;
    vector<double>y;
    for( index=0;index<test.size()&&found==false;index++){
        if(test[index][2]>=(20*pow(10,-6))){
                found=true;
                x2.push_back(test[index][1]);



        }

    }


    //Read all values after 20us for parameter optimization
    cout<<test.size()<<endl;
    for(int i=index;i<test.size();i=i+50){
        //Push time
        x1.push_back(test[i][2]);

        //Push voltage
        y.push_back(test[i][1]);
    }

     cout<<"Size of x1:"<<x1.size()<<endl;
     cout<<x2[0];

newton3(par,dh,x1,x2,y,x1.size());
    return 0;
}

