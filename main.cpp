#include <QApplication>
#include "mainwindow.h"


int main(int argc, char** argv)
{
   QApplication app(argc, argv);
   MainWindow s1;
   s1.resize(800, 800);
   s1.setWindowTitle("Asteroid-4-sem");
   s1.show();

   return app.exec();
}

