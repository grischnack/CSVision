#ifndef CSPLANE3D_H
#define CSPLANE3D_H


#include "csshape2d.h"
#include "cspoint3d.h"
#include "csline3d.h"

class CsPlane3D
{
public:
    CsPlane3D(QVector3D norm, float dist, CsShape2D shap, CsPoint3D cent);
    CsPlane3D();
    CsPoint3D intersection(const CsLine3D *lin) const;
    CsLine3D intersection(const CsPlane3D *plan) const;
    CsPoint3D intersection2(const CsLine3D *lin) const;
    float calculatePointsDist(CsPoint3D const *p1, CsPoint3D const *p2) const;

    QVector3D normal;
    float distance;
    CsShape2D shape;

    CsPoint3D center;
    QList< QGenericMatrix<4, 1, int> > pixels;
};


inline uint qHash(const CsPlane3D& key){
    return (uint) abs(key.normal.x()*key.normal.y()*key.normal.z()*key.distance*key.center.x* key.center.y* key.center.z);
}

inline bool operator< (const CsPlane3D &l1, const CsPlane3D &l2){
    return l1.distance < l2.distance;
}


inline bool operator== (const CsPlane3D &l1, const CsPlane3D &l2){
    return (l1.distance == l2.distance)
            && (l1.normal == l2.normal)
            && (l1.center.x == l2.center.x)
            && (l1.center.y==l2.center.y)
            && (l1.center.z == l2.center.z);
}


#endif // CSPLANE3D_H
