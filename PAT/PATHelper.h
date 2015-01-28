//
//  PATHelper.h
//  PAT
//
//  Created by YuanXuan on 1/13/15.
//  Copyright (c) 2015 felk. All rights reserved.
//

#ifndef PAT_PATHelper_h
#define PAT_PATHelper_h

#ifndef IGNORE_LIB
#include "stlheaders.h"
#endif

class PATHelper
{
public:
    
    template <class T> static std::vector<T> &split(const std::string &s, char delim, std::vector<T> &elems) {
        std::stringstream ss(s);
        std::string item;
        T value;
        while (std::getline(ss, item, delim)) {
            if (item.length() > 0)
            {
                std::stringstream strstream;
                strstream.str(item);
                strstream >> value;
                elems.push_back(value);
            }
        }
        while (!ss.eof())
        {
            
        }
        return elems;
    }
    
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        return split(s, delim, elems);;
    }

    
    template <class T> static std::vector< std::vector<T> > parseToMatrix(std::istream& inStream, char delim)
    {
        std::vector< std::vector<T> > rtn;
        std::string line;
        while (!inStream.eof())
        {
            std::getline(inStream, line);
//            inStream >> line;
            if (line.length() > 0)
            {
                std::vector<T> element;
                rtn.push_back(split(line, delim, element));
            }
            
        }
        return rtn;
    }
};

#endif
