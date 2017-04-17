#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <csline2d.h>
#include "csscene3d.h"
#include <QQuaternion>

CsPoint3D orig = CsPoint3D(0, 0, 0);
QVector3D o = QVector3D(0,0,0);
CsLine3D lines3d[120] = {CsLine3D(o, 0, 300, orig)};
CsScene3D SCN3 = CsScene3D();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QImage img = QImage(SCN3.imgw  , SCN3.imgh, QImage::Format_RGB888);


    //for(int j = 0; j < 30; j++){
      //  for(int i = 0; i < 600; i++){
       //         points3d[(j*600)+i] = OzPoint3d(((i *20)%600),((i*20)/600)*20, j*20);
         //       ii++;

        //}
    //}

    for(int i = 0; i < SCN3.imgw; i++){
        for(int j = 0; j < SCN3.imgh; j++){
                img.setPixel(i, j, qRgba(255, 255, 255, 255));
        }
    }

    for(int i  = 0; i < 30; i++){
        CsPoint3D pp = CsPoint3D(i*20, 0, 300);
        CsPoint3D pr = CsPoint3D(300, 0, i*20);
        QVector3D qp = QVector3D(1, 0, 0);
        QVector3D qr = QVector3D(0, 0, 1);
        lines3d[i] = CsLine3D(qp,0, 600000, pr);
        lines3d[30+i] = CsLine3D(qr, 0, 600000, pp);
    }
    for(int i  = 0; i < 30; i++){
        CsPoint3D pp = CsPoint3D( 0, i*20, 300);
        CsPoint3D pr = CsPoint3D( 0, 300, i*20);
        QVector3D qp = QVector3D(0, 1, 0);
        QVector3D qr = QVector3D(0, 0, 1);
        lines3d[60 + i] = CsLine3D(qp,0, 600000, pr);
        lines3d[90+i] = CsLine3D(qr, 0, 600000, pp);
    }

    ui->setupUi(this);

    ui->notLabel->setPixmap(QPixmap::fromImage(img));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refresh(){
    QImage img = QImage(SCN3.imgw  , SCN3.imgh, QImage::Format_RGB888);

    int iii = 0;
    for(int i = 0; i < SCN3.imgw; i++){
        for(int j = 0; j < SCN3.imgh; j++){
            if(SCN3.pixels[i][j]==0){

                img.setPixel(i, j, qRgba(0, 0, 0, 0));

            }else if(SCN3.pixels[i][j]==255){
                img.setPixel(i, j, qRgba(255, 255, 255, 255));
            } else {

                img.setPixel(i, j, qRgba(255, 255,255, 255 - SCN3.pixels[i][j]));

            }
        }
    }

    qApp->processEvents();

    ui->notLabel->setPixmap(QPixmap::fromImage(img));


}

CsPoint3D ppp = CsPoint3D(0, 0, 0);
QVector3D yy = QVector3D( 0,1,0);
CsLine3D longiy = CsLine3D(yy,0,30000, ppp);


void MainWindow::on_initButton_clicked()
{
    for(int i = 0; i < 120; i++){

        SCN3.putLine3d(&lines3d[i]);
       // SCN3.putPoint(&ponts[i]);
    }
    SCN3.putLine3d(&longiy);
    refresh();

}

