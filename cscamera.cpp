#include "cscamera.h"

CsCamera::CsCamera()
{


}

CsCamera::CsCamera(CsPoint3D nodpoint, int widthinpixels) {
    nodalPoint = nodpoint;

    widthInPixels = widthinpixels;
    generateRays();
}


void CsCamera::generateRays(){

    //--------------planar rays

    for(int i = 0; i < widthInPixels; i++){
        float ang = (float)i/(float)widthInPixels;
        QVector3D norm = QVector3D(0, focallength*widthInPixels, i-(widthInPixels/2));
        norm = norm.normalized();
        CsShape2D infinitshape;
        int nuls[4] = {0,0,0,0};

        CsPoint3D origo = CsPoint3D(0,0,0);
        CsPlane3D planarRay = CsPlane3D(norm, 0, infinitshape, nodalPoint);
        planarRaysOriginal.append(planarRay);
        planarRays.append(planarRay);



        norm = QVector3D(focallength*widthInPixels,  0,  i-(widthInPixels/2));
        norm = norm.normalized();
        planarRay = CsPlane3D(norm, 0, infinitshape, nodalPoint);
        planarRaysOriginal.append(planarRay);
        planarRays.append(planarRay);


        //--------------------- parallel planar rays

        QVector3D parallelnorm = QVector3D(1,0,0);
        CsPoint3D ppp = CsPoint3D(nodalPoint.x  + i-(widthInPixels/2), nodalPoint.y, nodalPoint.z);
        CsPlane3D parallelvertical= CsPlane3D(parallelnorm, 0, infinitshape,ppp);
        parallelPlanarRaysOriginal.append(parallelvertical);
        parallelPlanarRays.append(parallelvertical);


        parallelnorm = QVector3D(0,1,0);
        ppp = CsPoint3D(nodalPoint.x, nodalPoint.y + i-(widthInPixels/2), nodalPoint.z);
        CsPlane3D parallelhorizontal = CsPlane3D(parallelnorm, 0, infinitshape, ppp);
        parallelPlanarRaysOriginal.append(parallelhorizontal);
        parallelPlanarRays.append(parallelhorizontal);
    }

    // -------------------- rays


    for(int i = 0 ; i < widthInPixels; i++){
        for(int j = 0; j < widthInPixels; j++){

            QVector3D rayvec = QVector3D(j-widthInPixels/2, i-widthInPixels/2, focallength*widthInPixels);
            CsLine3D ray = CsLine3D(rayvec, 0, INFINITY, nodalPoint);
            raysOriginal.append(ray);
            rays.append(ray);
        }
    }

    // -------- parallel rays

}

void CsCamera::rotation(QQuaternion q){
    rot*= q;

    actualizeRays();

}


void CsCamera::setFocalLength(float len){
    focallength = len;

    generateRays();
    actualizeRays();

}

void CsCamera::actualizeRays(){

    planarRays.clear();
    int n = planarRaysOriginal.count();
    for(int i = 0; i < n; i++){
        CsPlane3D tmp = planarRaysOriginal.at(i);
        tmp.normal = rot.rotatedVector(tmp.normal);
        tmp.center = CsPoint3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
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
        rotplan = cam+rotplan;
        tmp.center = CsPoint3D(rotplan.x(), rotplan.y(), rotplan.z());
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
