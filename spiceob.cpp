#include "spiceob.h"
#include <cmath>
#include <iostream>

spiceob::spiceob(int initrnk,double initstepsize,int initsteps,vector<double>initial)
{

    rnk=initrnk;
    stepsize=initstepsize;
    numsteps=initsteps;
    curValues=initial;
    timeAdaptive=0;
}

spiceob::spiceob(int initrnk,double initstepsize,double initstop,vector<double>initial){
    rnk=initrnk;
    stepsize=initstepsize;
    stop=initstop;
    curValues=initial;
    timeAdaptive=1;
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

      //transistor circuit case
     // Model iD(curValues[1], curValues[0], 5*pow(10,-6), 0.7, 1.5, 26*pow(10,-3), 0.0);
     // temp[0]=-1*pow(10,8)*curValues[0]+pow(10,8)*current(t);
     // temp[1]= -1*pow(10,12)*iD.solveID()-2*pow(10,8)*curValues[1]+5*pow(10,8);
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
    if(!timeAdaptive){
        vec[0][0]=curValues[0];
        vec[1][0]=curValues[1];

        for(int i=1;i<numsteps;i++){

            nxtValues=fevaluate(rnk,curValues,t);
            curValues[0]=curValues[0]+nxtValues[0]*stepsize;
            //curValues[1]=curValues[1]+nxtValues[1]*stepsize;
            vec[0][i]=curValues[0];
            vec[1][i]=curValues[1];
            //cout<<"t:"<<t<<"val:"<<(curValues[0])<<endl;
            t+=stepsize;
        }

        curValues[0]=vec[0][0];
        curValues[1]=vec[1][0];
        return vec;
    }
    else{
        cout<<"Error a method without time adaptation cannot be used in a evironment with time adaptation\n";
        return vec;
    }

}

vector< vector<double> > spiceob::bwdEuler(){

    double v1next,v2next,v1,v2;
    double t=0;
    vector< vector<double> > vec(rnk, vector<double>(numsteps));

    if(!timeAdaptive){
        vec[0][0]=curValues[0];
        vec[1][0]=curValues[1];

        for(int i=0;i<numsteps;i++){

            //Used fixed point iteration to find next value
            v1=curValues[0];
            v2=curValues[1];
            nxtValues[0]=curValues[0];
            nxtValues[1]=curValues[1];


            v1next=v1;
            v2next=v2;



            for(int i=1; i<=500;i++){
                nxtValues=fevaluate(rnk,nxtValues,t+stepsize);

                v1next=curValues[0]+stepsize*nxtValues[0];
                v2next=curValues[1]+stepsize*nxtValues[1];

                nxtValues[0]=v1next;
                nxtValues[1]=v2next;

            }

            //
            curValues[0]=nxtValues[0];
            curValues[1]=nxtValues[1];
            vec[0][i]=curValues[0];
            vec[1][i]=curValues[1];

        }
        curValues[0]=vec[0][0];
        curValues[1]=vec[1][0];
        return vec;
    }
    else{
        cout<<"Error a method without time adaptation cannot be used in a evironment with time adaptation\n";
        return vec;
    }

}

vector< vector<double> > spiceob::trapEuler(){
    double t=0;
    vector< vector<double> > vec(rnk, vector<double>(numsteps));
    if(!timeAdaptive){
        vector<double>nxtIt(2,0);
        vec[0][0]=curValues[0];
        vec[1][0]=curValues[1];
        double v1pred,v2pred,v1cor,v2cor;

        for(int i=1;i<numsteps;i++){

            nxtValues=fevaluate(rnk,curValues,t);
            //FwdEuler
            v1pred=curValues[0]+nxtValues[0]*stepsize;
            v2pred=curValues[1]+nxtValues[1]*stepsize;


            nxtIt[0]=v1pred; nxtIt[1]=v2pred;

            nxtIt=fevaluate(rnk,nxtIt,t+stepsize);

            curValues[0]+=(nxtValues[0]+nxtIt[0])*(stepsize/2);
            curValues[1]+=(nxtValues[0]+nxtIt[0])*(stepsize/2);


            vec[0][i]=curValues[0];
            vec[1][i]=curValues[1];
            //cout<<"t:"<<t<<"val:"<<(curValues[0])<<endl;
            t+=stepsize;
        }
        curValues[0]=vec[0][0];
        curValues[1]=vec[1][0];
        return vec;
    }
    else{
        cout<<"Error a method without time adaptation cannot be used in a evironment with time adaptation\n";
        return vec;
    }

}

