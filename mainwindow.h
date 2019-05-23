#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include "scene3d.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Scene3D Wido;
    QMenuBar menuBar;
    QMenu menuFile;
    QMenu menuHelp;
    QPushButton Knopka;

private slots:
    void on_Knopka_clicked();
    void on_Import_file_triggered();


private:
    Ui::MainWindow *ui;
    void Import_file();
    void help();
    void free_main_window();

};

#endif // MAINWINDOW_H
