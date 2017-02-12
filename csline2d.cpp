#include "csline2d.h"
#include <QtGui>
#include "sys/types.h"

CsLine2D::CsLine2D( float ang, float dist, float len, CsPoint2D cent)
{

       angle = ang;
       distance = dist;
       length = len;
       centerr = cent;

}

