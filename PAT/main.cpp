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

#include "PATHelper.h"
#include "UndirectedGraph.h"

#define MAX_INT 0xFFFFFF

template <typename T> class NodePrintOperationConst : public NodeOperationConst<T>
{
public:
    virtual ~NodePrintOperationConst() {}
    virtual void Action(const UndirectedGraphNode<T>* node) const
    {
        std::cout << " " << node->GetValue();
    }
    
};

class Coordinate
{
public:
    float x;
    float y;
    Coordinate(float inX, float inY) :
        x(inX), y(inY)
    {}
    Coordinate() : x(0), y(0)
    {}
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coor)
    {
        os << coor.x << ',' << coor.y;
        return os;
    }
    friend inline bool operator< (const Coordinate& lhs, const Coordinate& rhs)
    {
        return abs(lhs.x) + abs(lhs.y) < abs(rhs.x) + abs(rhs.y);
        
    }
//    inline bool operator< (const Coordinate& rhs) const
//    {
//        return abs(x) + abs(y) < abs(rhs.x) + abs(rhs.y);
//        
//    }
};

int main(int argc, const char * argv[]) {
    int nodes = 0;
    int jumpDis = 0;
    std::ifstream fileStream(argv[1]);
    std::istream& stream = fileStream;
    // for matrix input
    std::vector< std::vector<int> > m = PATHelper::parseToMatrix<int>(stream, ' ');
    if (m.size() > 0 && m[0].size() > 1)
    {
        nodes = m[0][0];
        jumpDis = m[0][1];
        UndirectedGraph<Coordinate> graph;
        if (nodes > 0)
        {
            for (int i = 1; i < m.size(); ++i)
            {
                graph.AddNode(Coordinate(m[i][0], m[i][1]));
            }
        }
//        if (edges > 0)
//        {
//            
//            for (int i = 0; i < edges; ++i)
//            {
//                int from = m[i + 1][0];
//                int to = m[i + 1][1];
//                
//                graph.LinkNode(from, to);
//            }
//        }
//        int minNodeValue = 0;
        NodePrintOperationConst<Coordinate> op;
//        const UndirectedGraphNode<int>* minNode = graph.GetNode(minNodeValue);
        graph.DFSTraverseConst(op, NULL);
//        graph.BFSTraverseConst(op, minNode);

        
    }
    

    return 0;
}
