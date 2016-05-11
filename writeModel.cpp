//
//  writeModel.cpp
//  cspice
//
//  Created by Kaiyuan Liu on 5/2/16.
//  Copyright © 2016 Kaiyuan Liu. All rights reserved.
//

#include "writeModel.hpp"

void writeModel(string fileName, vector< vector <double> > outputValues, string direct){
    //MatDoub_IO input=parseFiles(trans, output, numTrans, numOutput);
    ofstream outfile;
    outfile.open("/Users/kaiyuanliu/Documents/SanDisk Data (Secure)/ECE MEng Works/Spring 2016/ECE 4960 - 001 - L401/Programming Assignment 5/cspice/cspice/"+fileName);
    if (outfile.is_open())
    {
        outfile << "V1(t) V2(t)\n";
        if(direct.compare("hor")==0){
            for(int i=0;i<outputValues[0].size();i++){
                outfile << outputValues[0][i]<<" "<<outputValues[1][i]<<"\n";
            }
        }
        else if(direct.compare("vert")==0)
            for(int i=0;i<outputValues.size();i++){
                outfile << outputValues[i][0]<<" "<<outputValues[i][1]<<"\n";
            }
        else
            cout<<"Error: Invalid direction";
        outfile.close();
    }
}
