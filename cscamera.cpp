#include "cscamera.h"

CsCamera::CsCamera()
{


}

CsCamera::CsCamera(CsPoint3D nodpoint, int widthinpixels) {
    nodalPoint = nodpoint;

    for(int i = 0; i < widthinpixels; i++){
        float ang = (float)i/(float)widthinpixels;
        QVector3D norm = QVector3D(0, focallength*widthinpixels, i-(widthinpixels/2));
        norm = norm.normalized();
        CsShape2D infinitshape;
        int nuls[4] = {0,0,0,0};

        CsPoint3D origo = CsPoint3D(0,0,0);
        CsPlane3D planarRay = CsPlane3D(norm, 0, infinitshape, nodalPoint);
        planarRaysOriginal.append(planarRay);
        planarRays.append(planarRay);



        norm = QVector3D(focallength*widthinpixels,  0,  i-(widthinpixels/2));
        norm = norm.normalized();
        planarRay = CsPlane3D(norm, 0, infinitshape, nodalPoint);
        planarRaysOriginal.append(planarRay);
        planarRays.append(planarRay);


        //---------------------

        QVector3D parallelnorm = QVector3D(1,0,0);
        CsPoint3D ppp = CsPoint3D(nodalPoint.x  + i-(widthinpixels/2), nodalPoint.y, nodalPoint.z);
        CsPlane3D parallelvertical= CsPlane3D(parallelnorm, 0, infinitshape,ppp);
        parallelPlanarRaysOriginal.append(parallelvertical);
        parallelPlanarRays.append(parallelvertical);


        parallelnorm = QVector3D(0,1,0);
        ppp = CsPoint3D(nodalPoint.x, nodalPoint.y + i-(widthinpixels/2), nodalPoint.z);
        CsPlane3D parallelhorizontal = CsPlane3D(parallelnorm, 0, infinitshape, ppp);
        parallelPlanarRaysOriginal.append(parallelhorizontal);
        parallelPlanarRays.append(parallelhorizontal);
    }

}

void CsCamera::rotation(QQuaternion q){
    rot*= q;

    actualizeRays();

}

void CsCamera::setFocalLength(float len){
    focallength = len;

    actualizeRays();

}

void CsCamera::actualizeRays(){

    planarRays.clear();
    int n = planarRaysOriginal.count();
    for(int i = 0; i < n; i++){
        CsPlane3D tmp = planarRaysOriginal.at(i);
        tmp.normal = rot.rotatedVector(tmp.normal);
        planarRays.append( tmp);
    }

    parallelPlanarRays.clear();
    int np = parallelPlanarRaysOriginal.count();
    for(int i = 0; i < np; i++){
        CsPlane3D tmp = parallelPlanarRaysOriginal.at(i);
        tmp.normal = rot.rotatedVector(tmp.normal);
        QVector3D cam = QVector3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
        QVector3D plan = QVector3D(tmp.center.x, tmp.center.y, tmp.center.z);
        QVector3D rotplan = cam-plan;
        rotplan = rot.rotatedVector(rotplan);
        //rotplan = cam+rotplan;
       // tmp.center = CsPoint3D(rotplan.x(), rotplan.y(), rotplan.z());
        parallelPlanarRays.append(tmp);
    }
}

void CsCamera::goForward(float val){

    QVector3D pos = QVector3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
    QVector3D inc = QVector3D(0, 0, -1);
    inc = rot.rotatedVector(inc);
    inc *=val;
    pos += inc;
    nodalPoint.x = pos.x();
    nodalPoint.y = pos.y();
    nodalPoint.z = pos.z();

    actualizeRays();

}

void CsCamera::goBackward(float val){

   // focus.z += val * cos(line.theta)*cos(line.phi);
   // focus.y += val * sin(line.phi)*sin(line.psi);
   // focus.x += val * sin(line.theta)*sin(line.psi);
   // line.center = focus;
    actualizeRays();
}
