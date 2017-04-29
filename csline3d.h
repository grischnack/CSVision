#ifndef CSLINE3D_H
#define CSLINE3D_H


#include "csline2d.h"
#include "cspoint3d.h"

class CsLine3D
{
public:
   // CsLine3D(QVector3D dir, float dist, float len, CsPoint3D cent);
    CsLine3D(QQuaternion r, float dist, float len, CsPoint3D cent);
    CsLine3D();

    void pitch(float angle);
    void yaw(float angle);
    void roll(float angle);
    QVector3D direction() const;
    QVector3D norm() const;
    void rotation(QQuaternion q);

    float distance;
    float length;

    QQuaternion rot = QQuaternion(1,0,0,0);

    QList< QGenericMatrix<4, 1, int> > pixels;
    CsPoint3D center;

};


inline uint qHash(const CsLine3D& key){
    return (uint) abs(key.rot.x()*key.rot.y()*key.rot.z()*key.distance*key.center.x* key.center.y *key.center.z);
}

inline bool operator< (const CsLine3D &l1, const CsLine3D &l2){
    return l1.length < l2.length;
}


inline bool operator== (const CsLine3D &l1, const CsLine3D &l2){
    return (l1.distance == l2.distance)
            && (l1.rot == l2.rot)
            && (l1.center.x == l2.center.x)
            && (l1.center.y==l2.center.y)
            && (l1.center.z==l2.center.z);
}

#endif // CSLINE3D_H
