#include "Loader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <map>
#include "EnumClass.h"
#include "StructClass.h"

Loader::Loader() {}

std::vector<std::vector<std::string>> Loader::getFiles(std::string folderPath, bool isWin){
    std::vector<std::string> allFiles = read_directory(folderPath);

    //-r
    for (int i = 0; i < allFiles.size(); ++i) {
        if(allFiles[i].find(".") == -1){
            std::vector<std::string> newFiles = read_directory(folderPath + (isWin ? "\\" : "/") + allFiles[i]);
            for (int j = 0; j < newFiles.size(); ++j) {
                newFiles[j] = allFiles[i] + (isWin ? "\\" : "/") + newFiles[j];
            }
            allFiles.insert(allFiles.end(), newFiles.begin(), newFiles.end());
        }
    }

    std::vector<std::string> headerFiles;
    headerFiles.reserve(allFiles.size());
    bool hasMain = false;

    for (std::string file : allFiles) {
        if(file.find(".h") != -1){
            headerFiles.push_back(file);
        }else if(file == "main.cpp"){
            hasMain = true;
        }
    }
    headerFiles.shrink_to_fit();
    std::vector<std::vector<std::string>> out;

    for (std::string fileName : headerFiles) {
        std::string filePath = folderPath + (isWin ? "\\" : "/") + fileName;
        std::vector<std::string> fileC;
        fileC.push_back(fileName);
        //load file
        std::ifstream file;
        file.open(filePath);
        //read file
        if(file.is_open()){
            //read and save each line
            std::string line;
            while(file.good()){
                std::getline(file, line);
                fileC.push_back(line);
            }
        }
        out.push_back(fileC);
    }

    if(hasMain){
        out.push_back(std::vector<std::string>{"main.cpp"});
    }

    return out;
}


std::vector<std::string> Loader::read_directory(const std::string& name)
{
    std::vector<std::string> v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);

    return v;
}

void Loader::saveXML(std::vector<aClass>& classes, std::vector<Arrow> &arrows, std::string path){
    std::string out = "";
    out += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    out += "<mxfile host=\"Electron\" modified=\"2024-04-23T07:52:20.908Z\"";
    out += " agent=\"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko)";
    out += " draw.io/22.1.2 Chrome/114.0.5735.289 Electron/25.9.4 Safari/537.36\" ";
    out += "etag=\"9FPmBtHjVVFl_MkUjTRh\" version=\"22.1.2\" type=\"device\">";
    out += "<diagram id=\"C5RBs43oDa-KdzZeNtuy\" name=\"Page-1\">";
    out += "<mxGraphModel dx=\"1768\" dy=\"644\" grid=\"1\" gridSize=\"10\" guides=\"1\"";
    out += " tooltips=\"1\" connect=\"1\" arrows=\"1\" fold=\"1\" page=\"1\" pageScale=\"1\"";
    out += " pageWidth=\"827\" pageHeight=\"1169\" math=\"0\" shadow=\"0\">";
    out += "<root><mxCell id=\"id1\" /><mxCell id=\"id2\" parent=\"id1\" />";

    std::map<std::string, std::string> classNamesToId;

    //classes
    int index = 0;
    for (int i = 0; i < classes.size(); ++i) {
        classNamesToId.insert(std::pair<std::string, std::string>{classes[i].getName(),"id-class-" + std::to_string(index)});
        out += classes[i].toXML(index);
        for (int j = 0; j < classes[i].getEnums().size(); ++j) {
            ++index;
            classNamesToId.insert(std::pair<std::string, std::string>{classes[i].getEnums()[j].getName(),"id-class-" + std::to_string(index)});
            out += classes[i].getEnums()[j].toXML(index);
        }
        for (int j = 0; j < classes[i].getStructs().size(); ++j) {
            ++index;
            classNamesToId.insert(std::pair<std::string, std::string>{classes[i].getStructs()[j].getName(),"id-class-" + std::to_string(index)});
            out += classes[i].getStructs()[j].toXML(index);
        }
        ++index;
    }

    //arrows
    for (int i = 0; i < arrows.size(); ++i) {
        out += arrows[i].toXML(classNamesToId, i);
    }


    out += "</root></mxGraphModel></diagram></mxfile>";

    std::ofstream myfile;
    myfile.open (path);
    myfile << out;
    myfile.close();

    std::cout << "Done: file can be found at " << path << std::endl;
}
