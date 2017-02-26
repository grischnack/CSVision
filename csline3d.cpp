#include "csline3d.h"

CsLine3D::CsLine3D()
{

}

CsLine3D::CsLine3D(QVector3D dir, float dist, float len, CsPoint3D cent){
    direction = dir;
    distance = dist;
    length = len;
    center = cent;
}

QQuaternion qFactory;
void CsLine3D::pitch(float angle){
    QQuaternion dir = qFactory.fromDirection(QVector3D(0, sin(angle), cos(angle)), QVector3D(0,0,0));

    direction = dir.rotatedVector(direction);
}

void CsLine3D::yaw(float angle){
    QQuaternion dir = qFactory.fromDirection(QVector3D( sin(angle),0, cos(angle)),QVector3D(0,0,0));

    direction = dir.rotatedVector(direction);

}
void CsLine3D::roll(float angle){

    QQuaternion upDir = qFactory.fromDirection(QVector3D(0,0,1),QVector3D( -sin(angle), cos(angle), 0));

    direction =upDir.rotatedVector(direction);
}
