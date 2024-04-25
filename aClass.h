#ifndef ACLASS_H
#define ACLASS_H

#include <string>
#include <vector>
#include "aLine.h"
#include "Arrow.h"

class aClass
{
public:
    aClass();
    aClass(std::vector<std::string> data) {mName = data[0]; mData = data; parse();}

    std::string getName(){return mName;}
    std::vector<aLine> getLines() {return mLines;};

    virtual std::string toXML(int id);

    std::vector<aClass> getEnums(){return mEnums;}
    std::vector<aClass> getStructs(){return mStructs;}

    std::vector<Arrow> getArrows(std::vector<std::string> classNames);


private:
    virtual void parse();

    std::vector<aClass> mEnums;
    std::vector<aClass> mStructs;

protected:
    std::vector<std::string> split(const std::string& line,
                                   char delim);
    bool evenParanteser(std::string line);

    std::string mName;
    std::string mBaseClassName;
    std::vector<std::string> mData;
    std::vector<aLine> mLines;

    const std::string xmldoc1 = "<mxCell id=\"";
    //id-class-0
    const std::string xmldoc2 = "\" value=\"";
    //PinHolder
    const std::string xmldoc3 = "\" style=\"swimlane;fontStyle=2;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=26;horizontalStack=0;resizeParent=1;resizeLast=0;collapsible=1;marginBottom=0;rounded=0;shadow=0;strokeWidth=1;\" parent=\"";
    //id2
    const std::string xmldoc4 = "\" vertex=\"1\"><mxGeometry x=\"";
    //220 * id
    const std::string xmldoc5 = "\" y=\"10\" width=\"200\" height=\"100\" as=\"geometry\"><mxRectangle x=\"230\" y=\"140\" width=\"160\" height=\"26\" as=\"alternateBounds\" /></mxGeometry></mxCell>";

    const std::string xmlLine1 = "<mxCell id=\"";
    //id-class-0-1
    const std::string xmlLine2 = "\" value=\"\" style=\"line;html=1;strokeWidth=1;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;\" parent=\"";
    //id-class-0
    const std::string xmlLine3 = "\" vertex=\"1\"><mxGeometry y=\"26\" width=\"490\" height=\"8\" as=\"geometry\" /></mxCell>";

    const std::string xmltext1 = "<mxCell id=\"";
    //id-class-0-2
    const std::string xmltext2 = "\" value=\"";
    //text
    const std::string xmltext3 = "\" style=\"text;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;";
    //static
    const std::string xmltext4 = "\" parent=\"";
    //id-class-0
    const std::string xmltext5 = "\" vertex=\"1\"><mxGeometry y=\"60\" width=\"490\" height=\"26\" as=\"geometry\" /></mxCell>";

    const std::string xmltextNonStatic = "fontStyle=0";
    const std::string xmltextStatic = "fontStyle=4";
};

#endif // ACLASS_H
