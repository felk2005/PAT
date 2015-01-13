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
    typedef std::map<T, UndirectedGraphNode<T>*> NodeMap;
    typedef typename std::map<T, UndirectedGraphNode<T>*>::iterator NodeMapIter;

private:
    NodeMap nodeMap;

public:
    UndirectedGraphNode<T>* AddNode(T value)
    {
        NodeMapIter it = nodeMap.find(value);
        if (it == nodeMap.end())
        {
            UndirectedGraphNode<T>* newNode = new UndirectedGraphNode<T>(value);
            nodeMap[value] = newNode;
            return newNode;
        }
        return it->second;
        
    }
    
    const UndirectedGraphNode<T>* GetNode(T value) const
    {
        NodeMapIter it = nodeMap.find(value);
        if (it != nodeMap.end())
        {
            return it->second;
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
            fromNode->second->AddNeighbour(toNode->second);
            toNode->second->AddNeighbour(fromNode->second);
        }
    }
    
    void LinkNode(UndirectedGraphNode<T>* from, UndirectedGraphNode<T>* to)
    {
        if (from != NULL && to != NULL)
        {
            from->AddNeighbour(to);
            to->AddNeighbour(from);
        }
    }
    
    void DFSTraverseConst(NodeOperationConst<T>& op)
    {
        
        for (NodeMapIter iter = nodeMap.begin(); iter != nodeMap.end(); ++iter)
        {
            op.Action(iter->second);
        }
        
    }
    
    void BFSTraverseConst(NodeOperationConst<T>& op)
    {
        
    }
    
};

#endif
