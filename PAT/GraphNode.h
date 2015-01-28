//
//  GraphNode.h
//  PAT
//
//  Created by YuanXuan on 1/14/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_GraphNode_h
#define PAT_GraphNode_h

#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif

template <typename T> class GraphNode
{
public:
    typedef std::vector<GraphNode* > NodeList;
    typedef typename std::vector<GraphNode* >::iterator NodeListIter;
    
    GraphNode(T inValue)
    {
        value = inValue;
    }
    
    T GetValue() const
    {
        return value;
    }
    
    struct SortCompare {
        bool operator() (GraphNode* i,GraphNode* j) { return (i->GetValue()<j->GetValue());}
    } sortCompare;
    void AddNeighbour(GraphNode* node)
    {
        neighbours.push_back(node);
        std::sort(neighbours.begin(), neighbours.end(), sortCompare);
    }
    bool RemoveNeighbour(GraphNode* node)
    {
        NodeListIter it = std::find(neighbours.begin(), neighbours.end(), 5);
        if(it != neighbours.end())
            neighbours.erase(it);
    }
    
    
    const std::vector<GraphNode*> GetNeighbours() const
    {
        return neighbours;
    }
    
private:
    T value;
    std::vector<GraphNode* > neighbours;
};
#endif
