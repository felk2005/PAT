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
#include "WeightedGraphNode.h"
#include "Dijkstra.h"
using namespace std;
//template <class T> struct NodeInfo
//{
//    WeightedGraphNode<T>* fromNode;
//    int distance;
//    NodeInfo()
//    :fromNode(NULL), distance(0x7fffffff)
//    {
//        
//    }
//};

int main(int argc, const char * argv[]) {
    

    ifstream filestream(argv[1]);
    istream& stream = filestream;
    
    int nodeNum, edgeNum, startId, destId;
    stream >> nodeNum >> edgeNum >> startId >> destId;
    
    // build graph
    vector<WeightedGraphNode<int>* > nodeList;
    for(int i = 0; i < nodeNum; ++i)
    {
        nodeList.push_back(new WeightedGraphNode<int>(i));
    }
    
    // read edges and build expense map
    map<pair<int, int>, int> expenseMap;
    for (int i = 0; i < edgeNum; ++i)
    {
        int start, end, weight, cost;
        stream >> start >> end >> weight >> cost;
        nodeList[start]->AddNeightbour(nodeList[end], weight);
        nodeList[end]->AddNeightbour(nodeList[start], weight);
        expenseMap[make_pair(min(start, end), max(start, end))] = cost;
    }

//    
//    set<WeightedGraphNode<int>*> unknownSet;
//    map<WeightedGraphNode<int>*, NodeInfo<int> > nodeInfoMap;
    
    vector<int> result = (new Dijkstra<int>)->Solution(nodeList, startId, destId);
    for (int i = 0; i < result.size(); ++i)
    {
        cout << result[i] << endl;
    }
    return 0;
}
