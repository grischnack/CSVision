#include "cspoint2d.h"

CsPoint2D::CsPoint2D(float xx, float yy)
{

    x = xx;
    y = yy;

    phi = atan2(y, x);
    d = sqrt(pow(x, 2) + pow(y, 2));
}

CsPoint2D::CsPoint2D(bool polar, float ph, float dd){
    phi = ph;
    d = dd;

    x = dd*cos(phi);
    y = dd*sin(phi);
}

CsPoint2D::CsPoint2D() : OzPoint2d(0,0){}

