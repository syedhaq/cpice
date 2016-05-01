#include <iostream>
#include <vector>
#include "spiceob.h"
#include <cmath>

int main(int argc, char *argv[])
{
    /*std::vector<double>init;
    init.push_back(2);
    spiceob A(1,1,5,init);

    std::vector< std::vector<double> > finalv;
    finalv=A.fwdEuler();

    for(int i=0;i<5;i++){
        cout<<(finalv[0][i])<<endl;
    } */

    std::vector<double>init;
    init.push_back(0);
    init.push_back(0);
    spiceob A(2,1*pow(10,-9),100,init);

    std::vector< std::vector<double> > finalv;
    finalv=A.fwdEuler();

    for(int i=0;i<100;i++){
        cout<<(finalv[0][i])<<" ";
    }

}
