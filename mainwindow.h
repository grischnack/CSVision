#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refresh();

private slots:
    void on_initButton_clicked();

    void on_upButtonCamera_clicked();

    void on_downButtonCamera_clicked();

    void on_leftButtonCamera_clicked();

    void on_rightButtonCamera_clicked();

    void on_forwardButtonCamera_clicked();

    void on_backwardbuttonCamera_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
