#ifndef STRUCTCLASS_H
#define STRUCTCLASS_H

#include "aClass.h"

class StructClass : public aClass

#include <vector>
#include <string>
{
public:
    StructClass();
    StructClass(std::vector<std::string> data) {mName = data[0]; mData = data; parse();}

    std::string toXML(int id){return aClass::toXML(id);};
private:
    void parse();
};

#endif // STRUCTCLASS_H
