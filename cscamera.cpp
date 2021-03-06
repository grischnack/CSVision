#include "cscamera.h"

CsCamera::CsCamera()
{


}

CsCamera::CsCamera(CsPoint3D nodpoint, int widthinpixels) {
    nodalPoint = nodpoint;

    widthInPixels = widthinpixels;
    generateRays();
}

void CsCamera::lookAt(CsPoint3D pp){
    QVector3D nodalv = QVector3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
    QVector3D ppv = QVector3D(pp.x, pp.y, pp.z);
    QVector3D relp = nodalv - ppv;
    rot = QQuaternion::fromDirection(relp, QVector3D(0,0,0));
}

void CsCamera::orbit( float r, float inc, float azi){


    QVector3D camline = QVector3D(0,0,-1);
    camline = rot.rotatedVector(camline);
    QVector3D nodalv = QVector3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
    QVector3D orbitedv = nodalv + (camline*r);

    QVector3D nodalrelorbitedv = orbitedv - nodalv;


    QVector3D upax = QVector3D(0,1,0);

    unRoll();
    upax = rot.conjugated().rotatedVector(QVector3D(0,1,0));


    QQuaternion absolutAzi = QQuaternion::fromDirection(QVector3D( sin(azi),0, cos(azi)), QVector3D(0,0,0));
    absolutAzi = absolutAzi.normalized();
    QQuaternion relAzi = QQuaternion::fromAxisAndAngle(upax,(180/M_PI)*azi );

    nodalrelorbitedv = absolutAzi.rotatedVector(-nodalrelorbitedv);
    nodalv = orbitedv + nodalrelorbitedv;
    CsPoint3D newNodal = CsPoint3D(nodalv.x(), nodalv.y(), nodalv.z());
    nodalPoint = newNodal;

    rotation(relAzi);
    actualizeRays();

    //_-------------------

    camline = QVector3D(0,0,-1);
    camline = rot.rotatedVector(camline);
    nodalv = QVector3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
    orbitedv = nodalv + (camline*r);
    nodalrelorbitedv = orbitedv  - nodalv;


    QVector3D rax = QVector3D(1,0,0);

    unRoll();

    rax = rot.rotatedVector(QVector3D(1,0,0));
    QQuaternion absolutInc = QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),-(180/M_PI)*inc );
    QQuaternion relInc =  QQuaternion::fromAxisAndAngle(rax,-(180/M_PI)*inc );

    nodalrelorbitedv = relInc.rotatedVector(-nodalrelorbitedv);
    nodalv = orbitedv + nodalrelorbitedv;
    newNodal = CsPoint3D(nodalv.x(), nodalv.y(), nodalv.z());
    nodalPoint = newNodal;

    rotation(absolutInc);
    actualizeRays();

}

void CsCamera::unRoll(){
    QVector3D fwd = QVector3D(0,0,1);
    fwd = rot.rotatedVector(fwd);
    QQuaternion unrolled = QQuaternion::fromDirection(fwd, QVector3D(0,1,0));

    rot = unrolled;
    actualizeRays();
}


void CsCamera::generateRays(){

    rays.clear();
    raysOriginal.clear();
    parallelRays.clear();
    parallelRaysOriginal.clear();

    planarRays.clear();
    planarRaysOriginal.clear();
    parallelPlanarRays.clear();
    parallelPlanarRaysOriginal.clear();
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
        CsPlane3D parallelvertical= CsPlane3D(parallelnorm, i-(widthInPixels/2), infinitshape,nodalPoint);
        parallelPlanarRaysOriginal.append(parallelvertical);
        parallelPlanarRays.append(parallelvertical);


        parallelnorm = QVector3D(0,1,0);
        ppp = CsPoint3D(nodalPoint.x, nodalPoint.y + i-(widthInPixels/2), nodalPoint.z);
        CsPlane3D parallelhorizontal = CsPlane3D(parallelnorm, i-(widthInPixels/2), infinitshape, nodalPoint);
        parallelPlanarRaysOriginal.append(parallelhorizontal);
        parallelPlanarRays.append(parallelhorizontal);
    }

    // -------------------- rays


    for(int i = 0 ; i < widthInPixels; i++){
        for(int j = 0; j < widthInPixels; j++){

            QVector3D rayvec = QVector3D(j-widthInPixels/2, i-widthInPixels/2, focallength*widthInPixels);
            rayvec = rayvec.normalized();
            QQuaternion rayq = QQuaternion::fromDirection(rayvec, QVector3D(0,0,0));
            CsLine3D ray = CsLine3D(rayq, 0, INFINITY, nodalPoint);
            raysOriginal.append(ray);
            rays.append(ray);
            raysInitialRotations.append(rayq.conjugated());
        }
    }

    // -------- parallel rays

    for(int i = 0; i < widthInPixels; i++){
        for(int j = 0; j < widthInPixels; j++){


            QVector3D camdir = QVector3D(0,0,-1);
            QVector3D raypos = QVector3D(j-widthInPixels/2, i-widthInPixels/2,0);
            raypos = raypos.normalized();
            float raydist = sqrt(pow(((j-widthInPixels/2)), 2)+pow((i-widthInPixels/2), 2));
            QQuaternion rayq = QQuaternion::fromDirection(camdir, raypos);
            CsLine3D ray = CsLine3D(rayq, raydist, INFINITY, nodalPoint);
            parallelRaysOriginal.append(ray);
            parallelRays.append(ray);
            parallelRaysInitialRotations.append(rayq);
        }
    }

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
         tmp.center = CsPoint3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
        parallelPlanarRays.append(tmp);
    }

    rays.clear();
    int nr = raysOriginal.count();

    for(int i = 0; i < nr; i++){
        CsLine3D tmp = raysOriginal.at(i);
        QVector3D rotax;
        float rotang;
        rot.getAxisAndAngle(&rotax, &rotang);
        QQuaternion tmpq = QQuaternion::fromAxisAndAngle(raysInitialRotations.at(i).rotatedVector(rotax), rotang);
        tmp.rotation(tmpq);
        rays.append(tmp);

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
    QVector3D pos = QVector3D(nodalPoint.x, nodalPoint.y, nodalPoint.z);
    QVector3D inc = QVector3D(0, 0, -1);
    inc = rot.rotatedVector(inc);
    inc *=val;
    pos -= inc;
    nodalPoint.x = pos.x();
    nodalPoint.y = pos.y();
    nodalPoint.z = pos.z();
    actualizeRays();
}
