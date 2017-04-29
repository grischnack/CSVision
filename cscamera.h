#ifndef CSCAMERA_H
#define CSCAMERA_H


#include "cspoint3d.h"
#include "csline3d.h"
#include "csplane3d.h"

class CsCamera
{
public:

    CsCamera();
    CsCamera(CsPoint3D focpoint, int widthpixels);

    void setFocalLength(float length);
    void goForward(float val);
    void goBackward(float val);
    void rotation(QQuaternion q);
    void actualizeRays();
    void generateRays();
    void unRoll();
    void orbit(float r, float inc, float azi);
    void lookAt(CsPoint3D pp);

    QQuaternion rot = QQuaternion(1, 0, 0, 0);

    int curvRectOrt = 1;

    CsPoint3D nodalPoint;
    float focallength = 1.0;

    int widthInPixels;


    QList<CsPlane3D> planarRaysOriginal;
    QList<CsPlane3D> planarRays;
    QList<CsPlane3D> parallelPlanarRaysOriginal;
    QList<CsPlane3D> parallelPlanarRays;
    QList<CsLine3D> raysOriginal;
    QList<CsLine3D> rays;
    QList<CsLine3D> parallelRaysOriginal;
    QList<CsLine3D> parallelRays;
    QList<QQuaternion> raysInitialRotations;
    QList<QQuaternion> parallelRaysInitialRotations;
};

#endif // CSCAMERA_H
