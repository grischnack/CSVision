#include "csscene3d.h"


CsScene3D::CsScene3D()
{

    clearScreen();
}


void CsScene3D::clearScreen(){
    for(int i = 0; i < imgw; i++){
        for(int j = 0; j < imgh; j++){
               pixels[i][j] = 255;

        }
    }
}


void CsScene3D::setPixel(int x, int y, int col){

    if(abs(x)<imgw/2 && abs(y)<imgh/2){
       pixels[x+(imgw/2)][imgh-(y+(imgh/2))] = col;
    }
}


void CsScene3D::redrawAll() {
    clearScreen();
    redrawPoints();
    redrawLines();
}


void CsScene3D::redrawPoints(){


    int n = pointss.count();
    for(int i = 0; i < n; i++){
        CsPoint3D *pp = pointss.takeAt(i);
        int nn = pp->pixels.count();
        for (int ii = 0; ii < nn; ii++) {
            QGenericMatrix<3, 1, int> pix = pp->pixels.at(ii);
           // setPixel(pix(0,0), pix(0,1), 255);

        }
        drawPoint(pp);
        pointss.insert(i, pp);
    }
}


void CsScene3D::redrawLines(){
    int n = lines.count();
    for(int i = 0; i < n; i++){
        CsLine3D *lin = lines.takeAt(i);
        int nn = lin->pixels.count();
        for (int ii = 0; ii < nn; ii++) {
            QGenericMatrix<3, 1, int> pix = lin->pixels.at(ii);
           // setPixel(pix(0,0), pix(0,1), 255);
        }
        drawLine(lin);
        lines.insert(i, lin);
    }

}


void CsScene3D::putPoint(CsPoint3D *point){

    drawPoint(point);

    bool newpoint = true;
    int n = pointss.count();
    for(int i = 0; i < n; i++){
        if(&pointss.at(i) == &point){
            newpoint = false;
        }
    }

    if(newpoint){
        pointss.append(point);
    }
}


void CsScene3D::putLine3d(CsLine3D *lin){

    drawLine(lin);

    bool newline = true;
    int n = lines.count();
    for(int i = 0; i < n; i++){
        if(&lines.at(i) == &lin){
            newline = false;
        }
    }

    if(newline){
        lines.append(lin);
    }
}


float CsScene3D::calculatePointDist(CsPoint3D *point){

    float ff = sqrt(pow( (point->x-camera.nodalPoint.x), 2)
                    +pow((point->y-camera.nodalPoint.y),2)
                    +pow((point->z-camera.nodalPoint.z),2));
    return ff;
}


float CsScene3D::calculatePointsDist( CsPoint3D *point1, CsPoint3D *point2){
    return sqrt(pow( (point1->x-point2->x), 2)
                +pow((point1->y-point2->y),2)
                +pow((point1->z-point2->z),2));
}


float* CsScene3D::calculatePointAngle(CsPoint3D *point){

    float pointxrelcamera =  point->x - camera.nodalPoint.x;
    float pointyrelcamera = point->y - camera.nodalPoint.y;
    float pointzrelcamera = point->z - camera.nodalPoint.z;

    float pointinclination = atan(pointyrelcamera/pointzrelcamera);
    float pointazimut = atan(pointxrelcamera/pointzrelcamera);
    float ret[2] = {pointinclination, pointazimut};
    return ret;
}


int* CsScene3D::calcualtePoint(CsPoint3D *point){

    float dist = calculatePointDist(point);

    float* angels = calculatePointAngle(point);

    float pointxrelcamera =  point->x - camera.nodalPoint.x;
    float pointyrelcamera = point->y - camera.nodalPoint.y;
    float pointzrelcamera = point->z - camera.nodalPoint.z;

    QVector3D pointv = QVector3D(pointxrelcamera, pointyrelcamera, pointzrelcamera);

    QVector3D relpoint = camera.rot.inverted().rotatedVector(pointv);

    float flx =0;
    float fly = 0;
    if(relpoint.z()<0){


      switch(camera.curvRectOrt){
        case 1:
            flx = (imgw*camera.focallength*relpoint.x())/dist;

            fly = (imgw*camera.focallength*relpoint.y())/dist;
        break;
        case 2:

            flx = (imgw*camera.focallength*relpoint.x())/(-relpoint.z());

            fly = (imgw*camera.focallength*relpoint.y())/(-relpoint.z());
        break;
        case 3:

            flx = (relpoint.x());

            fly = (relpoint.y());
        break;
    }

    }

    int x = round(flx);
    int y = round(fly);

    int coords[3] =  { x, y, 0};

    return coords;

}


void CsScene3D::drawPoint(CsPoint3D *point){

    int* coords = calcualtePoint(point);

    int x = coords[0];
    int y = coords[1];

    float dist = calculatePointDist(point);

    point->pixels.clear();
    int rad = round(imgw/dist);
    for(int i = 0; i < rad; i++){
        for(int j = 0; j < rad; j++){
            setPixel(x+i, y+j, round(dist*(255.0/1000.0)));
            int cords[3] =  { x+i, y+j, 0};

            point->pixels.append(QGenericMatrix<3, 1, int>(cords));
        }
    }

}


void CsScene3D::calculateLine(CsLine3D *lin){

    lin->pixels.clear();

        int n = camera.planarRays.count();
        if(camera.curvRectOrt == 3){
            n = camera.parallelPlanarRays.count();
        }
        for(int i = 0; i < n ; i++){
            CsPoint3D intersection;
            if(camera.curvRectOrt == 3){
                intersection = camera.parallelPlanarRays.at(i).intersection(lin);
            } else {
                intersection = camera.planarRays.at(i).intersection(lin);
            }
            int* coords = calcualtePoint(&intersection);

            int xx = coords[0];
            int yy = coords[1];
            setPixel(xx, yy, 0);
            int coqrds[3] = {xx, yy, 0};
            lin->pixels.append(QGenericMatrix<3, 1, int>(coqrds));

        }
}


void CsScene3D::drawLine(CsLine3D *lin){

    calculateLine(lin);
}


