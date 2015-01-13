#ifndef MAX_SEQ_SUM
#define MAX_SEQ_SUM
#include <iostream>
#include <vector>

using namespace std;

class MaxSequenceSum
{
public:
    static int Solution(vector<int>& inArray)
    {
        int result = 0;
        for (int i = 0; i < inArray.size(); ++i)
        {
            int sum = inArray[i];
            int maxSum = 0;
            for (int j = i+1; j < inArray.size(); ++j)
            {
                sum += inArray[j];
                if (sum > maxSum)
                    maxSum = sum;
            }
            if (maxSum > result)
                result = maxSum;
        }
        return result;
    }
};

#endif