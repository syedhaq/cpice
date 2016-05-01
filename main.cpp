#include <iostream>
#include <vector>
#include "spiceob.h"

int main(int argc, char *argv[])
{
    vector<double>initial;
    initial.push_back(2);
    spiceob A(1,1,5,initial);
    vector< vector<double> >test=A.rk34Nt();
    
    for(int i=0;i<test.size();i++)
        cout << "step "<<i<<" value: "<< test[i][0] << endl;
    return 0;
}
