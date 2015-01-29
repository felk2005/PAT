//
//  Solution.h
//  PAT
//
//  Created by YuanXuan on 1/29/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Solution_h
#define PAT_Solution_h


#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif
#include "Common/WeightedGraphNode.h"
using namespace std;
template <class T> struct NodeInfo
{
    int distance;
    vector<WeightedGraphNode<int>*> fromNodes;
    NodeInfo()
    : distance(0x7fffffff)
    {
        
    }
};

class Solution
{
private:
    set<WeightedGraphNode<int>*> unknownSet;
    map<WeightedGraphNode<int>*, NodeInfo<int> > nodeInfoMap;

    
public:

    map<WeightedGraphNode<int>*, NodeInfo<int> >& Resolve(vector<WeightedGraphNode<int>* >& graph, int startId)
    {
        
        
        // Initialize
        for (int i = 0; i < graph.size(); ++i)
        {
            unknownSet.insert(graph[i]);
            nodeInfoMap[graph[i]] = NodeInfo<int>();
        }
        
        WeightedGraphNode<int>* start = graph[startId];
        
        // Traverse
        
        nodeInfoMap[start].distance = 0;
        queue<WeightedGraphNode<int>*> nodeQueue;
        nodeQueue.push(start);
        
        while (nodeQueue.size() > 0)
        {
            WeightedGraphNode<int>* node = nodeQueue.front();
            nodeQueue.pop();
            unknownSet.erase(node);
            NodeInfo<int> currentInfo = nodeInfoMap[node];
            const typename WeightedGraphNode<int>::NodeList& neighbours = node->GetNeighbours();
            for (int i = 0; i < neighbours.size(); ++i)
            {
                pair<WeightedGraphNode<int>*, int> nodeWithWeight = neighbours[i];
                
                if (unknownSet.find(nodeWithWeight.first) != unknownSet.end())
                {
                    nodeQueue.push(nodeWithWeight.first);
                }
                NodeInfo<int>& neighbourInfo = nodeInfoMap[nodeWithWeight.first];
                int newDistance = currentInfo.distance + nodeWithWeight.second;
                if (newDistance < neighbourInfo.distance)
                {
                    neighbourInfo.distance = newDistance;
                    neighbourInfo.fromNodes.clear();
                    neighbourInfo.fromNodes.push_back(node);
                }
                else if (newDistance == neighbourInfo.distance)
                {
                    neighbourInfo.fromNodes.push_back(node);
                }
            }
        }
        return nodeInfoMap;
    }
    
};

#endif
