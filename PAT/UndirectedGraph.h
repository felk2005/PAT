//
//  Graph.h
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Graph_h
#define PAT_Graph_h
#include <vector>
#include <map>

template <typename T> class UndirectedGraphNode
{
public:
    typedef std::vector<UndirectedGraphNode* > NodeList;
    typedef typename std::vector<UndirectedGraphNode* >::iterator NodeListIter;
    
    UndirectedGraphNode(T inValue)
    {
        value = inValue;
    }
    
    void AddNeighbour(UndirectedGraphNode* node)
    {
        neighbours.push_back(node);
    }
    bool RemoveNeighbour(UndirectedGraphNode* node)
    {
        NodeListIter it = std::find(neighbours.begin(), neighbours.end(), 5);
        if(it != neighbours.end())
            neighbours.erase(it);
    }
    
    T GetValue()
    {
        return value;
    }
    
    const std::vector<UndirectedGraphNode*> GetNeighbours() const
    {
        return neighbours;
    }
    
private:
    T value;
    std::vector<UndirectedGraphNode* > neighbours;
};

template <typename T> class NodeOperationConst
{
public:
    virtual ~NodeOperationConst() {}
    virtual void Action(UndirectedGraphNode<T>* node) = 0;
};


template <typename T> class UndirectedGraph
{
private:
    typedef std::map<T, UndirectedGraph*> NodeMap;
    typedef typename NodeMap::iterator NodeMapIter;

private:
    std::map<T, UndirectedGraph*> nodeMap;

public:
    void AddNode(T value)
    {
        NodeMapIter it = nodeMap.find(value);
        if (it != nodeMap.end())
        {
            nodeMap[value] = new UndirectedGraphNode<T>(value);
        }
    }
    
    const UndirectedGraphNode<T>* GetNode(T value) const
    {
        NodeMapIter it = nodeMap.find(value);
        if (it != nodeMap.end())
        {
            return *it;
        }
        return NULL;
    }
    
//    bool RemoveNode(T value)
//    {
//        return false;
//    }
    
    void LinkNode(T from, T to)
    {
        NodeMapIter fromNode = nodeMap.find(from);
        NodeMapIter toNode = nodeMap.find(to);
        
        if (fromNode != nodeMap.end() && toNode != nodeMap.end())
        {
            (*fromNode)->AddNeighbour(*toNode);
            (*toNode)->AddNeighbour(*fromNode);
        }
    }
    
    void DFSTraverseConst(NodeOperationConst<T> op) const
    {
        
    }
    
    void BFSTraverseConst(NodeOperationConst<T> op) const
    {
        
    }
    
};

#endif
