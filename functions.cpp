#include <iostream>
#include <math.h>
#include "vector.h"
#include "matrix.h"
#include "functions.h"

using namespace std;

//2 parameters
double fevaluate(double par0,double par1,double x[],double y0[],int length){

    double fvalue=0;

   // if(getSize(x)!=getSize(&y0)){
     //   cout<<"File not read correctly"<<endl;
    //}

        for(int i=1; i <= length; ++i)
{
            //cout<<"xfunc:"<<x[i]<<endl;
            fvalue+=pow((par1*log(x[i-1])+log(par0)-log(y0[i-1])),2);


    }
    return fvalue;


}



//3 parameters
double fevaluate(double par0,double par1,double par2,vector<double>x1,vector<double>x2,vector<double>y,int length){

    double fvalue=0;

   // if(getSize(x)!=getSize(&y0)){
     //   cout<<"File not read correctly"<<endl;
    //}

        for(int index=0; index < length; index++)
{

            //fvalue+=pow((((par0*pow(log(1+exp((par1*(x1[index]-par2))/(2*.026))),2)-par0*pow(log(1+exp((par1*(x1[index]-par2)-x2[index])/(2*.026))),2)))-(y[index])),2);
            fvalue+=pow(((par0*exp(-x1[index]/par1) + (x2[0]-par0)*exp(-x1[index]/par2))-y[index]),2);

   //cout<<"par0: "<<par0<<" par1: "<<par1<<" par2: "<<par2<<" f "<<fvalue<<endl;
    }

    return fvalue;


}




void newton2(double par[],double dh,double x[],double y[],int length){
    Matrix <double>H(2,2);
    Vector<double>gradf(2);
    Vector<double>deltax(2);

    double par0=par[0];
    double par1=par[1];
      for(int i=0;i<=5;i++){

      gradf[0]=(fevaluate(par0+dh,par1,x,y,length)-fevaluate(par0-dh,par1,x,y,length))/(2*dh);
      gradf[1]=(fevaluate(par0,par1+dh,x,y,length)-fevaluate(par0,par1-dh,x,y,length))/(2*dh);

      //Construct hessian
      H[0][0]=(fevaluate(par0+dh,par1,x,y,length)-2*fevaluate(par0,par1,x,y,length)+fevaluate(par0-dh,par1,x,y,length))/pow(dh,2);
      H[0][1]=(fevaluate(par0+dh,par1+dh,x,y,length)-fevaluate(par0+dh,par1,x,y,length)-fevaluate(par0,par1+dh,x,y,length)+fevaluate(par0,par1,x,y,length))/pow(dh,2);
      H[1][0]=H[0][1];
      H[1][1]=(fevaluate(par0,par1+dh,x,y,length)-2*fevaluate(par0,par1,x,y,length)+fevaluate(par0,par1-dh,x,y,length))/pow(dh,2);
      deltax=-(H.inverse())*gradf;

      //Bissection to find t
      double c=1; int trial;


        if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],x,y,length))> (fevaluate(par0,par1,x,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],x,y,length))> (fevaluate(par0,par1,x,y,length))){
                c=c/2;

            }

        }
         else if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],x,y,length))< (fevaluate(par0,par1,x,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],x,y,length))< (fevaluate(par0,par1,x,y,length))){
                c=c*2;


            }
            c=c/2;
        }

    cout<<"c:"<<c<<endl;




      par0+=c*deltax[0];
      par1+=c*deltax[1];



      cout<<"par0:"<<par0<<endl;
      cout<<"par1:"<<par1<<endl;




      }
      par[0]=par0;
      par[1]=par1;

}

