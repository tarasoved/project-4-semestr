#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene3d.h"
#include <unistd.h>
#include <stdlib.h>
#include <QFileDialog>
#include <QString>

#include <fstream>
#include <experimental/filesystem>
#include <QTextBrowser>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <experimental/filesystem>
#include <iostream>

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
    ui->Wido->free_scene3D();
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
<<<<<<< HEAD
    ui->Wido->my_getArrays(path.toStdString());
    ui->Wido->update();
    path.clear();
=======
    std::cout << "asteroid path is " << path.toStdString() << '\n';
    if (path != NULL) {
        ui->Wido->my_getArrays(path.toStdString());
        ui->Wido->update();
    }
>>>>>>> 53986e8689438286a833cdaf4299c80c17ab60b6
}

void MainWindow::free_main_window()
{
  ui->Wido->free_scene3D();
}
#include <stdio.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>

std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}


void MainWindow::on_help_triggered()
{
<<<<<<< HEAD

}
=======
    std::string str;
    str = GetCurrentWorkingDir();
   str = str.substr(0, str.size() - 34);

   str = "firefox " + str + "asteroid-4-sem/html/index.html";
   system(str.c_str());
   }
>>>>>>> 53986e8689438286a833cdaf4299c80c17ab60b6
