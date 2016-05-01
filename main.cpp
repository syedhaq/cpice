#include <iostream>
#include <vector>
#include "spiceob.h"

int main(int argc, char *argv[])
{
    std::vector<double>init;
    init.push_back(2);
    spiceob A(1,1,5,init);
    
    /*
    std::vector< std::vector<double> > finalv;
    finalv=A.fwdEuler();

    for(int i=0;i<5;i++){
        cout<<(finalv[0][i])<<endl;
    }
    */
    vector< vector<double> >test=A.rk34Nt();
    
    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][0] << endl;
    return 0;
}
