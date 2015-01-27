//
//  AVLTree.h
//  PAT
//
//  Created by YuanXuan on 1/26/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_AVLTree_h
#define PAT_AVLTree_h
#include <cmath>
struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int value;
    int height;
    TreeNode(int val)
    :value(val), height(0), left(NULL), right(NULL)
    {
        
    }
    TreeNode(int val, TreeNode* lChild, TreeNode* rChild)
    : value(val), left(lChild), right(rChild)
    {
        UpdateHeight();
    }
    
    int GetLeftHeight()
    {
        return left != NULL ? left->height : -1;
    }
    
    int GetRightHeight()
    {
        return right != NULL ? right->height : -1;
    }
    
    void UpdateHeight()
    {
        if (left == NULL && right == NULL)
            height = 0;
        else if (left != NULL && right != NULL)
            height = std::max(left->height, right->height) + 1;
        else if (left == NULL)
            height = right->height + 1;
        else if (right == NULL)
            height = left->height + 1;
    }
};

class AVLTree
{
private:
    TreeNode* root;
    
private:
    void SingleLeftRotate(TreeNode*& node)
    {
        TreeNode* lnode = node->left;
        node->left = lnode->right;
        node->UpdateHeight();
        lnode->right = node;
        lnode->UpdateHeight();
        node = lnode;
        std::cout << "SL" << std::endl;
    }
    void SingleRightRotate(TreeNode*& node)
    {
        TreeNode* rnode = node->right;
        node->right = rnode->left;
        node->UpdateHeight();
        rnode->left = node;
        rnode->UpdateHeight();
        node = rnode;
        std::cout << "SR" << std::endl;
    }
    void LeftRightRotate(TreeNode*& node)
    {
        SingleRightRotate(node->left);
        SingleLeftRotate(node);
        /*TreeNode* rightChildOfLeft = node->left->right;
        node->left->right = rightChildOfLeft->left;
        rightChildOfLeft->left = node->left;
        node->left = rightChildOfLeft->right;
        rightChildOfLeft->right = node;
        node = node->left->right;
        std::cout << "DL" << std::endl;*/
    }
    void RightLeftRotate(TreeNode*& node)
    {
        SingleLeftRotate(node->right);
        SingleRightRotate(node);
        /*TreeNode* leftChildOfRight = node->right->left;
        node->right->left = leftChildOfRight->right;
        leftChildOfRight->right = node->right;
        node->right = leftChildOfRight->left;
        leftChildOfRight->left = node;
        node = leftChildOfRight;
        std::cout << "DR" << std::endl;*/
    }
    void Insert(int value, TreeNode*& parent)
    {
        if (parent == NULL)
        {
            parent = new TreeNode(value);
        }
        else if (value < parent->value) // insert to left
        {
            Insert(value, parent->left);
            if (parent->GetLeftHeight() - parent->GetRightHeight() == 2)
            {
                if (value < parent->left->value)
                    SingleLeftRotate(parent);
                else
                    LeftRightRotate(parent);
                    
            }
        }
        else if (value > parent->value) // insert to right
        {
            Insert(value, parent->right);
            if (parent->GetRightHeight() - parent->GetLeftHeight() == 2)
            {
                if (value > parent->right->value)
                    SingleRightRotate(parent);
                else
                    RightLeftRotate(parent);
            }
        }
        else // equals
        {
            return;
        }
        parent->UpdateHeight();
    }
    
    void PrintTree(TreeNode* node, int indent)
    {
        if (node == NULL)
            return;
        PrintTree(node->left, indent + 1);
        
        for (int i = 0; i < indent; ++i)
        {
            std::cout << "\t";
        }
        std::cout << node->value << "[" << node->height << "]" << std::endl;
        PrintTree(node->right, indent + 1);
        
    }
    
public:
    void Add(int value)
    {
        Insert(value, root);
    }
    
    const TreeNode* GetRoot()
    {
        return root;
    }
    void PrintTree()
    {
        PrintTree(root, 0);
    }
};

#endif
