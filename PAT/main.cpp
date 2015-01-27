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
#include <fstream>
#include <vector>
#include "AVLTree.h"

using namespace std;
int main(int argc, const char * argv[]) {

    fstream inFile(argv[1]);
    istream& stream = inFile;
    int count = 0;
    stream >> count;
    AVLTree tree;
    while (--count >= 0)
    {
        int v;
        stream >> v;
        tree.Add(v);
        tree.PrintTree();
        cout << endl << "=========================" << endl;
    }
    cout << tree.GetRoot()->value << endl;
    
    
    
    return 0;
}
