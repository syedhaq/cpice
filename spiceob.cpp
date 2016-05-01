#include "spiceob.h"
#include <cmath>
#include <iostream>

spiceob::spiceob(int initrnk,double initstepsize,int initsteps,vector<double>initial)
{

  rnk=initrnk;
  stepsize=initstepsize;
  numsteps=initsteps;
  curValues=initial;
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
      //cout<<(current(t))<<" ";
      temp[1]= pow(10,8)*curValues[0]-2*pow(10,8)*curValues[1];
      return temp;

  }
  else{
     std::cout<<"Error: Rank is not valid rank";
     return nxtValues;
  }
}

vector< vector<double> > spiceob::fwdEuler(){
    double t=0;
    vector< vector<double> > vec(rnk, vector<double>(numsteps));
    vec[0][0]=curValues[0];
    vec[1][0]=curValues[1];

    for(int i=1;i<numsteps;i++){

        nxtValues=fevaluate(rnk,curValues,t);
        curValues[0]=curValues[0]+nxtValues[0]*stepsize;
        curValues[1]=curValues[1]+nxtValues[1]*stepsize;
        vec[0][i]=curValues[0];
        vec[1][i]=curValues[1];
        //cout<<"t:"<<t<<"val:"<<(curValues[0])<<endl;
        t+=stepsize;
    }

    curValues[0]=vec[0][0];
    curValues[1]=vec[1][0];
    return vec;


}

//vector< vector<double> > spiceob::bwdEuler(){

    //Define method here
//}

//vector< vector<double> > spiceob::trapEuler(){

    //Define method here
//}

vector< vector<double> > spiceob::rk34Nt(){
    vector<double> kinit(rnk,0);
    vector< vector<double> > k(4,kinit);
    vector< vector<double> > results(numsteps,kinit);
    results[0]=curValues;
    double t=0;
    //loop for RK4 method
    for(int i=1;i<numsteps;i++){
        //calculate ks for RK4
        k[0]=fevaluate(rnk, curValues, t);
        
        k[1]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[0],stepsize/2)), t+stepsize/2);
        
        k[2]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[1],3*stepsize/4)), t+3*stepsize/4);
        
        k[3]=fevaluate(rnk, addToCurrVal(curValues,rkDelta(k,3)), t+stepsize);
        
        curValues=addToCurrVal(curValues,rkDelta(k,4));
            
        results[i]=curValues;
        t=t+stepsize;
    }
    curValues=results[0];
    return results;
}

vector< vector<double> > spiceob::rk34T(){
    vector<double> kinit(rnk,0);
    vector< vector<double> > k(4,kinit);
    vector< vector<double> > results(numsteps,kinit);
    results[0]=curValues;
    double t=0;
    //loop for RK4 method
    for(int i=1;i<numsteps;i++){
        //calculate ks for RK4
        k[0]=fevaluate(rnk, curValues, t);
        
        k[1]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[0],stepsize/2)), t+stepsize/2);
        
        k[2]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[1],3*stepsize/2)), t+3*stepsize/2);
        
        k[3]=fevaluate(rnk, addToCurrVal(curValues,rkDelta(k,3)), t+stepsize);
        
        curValues=addToCurrVal(curValues,rkDelta(k,4));
        
        results[i]=curValues;
        t=t+stepsize;
    }
    curValues=results[0];

    return results;
}

vector<double> spiceob::addToCurrVal(vector<double>curValues,double increment){
    for(int i=0;i<curValues.size();i++){
        curValues[i]=curValues[i]+increment;
    }
    return curValues;
}

vector<double> spiceob::addToCurrVal(vector<double>curValues,vector<double> increment){
    if(curValues.size()!=increment.size()){
        std::cout<<"Dimension Error: dimensions of both vectors must be the same!\n";
        return curValues;
    }
    for(int i=0;i<curValues.size();i++){
        curValues[i]=curValues[i]+increment[i];
    }
    return curValues;
}

vector<double> spiceob::multCurrValby(vector<double>curValues,double factor){
    for(int i=0;i<curValues.size();i++){
        curValues[i]=curValues[i]*factor;
    }
    return curValues;
}

vector<double> spiceob::rkDelta(vector< vector<double> > k, int order){
    vector<double> delta(rnk,0);
    if(order==3){
        for(int i=0;i<rnk;i++){
            delta[i]=1.0/9.0*(2*k[0][i]+3*k[1][i]+4*k[2][i])*stepsize;
        }
    }
    else if(order==4){
        for(int i=0;i<rnk;i++){
            delta[i]=1.0/24.0*(7*k[0][i]+6*k[1][i]+8*k[2][i]+3*k[3][i])*stepsize;
        }
    }
    else
        std::cout<<"Error: Invalid RK order. Order must be 3 or 4";
    return delta;
}

double spiceob::current(double t){
    if ((fmod(t*pow(10,9),20))>=0 && (fmod(t*pow(10,9),20))<=1){
        return (pow(10,-4)*t);
    }
    else if ((fmod(t*pow(10,9),20))>1 && (fmod(t*pow(10,9),20))<=10){
        return (pow(10,-4));
    }
    else if ((fmod(t*pow(10,9),20))>10 && (fmod(t*pow(10,9),20))<=11){
        return (pow(10,-4)*-t);
    }
    else return 0;
}

spiceob::~spiceob()
{
    //dtor
}
