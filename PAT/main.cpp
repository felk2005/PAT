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
enum EXCEPTIONS
{
    INPUT_ERROR,
    DIVIDE_ZERO
};
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

float string2float(string str)
{
    float thisValue = 0;
    stringstream ss(str);
    ss >> thisValue;
    return thisValue;
}
int main(int argc, const char * argv[]) {
    try{
    vector<string> stack;
//    ifstream file(argv[1]);
    istream& stream = std::cin;// use reference for stream
    while (stream)
    {
//        for (int i = 0; i < stack.size(); ++i)
//        {
//            cout << stack[i] << "\t";
//        }
        
        string str;
        stream >> str;
//        cout << (int)str[0] << "END" << endl;
        if (str.compare("\0") == 0)   // <----------- skip end
            break;
        OPERATOR op = getOperator(str);
        if (op != INVALID)
        {
            stack.push_back(str);
        }
        else
        {
            // FATAL ERROR: should pop in a loop
            float thisValue = string2float(str);
            while (stack.size() > 1 && getOperator(stack.back()) == INVALID)
            {
                

                float lastValue = string2float(stack.back());
                stack.pop_back();

                OPERATOR lastOp = getOperator(stack.back());
                if (lastOp == INVALID)
                {
                    throw INPUT_ERROR;
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
                            if (thisValue == 0)
                                throw DIVIDE_ZERO;
                            result = lastValue / thisValue;
                            break;
                        default:
                            break;
                    }
                    thisValue = result;
                    
                }
                
            }
            stringstream ss;
            ss << thisValue;
            stack.push_back(ss.str());
        }
    }
    float rtn = 0;
    stringstream ss(stack.back());
    ss >> rtn;
    printf ("%.1f\n", rtn);// string type not float
    return 0;
    }
    catch (...)
    {
        cout << "ERROR" << endl;
        return 0;
    }
}
