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
        vector< vector<double> > rk34Nt();
        vector< vector<double> > rk34T();

    private:
        int rnk,numsteps;
        double stepsize;
        vector<double> curValues;
        vector<double>nxtValues;
        vector< vector<double> >allvalues;
        double current (double t);
        vector<double> fevaluate(int rnk,vector<double>curValues,double stepsize);
        vector<double> addToCurrVal(vector<double>curValues,double increment);
        vector<double> addToCurrVal(vector<double>curValues,vector<double> increment);
        vector<double> multCurrValby(vector<double>curValues,double factor);
        vector<double> rkDelta(vector< vector<double> > k, int order);
    
};

#endif // SPICEOB_H
