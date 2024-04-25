#ifndef ENUMCLASS_H
#define ENUMCLASS_H

#include "aClass.h"
#include <vector>
#include <string>

class EnumClass : public aClass
{
public:
    EnumClass();
    EnumClass(std::vector<std::string> data) {mName = data[0]; mData = data; parse();}

    std::string toXML(int id){return aClass::toXML(id);};
private:
    void parse();
};

#endif // ENUMCLASS_H
