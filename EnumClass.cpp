#include "EnumClass.h"
#include <algorithm>
#include <iostream>

EnumClass::EnumClass() {}


void EnumClass::parse(){
    for (int i = 0; i < mData.size(); ++i) {
        std::string line = mData[i];
        if(line.rfind("enum", 0) == 0){
            //line with enum name
            //line = line.substr(line.find(":") + 1);
            line = line.substr(4);

            if(line.find("{") != -1){
                line = line.substr(0, line.find("{"));
            }

            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            //save
            mName = line;
            mLines.push_back(aLine{"int value;","private"});

            break;
        }
    }
}
