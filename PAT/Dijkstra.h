//
//  Dijkstra.h
//  PAT
//
//  Created by YuanXuan on 1/29/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Dijkstra_h
#define PAT_Dijkstra_h
#include "stlheaders.h"

using namespace std;

template <class T> class Dijkstra
{
    
private:
    struct NodeInfo
    {
        WeightedGraphNode<T>* fromNode;
        int distance;
        NodeInfo()
        :fromNode(NULL), distance(0x7fffffff)
        {
            
        }
    };

    
    set<WeightedGraphNode<T>*> unknownSet;
    map<WeightedGraphNode<T>*, NodeInfo> nodeInfoMap;

public:
    vector<T> Solution(vector<WeightedGraphNode<T>*>& graph, int startId, int destId)
    {
        // Initialize
        for (int i = 0; i < graph.size(); ++i)
        {
            unknownSet.insert(graph[i]);
            nodeInfoMap[graph[i]] = NodeInfo();
        }
            
        WeightedGraphNode<T>* start = graph[startId];
        WeightedGraphNode<T>* dest = graph[destId];
        
        // Traverse
        
        nodeInfoMap[start].distance = 0;
        queue<WeightedGraphNode<T>*> nodeQueue;
        nodeQueue.push(start);
        
        while (nodeQueue.size() > 0)
        {
            WeightedGraphNode<T>* node = nodeQueue.front();
            nodeQueue.pop();
            unknownSet.erase(node);
            NodeInfo currentInfo = nodeInfoMap[node];
            const typename WeightedGraphNode<T>::NodeList& neighbours = node->GetNeighbours();
            for (int i = 0; i < neighbours.size(); ++i)
            {
                pair<WeightedGraphNode<T>*, int> nodeWithWeight = neighbours[i];
                if (unknownSet.find(nodeWithWeight.first) != unknownSet.end())
                {
                    nodeQueue.push(nodeWithWeight.first);
                }
                    NodeInfo& neighbourInfo = nodeInfoMap[nodeWithWeight.first];
                    int newDistance = currentInfo.distance + nodeWithWeight.second;
                    if (newDistance < neighbourInfo.distance)
                    {
                        neighbourInfo.distance = newDistance;
                        neighbourInfo.fromNode = node;
                    }
                
            }
            for (int i = 0; i < graph.size(); ++i)
            {
                NodeInfo info = nodeInfoMap[graph[i]];
                cout << graph[i]->GetValue() + 1 << "\t" ;
                cout << (unknownSet.find(graph[i]) == unknownSet.end() ? "TRUE" : "FALSE") << "\t\t" ;
                if (info.distance == 0x7fffffff)
                {
                    cout << "+oo";
                }
                else
                {
                    cout << info.distance;
                    
                }
                    
                cout << "\t" << (info.fromNode == NULL ? -1 : info.fromNode->GetValue() + 1) << endl;
            }
            cout << "====================" << endl;
        }
        
        vector<T> result;
        WeightedGraphNode<T>* node = dest;
        
        while (node != NULL)
        {
            result.push_back(node->GetValue());
            node = nodeInfoMap[node].fromNode;
        }
        
         
         
         return result;
    }
};

#endif
