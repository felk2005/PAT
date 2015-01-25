//
//  Solution.h
//  PAT
//
//  Created by YuanXuan on 1/23/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Solution_h
#define PAT_Solution_h
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
#define INVALID_INDEX (-1)

class BinaryTreeNode
{
public:
	int value;
	bool hasLeft(){return leftChildId != INVALID_INDEX;}
	bool hasRight(){return rightChildId != INVALID_INDEX;}
private:
	int leftChildId;
	int rightChildId;
    friend class BinaryTree;
};

class BinaryTree
{
public:
private:
	vector<BinaryTreeNode*> nodeArray;
public:
	BinaryTree(int size)
	{
		nodeArray.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			nodeArray.push_back(NULL);
		}
	}

	BinaryTreeNode* AddNode(int value, int left, int right)
	{
		BinaryTreeNode* node = new BinaryTreeNode();
		node->value = value;
		node->leftChildId = left;
		node->rightChildId = right;
		nodeArray[value] = node;
		return node;
	}

    BinaryTreeNode* GetLeftChild(BinaryTreeNode* node)
	{
		if (INVALID_INDEX == node->leftChildId)
			return NULL;
		return nodeArray[node->leftChildId];
	}

    BinaryTreeNode* GetRightChild(BinaryTreeNode* node)
	{
		if (INVALID_INDEX == node->rightChildId)
			return NULL;
		return nodeArray[node->rightChildId];
	}

    BinaryTreeNode* GetRoot()
	{
		vector<bool> rootFlag;
		rootFlag.reserve(nodeArray.size());
		for (int i = 0; i < nodeArray.size(); ++i)
		{
			rootFlag.push_back(true);
		}
		for (int i = 0; i < nodeArray.size(); ++i)
		{
			BinaryTreeNode* node = nodeArray[i];
			if (node->leftChildId != INVALID_INDEX)
				rootFlag[node->leftChildId] = false;
			if (node->rightChildId != INVALID_INDEX)
				rootFlag[node->rightChildId] = false;
		}
		for (int i = 0; i < nodeArray.size(); ++i)
		{
			if (rootFlag[i] == true)
				return nodeArray[i];
		}
		return NULL;
	}
    
    


};
class Solution
{
public:
    void Resolve(BinaryTree& tree)
	{
		BinaryTreeNode* root = tree.GetRoot();
		queue<BinaryTreeNode*> nodeQueue;
		nodeQueue.push(root);
		bool firstNode = true;
		while (nodeQueue.size() != 0)
		{
			// check leaf
			BinaryTreeNode* node = nodeQueue.front();
			nodeQueue.pop();
			if (!node->hasLeft() && !node->hasRight())
			{
				if (!firstNode)
				{
					cout << " ";
				}
				firstNode = false;
				cout << node->value;
				continue;
			}

			// push to queue
			BinaryTreeNode* tempNode = tree.GetLeftChild(node);
			if (tempNode != NULL)
			{
				nodeQueue.push(tempNode);
			}
			tempNode = tree.GetRightChild(node);
			if (tempNode != NULL)
			{
				nodeQueue.push(tempNode);
			}
		}
	}


};

#endif
