#ifndef CSSHAPE2D_H
#define CSSHAPE2D_H

#include "csline2d.h"

class CsShape2D
{
public:
    CsShape2D(uint sidenum, int siz, CsPoint2D cent);
    CsShape2D();

    QList<CsLine2D> borderLines;
    QGenericMatrix<3, 1, int> center;

    float angle = 0;

    void rotate(float increment);

    int nuls[3] = {0, 0, 0} ;
};

#endif // CSSHAPE2D_H
