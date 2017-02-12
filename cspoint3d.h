#ifndef CSPOINT3D_H
#define CSPOINT3D_H

#include "csline2d.h"


class CsPoint3D
{
public:
    CsPoint3D();
    CsPoint3D(float xx, float yy, float zz);
    CsPoint3D(bool noth, float r, float inc, float az);

    float x;
    float y;
    float z;

    float dist;
    float inclination;
    float azimut;

    QList<QGenericMatrix<3, 1, int> > pixels;
  //  QGenericMatrix<3, 1, int> pixel;
};



inline uint qHash(const CsPoint3D& key){
    return (uint) abs(key.x*key.y*key.z);
}

inline bool operator< (const CsPoint3D &l1, const CsPoint3D &l2){
    return l1.x < l2.x;
}


inline bool operator== (const CsPoint3D &l1, const CsPoint3D &l2){
    return (l1.x == l2.x)
            && (l1.y == l2.y)
            && (l1.z == l2.z);
}


#endif // CSPOINT3D_H
