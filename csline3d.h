#ifndef CSLINE3D_H
#define CSLINE3D_H


#include "csline2d.h"
#include "cspoint3d.h"

class CsLine3D
{
public:
    CsLine3D(float thet, float ph, float ps, float dist, float len , CsPoint3D cent);
    CsLine3D(QVector3D dir, float dist, float len, CsPoint3D cent);
    CsLine3D();

    void pitch(float angle);
    void yaw(float angle);
    void roll(float angle);

    float theta;
    float phi;
    float psi;
    float distance;
    float length;

    QVector3D direction = QVector3D( 0, 0, 1);

    QList< QGenericMatrix<3, 1, int> > pixels;
    CsPoint3D center;
};


inline uint qHash(const CsLine3D& key){
    return (uint) abs(key.theta*key.phi*key.psi*key.distance*key.center.x* key.center.y *key.center.z);
}

inline bool operator< (const CsLine3D &l1, const CsLine3D &l2){
    return l1.length < l2.length;
}


inline bool operator== (const CsLine3D &l1, const CsLine3D &l2){
    return (l1.distance == l2.distance)
            && (l1.theta == l2.theta) && (l1.phi == l2.phi) && (l1.psi == l2.psi)
            && (l1.center.x == l2.center.x)
            && (l1.center.y==l2.center.y)
            && (l1.center.z==l2.center.z);
}

#endif // CSLINE3D_H
