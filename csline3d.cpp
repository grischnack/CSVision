#include "csline3d.h"

CsLine3D::CsLine3D()
{

}

CsLine3D::CsLine3D(QQuaternion r, float dist, float len, CsPoint3D cent){
    rot = r;
   distance = dist;
    length = len;
    center = cent;
}

QVector3D CsLine3D::direction() const{
    return rot.rotatedVector(QVector3D(0,0,1));
}
QVector3D CsLine3D::norm() const{
    return rot.rotatedVector(QVector3D(0,1,0));
}

void CsLine3D::rotation(QQuaternion q){
    rot*= q;
}



QQuaternion qFactory;
void CsLine3D::pitch(float angle){

}

void CsLine3D::yaw(float angle){


}
void CsLine3D::roll(float angle){


}
