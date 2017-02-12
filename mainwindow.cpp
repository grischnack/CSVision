#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <csline2d.h>
#include "csscene3d.h"
#include <QQuaternion>

OzLine3d lines3d[60] = {OzLine3d(0, 0, 0, 0, 300, orig)};
OzScene3d SCN3 = OzScene3d(112);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QImage img = QImage(SCN3.imgw  , SCN3.imgh, QImage::Format_RGB888);

    for(int i = 0; i < SCN3.imgw; i++){
        for(int j = 0; j < SCN3.imgh; j++){
                img.setPixel(i, j, qRgba(255, 255, 255, 255));
        }
    }

    for(int i  = 0; i < 30; i++){
        CsPoint3d pp = CsPoint3d(i*20, 0, 300);
        CsPoint3d pr = CsPoint3d(300, 0, i*20);
        QVector3D qp = QVector3D(1, 0, 0);
        QVector3D qr = QVector3D(0, 0, 1);
        lines3d[i] = CsLine3d(qp,0, 600, pr);
        lines3d[30+i] = CsLine3d(qr, 0, 600, pp);
    }

    ui->setupUi(this);

    ui->notLabel->setPixmap(QPixmap::fromImage(img));

}

MainWindow::~MainWindow()
{
    delete ui;
}
