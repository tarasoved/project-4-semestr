#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include "scene3d.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Scene3D Wido;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
