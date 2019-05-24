#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene3d.h"
#include <unistd.h>
#include <stdlib.h>
#include <QFileDialog>
#include <QString>

static QString xxx, yyy, zzz;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Wido->setFocusPolicy (Qt::ClickFocus);
    ui->Wido->flag_arr = 0;
    ui->Wido->flag_pnt = 0;
  }

MainWindow::~MainWindow()
{
    //ui->Wido->free_scene3D();
    delete ui;
}

void MainWindow::on_Knopka_clicked()
{
    xxx = ui->lineEdit_X->text();
    yyy = ui->lineEdit_Y->text();
    zzz = ui->lineEdit_Z->text();
    ui->Wido->p[0] = xxx.toDouble();
    ui->Wido->p[1] = yyy.toDouble();
    ui->Wido->p[2] = zzz.toDouble();
    ui->Wido->flag_arr = 1;
    ui->Wido->flag_pnt = 1;
    ui->Wido->update();
    ui->Wido->paintGL();
    ui->lineEdit_A->setText('(' + QString::number(ui->Wido->v[0]) + "; "
                                + QString::number(ui->Wido->v[1]) + "; "
                                + QString::number(ui->Wido->v[2]) + ')');
}

void MainWindow::on_Import_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open asteroid"), "", tr("txt (*.txt);;All Files (*)"));
    ui->Wido->my_getArrays(path.toStdString());
    ui->Wido->update();
}

void MainWindow::free_main_window()
{
  ui->Wido->free_scene3D();
}


void MainWindow::on_help_triggered()
{
   }
