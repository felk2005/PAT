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
#include "GraphNode.h"

#define MAX_INT 0xFFFFFF



class Coordinate
{
public:
    float x;
    float y;
    static const Coordinate zero;
    
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

const Coordinate Coordinate::zero = Coordinate(0, 0);

bool DistanceLessThan(const Coordinate& from, const Coordinate& to, float distance)
{
    float distanceX = abs(from.x - to.x);
    float distanceY = abs(from.y - to.y);
    if (distanceX <= distance
        && distanceY <= distance
        && std::sqrt(distanceX * distanceX + distanceY * distanceY) <= distance)
    {
        return true;
    }

    return false;
}
int main(int argc, const char * argv[]) {
    enum Constant
    {
        ESCAPE_COORD = 1000,
        START_COORD = -1000,
        START_RADIUS = 15,
        MIN_EDGE = -50,
        MAX_EDGE = 50
    };
    
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
        std::vector<GraphNode<Coordinate>*> graph;
        
        // add all nodes
        if (nodes > 0)
        {
            for (int i = 1; i < m.size(); ++i)
            {
                graph.push_back(new GraphNode<Coordinate>(Coordinate(m[i][0], m[i][1])));
            }
        }
        
        // add escape nodes
        GraphNode<Coordinate>* escapeNode = new GraphNode<Coordinate>(Coordinate(ESCAPE_COORD, ESCAPE_COORD));
        graph.push_back(escapeNode);
        
        // add start node
        GraphNode<Coordinate>* startNode = new GraphNode<Coordinate>(Coordinate(START_COORD, START_COORD));
        graph.push_back(startNode);
        
        for (int i = 0; i < graph.size(); ++i)
        {
            
            Coordinate from = graph[i]->GetValue();
            for (int j = i + 1; j < graph.size(); ++j)
            {
                Coordinate to = graph[j]->GetValue();
                if (DistanceLessThan(from, to, jumpDis))
                {
                    graph[i]->AddNeighbour(graph[j]);
                    graph[j]->AddNeighbour(graph[i]);
                }
            }
            
            // Add EscapeNode if close to edge
            if (abs(fmin(from.x, from.y) - MIN_EDGE) <= jumpDis
                || abs(MAX_EDGE - fmax(from.x, from.y)) <= jumpDis)
            {
                graph[i]->AddNeighbour(escapeNode);
            }
            
            // Add node to start node if close enough
            if (DistanceLessThan(from, Coordinate::zero, jumpDis + START_RADIUS))
            {
                startNode->AddNeighbour(graph[i]);
            }
            
        }
        
        // BFS traverse from start node
        std::queue<GraphNode<Coordinate>*> bfsQueue;
        std::set<GraphNode<Coordinate>*> visited;
        bfsQueue.push(startNode);
        while (bfsQueue.size() != 0)
        {
            GraphNode<Coordinate>* traverseNode = bfsQueue.front();
            bfsQueue.pop();
            if (traverseNode == escapeNode)
            {
                std::cout << "Yes" << std::endl;
                return 0;
            }
            const std::vector<GraphNode<Coordinate>*> neighbours = traverseNode->GetNeighbours();
            for (int i = 0; i < neighbours.size(); ++i)
            {
                if (visited.find(neighbours[i]) == visited.end())
                {
                    visited.insert(neighbours[i]);
                    bfsQueue.push(neighbours[i]);
                }
            }
            
        }
        
        std::cout << "No" << std::endl;

        
    }
    

    return 0;
}
