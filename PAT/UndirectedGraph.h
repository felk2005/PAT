//
//  Graph.h
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Graph_h
#define PAT_Graph_h
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>

template <typename T> class UndirectedGraphNode
{
public:
    typedef std::vector<UndirectedGraphNode* > NodeList;
    typedef typename std::vector<UndirectedGraphNode* >::iterator NodeListIter;
    
    UndirectedGraphNode(T inValue)
    {
        value = inValue;
    }
    
    T GetValue() const
    {
        return value;
    }
    
    struct SortCompare {
        bool operator() (UndirectedGraphNode* i,UndirectedGraphNode* j) { return (i->GetValue()<j->GetValue());}
    } sortCompare;
    void AddNeighbour(UndirectedGraphNode* node)
    {
        neighbours.push_back(node);
        std::sort(neighbours.begin(), neighbours.end(), sortCompare);
    }
    bool RemoveNeighbour(UndirectedGraphNode* node)
    {
        NodeListIter it = std::find(neighbours.begin(), neighbours.end(), 5);
        if(it != neighbours.end())
            neighbours.erase(it);
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
    virtual void Action(const UndirectedGraphNode<T>* node) const= 0;
};


template <typename T> class UndirectedGraph
{
private:
    typedef std::map<T, UndirectedGraphNode<T>*> NodeMap;
    typedef typename std::map<T, UndirectedGraphNode<T>*>::iterator NodeMapIter;
    typedef typename std::map<T, UndirectedGraphNode<T>*>::const_iterator NodeMapIterConst;

private:
    NodeMap nodeMap;
    std::set<T> traversingKey;
    

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
    
    void LinkNode(UndirectedGraphNode<T>* from, UndirectedGraphNode<T>* to)
    {
        if (from != NULL && to != NULL)
        {
            from->AddNeighbour(to);
            to->AddNeighbour(from);
        }
    }
    
    void DFSTraverseConst(NodeOperationConst<T>& op, const UndirectedGraphNode<T>* startNode)
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
    
    void BFSTraverseConst(NodeOperationConst<T>& op, const UndirectedGraphNode<T>* startNode)
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
    
    void DoDFSTraverseConst(NodeOperationConst<T>& op, const UndirectedGraphNode<T>* node)
    {
        if (node != NULL && traversingKey.find(node->GetValue()) == traversingKey.end())
        {
            op.Action(node);
            traversingKey.insert(node->GetValue());
            const std::vector<UndirectedGraphNode<T>*> neighbours = node->GetNeighbours();
            for (int i = 0; i < neighbours.size(); ++i)
            {
                DoDFSTraverseConst(op, neighbours[i]);
            }
        }
    }
    std::queue<const UndirectedGraphNode<T>* , std::list<const UndirectedGraphNode<T>*> > bfsQueue;
    void DoBFSTraverseConst(NodeOperationConst<T>& op, const UndirectedGraphNode<T>* node)
    {
        if (node != NULL && traversingKey.find(node->GetValue()) == traversingKey.end())
        {
            bfsQueue.push(node);
            traversingKey.insert(node->GetValue());
        }
        while (bfsQueue.size() != 0)
        {
            const UndirectedGraphNode<T>* first = bfsQueue.front();
            bfsQueue.pop();
            op.Action(first);
            
            const std::vector<UndirectedGraphNode<T>*> neighbours = first->GetNeighbours();
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
