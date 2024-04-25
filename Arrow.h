#ifndef ARROW_H
#define ARROW_H

#include <map>
#include <string>

class Arrow
{
public:
    Arrow();
    bool isSubClass = false;

    std::string from;
    bool fromHasNoMax = false;
    int fromMax = 0;

    std::string to;
    bool toHasNoMax = false;
    int toMax = 0;

    std::string toXML(std::map<std::string, std::string> &classNamesToId, int id);
};

#endif // ARROW_H
