#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene3d.h"

#include <unistd.h>

QString xxx, yyy, zzz;
#include "grav_calc.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Wido->setFocusPolicy (Qt::ClickFocus);
    ui->Wido->flag_arr = 0;
    ui->Wido->flag_pnt = 0;
    //setCentralWidget(&Wido);
    QHBoxLayout *buttonsLayout = new QHBoxLayout ;
    buttonsLayout->addWidget(&Knopka);
    setLayout(buttonsLayout);

}

void MainWindow::help()
{

}


MainWindow::~MainWindow()
{
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
    QString path = QFileDialog::getOpenFileName(this,
    tr("Open Address Book"), "",
    tr("txt (*.txt);;All Files (*)"));
    Wido.my_getArrays(path.toStdString());
    std::cout<<"1111";
}

void MainWindow::on_Wido_resized()
{

}
