//
//  Graph.h
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Graph_h
#define PAT_Graph_h

#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif
#include "GraphNode.h"


template <typename T> class NodeOperationConst
{
public:
    virtual ~NodeOperationConst() {}
    virtual void Action(const GraphNode<T>* node) const= 0;
};

template <typename T> class NodePrintOperationConst : public NodeOperationConst<T>
{
public:
    virtual ~NodePrintOperationConst() {}
    virtual void Action(const GraphNode<T>* node) const
    {
        std::cout << " " << node->GetValue();
    }
    
};
template <typename T> class UndirectedGraph
{
private:
    typedef std::map<T, GraphNode<T>*> NodeMap;
    typedef typename std::map<T, GraphNode<T>*>::iterator NodeMapIter;
    typedef typename std::map<T, GraphNode<T>*>::const_iterator NodeMapIterConst;

private:
    NodeMap nodeMap;
    std::set<T> traversingKey;
    

public:
    GraphNode<T>* AddNode(T value)
    {
        NodeMapIter it = nodeMap.find(value);
        if (it == nodeMap.end())
        {
            GraphNode<T>* newNode = new GraphNode<T>(value);
            nodeMap[value] = newNode;
            return newNode;
        }
        return it->second;
        
    }
    
    const GraphNode<T>* GetNode(T value) const
    {
        NodeMapIterConst it = nodeMap.find(value);
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
    
    void LinkNode(GraphNode<T>* from, GraphNode<T>* to)
    {
        if (from != NULL && to != NULL)
        {
            from->AddNeighbour(to);
            to->AddNeighbour(from);
        }
    }
    
    void DFSTraverseConst(NodeOperationConst<T>& op, const GraphNode<T>* startNode)
    {

        if (startNode != NULL)
        {
            std::cout << "{";
            DoDFSTraverseConst(op, startNode);
            std::cout << " }" << std::endl;
        }
        
        for (NodeMapIter iter = nodeMap.begin(); iter != nodeMap.end(); ++iter)
        {
            if (traversingKey.find(iter->first) == traversingKey.end())
            {
                std::cout << "{";
                DoDFSTraverseConst(op, iter->second);
                std::cout << " }" << std::endl;
            }
        }
        traversingKey.clear();
        
    }
    
    void BFSTraverseConst(NodeOperationConst<T>& op, const GraphNode<T>* startNode)
    {
        if (startNode != NULL)
        {
            std::cout << "{";
            DoBFSTraverseConst(op, startNode);
            std::cout << " }" << std::endl;
        }
        
        for (NodeMapIter iter = nodeMap.begin(); iter != nodeMap.end(); ++iter)
        {
            if (traversingKey.find(iter->first) == traversingKey.end())
            {
                std::cout << "{";
                DoBFSTraverseConst(op, iter->second);
                std::cout << " }" << std::endl;
            }
        }
        traversingKey.clear();
    }
private:
    
    void DoDFSTraverseConst(NodeOperationConst<T>& op, const GraphNode<T>* node)
    {
        if (node != NULL && traversingKey.find(node->GetValue()) == traversingKey.end())
        {
            op.Action(node);
            traversingKey.insert(node->GetValue());
            const std::vector<GraphNode<T>*> neighbours = node->GetNeighbours();
            for (int i = 0; i < neighbours.size(); ++i)
            {
                DoDFSTraverseConst(op, neighbours[i]);
            }
        }
    }
    std::queue<const GraphNode<T>* , std::list<const GraphNode<T>*> > bfsQueue;
    void DoBFSTraverseConst(NodeOperationConst<T>& op, const GraphNode<T>* node)
    {
        if (node != NULL && traversingKey.find(node->GetValue()) == traversingKey.end())
        {
            bfsQueue.push(node);
            traversingKey.insert(node->GetValue());
        }
        while (bfsQueue.size() != 0)
        {
            const GraphNode<T>* first = bfsQueue.front();
            bfsQueue.pop();
            op.Action(first);
            
            const std::vector<GraphNode<T>*> neighbours = first->GetNeighbours();
            for (int i = 0; i < neighbours.size(); ++i)
            {
                if (traversingKey.find(neighbours[i]->GetValue()) == traversingKey.end())
                    bfsQueue.push(neighbours[i]);
                    traversingKey.insert(neighbours[i]->GetValue());
            }
        }
    }
    
};

#endif
