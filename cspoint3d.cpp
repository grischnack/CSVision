#include "cspoint3d.h"

CsPoint3D::CsPoint3D(float xx, float yy, float zz){
    x = xx;
    y = yy;
    z = zz;
    dist =sqrt(pow( xx, 2)+pow(yy,2)+pow((zz),2));
    inclination = acos(zz/dist);
    azimut = atan2( yy, xx);
}

CsPoint3D::CsPoint3D(bool noth, float r, float inc, float az){
    x = r * sin(inc) * cos(az);
    y = r * sin(inc) * sin(az);
    z = r * sin(az);
    dist = r;
    inclination = inc;
    azimut = az;
}

CsPoint3D::CsPoint3D() : CsPoint3D(1, 1, 1)
{

}

