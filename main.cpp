#include <iostream>
#include <vector>
#include "spiceob.h"
using namespace std;

int main()
{
    vector<double>initial;
    initial.push_back(0);
    spiceob A(1,0.2,500,initial);


    cout << "Hello world!" << endl;
    return 0;
}
