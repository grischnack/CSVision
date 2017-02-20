#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <csline2d.h>
#include "csscene3d.h"
#include <QQuaternion>

CsPoint3D orig = CsPoint3D(0, 0, 0);
QVector3D o = QVector3D(0,0,0);
CsLine3D lines3d[60] = {CsLine3D(o, 0, 300, orig)};
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
        lines3d[i] = CsLine3D(qp,0, 600, pr);
        lines3d[30+i] = CsLine3D(qr, 0, 600, pp);
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

                img.setPixel(i, j, qRgba(0, 255,0, 255 - SCN3.pixels[i][j]));

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
    for(int i = 0; i < 60; i++){

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
