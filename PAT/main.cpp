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
#include "UndirectedGraph.h"

template <typename T> class NodePrintOperationConst : public NodeOperationConst<T>
{
public:
    virtual ~NodePrintOperationConst() {}
    virtual void Action(UndirectedGraphNode<T>* node)
    {
        std::cout << "{ " << node->GetValue();
        const std::vector<UndirectedGraphNode<T>*> neighbours = node->GetNeighbours();
        for (int i = 0; i < neighbours.size(); ++i)
        {
            std::cout << ' ' << neighbours[i]->GetValue();
        }
        std::cout << " }" << std::endl;
        
    }
};

int main(int argc, const char * argv[]) {

    std::fstream inFile(argv[1]);
    int nodes = 0;
    int edges = 0;
    // for matrix input
    std::vector< std::vector<int> > m = PATHelper::parseToMatrix<int>(inFile, ' ');
    if (m.size() > 0 && m[0].size() > 1)
    {
        nodes = m[0][0];
        edges = m[0][1];
        
        for (int i = 0; i < nodes; ++i)
        {
            
        }
        
        
    }
    
//    // for test print
//    for (int i = 0; i < m.size(); ++i)
//    {
//        std::vector<int>& row = m[i];
//        for (int j = 0; j < row.size(); ++j)
//        {
//            std::cout << row[j] << "\t";
//        }
//        std::cout << std::endl;
//    }
    return 0;
}
