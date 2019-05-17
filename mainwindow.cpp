#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene3d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Wido.setFocusPolicy (Qt::StrongFocus);
    //setCentralWidget(&Wido);
    QHBoxLayout *buttonsLayout = new QHBoxLayout ;
    buttonsLayout->addWidget(&Knopka);
    setLayout(buttonsLayout);



}

void MainWindow::help()
{

}
void MainWindow::Import_file()
{
   // Wido.fin.open("../app2/database/pallas.txt");
    //tetrahedralization(&in, &out, &behavior, &fin);
    //fin.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Knopka_clicked()
{
    printf("ok!!!!");
}

void MainWindow::on_Wido_resized()
{

}
