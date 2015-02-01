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
#include "Solution.h"

using namespace std;
int main(int argc, const char * argv[]) {
    fstream inFile(argv[1]);
    istream& stream = inFile;
    
    int count, lowBound, highBound;
    
    stream >> count >> lowBound >> highBound;
    
    int id, virtue, talent;
    vector<Record*> recordList[4];
    int validCount = 0;
    for (int i = 0; i < count; ++i)
    {
        stream >> id >> virtue >> talent;
        if (virtue < lowBound || talent < lowBound)
            continue;
        if (talent >= highBound && virtue >= highBound)
        {
            recordList[0].push_back(new Record(id, virtue, talent));
        }
        else if (virtue >= highBound)
        {
            recordList[1].push_back(new Record(id, virtue, talent));
        }
        else if (virtue >= talent)
        {
            recordList[2].push_back(new Record(id, virtue, talent));
        }
        else
        {
            recordList[3].push_back(new Record(id, virtue, talent));
        }
        ++validCount;
    }
    
    for (int i = 0; i < 4; ++i)
    {
        sort(recordList[i].begin(), recordList[i].end(), RecordCompare());
    }
    
    cout << validCount << endl;
    for (int i = 0; i < 4; ++i)
    {
        
        for (int j = 0; j < recordList[i].size(); ++j)
        {
            cout << *recordList[i][j];
        }
    }
    

    return 0;
}
