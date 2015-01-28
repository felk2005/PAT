//
//  WeightedGraphNode.h
//  PAT
//
//  Created by YuanXuan on 1/28/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_WeightedGraphNode_h
#define PAT_WeightedGraphNode_h
#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif

template <typename T> class WeightedGraphNode
{
public:
    typedef std::vector<std::pair<WeightedGraphNode*, int> > NodeList;
    typedef typename NodeList::iterator NodeListIter;
private:
    T value;
    //NodeList neighbours;
    NodeList neighbours;
public:
    WeightedGraphNode(T inValue)
    {
        value = inValue;
    }
    
    T GetValue() const
    {
        return value;
    }

    void AddNeightbour(WeightedGraphNode* node)
    {
        AddNeightbour(node, 0);
    }
    void AddNeightbour(WeightedGraphNode* node, int weight)
    {
        neighbours.push_back(std::make_pair(node, weight));
    }
    

    bool RemoveNeighbour(WeightedGraphNode* node)
    {
        NodeListIter it = neighbours.begin();
        for(; it != neighbours.end(); ++it)
        {
            if (it->first == node)
            {
                break;
            }
        }
        if(it != neighbours.end())
        {
            neighbours.erase(it);
        }
    }
    
    
    const NodeList& GetNeighbours() const
    {
        return neighbours;
    }
    
    struct SortCompare {
        bool operator() (WeightedGraphNode* i,WeightedGraphNode* j) { return (i->GetValue()<j->GetValue());}
    } sortCompare;
    
    void SortNeighbours()
    {
        SortNeighbours(sortCompare);
    }
    template <class _Compare> void SortNeighbours(_Compare compare)
    {
        std::sort(neighbours.begin(), neighbours.end(), compare);
    }
};

#endif
