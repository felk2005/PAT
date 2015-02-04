//
//  main.cpp
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif

#include "SimpleHashSet.h"

using namespace std;
int main(int argc, const char * argv[]) {
    fstream file(argv[1]);
    istream& stream = file;
    int maxSize, inputCount;
    stream >> maxSize >> inputCount;
    
    SimpleHashSet shs(maxSize);
    for (int i = 0; i < inputCount; ++i)
    {
        int val;
        stream >> val;
        if (i != 0)
            cout << ' ';
        int value = shs.Insert(val);
        if (value < 0)
            cout << '-';
        else
            cout << value;
    }
    

    return 0;
}
