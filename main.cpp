#include <QApplication>
#include "scene3d.h"
#include "mainwindow.h"


int main(int argc, char** argv)
{
   QApplication app(argc, argv);

   MainWindow s1;
   s1.Wido.setWindowTitle("Asteroid");
   s1.Wido.resize(800, 800);
   s1.show();

   //scenel.getfile();

   return app.exec();
}