vector< vector<double> > spiceob::rk34Nt(){
    vector<double> kinit(rnk,0);
    vector< vector<double> > k(4,kinit);
    if(!timeAdaptive){
        vector< vector<double> > results(numsteps,kinit);
        vector<double> rk3;
        vector<double> rk4;
        vector<double> e;
        results[0]=curValues;
        double t=0;
        //loop for RK4 method
        for(int i=1;i<numsteps;i++){
            //calculate ks for RK4
            k[0]=fevaluate(rnk, curValues, t);

            k[1]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[0],stepsize/2)), t+stepsize/2);

            k[2]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[1],3*stepsize/4)), t+3*stepsize/4);

            rk3=rkDelta(k,3);

            k[3]=fevaluate(rnk, addToCurrVal(curValues,rk3), t+stepsize);

            rk4=rkDelta(k,4);

            curValues=addToCurrVal(curValues,rk4);

            e=addToCurrVal(rk3,multCurrValby(rk4,-1.0));

            results[i]=curValues;

            t=t+stepsize;
        }
        curValues=results[0];
        return results;
    }
    else{
        cout<<"Error a method without time adaptation cannot be used in a evironment with time adaptation\n";
        return k;
    }
}

vector< vector<double> > spiceob::rk34T(double tol1, double tol2){
    vector<double> kinit(rnk,0);
    vector< vector<double> > k(4,kinit);
    int totalSteps;
    if(timeAdaptive){
        vector< vector<double> > results(1,kinit);
        vector<double> rk3;
        vector<double> rk4;
        vector<double> e;
        results[0]=curValues;
        double initstep=stepsize;
        double t=0;
        results[0].push_back(t);
        //loop for RK4 method
        int i=1;
        while(t<stop){
            //calculate ks for RK4
            k[0]=fevaluate(rnk, curValues, t);

            k[1]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[0],stepsize/2)), t+stepsize/2);

            k[2]=fevaluate(rnk, addToCurrVal(curValues,multCurrValby(k[1],3*stepsize/4)), t+3*stepsize/4);

            rk3=rkDelta(k,3);

            k[3]=fevaluate(rnk, addToCurrVal(curValues,rk3), t+stepsize);

            rk4=rkDelta(k,4);

            curValues=addToCurrVal(curValues,rk4);

            e=addToCurrVal(rk3,multCurrValby(rk4,-1.0));

            //cout<<norm(e)<<", "<<norm(curValues)<<", "<<norm(e)/norm(curValues)<<"\n";

            if(norm(e)/norm(curValues)>tol1)
                stepsize=stepsize/2;
            else if(norm(e)/norm(curValues)<tol2)
                stepsize=2*stepsize;
            else
                stepsize=stepsize;


            results.push_back(kinit);
            results[i]=curValues;
            t=t+stepsize;
            results[i].push_back(t);
            i=i+1;
        }
        curValues=results[0];
        stepsize=initstep;
        return results;
    }
    else{
        cout<<"Error a method without time adaptation cannot be used in a evironment without time adaptation\n";
        return k;
    }
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

double spiceob::norm(vector<double> input){
    double sum=0.0;
    for(int i=0;i<input.size();i++){
        sum=sum+input[i]*input[i];
    }
    return sqrt(sum);
}

double spiceob::current(double t){
    if ((fmod(t*pow(10,9),20))>=0 && (fmod(t*pow(10,9),20))<=0.5){
        return (pow(10,-4)*t);
    }
    else if ((fmod(t*pow(10,9),20))>0.5 && (fmod(t*pow(10,9),20))<=20500){
        return (pow(10,-4));
    }
    else if ((fmod(t*pow(10,9),20))>20500 && (fmod(t*pow(10,9),20))<=20500.5){
        return (pow(10,-4)*-t);
    }
    else return 0;
}

spiceob::~spiceob()
{
    //dtor
}
