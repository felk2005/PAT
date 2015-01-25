//
//  main.cpp
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Solution.h"
#include "PATHelper.h"

using namespace std;
int parseIndex(string str)
{
	if (str.compare("-") == 0)
		return INVALID_INDEX;

	stringstream ss(str);
	int rtn = 0;
	ss >> rtn;
	return rtn;
}

int main(int argc, const char * argv[]) {

    fstream inFile(argv[1]);
    // Construct tree
	istream& stream = inFile;

	int count = 0;
	stream >> count;
	BinaryTree tree(count);
	for (int i = 0; i < count; ++i)
	{
		string leftIndex;
		string rightIndex;
		stream >> leftIndex >> rightIndex;
		
		tree.AddNode(i, parseIndex(leftIndex), parseIndex(rightIndex));
	}
	(new Solution())->Resolve(tree);

    
    return 0;
}
