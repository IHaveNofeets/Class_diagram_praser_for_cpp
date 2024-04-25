#ifndef LOADER_H
#define LOADER_H

#include "aClass.h"
#include "Arrow.h"
#include <vector>
#include <string>

class Loader
{
public:
    Loader();

    //both name of file and what it contains
    std::vector<std::vector<std::string>> getFiles(std::string folderPath, bool isWin);

    void saveXML(std::vector<aClass> &classes, std::vector<Arrow> &arrows, std::string path);
private:
    std::vector<std::string> read_directory(const std::string& name);
};

#endif // LOADER_H
