#include "aClass.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "aLine.h"
#include "EnumClass.h"
#include "StructClass.h"

aClass::aClass() {}

std::vector<std::string> aClass::split(const std::string& line, char delim){
    //have a vaible that is not const
    std::string line_remender = line;
    //output to save to
    std::vector<std::string> out;

    while(line_remender.size() != 0) {
        //finds the next time delim and gets from pos 0 to that pos and then removes the copyed part + 1 (for ',')
        int pos = line_remender.find(delim);
        if(pos == std::string::npos){pos = line_remender.size();} //end of line
        std::string part = line_remender.substr(0,pos);
        out.push_back(part);
        line_remender.erase(0,pos+1);
    }
    return out;
}

void aClass::parse(){
    if(mName == "main.cpp"){return;}
    //remove name
    for (int i = 0; i < mData.size()-1; ++i) {
        mData[i] = mData[i + 1];
    }
    mData.pop_back();

    std::vector<std::string> dataCopy = mData;

    //space infront removed
    for (int i = 0; i < dataCopy.size(); ++i) {
        while(dataCopy[i].size() > 0 && dataCopy[i].at(0) == ' '){
            dataCopy[i] = dataCopy[i].substr(1);
        }
    }
    //erase
    dataCopy.erase(std::remove_if(dataCopy.begin(), dataCopy.end(),
                                  [](const std::string s){return s.size() == 0;}), dataCopy.end());
    dataCopy.erase(std::remove_if(dataCopy.begin(), dataCopy.end(),
                                  [](const std::string s){return s.at(0) == '#';}), dataCopy.end());

    //remove until "class "
    for (int i = 0; i < dataCopy.size(); ++i) {

        bool brack = false;
        if(dataCopy[0].rfind("class ", 0) == 0 && dataCopy[0].find(";") == -1){
            brack = true;
            mName = dataCopy[0].substr(6);
            if(mName.find("{") != -1){
                mName = mName.substr(0, mName.find("{"));
            }
            if(mName.find(":") != -1){
                mBaseClassName = mName.substr(mName.find(":") + 1);
                while (std::isspace(mBaseClassName[mBaseClassName.size()-1])) {
                    mBaseClassName = mBaseClassName.substr(0, mBaseClassName.size()-2);
                }
                int pos = mBaseClassName.find_last_of(" ");
                if(pos != -1){
                    mBaseClassName = mBaseClassName.substr(pos, mBaseClassName.size()-1);
                }
                mBaseClassName.erase(std::remove_if(mBaseClassName.begin(), mBaseClassName.end(), isspace), mBaseClassName.end());

                mName = mName.substr(0, mName.find(":"));
            }

            mName.erase(std::remove_if(mName.begin(), mName.end(), isspace), mName.end());
        }
        else if(dataCopy[0].rfind("enum", 0) == 0){
            mEnums.push_back(EnumClass{std::vector<std::string>{dataCopy[0]}});
        }
        else if(dataCopy[0].rfind("struct", 0) == 0){
            std::vector<std::string> structPart;
            std::string structPartString = dataCopy[0];
            structPart.push_back(dataCopy[0]);

            for (int j = 1; j < dataCopy.size(); ++j) {
                if(structPartString.find("{") != -1 && evenParanteser(structPartString)){
                    break;
                }
                structPartString += dataCopy[j];
                structPart.push_back(dataCopy[j]);
            }

            mEnums.push_back(StructClass{structPart});
        }

        if(i + 1 != dataCopy.size()){
            for (int j = 0; j < dataCopy.size() - 1; ++j) {
                dataCopy[j] = dataCopy[j + 1];
            }
            dataCopy.pop_back();
        }

        if(brack){break;}
    }

    if(dataCopy[0] == "{" && dataCopy.size() > 1){
        for (int j = 0; j < dataCopy.size() - 1; ++j) {
            dataCopy[j] = dataCopy[j + 1];
        }
        dataCopy.pop_back();
    }
    //combline multilined lines
    int index = 0;
    std::string notToEndOn = ",:";
    std::string isAcc = "abcdefghijklmnopqrsturvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

    while(dataCopy.size() > index + 1){
        if(!evenParanteser(dataCopy[index]) ||
            ((notToEndOn.find(dataCopy[index][dataCopy[index].size()-1]) != -1) &&
                (isAcc.find(dataCopy[index][dataCopy[index].size()-2]) == -1))){
            dataCopy[index] += dataCopy[index + 1];
            for (int i = index + 1; i < dataCopy.size() - 1; ++i) {
                dataCopy[i] = dataCopy[i + 1];
            }
            dataCopy.pop_back();
        }else{
            ++index;
        }
    }

    for (int i = 0; i < dataCopy.size(); ++i) {
        //std::cout << dataCopy[i].size() << std::endl;
        int pos = dataCopy[i].find("//");
        if(pos != -1 && pos != 0 && dataCopy[i].size() != 0){
            dataCopy[i] = dataCopy[i].substr(0, pos);
        }
    }

    dataCopy.erase(std::remove_if(dataCopy.begin(), dataCopy.end(),
                                  [](const std::string s){return !s.rfind("//", 0);}), dataCopy.end());
    dataCopy.erase(std::remove_if(dataCopy.begin(), dataCopy.end(),
                                  [](const std::string s){return s == "{" || s == "}" || s == "};";}), dataCopy.end());
    dataCopy.erase(std::remove_if(dataCopy.begin(), dataCopy.end(),
                                  [](const std::string s){return std::isdigit(s.at(0));}), dataCopy.end());


    std::string type = "NONE";
    std::vector<std::vector<std::string>> linesWithType;
    for (auto line : dataCopy) {
        std::string lineCopy = line;
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        //if(line == "public:" || line == "private:" || line == "protected:" ||
        //    line == "package:" || line == "derived:"){
        if(line.find(":") != -1 && line.find(":") != line.find("::") && line.size() - 1 == line.find(":")){
            type = line.substr(0, line.size() - 1);
            //std::cout << line.size() << std::endl;
        }else{
            linesWithType.push_back(std::vector<std::string>{type, lineCopy});
        }
    }

    for (int i = 0; i < linesWithType.size(); ++i) {
        mLines.push_back(aLine{linesWithType[i][1], linesWithType[i][0]});
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

    mData.clear();
    dataCopy.clear();
}

bool aClass::evenParanteser(std::string line){
    int arrowCount = std::count_if(line.begin(), line.end(), []( char c ){return c =='<';}) -
                     std::count_if(line.begin(), line.end(), []( char c ){return c =='>';});

    int pCount = std::count_if(line.begin(), line.end(), []( char c ){return c =='(';}) -
                 std::count_if(line.begin(), line.end(), []( char c ){return c ==')';});

    int firkantCount = std::count_if(line.begin(), line.end(), []( char c ){return c =='[';}) -
                       std::count_if(line.begin(), line.end(), []( char c ){return c ==']';});

    int bracketsCount = std::count_if(line.begin(), line.end(), []( char c ){return c =='{';}) -
                        std::count_if(line.begin(), line.end(), []( char c ){return c =='}';});

    return arrowCount == 0 && pCount == 0 && firkantCount == 0 && bracketsCount == 0;
}

std::string aClass::toXML(int id){
    std::vector<aLine> attebutes;
    std::vector<aLine> functions;

    for (int i = 0; i < mLines.size(); ++i) {
        if(mLines[i].getIsFunction()){
            functions.push_back(mLines[i]);
        }else{
            attebutes.push_back(mLines[i]);
        }
    }
    std::string out = "";
    //write
    out += xmldoc1 + "id-class-" + std::to_string(id);
    out += xmldoc2 + mName;
    out += xmldoc3 + "id2";
    out += xmldoc4 + std::to_string(10 + 220 * id);
    out += xmldoc5;
    int index = 0;
    for (int i = 0; i < attebutes.size(); ++i) {
        ++index;
        out += xmltext1 + "id-class-" + std::to_string(id) + "-" + std::to_string(index);
        out += xmltext2 + attebutes[i].toString();
        out += xmltext3 + (attebutes[i].getIsStatic() ? xmltextStatic : xmltextNonStatic);
        out += xmltext4 + "id-class-" + std::to_string(id);
        out += xmltext5;
    }

    ++index;
    out += xmlLine1 + "id-class-" + std::to_string(id) + "-" + std::to_string(index);
    out += xmlLine2 + "id-class-" + std::to_string(id);
    out += xmlLine3;

    for (int i = 0; i < functions.size(); ++i) {
        ++index;
        out += xmltext1 + "id-class-" + std::to_string(id) + "-" + std::to_string(index);
        out += xmltext2 + functions[i].toString();
        out += xmltext3 + (functions[i].getIsStatic() ? xmltextStatic : xmltextNonStatic);
        out += xmltext4 + "id-class-" + std::to_string(id);
        out += xmltext5;
    }

    return out;
}

std::vector<Arrow> aClass::getArrows(std::vector<std::string> classNames){
    std::vector<Arrow> out;

    if(mBaseClassName != ""){
        for (int i = 0; i < classNames.size(); ++i) {
            if(mBaseClassName == classNames[i]){
                Arrow a{};
                a.from = mName;
                a.to = classNames[i];
                a.isSubClass = true;
                out.push_back(a);

                break;
            }
        }
    }

    std::vector<aLine> attebutes;
    std::vector<aLine> functions;

    for (int i = 0; i < mLines.size(); ++i) {
        if(mLines[i].getIsFunction()){
            functions.push_back(mLines[i]);
        }else{
            attebutes.push_back(mLines[i]);
        }
    }

    for (int i = 0; i < classNames.size(); ++i) {
        if(classNames[i] == mName){continue;}
        for (int j = 0; j < attebutes.size(); ++j) {
            if(attebutes[j].getType().find(classNames[i]) != -1){
                Arrow a{};
                a.from = mName;
                a.fromMax = 1;
                a.to = classNames[i];
                if(attebutes[j].getType().find("<") != -1){
                    a.toHasNoMax = true;
                }else{
                    a.toMax = 1;
                }

                out.push_back(a);
            }
        }
    }




    return out;
}
