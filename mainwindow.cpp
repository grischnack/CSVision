#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <csline2d.h>
#include "csscene3d.h"
#include <QQuaternion>

CsPoint3D orig = CsPoint3D(0, 0, 0);
QVector3D o = QVector3D(0,0,0);
CsLine3D lines3d[120] = {CsLine3D(QQuaternion(), 0, 300, orig)};
CsLine3D raystest[100] = {CsLine3D(QQuaternion(), 0, 300, orig)};
QQuaternion raysq[100] = {QQuaternion()};
CsLine3D raystest2[100] = {CsLine3D(QQuaternion(), 0, 300, orig)};
QQuaternion raysq2[100] = {QQuaternion()};
CsPlane3D raystest3horiz[50] = {CsPlane3D()};
CsPlane3D raystest3vertic[50] = {CsPlane3D()};
QQuaternion raysq3[100] = {QQuaternion()};
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
        QQuaternion qpq = QQuaternion::fromDirection(qp, QVector3D(0,0,0));
        QVector3D qr = QVector3D(0, 0, 1);
        QQuaternion qrq = QQuaternion::fromDirection(qr, QVector3D(0,0,0));
        lines3d[i] = CsLine3D(qpq,0, 600000, pr);
        lines3d[30+i] = CsLine3D(qrq, 0, 600000, pp);
    }
    for(int i  = 0; i < 30; i++){
        CsPoint3D pp = CsPoint3D( 0, i*20, 300);
        CsPoint3D pr = CsPoint3D( 0, 300, i*20);
        QVector3D qp = QVector3D(0, 1, 0);
        QQuaternion qpq = QQuaternion::fromDirection(qp, QVector3D(0,0,0));
        QVector3D qr = QVector3D(0, 0, 1);
        QQuaternion qrq = QQuaternion::fromDirection(qr, QVector3D(0,0,0));
        lines3d[60 + i] = CsLine3D(qpq,0, 600000, pr);
        lines3d[90+i] = CsLine3D(qrq, 0, 600000, pp);
    }

    CsPoint3D raytestnod = CsPoint3D(1000, 1000, -1000);
    for(int i = -5; i < 5; i++){
        for(int j = -5; j < 5; j++){

            QQuaternion tmpq = QQuaternion::fromDirection(QVector3D(0,0,1),QVector3D( i*10, j*10, 0).normalized());
            raystest[((i+5)*10)+j+5] = CsLine3D(tmpq, sqrt(pow((i*10), 2)+pow((j*10), 2)), 300, raytestnod);

            raysq[((i+5)*10)+j+5] = tmpq.conjugated();

        }
    }

    CsPoint3D raytestnod2 = CsPoint3D(1000, 1000, 700);
    for(int i = -5 ; i < 5; i++){
        for(int j = -5; j < 5; j++){

            QVector3D rayvec = QVector3D(j, i, 10);
            rayvec = rayvec.normalized();
            QQuaternion rayq = QQuaternion::fromDirection(rayvec, QVector3D(0,0,0));
            CsLine3D ray = CsLine3D(rayq, 0, 300, raytestnod2);

            raystest2[((i+5)*10)+j+5] = ray;
            raysq2[((i+5)*10)+j+5] = rayq.conjugated();
        }
    }

    CsPoint3D raytestnod3 = CsPoint3D(1000,500,500);

    for(int i = 0; i < 50; i++){

        QVector3D norm = QVector3D(0, 50, i-(50/2));
        norm = norm.normalized();
        CsShape2D infinitshape;
        int nuls[4] = {0,0,0,0};

        CsPoint3D origo = CsPoint3D(0,0,0);
        CsPlane3D planarRay = CsPlane3D(norm, 0, infinitshape, raytestnod3);

        raystest3horiz[i] = planarRay;



        norm = QVector3D(50,  0,  i-(50/2));
        norm = norm.normalized();
        planarRay = CsPlane3D(norm, 0, infinitshape, raytestnod3);
        raystest3vertic[i] = planarRay;

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

                int t = SCN3.pixels[i][j];
                int r, g, b;
                QColor::fromHsv(t,255,255).toRgb().getRgb(&r, &g,&b);
//                img.setPixel(i, j, qRgba(255, 255,255, 255 - SCN3.pixels[i][j]));

                img.setPixel(i,j, qRgba(r,g,b,255));

            }
        }
    }

    qApp->processEvents();

    ui->notLabel->setPixmap(QPixmap::fromImage(img));


}

CsPoint3D ppp = CsPoint3D(0, 0, 0);
QVector3D yy = QVector3D( 0,1,0);
QQuaternion yyq = QQuaternion::fromDirection(yy, QVector3D(0,0,0));
CsLine3D longiy = CsLine3D(yyq,0,30000, ppp);
CsPlane3D pp = CsPlane3D(QVector3D(1,0,0), 0, CsShape2D(), CsPoint3D(500,100,0));