void newton3(double par[],double dh,vector<double> x1,vector<double> x2,vector<double> y,int length){
    Matrix <double>H(3,3);
    Vector<double>gradf(3);
    Vector<double>deltax(3);
    deltax[0]=1;deltax[1]=1;deltax[2]=1;//initialise to get through first loop

    double par0=par[0];
    double par1=par[1];
    double par2=par[2];
    double c=1;//Line search var


      for(int i=0; i<=5;i++){

      gradf[0]=(fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0-dh,par1,par2,x1,x2,y,length))/(2*dh);
      gradf[1]=(fevaluate(par0,par1+dh,par2,x1,x2,y,length)-fevaluate(par0,par1-dh,par2,x1,x2,y,length))/(2*dh);
      gradf[2]=(fevaluate(par0,par1,par2+dh,x1,x2,y,length)-fevaluate(par0,par1,par2-dh,x1,x2,y,length))/(2*dh);

      //Construct hessian
      H[0][0]=(fevaluate(par0+dh,par1,par2,x1,x2,y,length)-2*fevaluate(par0,par1,par2,x1,x2,y,length)+fevaluate(par0-dh,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[0][1]=(fevaluate(par0+dh,par1+dh,par2,x1,x2,y,length)-fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0,par1+dh,par2,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[0][2]=(fevaluate(par0+dh,par1,par2+dh,x1,x2,y,length)-fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0,par1,par2+dh,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[1][0]=H[0][1];
      H[1][1]=(fevaluate(par0,par1+dh,par2,x1,x2,y,length)-2*fevaluate(par0,par1,par2,x1,x2,y,length)+fevaluate(par0,par1-dh,par2,x1,x2,y,length))/pow(dh,2);
      H[1][2]=(fevaluate(par0,par1+dh,par2+dh,x1,x2,y,length)-fevaluate(par0,par1,par2+dh,x1,x2,y,length)-fevaluate(par0,par1+dh,par2,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[2][1]=H[1][2];
      H[2][2]=(fevaluate(par0,par1,par2+dh,x1,x2,y,length)-2*fevaluate(par0,par1,par2,x1,x2,y,length)+fevaluate(par0,par1,par2-dh,x1,x2,y,length))/pow(dh,2);

      deltax=-(H.inverse())*gradf;


      //Bissection to find t
        if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))> (fevaluate(par0,par1,par2,x1,x2,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))> (fevaluate(par0,par1,par2,x1,x2,y,length))){
                c=c/2;

            }

        }
         else if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))< (fevaluate(par0,par1,par2,x1,x2,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))< (fevaluate(par0,par1,par2,x1,x2,y,length))&& c<pow(2,40)){
                c=c*2;



            }
             c=c/2;

      }

      if(c<1){c=1;}
      par0+=c*deltax[0];
      par1+=c*deltax[1];
      par2+=c*deltax[2];

      cout<<"par0:"<<par0<<"par1:"<<par1<<"par2:"<<par2<<endl;
}
      cout<<"Newton completed"<<endl;
      cout<<"par0:"<<par0<<endl;
      cout<<"par1:"<<par1<<endl;
      cout<<"par2:"<<par2<<endl;
      cout<<"||V||"<<fevaluate(par0,par1,par2,x1,x2,y,length)<<endl;
}
void secant3(double par[],double dh,vector<double> x1,vector<double> x2,vector<double> y,int length){
    Matrix <double>H(3,3);
    Vector<double>gradf(3);
    Vector<double>deltax(3);

    double par0=par[0];
    double par1=par[1];
    double par2=par[2];

      //Determine values for first iteration

      gradf[0]=(fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0-dh,par1,par2,x1,x2,y,length))/(2*dh);
      gradf[1]=(fevaluate(par0,par1+dh,par2,x1,x2,y,length)-fevaluate(par0,par1-dh,par2,x1,x2,y,length))/(2*dh);
      gradf[2]=(fevaluate(par0,par1,par2+dh,x1,x2,y,length)-fevaluate(par0,par1,par2-dh,x1,x2,y,length))/(2*dh);

      //Construct hessian
      H[0][0]=(fevaluate(par0+dh,par1,par2,x1,x2,y,length)-2*fevaluate(par0,par1,par2,x1,x2,y,length)+fevaluate(par0-dh,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[0][1]=(fevaluate(par0+dh,par1+dh,par2,x1,x2,y,length)-fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0,par1+dh,par2,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[0][2]=(fevaluate(par0+dh,par1,par2+dh,x1,x2,y,length)-fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0,par1,par2+dh,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[1][0]=H[0][1];
      H[1][1]=(fevaluate(par0,par1+dh,par2,x1,x2,y,length)-2*fevaluate(par0,par1,par2,x1,x2,y,length)+fevaluate(par0,par1-dh,par2,x1,x2,y,length))/pow(dh,2);
      H[1][2]=(fevaluate(par0,par1+dh,par2+dh,x1,x2,y,length)-fevaluate(par0,par1,par2+dh,x1,x2,y,length)-fevaluate(par0,par1+dh,par2,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[2][1]=H[1][2];
      H[2][2]=(fevaluate(par0,par1,par2+dh,x1,x2,y,length)-2*fevaluate(par0,par1,par2,x1,x2,y,length)+fevaluate(par0,par1,par2-dh,x1,x2,y,length))/pow(dh,2);

      deltax=-(H.inverse())*gradf;


      //Bissection to find t
      double c=1; int trial;


        if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))> (fevaluate(par0,par1,par2,x1,x2,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))> (fevaluate(par0,par1,par2,x1,x2,y,length))){
                c=c/2;

            }

        }
         else if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))< (fevaluate(par0,par1,par2,x1,x2,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))< (fevaluate(par0,par1,par2,x1,x2,y,length))&& c<pow(2,40)){
                c=c*2;



            }
            c=c/2;

                }


      par0+=c*deltax[0];
      par1+=c*deltax[1];
      par2+=c*deltax[2];
      par[0]=par0;
      par[1]=par1;
      par[2]=par2;

      //for remaining iterations use difference between functions to determine jacobian

      for(int i=0;((fevaluate(par0,par1,par2,x1,x2,y,length)-(fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length))))!=0 && i<=50;i++){
      gradf[0]=(fevaluate(par0+dh,par1,par2,x1,x2,y,length)-fevaluate(par0-dh,par1,par2,x1,x2,y,length))/(2*dh);
      gradf[1]=(fevaluate(par0,par1+dh,par2,x1,x2,y,length)-fevaluate(par0,par1-dh,par2,x1,x2,y,length))/(2*dh);
      gradf[2]=(fevaluate(par0,par1,par2+dh,x1,x2,y,length)-fevaluate(par0,par1,par2-dh,x1,x2,y,length))/(2*dh);

      //Construct hessian
      H[0][0]=(fevaluate(par0,par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length)-2*fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length)+fevaluate(par0-2*c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length))/(c*deltax[0]*c*deltax[0]);
      H[0][1]=(fevaluate(par0,par1,par2-c*deltax[2],x1,x2,y,length)-fevaluate(par0,par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length)-fevaluate(par0-c*deltax[0],par1,par2-c*deltax[2],x1,x2,y,length)+fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length))/(c*deltax[0]*c*deltax[1]);
      H[0][2]=(fevaluate(par0,par1-c*deltax[1],par2,x1,x2,y,length)-fevaluate(par0,par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length)-fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2,x1,x2,y,length)+fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length))/(c*deltax[0]*c*deltax[2]);
      H[1][0]=H[0][1];
      H[1][1]=(fevaluate(par0-c*deltax[0],par1,par2-c*deltax[2],x1,x2,y,length)-2*fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length)+fevaluate(par0-c*deltax[0],par1-2*c*deltax[1],par2-c*deltax[2],x1,x2,y,length))/(c*deltax[1]*c*deltax[1]);
      H[1][2]=(fevaluate(par0,par1+dh,par2+dh,x1,x2,y,length)-fevaluate(par0,par1,par2+dh,x1,x2,y,length)-fevaluate(par0,par1+dh,par2,x1,x2,y,length)+fevaluate(par0,par1,par2,x1,x2,y,length))/pow(dh,2);
      H[2][1]=H[1][2];
      H[2][2]=(fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2,x1,x2,y,length)-2*fevaluate(par0-c*deltax[0],par1-c*deltax[1],par2-c*deltax[2],x1,x2,y,length)+fevaluate(par0-c*deltax[0],par1-c*deltax[0],par2-2*c*deltax[0],x1,x2,y,length))/(c*deltax[2]*c*deltax[2]);

      deltax=-(H.inverse())*gradf;


      //Bissection to find t
       c=1;


        if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))> (fevaluate(par0,par1,par2,x1,x2,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))> (fevaluate(par0,par1,par2,x1,x2,y,length))){
                c=c/2;

            }

        }
         else if ((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))< (fevaluate(par0,par1,par2,x1,x2,y,length))){
            while((fevaluate(par0+c*deltax[0],par1+c*deltax[1],par2+c*deltax[2],x1,x2,y,length))< (fevaluate(par0,par1,par2,x1,x2,y,length))&& c<pow(2,40)){
                c=c*2;



            }
            c=c/2;

                }



      if(c<1){c=1;}
      par0+=c*deltax[0];
      par1+=c*deltax[1];
      par2+=c*deltax[2];


      }
      cout<<"Secant completed"<<endl;
      cout<<"par0:"<<par0<<endl;
      cout<<"par1:"<<par1<<endl;
      cout<<"par2:"<<par2<<endl;
      cout<<"||V||"<<fevaluate(par0,par1,par2,x1,x2,y,length)<<endl;



}

void fullSearch (vector<double> par0,vector<double> par1,vector<double> par2,vector<double> x1,vector<double> x2,vector<double> y,int length){


    double par0m,par1m,par2m;
    double fmin=fevaluate(par0[0],par1[0],par2[0],x1,x2,y,length);
    for(int i=0;i<par0.size();i++){
        for(int j=0;j<par1.size();j++){
            for(int k=0;k<par2.size();k++){
                if(fevaluate(par0[i],par1[j],par2[k],x1,x2,y,length)<=fmin){
                    fmin=fevaluate(par0[i],par1[j],par2[k],x1,x2,y,length);
                    par0m=par0[i];par1m=par1[j];par2m=par2[k];
                }
            }
        }
    }
    cout<<"Full search completed"<<endl;
    cout<<"par0:"<<par0m<<endl;
    cout<<"par1:"<<par1m<<endl;
    cout<<"par2:"<<par2m<<endl;
    cout<<"||V||"<<fevaluate(par0m,par1m,par2m,x1,x2,y,length)<<endl;

}
