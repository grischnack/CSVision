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

    ui->label->setPixmap(QPixmap::fromImage(img));


}

