#include "spiceob.h"
#include <cmath>
#include <iostream>

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

  else if(rnk==2){
      vector<double>temp(2,0);
      //linear circuit case
      temp[0]=-2*pow(10,8)*curValues[0]+pow(10,8)*curValues[1]+current(t)*pow(10,12);
      temp[1]= pow(10,8)*curValues[0]-2*pow(10,8)*curValues[1];
      return temp;

  }
  else{
     cout<<"Warning: Rank is not 1";
     return nxtValues;
  }
}

vector< vector<double> > spiceob::fwdEuler(){


            double t=0;
            vector< vector<double> > vec(rnk, vector<double>(numsteps));
            vec[0][0]=curValues[0];
            vec[0][1]=curValues[1];

        for(int i=1;i<numsteps;i++){

            nxtValues=fevaluate(rnk,curValues,t);
            curValues[0]=curValues[0]+nxtValues[0]*stepsize;
            curValues[1]=curValues[1]+nxtValues[1]*stepsize;
            vec[0][i]=curValues[0];
            vec[1][i]=curValues[1];
            //cout<<"t:"<<t<<"val:"<<(curValues[0])<<endl;
            t+=stepsize;

        }

    return vec;


}
    //Define method here
//}

//vector< vector<double> > spiceob::bwdEuler(){

    //Define method here
//}


//spiceob::trapEuler(){

    //Define method here
//}
//vector< vector<double> > spiceob::trapEuler(){

    //Define method here
//}

double spiceob::current(double t){
    if ((fmod(t,20))>=0 && (fmod(t,20))<=1){
        return (pow(10,-4)*t);
    }
    else if ((fmod(t,20))>1 && (fmod(t,20))<=10){
        return (pow(10,-4));
    }
    else if ((fmod(t,20))>10 && (fmod(t,20))<=11){
        return (pow(10,-4)*-t);
    }
    else return 0;

}

spiceob::~spiceob()
{
    //dtor
}
