//
//  Model.hpp
//  Parameter Extraction from Least-Square Fitting
//
//  Created by Kaiyuan Liu on 3/31/16.
//  Copyright © 2016 Kaiyuan Liu. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

class Model
{
private:
    double m_is,m_k,m_vth,m_vgs,m_vds,m_vt,m_id;
    
public:
    Model(double vt);
    Model(double vgs, double vds, double is, double k, double vth,double vt,double id);
    double solveID();
    double solveIDDivIDm();
    double solveLogID();
    void setIs(double is);
    void setK(double k);
    void setVth(double vth);
    void setVgs(double vgs);
    void setVds(double vds);
    void setVt(double vt);
    void setId(double id);
    void setParams(double is, double k, double vth);
    double getIs();
    double getK();
    double getVth();
    double *getParams();
};

#endif /* Model_hpp */
