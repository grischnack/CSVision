#include "csshape2d.h"

CsShape2D::CsShape2D(uint sidenum, int siz, CsPoint2D cent)
{

    if(sidenum > 2){

        for(int i = 0; i < sidenum; i++){
            CsLine2D lin = CsLine2D(angle+i*((M_PI*2)/sidenum), siz/2, siz/(sidenum/4.0), cent);
            borderLines.append(lin);
        }
    }
}

CsShape2d::CsShape2D() :
    CsShape2D(4, 50, CsPoint2D(0,0)){

}

void CsShape2D::rotate(float increment){

    angle += increment;
    for(int i = 0; i < borderlines.count(); i++){
        borderlines[i].angle += increment;

    }
}

