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

#define MAX_INT 0xFFFFFF

template <typename T> class NodePrintOperationConst : public NodeOperationConst<T>
{
public:
    virtual ~NodePrintOperationConst() {}
    virtual void Action(const UndirectedGraphNode<T>* node) const
    {
        std::cout << " " << node->GetValue();
        
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
        if (edges > 0)
        {
        
            UndirectedGraph<int> graph;
            int minNodeValue = MAX_INT;
            
            for (int i = 0; i < edges; ++i)
            {
                int from = m[i + 1][0];
                int to = m[i + 1][1];
                if (from < minNodeValue)
                    minNodeValue = from;
                if (to < minNodeValue)
                    minNodeValue = to;
                
                graph.AddNode(from);
                graph.AddNode(to);
                graph.LinkNode(from, to);
            }
            NodePrintOperationConst<int> op;
            const UndirectedGraphNode<int>* minNode = graph.GetNode(minNodeValue);
            graph.DFSTraverseConst(op, minNode);
            graph.BFSTraverseConst(op, minNode);
        }
        
    }
    

    return 0;
}
