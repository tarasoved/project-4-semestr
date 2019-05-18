#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene3d.h"
#include "grav_calc.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Wido.setFocusPolicy (Qt::ClickFocus);


}

void MainWindow::help()
{

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Import_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,
    tr("Open Address Book"), "",
    tr("txt (*.txt);;All Files (*)"));
    Wido.my_getArrays(path.toStdString());
    std::cout<<"1111";
}

