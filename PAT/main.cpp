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
#include "Common/WeightedGraphNode.h"
#include "Solution.h"
//#include "Dijkstra.h"
using namespace std;


map<pair<int, int>, int> expenseMap;

int GetPath(map<WeightedGraphNode<int>*, NodeInfo<int> >& result, WeightedGraphNode<int>* destNode, vector<int>& steps)
{
    if (destNode == NULL || result.find(destNode) == result.end())
        return 0;
    
    NodeInfo<int>& info = result[destNode];
    
    int minCost = 0x7fffffff;
    int minCostNodeIndex = -1;
//    cout << destNode->GetValue() << ":";
    
//    for (int i = 0; i < info.fromNodes.size(); ++i)
//    {
//        cout << "\t" << info.fromNodes[i]->GetValue();
//    }
    
//    cout << endl;
    vector<vector<int> > resultList(info.fromNodes.size());
    
    for (int i = 0; i < info.fromNodes.size(); ++i)
    {
        WeightedGraphNode<int>* fromNode = info.fromNodes[i];
        
        int cost = GetPath(result, fromNode, resultList[i]);
        int thisCost = expenseMap[make_pair(min(fromNode->GetValue(), destNode->GetValue()), max(fromNode->GetValue(), destNode->GetValue()))];

        cost += thisCost;
        
        if (cost < minCost)
        {
            minCost = cost;
            minCostNodeIndex = i;
        }
    }
    if (minCostNodeIndex == -1)
    {
        return 0;
    }
    
    WeightedGraphNode<int>* fromNode = info.fromNodes[minCostNodeIndex];
    steps.insert(steps.begin(), resultList[minCostNodeIndex].begin(), resultList[minCostNodeIndex].end());
    steps.push_back(fromNode->GetValue());
    
    return minCost;
    
        
    return 0;
}

int main(int argc, const char * argv[]) {
    

//    ifstream filestream(argv[1]);
    istream& stream = cin;
    
    int nodeNum, edgeNum, startId, destId;
    stream >> nodeNum >> edgeNum >> startId >> destId;
    
    // build graph
    vector<WeightedGraphNode<int>* > graph;
    for(int i = 0; i < nodeNum; ++i)
    {
        graph.push_back(new WeightedGraphNode<int>(i));
    }
    
    // read edges and build expense map
    for (int i = 0; i < edgeNum; ++i)
    {
        int start, end, weight, cost;
        stream >> start >> end >> weight >> cost;
        graph[start]->AddNeightbour(graph[end], weight);
        graph[end]->AddNeightbour(graph[start], weight);
        expenseMap[make_pair(min(start, end), max(start, end))] = cost;
    }

    
    map<WeightedGraphNode<int>*, NodeInfo<int> >& result = (new Solution())->Resolve(graph, startId);
    WeightedGraphNode<int>* destNode = graph[destId];
    
    
    // trace back result
    vector<int> steps;
    int cost = GetPath(result, destNode, steps);
    steps.push_back(destNode->GetValue());
    
    cout << steps.size() << " " << cost;
    
//    cout << endl;
//    for (int i = 0; i < steps.size(); ++i)
//    {
//        cout << steps[i] << endl;
//    }
    

    
   
    
    
    return 0;
}
