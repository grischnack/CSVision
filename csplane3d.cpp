#include "csplane3d.h"

CsPlane3D::CsPlane3D(QVector3D norm, float dist, CsShape2D shap, CsPoint3D cent){
    normal = norm;
    distance = dist;
    shape = shap;
    center = cent;
}

CsPoint3D CsPlane3D::intersection(const CsLine3D *lin) const{



    CsPoint3D pointInters;
    QVector3D lincent = QVector3D(lin->center.x, lin->center.y, lin->center.z);
    QVector3D zvec = QVector3D(0,0,1);
    QVector3D nulvec = QVector3D(0,0,0);
    QQuaternion qq = QQuaternion::fromDirection(zvec, nulvec);
    qq *= QQuaternion::fromDirection(lin->direction, nulvec);
    QVector3D linNorm = qq.rotatedVector(lin->direction);
    linNorm *= lin->distance;
    lincent = lincent + linNorm;
    float length;
            float dotNumerator;
            float dotDenominator;
            QVector3D vector;

            QVector3D planecent = QVector3D(center.x, center.y, center.z );
            planecent = planecent + (normal*distance);

            dotNumerator = QVector3D::dotProduct(( planecent - lincent), normal);
            dotDenominator = QVector3D::dotProduct(lin->direction, normal);


            if(dotDenominator != 0.0f){
                length =  dotNumerator / dotDenominator;

                if(abs(length)<lin->length/2){
                vector = lin->direction;
                vector *= length;

                QVector3D intersection = lincent + vector;

                pointInters = CsPoint3D(intersection.x(), intersection.y(), intersection.z());

                }

            }


    return pointInters;
}
