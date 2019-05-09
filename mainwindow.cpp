#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene3d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(&Wido);
    Wido.setFocusPolicy (Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}
