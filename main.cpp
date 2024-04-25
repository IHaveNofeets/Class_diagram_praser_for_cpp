#include <iostream>

#include "Loader.h"
#include "aClass.h"

#include <string>
#include <vector>

#ifndef MY_HEADER
#define MY_HEADER
void folderToClassDiagram(std::string folderpath, bool isWin);
#endif

int main()
{
    //folderToClassDiagram("C:\\Users\\tobia\\OneDrive - Syddansk Universitet\\Skrivebord\\SDU\\Sem_2\\C++\\Class_diagram\\class_diagram", true);
    folderToClassDiagram("C:\\Users\\tobia\\OneDrive - Syddansk Universitet\\Skrivebord\\SDU\\Sem_2\\projekt\\c++ code\\SDU-Gripper-sem2", true);

    //TODO: arrows number

    return 0;
}


void folderToClassDiagram(std::string folderpath, bool isWin){
    Loader loader{};
    auto classesText = loader.getFiles(folderpath, true);
    std::cout << "folder: " + folderpath<< " choosen" << std::endl;
    std::vector<aClass> classes;
    for (int i = 0; i < classesText.size(); ++i) {
        classes.push_back(aClass{classesText[i]});
    }
    std::vector<std::string> classNames;
    for (int i = 0; i < classesText.size(); ++i) {
        classNames.push_back(classes[i].getName());
    }

    std::vector<Arrow> allArrows;
    for (int i = 0; i < classesText.size(); ++i) {
        std::vector<Arrow> classArrow = classes[i].getArrows(classNames);
        allArrows.insert(allArrows.end(), classArrow.begin(), classArrow.end());
    }

    loader.saveXML(classes, allArrows, folderpath + (isWin ? "\\" : "/") + "class_diagram.xml");

}
