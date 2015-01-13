//
//  main.cpp
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "PATHelper.h"

int main(int argc, const char * argv[]) {

    std::fstream inFile(argv[1]);
    // for matrix input
    std::vector< std::vector<int> > m = PATHelper::parseToMatrix<int>(inFile, ' ');
    
    // for test print
    for (int i = 0; i < m.size(); ++i)
    {
        std::vector<int>& row = m[i];
        for (int j = 0; j < row.size(); ++j)
        {
            std::cout << row[j] << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}
