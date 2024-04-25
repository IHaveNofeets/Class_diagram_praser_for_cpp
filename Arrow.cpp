#include "Arrow.h"

Arrow::Arrow() {}
std::string Arrow::toXML(std::map<std::string, std::string> &classNamesToId, int id){
    std::string out;
    /*
<mxCell id="jFbF_QeLPzmfpAF6_2OH-2085" style="edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;exitX=1;exitY=0.5;exitDx=0;exitDy=0;entryX=0.5;entryY=1;entryDx=0;entryDy=0;" edge="1" parent="1" source="jFbF_QeLPzmfpAF6_2OH-1905" target="jFbF_QeLPzmfpAF6_2OH-1928">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
*/
    double startX, startY, endX, endY;
    if(isSubClass){
        startX = 0.5;
        startY = 1;
        endX = 0.5;
        endY = 0;
    }else{
        startX = 1;
        startY = 0.5;
        endX = 0;
        endY = 0.5;
    }


    out += "<mxCell id=\"id-arrow-" + std::to_string(id);
    out += "\" style=\"edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;exitX=";
    out += std::to_string(startX) + ";exitY=";
    out += std::to_string(startY) + ";exitDx=0;exitDy=0;entryX=";
    out += std::to_string(endX) + ";entryY=";
    out += std::to_string(endY) + ";entryDx=0;entryDy=0;";

    if(isSubClass){
        out += "endArrow=block;endFill=0;startArrow=none;startFill=0;";
    }else{
        out += "endArrow=classic;endFill=1;startArrow=none;startFill=0;";
    }

    out += "\" edge=\"1\" parent=\"id2\" source=\"" + classNamesToId[from];
    out += "\" target=\"" + classNamesToId[to];
    out += "\"><mxGeometry relative=\"1\" as=\"geometry\" /></mxCell>";

    return out;
}
