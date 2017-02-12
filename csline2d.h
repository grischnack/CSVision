#ifndef CSLINE2D_H
#define CSLINE2D_H


#include "sys/types.h"
#include <math.h>
#include "cspoint2d.h"
#include <QtGui>

class CsLine2D
{
public:
    CsLine2D();
    explicit CsLine2D(float angle, float dist = 0, float len = 0, CsPoint2D cent = CsPoint2D(0,0));

    float angle;
    float distance;
    float length;

    QList< QGenericMatrix<3, 1, int> > pixels;
    CsPoint2D centerr;
};


inline uint qHash(const CsLine2D& key){
    return (uint) abs(key.angle*key.distance*key.centerr.x* key.centerr.y);
}

inline bool operator< (const CsLine2D &l1, const CsLine2D &l2){
    return l1.length < l2.length;
}


inline bool operator== (const CsLine2D &l1, const CsLine2D &l2){
    return (l1.distance == l2.distance) && (l1.angle == l2.angle)
            && (l1.centerr.x == l2.centerr.x)
            && (l1.centerr.y==l2.centerr.y);
}

#endif // CSLINE2D_H
