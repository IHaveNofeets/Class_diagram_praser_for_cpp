#include "aLine.h"
#include <iostream>
#include <qstring.h>

void aLine::setLine(std::string line, std::string acc){
    if(QString::fromStdString(acc).toLower() == "public"){isPublic = true;}
    else if(QString::fromStdString(acc).toLower() == "private"){isPrivate = true;}
    else if(QString::fromStdString(acc).toLower() == "protected"){isProtected = true;}
    else if(QString::fromStdString(acc).toLower() == "package"){isPackage = true;}
    else if(QString::fromStdString(acc).toLower() == "derived"){isDerived = true;}
    else{
        hasCustomAcc = true;
        customAcc = "[";
        bool v = true;
        for (int i = 0; i < acc.length(); i++)
        {
            // If it is space, set v as true.
            if (acc[i] == ' ')
                v = true;

            // Else check if v is true or not.
            // If true, copy character in output
            // string and set v as false.
            else if (acc[i] != ' ' && v == true)
            {
                customAcc.push_back(acc[i]);
                v = false;
            }
        }
        customAcc += "] ";
    }

    std::string lineCheck = "static ";
    if(QString::fromStdString(line).toLower().contains(QString::fromStdString(lineCheck))){
        int pos = QString::fromStdString(line).toLower().toStdString().find(lineCheck);
        if(pos == 0 || line[pos - 1] == ' '){
            isStatic = true;
            line.replace(pos,lineCheck.size(),"");
        }
    }
    lineCheck = "package ";
    if(QString::fromStdString(line).toLower().contains(QString::fromStdString(lineCheck))){
        int pos = QString::fromStdString(line).toLower().toStdString().find(lineCheck);
        if(pos == 0 || line[pos - 1] == ' '){
            isPackage = true;
            line.replace(pos,lineCheck.size(),"");
        }
    }
    lineCheck = "derived ";
    if(QString::fromStdString(line).toLower().contains(QString::fromStdString(lineCheck))){
        int pos = QString::fromStdString(line).toLower().toStdString().find(lineCheck);
        if(pos == 0 || line[pos - 1] == ' '){
            isDerived = true;
            line.replace(pos,lineCheck.size(),"");
        }
    }

    //a function has '(' and ')'
    isFunction = QString::fromStdString(line).toLower().contains("(") &&
                 QString::fromStdString(line).toLower().contains(")");

    //remove all after name:
    if(isFunction){
        int pos = line.find("(");
        line.erase(line.begin() + pos, line.end());
    }else{
        if(QString::fromStdString(line).toLower().contains("=")){
            int pos = line.find("=");
            line.erase(line.begin() + pos, line.end());
        }else if(QString::fromStdString(line).toLower().contains("{")){
            int pos = line.find("{");
            line.erase(line.begin() + pos, line.end());
        }
    }


    while(QString::fromStdString(line).last(1) == " "){
        line = QString::fromStdString(line).removeLast().toStdString();
    }

    //get name
    int pos = line.find_last_of(" ");
    if(pos == -1){
        name = line;
    }else{
        name = QString::fromStdString(line.substr(pos)).remove(" ").toStdString();
        line.erase(line.begin()+ pos, line.end());
    }

    name.erase(std::remove_if(name.begin(), name.end(), isspace), name.end());
    name.erase(std::remove_if(name.begin(), name.end(), [](char c){return c == ';';}), name.end());

    //get type
    type = line;
}

std::string aLine::toString(){
    std::string out = "";
    //if(isStatic){out += "";}
    if(isPublic){out += "+ ";}
    else if(isPrivate){out += "- ";}
    else if(isProtected){out += "# ";}
    else if(isPackage){out += "~ ";}
    else if(isDerived){out += "/ ";}
    else if(hasCustomAcc){out += customAcc;}

    out += name;

    out += isFunction ? "()" : ": " + type;

    while(out.find("<") != -1){
        int pos = out.find("<");
        out.replace(pos,1,"&lt;");
    }
    while(out.find(">") != -1){
        int pos = out.find(">");
        out.replace(pos,1,"&gt;");
    }

    return out;
}
