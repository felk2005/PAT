//
//  Solution.h
//  PAT
//
//  Created by YuanXuan on 2/1/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Solution_h
#define PAT_Solution_h
struct Record
{
    int id;
    int virtue;
    int talent;
    
    Record(int _id, int _virtue, int _talent)
    : id(_id), virtue(_virtue), talent(_talent)
    {
        
    }
    
};

struct RecordCompare
{
    bool operator()(const Record &a, const Record &b)
    {
        int leftSum = a.virtue + a.talent;
        int rightSum = b.virtue + b.talent;
        if (leftSum < rightSum)
            return true;
        if (rightSum < leftSum)
            return false;
        if (a.virtue < b.virtue)
            return true;
        if (b.virtue < a.virtue)
            return false;
        if (a.id < b.id)
            return true;
        return false;
    }
};

#endif
