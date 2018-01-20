#include "csplane3d.h"


CsPlane3D::CsPlane3D(QVector3D norm, float dist, CsShape2D shap, CsPoint3D cent){
    normal = norm;
    distance = dist;
    shape = shap;
    center = cent;
}

CsPlane3D::CsPlane3D(){
    normal = QVector3D(0,0,1);
    distance = 0.0f;
    shape = CsShape2D(3, 100, CsPoint2D(0,0));
    center = CsPoint3D(0,0,0);
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

float CsPlane3D::calculatePointsDist( CsPoint3D const *point1, CsPoint3D const *point2) const{
    return sqrt(pow( (point1->x-point2->x), 2)
                +pow((point1->y-point2->y),2)
                +pow((point1->z-point2->z),2));
}

//Returns line with same center as this plane.
CsLine3D CsPlane3D::intersection(const CsPlane3D *plan) const{



    QVector3D linedir = QVector3D::crossProduct(normal,plan->normal);
    linedir = linedir.normalized();

    QVector3D dirFromPointOnThisPlaneToClosestPointOfIntersection = QVector3D::crossProduct(-normal, linedir);
    QVector3D dirFromPointOnOtherPlaneToClosestPointOfIntersection = QVector3D::crossProduct(plan->normal, linedir);


    CsLine3D helperline = CsLine3D(QQuaternion::fromDirection(dirFromPointOnThisPlaneToClosestPointOfIntersection, normal),
                          distance, INFINITY, center);

    CsPoint3D closestpoint = plan->intersection(&helperline);


    float linedist = calculatePointsDist(&center, &closestpoint);



    QVector3D centerv = QVector3D(center.x, center.y, center.z);
    QVector3D pointonplanv = centerv + (normal*distance);
    CsPoint3D pointonplan = CsPoint3D(pointonplanv.x(), pointonplanv.y(), pointonplanv.z());

    //dirvector is linedir

    //upvector is following:

    float x = distance;
    float y = calculatePointsDist(&pointonplan, &closestpoint);
    float z = 0;
    QVector3D up = QVector3D(x, y, z);
    up = up.normalized();
    CsLine3D result = CsLine3D(QQuaternion::fromDirection(linedir, up), linedist, INFINITY, center);

    return result;
    //TODO: test
}
