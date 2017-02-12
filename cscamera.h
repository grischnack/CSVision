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

    QQuaternion rot = QQuaternion(1, 0, 0, 0);

    int curvRectOrt = 1;

    CsPoint3D nodalPoint;
    float focallength = 1.0;
    float angleOfView;


    QList<OzPlane3d> planarraysoriginal;
    QList<OzPlane3d> planarrays;
    QList<OzPlane3d> parallelplanarraysoriginal;
    QList<OzPlane3d> parallelplanarrays;
    QList<OzLine3d> rays;
};

#endif // CSCAMERA_H
