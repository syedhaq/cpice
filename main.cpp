#include <iostream>
#include <vector>
#include "spiceob.h"
#include <cmath>
#include "writeModel.hpp"
#include "functions.h"

int main(int argc, char *argv[]){
    
    std::vector<double>init;
    init.push_back(0);
    init.push_back(0);
    
    spiceob A(2,1*pow(10,-6),40*pow(10,-6),init);

    cout<<"\nTask2:\n\n";
    vector< vector<double> >test=A.rk34T(pow(10,-1),pow(10,-9.0));
    
    //Find v2 after 20us and initiate parameter search
    bool found=false;
    int index=0;
    double dh=.000008;
    double par[]={1,pow(10,-8),6*pow(10,-8)};
    vector<double>x1;
    vector<double>x2;
    vector<double>y;
    for(index=0;index<test.size()&&found==false;index++){
        if(test[index][2]>=(20*pow(10,-6))){
                found=true;
                x2.push_back(test[index][1]);



        }

    }


    //Read all values after 20us for parameter optimization
    for(int i=index;i<test.size();i=i+50){
        //Push time
        x1.push_back(test[i][2]);

        //Push voltage
        y.push_back(test[i][1]);
    }

    newton3(par,dh,x1,x2,y,x1.size());
    cout<<"\nTask3:\n";
    cout<<"Two functions inherited from previous assignments are newton3 and rk34T.\n";
    return 0;
}

