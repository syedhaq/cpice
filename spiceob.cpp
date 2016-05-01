#include "spiceob.h"
#include <cmath>

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
  else{
     std::cout<<"Error: Rank is not 1";
     return nxtValues;
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

vector< vector<double> > spiceob::rk34Nt(){
    vector< vector<double> > k;
    vector<double> initialVals=curValues; //saves the initial values so they don't get lost.
    //loop for RK4 method
    for(int i=0;i<=numsteps;i++){
        //calculate ks for RK4
        k[0]=fevaluate(rnk, curValues, i);
        k[1]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[0],stepsize/2)), i+stepsize/2);
        k[2]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[1],3*stepsize/2)), i+3*stepsize/2);
        k[3]=fevaluate(rnk, addToCurrVal(curValues,rkDelta(k,3)), i+stepsize);
        curValues=addToCurrVal(curValues,rkDelta(k, 4));
        allvalues[i]=curValues;
    }
    curValues=initialVals;
    return allvalues;
}

vector< vector<double> > spiceob::rk34T(){
    vector< vector<double> > results;
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
        std::cout<<"Dimension Error: dimensions of both vectors must be the same!";
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
    vector<double> delta;
    if(order==3){
        for(int i=0;i<k.size();i++){
            delta[i]=1/9*(2*k[i][0]+3*k[i][1]+4*k[i][2])*stepsize;
        }
    }
    else if(order==4){
        for(int i=0;i<k.size();i++){
            delta[i]=1/24*(7*k[i][0]+6*k[i][1]+8*k[i][2]+3*k[i][3])*stepsize;
        }
    }
    else
        std::cout<<"Error: Invalid RK order. Order must be 3 or 4";
    return delta;
}

spiceob::~spiceob()
{
    //dtor
}
