#include "spiceob.h"
#include <cmath>

spiceob::spiceob(int initrnk,double initstepsize,int initsteps,vector<double>initial)
{

  rnk=initrnk;
  stepsize=initstepsize;
  numsteps=initsteps;




}

vector<double> spiceob::fevaluate(int rnk,vector<double>curValues,double stepsize){
  if(rnk==1){
      nxtValues[0]=4*exp(0.8*stepsize)-0.5*curValues[0];

      return nxtValues;




  }
}

vector< vector<double> > spiceob::fwdEuler(){

    //Define method here
}

vector< vector<double> > spiceob::bwdEuler(){

    //Define method here
}

vector< vector<double> > spiceob::trapEuler(){

    //Define method here
}

spiceob::~spiceob()
{
    //dtor
}
