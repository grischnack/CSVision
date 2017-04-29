#include "csplane3d.h"


CsPlane3D::CsPlane3D(QVector3D norm, float dist, CsShape2D shap, CsPoint3D cent){
    normal = norm;
    distance = dist;
    shape = shap;
    center = cent;
}

CsPoint3D CsPlane3D::intersection2(const CsLine3D *lin) const{




}

CsPoint3D CsPlane3D::intersection(const CsLine3D *lin) const{


    CsPoint3D intersp;

    QVector3D plancent = QVector3D(center.x, center.y, center.z);
    plancent = plancent +(normal*distance);

    QVector3D lincent = QVector3D(lin->center.x, lin->center.y, lin->center.z);
    QVector3D linNorm = lin->norm();
    linNorm *= lin->distance;
    lincent = lincent + linNorm;

    float length;
    float dotNumerator;
    float dotDenominator;
    dotNumerator = QVector3D::dotProduct(( plancent - lincent), normal);
    dotDenominator = QVector3D::dotProduct(lin->direction(), normal);

    QVector3D vector = QVector3D(0,0,0);

    if(dotDenominator != 0.0f){
        length =  dotNumerator / dotDenominator;

        if(abs(length)<lin->length/2){
        vector = lin->direction();
        vector *= length;

        QVector3D intersection = lincent + vector;

        intersp = CsPoint3D(intersection.x(), intersection.y(), intersection.z());

        }


    }
    return intersp;
}

//Returns line with same center as this plane.
CsLine3D CsPlane3D::intersection(const CsPlane3D *plan) const{



    QVector3D linecent = center;

    QVector3D linedir = QVector3D::crossProduct(normal,plan->normal);
    linedir = linedir.normalized();

    QVector3D dirFromPointOnThisPlaneToClosestPointOfIntersection = QVector3D(normal, linedir);
    QVector3D dirFromPointOnOtherPlaneToClosestPointOfIntersection = QVector3D(plan->normal, linedir);


    CsLine3D helperline = CsLine3D(QQuaternion::fromDirection(dirFromPointOnThisPlaneToClosestPointOfIntersection, normal),
                          distance, INFINITY, center);

    CsPoint3D closestpoint = plan->intersection(&helperline);


    float linedist = CsScene3D::calculatePointsDist(center, closestpoint);

    //dirvector is linedir

    //upvector is following:

    float x = distance;
    float y = CsScene3D::calculatePointsDist(pointonplan, closestpoint);
    float z = 0;
    QVector3D up = QVector3D(x, y, z);

    CsLine3D result = CsLine3D(QQuaternion(linedir, up), linedist, INFINITY, center);

    //TODO: test
}
