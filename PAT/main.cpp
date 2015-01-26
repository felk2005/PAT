//
//  main.cpp
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

#define ROOT_ID "root"
class ListNode
{
public:
	string id;
	int value;
	string next;
};
int main(int argc, const char * argv[])
{

	//
	//00100 6 4
	//00000 4 99999
	//00100 1 12309
	//68237 6 -1
	//33218 3 00000
	//99999 5 68237
	//12309 2 33218
    fstream inFile(argv[1]);
    istream& stream = inFile;
	string root;
	int nodeNum, reverseNum;
	map<string, ListNode*> nodeMap;
	stream >> root >> nodeNum >> reverseNum;

	for (int i = 0; i < nodeNum; ++i)
	{
		ListNode* node = new ListNode();
		stream >> node->id >> node->value >> node->next;
		nodeMap[node->id] = node;
	}

	// add first node
	ListNode* rootNode = new ListNode();
	rootNode->id = ROOT_ID;
	rootNode->value = -1;
	rootNode->next = root;
    
    // reverse list
    ListNode* node = nodeMap[rootNode->next];
    ListNode* nextNode = nodeMap[node->next];
    if (nextNode != NULL)
    {
        while (--reverseNum > 0)
        {
            ListNode* nextNextNode = nodeMap[nextNode->next];
            nextNode->next = node->id;
            node = nextNode;
            nextNode = nextNextNode;
        }
        ListNode* oldSecondNode = nodeMap[rootNode->next];
        if (nextNode != NULL)
            oldSecondNode->next = nextNode->id;
        else
            oldSecondNode->next = "-1";
        rootNode->next = node->id;
    }
    

    // print nodes
	node = nodeMap[rootNode->next];
	while (node != NULL)
	{
		cout << node->id << " " << node->value << " " << node->next << endl;
		map<string, ListNode*>::iterator iter = nodeMap.find(node->next);
		if (iter != nodeMap.end())
		{
			node = iter->second;
		}
		else
		{
			node = NULL;
		}
	}

    return 0;
}
