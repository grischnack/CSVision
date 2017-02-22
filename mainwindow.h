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

    void on_radioButtonCurvilinear_toggled(bool checked);

    void on_radioButtonRectilinear_toggled(bool checked);

    void on_radioButtonOrtographic_toggled(bool checked);

    void on_focalLengthSlider_valueChanged(int value);

    void on_rollLeftButtonCamera_clicked();

    void on_rollRightButtonCamera_clicked();

    void on_lineSliderx_valueChanged(int value);

    void on_lineSlidery_valueChanged(int value);

    void on_lineSliderz_valueChanged(int value);

    void on_lineSlidertheta_valueChanged(int value);

    void on_lineSliderphi_valueChanged(int value);

    void on_lineSliderpsi_valueChanged(int value);

    void on_lineSliderd_valueChanged(int value);

    void on_lineSliderl_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
