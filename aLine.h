#ifndef ALINE_H
#define ALINE_H

#include <string>

class aLine
{
public:
    aLine(){}
    aLine(std::string line, std::string acc){setLine(line, acc);}

    void setLine(std::string line, std::string acc);

    std::string toString();

    bool getIsFunction(){return isFunction;}
    bool getIsStatic(){return isStatic;}
    std::string getType(){return type;}

private:
    bool isStatic = false;
    bool isPublic = false;
    bool isPrivate = false;
    bool isProtected = false;
    bool isPackage = false;
    bool isDerived = false;
    bool hasCustomAcc = false;
    std::string customAcc = "";

    bool isFunction = false;

    std::string name;
    std::string type;
};

#endif // ALINE_H
