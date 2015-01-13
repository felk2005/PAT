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
    // insert code here...
    std::string str = "Hello   World !";
    std::cout << str << std::endl;
    std::vector<std::string> rtn = PATHelper::split(str, ' ');
    for (int i = 0; i < rtn.size(); ++i)
    {
        std::cout << rtn[i] << std::endl;
    }
    
    std::stringstream ss;
    ss << "1 2 3 4 5" << std::endl << "21 22 23 24 25";
    std::vector< std::vector<int> > m = PATHelper::parseToMatrix<int>(ss, ' ');
    
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
