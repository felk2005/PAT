//
//  Solution.h
//  PAT
//
//  Created by YuanXuan on 2/1/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_Solution_h
#define PAT_Solution_h
#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif

using namespace std;
#define MAX_VALUE 100
class Record
{
public:
    int id;
    int virtue;
    int talent;
    
    Record(int _id, int _virtue, int _talent)
    : id(_id), virtue(_virtue), talent(_talent)
    {
        
    }
    friend std::ostream& operator<<(std::ostream& os, const Record& rec)
    {
        os << rec.id << ' ' << rec.virtue << ' ' << rec.talent << std::endl;
        return os;
    }
    
};
struct RecordCompare
{
    bool operator()(const Record& a, const Record& b)
    {
        int leftSum = a.virtue + a.talent;
        int rightSum = b.virtue + b.talent;
        if (leftSum < rightSum)
            return !true;
        if (rightSum < leftSum)
            return !false;
        if (a.virtue < b.virtue)
            return !true;
        if (b.virtue < a.virtue)
            return !false;
        if (a.id < b.id)
            return true;
        return false;
    }
};


struct RecordComparePointer
{
    bool operator()(const Record* a, const Record* b)
    {
        if (a->id < b->id)
            return true;
        return false;
    }
};

class BucketSort
{
private:
    int low;
    int lowerVirtue;
    int higherVirtue;
    int lowerId;
    int higherId;
    
    enum SortType
    {
        ST_SUM,
        ST_VIRTUE,
        ST_ID
    };
    
    void SubSort(forward_list<Record*>& inList,
                 vector<forward_list<Record*>*>& emptyBucket,
                 SortType sortType)
    {
        int bucketCount = 0;
        if (sortType == ST_VIRTUE)
        {
            bucketCount = higherVirtue + 1 - lowerVirtue;
        }
        else if (sortType == ST_ID)
        {
            bucketCount = higherId + 1 - lowerId;
        }
        
//        int lowBound = sortType == ST_VIRTUE ? lowerVirtue : lowerId;
        
        emptyBucket.clear();
        for (int i = 0; i < bucketCount; ++i)
        {
            emptyBucket.push_back(NULL);
        }
        
        // first pass
        for (std::forward_list<Record*>::const_iterator iter = inList.begin();
             iter != inList.end();
             ++iter)
        {
            Record* rec = *iter;
            
            int index = (sortType == ST_VIRTUE ? rec->virtue - lowerVirtue : higherId - rec->id) ;
            if (emptyBucket[index] == NULL)
            {
                emptyBucket[index] = new std::forward_list<Record*>();
            }
            emptyBucket[index]->push_front(rec);
        }

    }
                 

    void SortFirstPass(std::forward_list<Record*>& inList)
    {
        // init values
        Record* first = inList.front();
        lowerVirtue = first->virtue;
        higherVirtue = first->virtue;
        lowerId = first->id;
        higherId = first->id;
        
        
        int maxBucket = (MAX_VALUE  + 1 - low) << 1;
        int lowBound = low << 1;
        
        std::vector<std::forward_list<Record*>*> emptyBucket;
        for (int i = 0; i < maxBucket; ++i)
        {
            emptyBucket.push_back(NULL);
        }
        
        // first pass
        for (std::forward_list<Record*>::const_iterator iter = inList.begin();
             iter != inList.end();
             ++iter)
        {
            Record* rec = *iter;
            lowerVirtue = min(lowerVirtue, rec->virtue);
            higherVirtue = max(higherVirtue, rec->virtue);
            lowerId = min(lowerId, rec->id);
            higherId = max(higherId, rec->id);
            
            
            int index = rec->talent + rec->virtue - lowBound;
            if (emptyBucket[index] == NULL)
            {
                emptyBucket[index] = new std::forward_list<Record*>();
            }
            emptyBucket[index]->push_front(rec);
        }
        inList.clear();
        // second pass
        for (int i = 0; i < emptyBucket.size(); ++i)
        {
            if (emptyBucket[i] != NULL)
            {
                vector<forward_list<Record*>*> bucket2;
                SubSort(*emptyBucket[i], bucket2, ST_VIRTUE);
                
                // third pass
                for (int j = 0; j < bucket2.size(); ++j)
                {
                    if (bucket2[j] != NULL)
                    {
                        bucket2[j]->sort(RecordComparePointer());
                        //sort(bucket2[j].begin(), bucket2[j].end(), RecordComparePointer());
                        //vector<forward_list<Record*>*> bucket3;
                        //SubSort(*bucket2[j], bucket3, ST_ID);
                        //BucketToList(bucket3, inList);
                        inList.splice_after(inList.before_begin(), *bucket2[j]);
                    }
                }
            }
        }
        
    }
    void BucketToList(std::vector<std::forward_list<Record*>*>& bucket, std::forward_list<Record*>& inList)
    {
        for (int i = 0; i < bucket.size(); ++i)
        {
            if (bucket[i] != NULL)
            {
                for (std::forward_list<Record*>::const_iterator iter = bucket[i]->begin();
                     iter != bucket[i]->end();
                     ++iter)
                {
                    inList.push_front(*iter);
                }
            }
        }
    }
public:
    BucketSort(int minValue)
    : low(minValue)    {
    
    }
    void Sort(std::forward_list<Record*>& inList)
    {
        std::vector<std::forward_list<Record*>*> bucket;
        SortFirstPass(inList);
    }
};

#endif
