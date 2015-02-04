//
//  SimpleHashSet.h
//  PAT
//
//  Created by YuanXuan on 2/4/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_SimpleHashSet_h
#define PAT_SimpleHashSet_h


using namespace std;
#define UNUSED (-1)
#define INVALID_HASH (-1)

class SimpleHashSet
{
    
    int* list;
    int _size;
    
    
    // TODO: Optimize
    bool isPrime(int value)
    {
        int sqrtValue = int(sqrt(value))+ 1;
        for (int i = 2; i < sqrtValue; ++i)
        {
            if (value % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    
    int GetMinPrimeGreaterThan(int givenValue)
    {
        int i = givenValue;
        if (i % 2 == 0)
            ++i;
        
        // only test odd numbers
        while (true)
        {
            if (isPrime(i))
                break;
        
            i += 2;
        }
        return i;
    }
    
    int GetValidHash(int value)
    {
        int rtn = (value % _size);
        if (*(list + rtn) != UNUSED)
        {
            
            for (int i = 1; ; ++i)
            {
                
                if (i > (_size >> 1))
                {
                    rtn = INVALID_HASH;
                    break;
                }
                int testHash = rtn + i * i;
                if (*(list + (testHash % _size)) == UNUSED)
                {
                    rtn = testHash % _size;
                    break;
                }
            }
        }
        return rtn;
    }
    


public:
    
    SimpleHashSet(int maxSize)
    {
        _size = GetMinPrimeGreaterThan(maxSize);
        list = new int[_size];
        memset(list, UNUSED, _size * sizeof(int));
    }
    
    int Insert(int value)
    {
        int hash = GetValidHash(value);
        if (hash < 0)
            return INVALID_HASH;
        *(list + hash) = value;
        return hash;
    }
};

#endif