void MainWindow::on_initButton_clicked()
{
    for(int i = 0; i < 120; i++){

        SCN3.putLine3d(&lines3d[i]);
       // SCN3.putPoint(&ponts[i]);
    }
    for(int i = 0; i < 100; i++){
        //SCN3.putLine3d(&raystest[i]);
        //SCN3.putLine3d(&raystest2[i]);
    }
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            CsLine3D lini = raystest3horiz[i].intersection(&raystest3vertic[j]);
            lini.length = 200.0;
            QVector3D vvv = lini.rot.rotatedVector(QVector3D(0,0,1));

            qDebug() << "liniii: "  << vvv << lini.center.x << lini.center.y << lini.center.z;
            SCN3.putLine3d(&lini);
        }
    }
    SCN3.putLine3d(&longiy);
    SCN3.putPlane(&pp);


    refresh();


    srand(time(0));

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

    SCN3.camera.goForward(20);
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_backwardbuttonCamera_clicked()
{

    SCN3.camera.goBackward(20);
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
    //longiy.pitch((value - pitchdiff)*M_PI*0.01);
    QQuaternion upDir = QQuaternion::fromDirection(QVector3D(0,0,1),QVector3D( -sin(M_PI/20), cos(M_PI/20), 0));
    longiy.rotation(upDir);
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

float orbitincdiff = 0;
void MainWindow::on_verticalSlider_valueChanged(int value)
{

    float radv = (float)value*(M_PI/50.0);

    SCN3.camera.orbit(500.0, radv-orbitincdiff,0);
    SCN3.redrawAll();
    refresh();
    orbitincdiff = radv;
}


float orbitazdiff = 0;
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float radv = (float)value*(M_PI/50.0);
    SCN3.camera.orbit(500.0, 0, radv-orbitazdiff);
    SCN3.redrawAll();
    refresh();
    orbitazdiff = radv;
}


void MainWindow::on_randqButton_clicked()
{


}


void MainWindow::on_unrollButton_clicked()
{
    SCN3.camera.unRoll();
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_orbitvButton_clicked()
{
}

void MainWindow::on_lookatButton_clicked()
{

    float scalar = ((float)rand());
    float x = (float)(rand()%1000);
    float y = (float)(rand()%1000);
    float z = (float)(rand()%1000);
    CsPoint3D randp = CsPoint3D(x,y,z);
    SCN3.camera.lookAt(randp);
    SCN3.camera.actualizeRays();
    SCN3.redrawAll();
    refresh();
    qDebug() << x << y << z;
}

void MainWindow::on_pushButton_clicked()
{
    QQuaternion fwdDir;
    QQuaternion fwdDir2;

    for(int i = 0; i < 100; i++){
        fwdDir = QQuaternion::fromAxisAndAngle(raysq[i].rotatedVector(QVector3D(1,0,0)),10.0);
        raystest[i].rotation(fwdDir);

        fwdDir2 = QQuaternion::fromAxisAndAngle(raysq2[i].rotatedVector(QVector3D(1,0,0)), 10.0);
        raystest2[i].rotation(fwdDir2);
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_pushButton_2_clicked()
{
    QQuaternion fwdDir;
    QQuaternion fwdDir2;


    for(int i = 0; i < 100; i++){
        fwdDir = QQuaternion::fromAxisAndAngle(raysq[i].rotatedVector(QVector3D(1,0,0)),-10.0);
        raystest[i].rotation(fwdDir);

        fwdDir2 = QQuaternion::fromAxisAndAngle(raysq2[i].rotatedVector(QVector3D(1,0,0)), -10.0);
        raystest2[i].rotation(fwdDir2);
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_pushButton_3_clicked()
{
    QQuaternion fwdDir;
    QQuaternion fwdDir2;
    for(int i = 0; i < 100; i++){
        fwdDir = QQuaternion::fromAxisAndAngle(raysq[i].rotatedVector(QVector3D(0,1,0)),10.0);
        raystest[i].rotation(fwdDir);

        fwdDir2 = QQuaternion::fromAxisAndAngle(raysq2[i].rotatedVector(QVector3D(0,1,0)),10.0);
        raystest2[i].rotation(fwdDir2);
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_pushButton_4_clicked()
{

    QQuaternion fwdDir;

    QQuaternion fwdDir2;
    for(int i = 0; i < 100; i++){
        fwdDir = QQuaternion::fromAxisAndAngle(raysq[i].rotatedVector(QVector3D(0,1,0)),-10.0);
        raystest[i].rotation(fwdDir);

        fwdDir2 = QQuaternion::fromAxisAndAngle(raysq2[i].rotatedVector(QVector3D(0,1,0)),-10.0);
        raystest2[i].rotation(fwdDir2);
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_pushButton_5_clicked()
{
    QQuaternion upDir;
    QQuaternion upDir2;
    for(int i = 0; i < 100; i++){
        upDir = QQuaternion::fromAxisAndAngle(raysq[i].rotatedVector(QVector3D(0,0,1)),10.0);
        raystest[i].rotation(upDir);

        upDir2 = QQuaternion::fromAxisAndAngle(raysq2[i].rotatedVector(QVector3D(0,0,1)),10.0);
        raystest2[i].rotation(upDir2);

    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_pushButton_6_clicked()
{
    QQuaternion upDir;
    QQuaternion upDir2;
    for(int i = 0; i < 100; i++){
        upDir = QQuaternion::fromAxisAndAngle(raysq[i].rotatedVector(QVector3D(0,0,1)),-10.0);
        raystest[i].rotation(upDir);

        upDir2 = QQuaternion::fromAxisAndAngle(raysq2[i].rotatedVector(QVector3D(0,0,1)),-10.0);
        raystest2[i].rotation(upDir2);
    }
    SCN3.redrawAll();
    refresh();
}

void MainWindow::on_pushButton_7_clicked()
{
    CsPlane3D p1 = CsPlane3D(QVector3D(1,0,0), 100, CsShape2D(), CsPoint3D(0,0,0));
    CsPlane3D p2 = CsPlane3D(QVector3D(0,1,0),  100, CsShape2D(), CsPoint3D(100,100,100));
    CsLine3D ll = p1.intersection(&p2);
    QVector3D camline = QVector3D(0,0,-1);
    QVector3D camupline = QVector3D(0,1,0);
    camline = ll.rot.rotatedVector(camline);
    camupline = ll.rot.rotatedVector(camupline);
    qDebug() << "eleree" << camline << ll.distance;
    qDebug() << "feleee" << camupline;


}
