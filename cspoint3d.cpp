#include "cspoint3d.h"

CsPoint3D::CsPoint3D(float xx, float yy, float zz){
    x = xx;
    y = yy;
    z = zz;
    dist =sqrt(pow( xx, 2)+pow(yy,2)+pow((zz),2));
    inclination = acos(zz/dist);
    azimut =atan(yy/xx);
}

CsPoint3D::CsPoint3D(bool noth, float r, float inc, float az){
    x = r * cos(inc) * cos(az);
    y = r * sin(inc) * cos(az);
    z = r * cos(inc);
    dist = r;
    inclination = inc;
    azimut = az;
   // qDebug() << x << y << z << inc << az;
}

CsPoint3D::CsPoint3D() : CsPoint3D(1, 1, 1)
{

}

