//
//  Model.cpp
//  Parameter Extraction from Least-Square Fitting
//
//  Created by Kaiyuan Liu on 3/31/16.
//  Copyright © 2016 Kaiyuan Liu. All rights reserved.
//

#include "Model.hpp"
#include <cmath>

Model::Model(double vt){
    m_vgs=0;
    m_vds=0;
    m_vt=vt;
    m_id=0;
    setParams(0,0,0);
}
Model::Model(double vgs, double vds, double is, double k, double vth, double vt,double id){
    m_vgs=vgs;
    m_vds=vds;
    m_vt=vt;
    m_id=id;
    setParams(is,k,vth);
}
double Model::solveID(){
    double id=m_is*(log(1+exp((m_k*(m_vgs-m_vth))/(2*m_vt))))*(log(1+exp((m_k*(m_vgs-m_vth))/(2*m_vt))))-m_is*(log(1+exp((m_k*(m_vgs-m_vth)-m_vds)/(2*m_vt))))*(log(1+exp((m_k*(m_vgs-m_vth)-m_vds)/(2*m_vt))));
    return id;
}
double Model::solveIDDivIDm(){
    return solveID()/m_id;
}
double Model::solveLogID(){
    return log10(solveID());
}
void Model::setIs(double is){
    m_is=is;
}
void Model::setK(double k){
    m_k=k;
}
void Model::setVth(double vth){
    m_vth=vth;
}
void Model::setVgs(double vgs){
    m_vgs=vgs;
}
void Model::setVds(double vds){
    m_vds=vds;
}
void Model::setVt(double vt){
    m_vt=vt;
}
void Model::setId(double id){
    m_id=id;
}
void Model::setParams(double is, double k, double vth){
    m_is=is;
    m_k=k;
    m_vth=vth;
}
double Model::getIs(){
    return m_is;
}
double Model::getK(){
    return m_k;
}
double Model::getVth(){
    return m_vth;
}
double *Model::getParams(){
    double *params=new double[3];
    params[0]=m_is;
    params[1]=m_k;
    params[2]=m_vth;
    return params;
}