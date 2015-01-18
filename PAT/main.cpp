//
//  main.cpp
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>//miss
#include <string>//miss

using namespace std;
enum OPERATOR
{
    INVALID,
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE
};// mistake 1
OPERATOR getOperator(string inStr)
{
    // mistake 2, switch not support string
    if (inStr.compare("+") == 0)
    {
        return ADD;
    }
    else if (inStr.compare("-") == 0)
    {
        return SUBSTRACT;
    }
    else if (inStr.compare("*") == 0)
    {
        return MULTIPLY;
    }
    else if (inStr.compare("/") == 0)
    {
        return DIVIDE;
    }
    return INVALID;
}
int main(int argc, const char * argv[]) {
    
    vector<string> stack;
    istream& stream = ifstream(argv[1]);//std::cin;// use reference for stream
    while (!stream.eof())
    {
        string str;
        stream >> str;
        OPERATOR op = getOperator(str);
        if (op != INVALID)
        {
            stack.push_back(str);
        }
        else
        {
            if (stack.size() > 1 && getOperator(stack.back()) == INVALID)
            {
                float thisValue = 0;
                stringstream ss(str);
                ss >> thisValue;
                // get last number
                ss.str(stack.back());
                stack.pop_back();
                float lastValue = 0;
                ss >> lastValue;
                OPERATOR lastOp = getOperator(stack.back());
                if (lastOp == INVALID)
                {
                    cout << "Wrong Input" << endl;
                    return 1;
                }
                else
                {
                    stack.pop_back();
                    float result = 0;
                    switch (lastOp)
                    {
                        case ADD:
                            result = thisValue + lastValue;
                            break;
                        case SUBSTRACT:
                            result = lastValue - thisValue;
                            break;
                        case MULTIPLY:
                            result = lastValue * thisValue;	
                            break;
                        case DIVIDE:
                            result = lastValue / thisValue;
                            break;
                        default:
                            break;
                    }
                    ss.str("");
                    ss << result;
                    stack.push_back(ss.str());
                }
            }
            else
            {
                stack.push_back(str);
            }
        }
    }
    float rtn = 0;
    stringstream ss(stack.back());
    ss >> rtn;
    printf ("%.2f", rtn);// string type not float
    return 0;
}
