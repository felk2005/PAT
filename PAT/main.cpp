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
    int nodes = 0;
    int edges = 0;
    // for matrix input
    std::vector< std::vector<int> > m = PATHelper::parseToMatrix<int>(std::cin, ' ');
    if (m.size() > 0 && m[0].size() > 1)
    {
        nodes = m[0][0];
        edges = m[0][1];
        UndirectedGraph<int> graph;
        if (nodes > 0)
        {
            for (int i = 0; i < nodes; ++i)
            {
                graph.AddNode(i);
            }
        }
        if (edges > 0)
        {
            
            for (int i = 0; i < edges; ++i)
            {
                int from = m[i + 1][0];
                int to = m[i + 1][1];
                
                graph.LinkNode(from, to);
            }
        }
        int minNodeValue = 0;
        NodePrintOperationConst<int> op;
        const UndirectedGraphNode<int>* minNode = graph.GetNode(minNodeValue);
        graph.DFSTraverseConst(op, minNode);
        graph.BFSTraverseConst(op, minNode);

        
    }
    

    return 0;
}