void MainWindow::on_upButtonCamera_clicked()
{
    QQuaternion fact;
    QQuaternion fwdDir = fact.fromDirection(QVector3D(0, -sin(M_PI/20), cos(M_PI/20)), QVector3D(0,0,0));
    SCN3.camera.rotation(fwdDir);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_downButtonCamera_clicked()
{
    QQuaternion fact;
    QQuaternion fwdDir = fact.fromDirection(QVector3D(0, sin(M_PI/20), cos(M_PI/20)), QVector3D(0,0,0));
    SCN3.camera.rotation(fwdDir);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_leftButtonCamera_clicked()
{
    QQuaternion fact;
    QQuaternion fwdDir = fact.fromDirection(QVector3D( sin(M_PI/20),0, cos(M_PI/20)),QVector3D(0,0,0));
    SCN3.camera.rotation(fwdDir);

    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_rightButtonCamera_clicked()
{

    QQuaternion fact;
    QQuaternion fwdDir = fact.fromDirection(QVector3D( -sin(M_PI/20),0, cos(M_PI/20)),QVector3D(0,0,0));
    SCN3.camera.rotation( fwdDir);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_forwardButtonCamera_clicked()
{

    SCN3.camera.goForward(1);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_backwardbuttonCamera_clicked()
{

    SCN3.camera.goBackward(1);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_radioButtonCurvilinear_toggled(bool checked)
{
    if(checked){
        SCN3.camera.curvRectOrt = 1;
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_radioButtonRectilinear_toggled(bool checked)
{
    if(checked){
        SCN3.camera.curvRectOrt = 2;
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_radioButtonOrtographic_toggled(bool checked)
{
    if(checked){
        SCN3.camera.curvRectOrt = 3;
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_focalLengthSlider_valueChanged(int value)
{
    SCN3.camera.setFocalLength(value*0.01);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_rollLeftButtonCamera_clicked()
{
    QQuaternion fact;
    QQuaternion upDir = fact.fromDirection(QVector3D(0,0,1),QVector3D( -sin(M_PI/20), cos(M_PI/20), 0));
    SCN3.camera.rotation(upDir);

    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_rollRightButtonCamera_clicked()
{

    QQuaternion fact;
    QQuaternion upDir = fact.fromDirection(QVector3D(0,0,1),QVector3D( sin(M_PI/20), cos(M_PI/20), 0));
    SCN3.camera.rotation( upDir);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_lineSliderx_valueChanged(int value)
{

    longiy.center.x = value*10;
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_lineSlidery_valueChanged(int value)
{

    longiy.center.y = value*10;
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_lineSliderz_valueChanged(int value)
{

    longiy.center.z = value*10;
    SCN3.redrawAll();
    refresh();
}

int pitchdiff = 0;
void MainWindow::on_lineSlidertheta_valueChanged(int value)
{
    longiy.pitch((value - pitchdiff)*M_PI*0.01);
    pitchdiff = value;
    SCN3.redrawAll();
    refresh();
}

int yawdiff = 0;
void MainWindow::on_lineSliderphi_valueChanged(int value)
{
    longiy.yaw((value - yawdiff)*M_PI*0.01);
    yawdiff = value;
    SCN3.redrawAll();
    refresh();
}

int rolldiff = 0;
void MainWindow::on_lineSliderpsi_valueChanged(int value)
{
    longiy.roll((value - rolldiff)*M_PI*0.01);
    rolldiff =value;
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_lineSliderd_valueChanged(int value)
{
    longiy.distance = value*10;
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_lineSliderl_valueChanged(int value)
{

    longiy.length = value*10;
    SCN3.redrawAll();
    refresh();
}

int orbitincdiff = 0;
void MainWindow::on_verticalSlider_valueChanged(int value)
{

    QVector3D camdir = QVector3D(0,0,-1);
    camdir = SCN3.camera.rot.rotatedVector(camdir);

    float angle = (value-orbitincdiff)*0.02*M_PI;
    orbitincdiff = value;

    QQuaternion fwdDir = QQuaternion::fromDirection(QVector3D(0, sin(angle), cos(angle)), QVector3D(0,0,0));
    SCN3.camera.rotation(fwdDir);


    CsLine3D camline = CsLine3D(camdir, 0,INFINITY, SCN3.camera.nodalPoint);
    CsShape2D inf = CsShape2D();
    CsPlane3D ground = CsPlane3D(QVector3D(0,1,0), 0, inf, orig);
    CsPoint3D groundpoint = ground.intersection(&camline);
    QVector3D nodalrelground = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z)
            - QVector3D(SCN3.camera.nodalPoint.x, SCN3.camera.nodalPoint.y, SCN3.camera.nodalPoint.z);
    qDebug() << "gp" << groundpoint.x << groundpoint.y << groundpoint.z;

    nodalrelground = fwdDir.rotatedVector(-nodalrelground);


    QVector3D nodalv = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z) + nodalrelground;
    CsPoint3D newNodal = CsPoint3D(nodalv.x(), nodalv.y(), nodalv.z());
    qDebug() << "oldd" << SCN3.camera.nodalPoint.x << SCN3.camera.nodalPoint.y << SCN3.camera.nodalPoint.z;
    qDebug() << "neww" << newNodal.x << newNodal.y  << newNodal.z;
    SCN3.camera.nodalPoint = newNodal;
    SCN3.camera.actualizeRays();
    SCN3.redrawAll();
    refresh();
}


int orbitazdiff = 0;
void MainWindow::on_horizontalSlider_valueChanged(int value)
{

   // float angle = (value-orbitazdiff)*0.02*M_PI;
    float angle = value*0.02*M_PI;
    float upangle = (value*0.02*M_PI)/100;
    orbitazdiff = value;


   // QVector3D axis = QVector3D(0,1,0);
   // QQuaternion axang = QQuaternion::fromAxisAndAngle(axis, angle*(180/M_PI));
   // SCN3.camera.rotation(axang);

    //QQuaternion fwdDir = QQuaternion::fromDirection(QVector3D( sin(angle), 0, cos(angle)), QVector3D( 0,0,0));
    //SCN3.camera.rotation(fwdDir);
    //QQuaternion upDir = QQuaternion::fromDirection( QVector3D(0,0,1), QVector3D( -sin(upangle), cos(upangle),0));
    //SCN3.camera.rotation(upDir);


    QVector3D camdir = QVector3D(0,0,-1);
    camdir = SCN3.camera.rot.rotatedVector(camdir);




    CsLine3D camline = CsLine3D(camdir, 0,INFINITY, SCN3.camera.nodalPoint);
    CsShape2D inf = CsShape2D();
    CsPlane3D ground = CsPlane3D(QVector3D(0,1,0), 0, inf, orig);
    CsPoint3D groundpoint =  CsPoint3D(0,0,0); //ground.intersection(&camline);

    QVector3D nodalrelground = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z)
            - QVector3D(SCN3.camera.nodalPoint.x, SCN3.camera.nodalPoint.y, SCN3.camera.nodalPoint.z);
    nodalrelground = -nodalrelground;
    qDebug() << "gp" << groundpoint.x << groundpoint.y << groundpoint.z;

//TODO first change nodalrelground to spherical then increment.
    //Then create quaternion from nodalrelground (not sure about roll) and feed it to camera.
    //TODO Update: disregard original cartesian coordinates and calculate spherical coordinates whilst reserving the ground point
    // also implement camera.unroll function
    //TODO Update 2: dont use sphericals. Constuct Quaternion from axis and angle and use it on nodalrelground
    //and its inverse in camera

    CsPoint3D nodalrelgroundpoint = CsPoint3D(nodalrelground.x(), nodalrelground.y(), nodalrelground.z());
    qDebug() << "spherics" << nodalrelground << nodalrelgroundpoint.dist << nodalrelgroundpoint.inclination << nodalrelgroundpoint.azimut << angle ;
    //CsPoint3D nodalrelgroundincremented = CsPoint3D(true, nodalrelgroundpoint.dist, nodalrelgroundpoint.inclination, nodalrelgroundpoint.azimut+angle); //az+angle
    CsPoint3D nodalrelgroundincremented = CsPoint3D(true, nodalrelgroundpoint.dist, M_PI/2-angle, 0);
    QVector3D nodalrelgroundincrementedv = QVector3D(nodalrelgroundincremented.x, nodalrelgroundincremented.y, nodalrelgroundincremented.z);
    QVector3D nodalrelgroundcrossp = QVector3D::crossProduct( nodalrelgroundincrementedv, nodalrelground);

    qDebug() << "nodalrelg" << nodalrelground << nodalrelgroundincrementedv;

    QQuaternion lookatdir = QQuaternion(sqrt(pow(nodalrelgroundincrementedv.length(),2)*pow(nodalrelground.length(),2)) + QVector3D::dotProduct( nodalrelgroundincrementedv, nodalrelground  ), -nodalrelgroundcrossp);
    lookatdir = lookatdir.normalized();
    QVector3D nix = QVector3D(0,0,1);
    nix = lookatdir.rotatedVector(nix);
    qDebug() << "quater" << nix;
    SCN3.camera.rotation(lookatdir);


    nodalrelground = nodalrelgroundincrementedv;
    //------------------TODO debug
    //nodalrelground = axang.rotatedVector(-nodalrelground);
   // nodalrelground = upDir.inverted().rotatedVector(nodalrelground);

    QVector3D nodalv = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z) + nodalrelground;
    CsPoint3D newNodal = CsPoint3D(nodalv.x(), nodalv.y(), nodalv.z());
    qDebug() << "olddnodal" << SCN3.camera.nodalPoint.x << SCN3.camera.nodalPoint.y << SCN3.camera.nodalPoint.z;
    qDebug() << "newwnodal" << newNodal.x << newNodal.y  << newNodal.z;
    SCN3.camera.nodalPoint = newNodal;
    SCN3.camera.actualizeRays();
    SCN3.redrawAll();
    refresh();
}


QVector3D upax = QVector3D(0,1,0);
CsPoint3D groundpoint = CsPoint3D(0,0,0);

void MainWindow::on_randqButton_clicked()
{

    float scalar = ((float)rand());
    float x = ((float)rand());
    float y = ((float)rand());
    float z = ((float)rand());
   // QQuaternion random = QQuaternion(scalar, x, y, z);
    //QQuaternion random = QQuaternion::fromDirection(QVector3D(sin(0.1),0, cos(0.1)), QVector3D(0,0,0));

    QQuaternion random = QQuaternion::fromDirection(QVector3D( sin(0.1),0, cos(0.1)), QVector3D(0,0,0));
    random = random.normalized();
    QVector3D nix = QVector3D(0,0,-1);


    QVector3D camdir = QVector3D(0,0,-1);
    camdir = SCN3.camera.rot.rotatedVector(camdir);
    CsLine3D camline = CsLine3D(camdir, 0,INFINITY, SCN3.camera.nodalPoint);
    CsShape2D inf = CsShape2D();
    CsPlane3D ground = CsPlane3D(QVector3D(0,1,0), 0, inf, orig);

    CsPoint3D tmpgroundpoint =  ground.intersection(&camline);
    //if(abs(tmpgroundpoint.x - groundpoint.x) > 1.0 || abs(tmpgroundpoint.y - groundpoint.y) > 1.0 || abs(tmpgroundpoint.z-groundpoint.z) > 1.0){
        groundpoint = tmpgroundpoint;


        SCN3.camera.unRoll();
        upax = SCN3.camera.rot.conjugated().rotatedVector(QVector3D(0,1,0));

    //}

    QVector3D nodalrelground = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z)
            - QVector3D(SCN3.camera.nodalPoint.x, SCN3.camera.nodalPoint.y, SCN3.camera.nodalPoint.z);


    nodalrelground = random.rotatedVector(-nodalrelground);

    QVector3D nodalv = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z) + nodalrelground;
    CsPoint3D newNodal = CsPoint3D(nodalv.x(), nodalv.y(), nodalv.z());

    SCN3.camera.nodalPoint = newNodal;

    QQuaternion randomm = QQuaternion::fromAxisAndAngle(upax,(180/M_PI)*0.1 );



    SCN3.camera.rotation(randomm);
    nix = SCN3.camera.rot.rotatedVector(nix);
    SCN3.camera.actualizeRays();
    SCN3.redrawAll();
    refresh();
    //qDebug() << random;
    //qDebug() << SCN3.camera.rot;
    //qDebug() << nix;

    qDebug() << "gp" << groundpoint.x << groundpoint.y << groundpoint.z;


}


void MainWindow::on_unrollButton_clicked()
{
    SCN3.camera.unRoll();
    SCN3.redrawAll();
    refresh();
}


QVector3D rax = QVector3D(1,0,0);

void MainWindow::on_orbitvButton_clicked()
{
    QQuaternion random = QQuaternion::fromDirection(QVector3D(0, sin(0.1), cos(0.1)), QVector3D(0,0,0));
    random = random.normalized();

    QVector3D camdir = QVector3D(0,0,-1);
    camdir = SCN3.camera.rot.rotatedVector(camdir);
    CsLine3D camline = CsLine3D(camdir, 0,INFINITY, SCN3.camera.nodalPoint);
    CsShape2D inf = CsShape2D();
    CsPlane3D ground = CsPlane3D(QVector3D(0,1,0), 0, inf, orig);

    CsPoint3D tmpgroundpoint =  ground.intersection(&camline);

    groundpoint = tmpgroundpoint;

    SCN3.camera.unRoll();
    rax = SCN3.camera.rot.rotatedVector(QVector3D(1,0,0));


    QVector3D nodalrelground = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z)
            - QVector3D(SCN3.camera.nodalPoint.x, SCN3.camera.nodalPoint.y, SCN3.camera.nodalPoint.z);
    random =  QQuaternion::fromAxisAndAngle(rax,-(180/M_PI)*0.1 );
    nodalrelground = random.rotatedVector(-nodalrelground);


    QVector3D nodalv = QVector3D(groundpoint.x, groundpoint.y, groundpoint.z) + nodalrelground;
    CsPoint3D newNodal = CsPoint3D(nodalv.x(), nodalv.y(), nodalv.z());
    SCN3.camera.nodalPoint = newNodal;


    QQuaternion randomm = QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),-(180/M_PI)*0.1 );



    SCN3.camera.rotation(randomm);
    SCN3.camera.actualizeRays();
    SCN3.redrawAll();
    refresh();

    qDebug() << "gp" << groundpoint.x << groundpoint.y << groundpoint.z;

}

void MainWindow::on_lookatButton_clicked()
{

}
