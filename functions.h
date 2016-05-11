#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;



double fevaluate(double par0,double par1,double x[],double y0[],int length);
double fevaluate(double par0,double par1,double par2,vector<double> x1,vector<double> x2,vector<double> y,int length);
void newton2(double par[],double dh,double x[],double y[],int length);
void newton3(double par[],double dh,vector<double> x1,vector<double> x2,vector<double> y,int length);
void secant3(double par[],double dh,vector<double> x1,vector<double> x2,vector<double> y,int length);
void fullSearch (vector<double> par0,vector<double> par1,vector<double> par2,vector<double> x1,vector<double> x2,vector<double> y,int length);

#endif // FUNCTIONS_H_INCLUDED
