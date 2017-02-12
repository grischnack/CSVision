#ifndef CSPOINT2D_H
#define CSPOINT2D_H

#include <math.h>
#include "sys/types.h"
#include <stdlib.h>


class CsPoint2D
{
public:
    CsPoint2D(float xx, float yy);
    CsPoint2D(bool polar, float phi, float d);
    CsPoint2D();

    float x;
    float y;

    float phi;
    float d;
};


inline uint qHash(const CsPoint2D& key){
    return (uint) abs(key.x*key.y);
}

inline bool operator< (const CsPoint2D &l1, const CsPoint2D &l2){
    return l1.x < l2.x;
}


inline bool operator== (const CsPoint2D &l1, const CsPoint2D &l2){
    return (l1.x == l2.x)
            && (l1.y == l2.y);
}

#endif // CSPOINT2D_H
