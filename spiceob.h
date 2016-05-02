#ifndef SPICEOB_H
#define SPICEOB_H
#include <iostream>
#include <vector>

using namespace std;

class spiceob
{
    public:
        spiceob(int initrnk,double initstepsize,int initsteps,vector<double>initial);
        spiceob(int initrnk,double initstepsize,double initstop,vector<double>initial);
        ~spiceob();

        vector< vector<double> > fwdEuler();
        vector< vector<double> > bwdEuler();
        vector< vector<double> > trapEuler();
        vector< vector<double> > rk34Nt();
        vector< vector<double> > rk34T(double tol1, double tol2);

    private:
        int rnk,numsteps, timeAdaptive;
        double stepsize, stop;
        vector<double> curValues;
        vector<double>nxtValues;
        vector< vector<double> >allvalues;
        double current (double t);
        vector<double> fevaluate(int rnk,vector<double>curValues,double stepsize);
        vector<double> addToCurrVal(vector<double>curValues,double increment);
        vector<double> addToCurrVal(vector<double>curValues,vector<double> increment);
        vector<double> multCurrValby(vector<double>curValues,double factor);
        vector<double> rkDelta(vector< vector<double> > k, int order);
        double norm(vector<double> input);
};

#endif // SPICEOB_H
