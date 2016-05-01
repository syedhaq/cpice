#ifndef SPICEOB_H
#define SPICEOB_H
#include <iostream>
#include <vector>

using namespace std;

class spiceob
{
    public:
        spiceob(int rank,double stepsize,int steps,vector<double>initial);
        ~spiceob();

        vector< vector<double> > fwdEuler();
        vector< vector<double> > bwdEuler();
        vector< vector<double> > trapEuler();

    private:
        int rnk,numsteps;
        double stepsize;
        vector<double> curValues;
        vector<double>nxtValues;
        vector< vector<double> >allvalues;
        double current (double t);
        vector<double> fevaluate(int rnk,vector<double>curValues,double stepsize);




};

#endif // SPICEOB_H
