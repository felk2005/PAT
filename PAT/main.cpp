//
//  main.cpp
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include<iomanip>

using namespace std;
#define FLOAT_PRECISE (0.000001f)
float getFunctionValue(float x, vector<int>& ratios)
{
    float rtn = ratios[0];
    
    // ax^3 + bx^2 + cx + d = ((ax + b) * x + c) * x + d
    
    for (int i = 1; i < ratios.size(); ++i)
    {
        rtn = rtn * x + ratios[i];
    }
    return rtn;
}
int sign(float x, float y)
{
	if (abs(x) < FLOAT_PRECISE && abs(y) < FLOAT_PRECISE)
		return 0;
	else if ((x > 0 && y < 0) || (x < 0 && y > 0))
		return -1;
	return 1;
	
}
int main(int argc, const char * argv[]) {

    fstream inFile(argv[1]);
    
    istream& stream = inFile;
    vector<int> ratio;
    int i = 4;
    while (i-- > 0)
    {
        int val;
        stream >> val;
        ratio.push_back(val);
    }
    
    float start, end;
    stream >> start;
    stream >> end;
    if (start > end)
    {
        float temp = end;
        end = start;
        start = temp;
    }

    
    float loopStart = start;
    float loopEnd = end;
    while (loopEnd - loopStart > FLOAT_PRECISE)
    {
        float fstart = getFunctionValue(loopStart, ratio);
		float fend = getFunctionValue(loopEnd, ratio);
		if (sign(fstart, fend) < 0)
		{
			float half = (loopStart + loopEnd) / 2;
			float fhalf = getFunctionValue(half, ratio);
			if (abs(fhalf) < FLOAT_PRECISE)
			{
                cout << setiosflags(ios::fixed)<<setprecision(2) << half;
//                cout << endl << getFunctionValue(half, ratio);
				return 0;
			}
			else if (sign(fhalf, fstart) == 1)
			{
				loopStart = half;
			}
			else if (sign(fhalf, fend) == 1)
			{
				loopEnd = half;
			}

		}
		else
			break;
        
    }
    cout << setiosflags(ios::fixed)<<setprecision(2) << (loopStart + loopEnd) / 2;
//    cout << endl << getFunctionValue((loopStart + loopEnd) / 2, ratio);


    return 0;
}
