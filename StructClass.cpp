#include "StructClass.h"
#include <algorithm>
#include <iostream>

StructClass::StructClass() {}

void StructClass::parse(){
    //remove { and }
    int index = 0;
    while(mData.size() > index + 1){
        if((mData[index].rfind("}", 0) == 0) || (mData[index] == "{") || (mData[index] == "};")){
            mData[index] = mData[index + 1];
            for (int i = index + 1; i < mData.size() - 1; ++i) {
                mData[i] = mData[i + 1];
            }
            mData.pop_back();
        }else{
            ++index;
        }
    }

    //combline multilined lines
    index = 0;
    std::string notToEndOn = ",:";
    while(mData.size() > index + 1){
        if(!evenParanteser(mData[index]) || (notToEndOn.find(mData[index][mData[index].size()-1]) != -1)){
        //if(!evenParanteser(mData[index])){
            mData[index] += mData[index + 1];
            for (int i = index + 1; i < mData.size() - 1; ++i) {
                mData[i] = mData[i + 1];
            }
            mData.pop_back();
        }else{
            ++index;
        }
    }

    for (int i = 0; i < mData.size(); ++i) {
        std::string line = mData[i];
        //std::cout << line << std::endl;
        if(line.rfind("struct", 0) == 0){
            //line with struct name
            //line = line.substr(line.find(":") + 1);
            line = line.substr(6);

            if(line.find("{") != -1){
                line = line.substr(0, line.find("{"));
            }

            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            //save
            mName = line;
        }else if((line.rfind("}", 0) == 0) || (line == "{")){
        }else{
            mLines.push_back(aLine{line, "public"});
        }
    }

    std::vector<aLine> tmpLinesWithType;
    for (int i = 0; i < mLines.size(); ++i) {
        bool insert = true;
        for (int j = 0; j < tmpLinesWithType.size(); ++j) {
            if(mLines[i].toString() == tmpLinesWithType[j].toString()){
                insert = false;
            }
        }
        if(insert){tmpLinesWithType.push_back(mLines[i]);}
    }
    mLines = tmpLinesWithType;
}
