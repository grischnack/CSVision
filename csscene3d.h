#ifndef CSSCENE3D_H
#define CSSCENE3D_H


#include "csplane3d.h"
#include "csline3d.h"
#include "cspoint3d.h"
#include "cscamera.h"

class CsScene3D
{
public:
    CsScene3D();

    void clearScreen();
    void redrawAll();
    void putLine3d(CsLine3D *lin);
    void putPoint(CsPoint3D *point);
    void redrawPoints();
    void setPixel(int x, int y, int col);
    void drawPoint(CsPoint3D* point);
    void redrawLines();
    float calculatePointDist(CsPoint3D* point);
    float calculatePointsDist( CsPoint3D *point1, CsPoint3D *point2);
    float* calculatePointAngle(CsPoint3D* point);
    int* calcualtePoint(CsPoint3D* point);
    void drawLine(CsLine3D *lin);
    void calculateLine(CsLine3D *lin);

    QList<float> cartesianToSpherical(float x, float y, float z);
    QList<float> sphericalToCartesian(float r, float inclination, float azimuth);

    QList<CsLine3D*> lines;
    QList<CsPlane3D*> planes;
    QList<CsPoint3D*> pointss;
    CsPoint3D ppp = CsPoint3D(200, 200, 700);

    CsCamera camera = CsCamera(ppp, imgw) ;


    const static int imgw = 500;
    const static int imgh = 300;



    int pixels[imgw][imgh] = {{1}};
};

#endif // CSSCENE3D_H
