#include "spiceob.h"
#include <cmath>

spiceob::spiceob(int initrnk,double initstepsize,int initsteps,vector<double>initial)
{

  rnk=initrnk;
  stepsize=initstepsize;
  numsteps=initsteps;

  for(int i=0;i<initrnk;i++){
    curValues.push_back(initial[i]);
  }

    for(int i=0;i<initrnk;i++){
    nxtValues.push_back(0);
  }











}

vector<double> spiceob::fevaluate(int rnk,vector<double>curValues,double t){


  if(rnk==1){
      vector<double>temp(1,0);
      temp[0]=(4*exp(0.8*t))-(0.5*curValues[0]);
      return temp;




  }
}

vector< vector<double> > spiceob::fwdEuler(){

    if (rnk==1){
            double t=0;
            vector< vector<double> > vec(1, vector<double>(numsteps));
            vec[0][0]=curValues[0];

        for(int i=1;i<numsteps;i++){

            nxtValues=fevaluate(rnk,curValues,t);
            curValues[0]=curValues[0]+nxtValues[0];
            vec[0][i]=curValues[0];
            //cout<<"t:"<<t<<"val:"<<(curValues[0])<<endl;
            t+=stepsize;

        }

    return vec;
    }

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
