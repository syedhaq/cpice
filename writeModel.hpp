//
//  writeModel.hpp
//  cspice
//
//  Created by Kaiyuan Liu on 5/2/16.
//  Copyright © 2016 Kaiyuan Liu. All rights reserved.
//

#ifndef writeModel_hpp
#define writeModel_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

//write model data to file for graphing
void writeModel(string fileName, vector< vector <double> > outputValues, string direct);

#endif /* writeModel_hpp */
