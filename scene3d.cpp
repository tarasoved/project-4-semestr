#include <QtGui>
#include <math.h>
#include "scene3d.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cmath>

#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>

struct CFace{
    int v1,v2,v3;
};

struct CVertex3{
    GLfloat x,y,z;
};

struct CColor3{
    GLfloat r,g,b;
};

int IndexSize;

CFace * StrMyIndexArray;
CVertex3 * StrMyVertexArray;
CColor3 * StrMyColorArray;

Scene3D::Scene3D(QWidget* parent) : QGLWidget(parent)
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::initializeGL()
{
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);

   my_getArrays();

   //getVertexArray();
   //getColorArray();
   //getIndexArray();

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
}

void Scene3D::resizeGL(int nWidth, int nHeight)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

   if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void Scene3D::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();
      break;

      case Qt::Key_Equal:
         scale_plus();
      break;

      case Qt::Key_Minus:
         scale_minus();
      break;

   case Qt::Key_Up:
      rotate_up();
   break;

   case Qt::Key_Down:
      rotate_down();
   break;

   case Qt::Key_Left:
     rotate_left();
   break;

   case Qt::Key_Right:
      rotate_right();
   break;

   case Qt::Key_S:
      translate_down();
   break;

   case Qt::Key_W:
      translate_up();
   break;
   }

   updateGL();
}

void Scene3D::scale_plus()
{
   nSca = nSca*1.1;
}

void Scene3D::scale_minus()
{
   nSca = nSca/1.1;
}

void Scene3D::rotate_up()
{
   xRot += 1.0;
}

void Scene3D::rotate_down()
{
   xRot -= 1.0;
}

void Scene3D::rotate_left()
{
   zRot += 1.0;
}

void Scene3D::rotate_right()
{
   zRot -= 1.0;
}

void Scene3D::translate_down()
{
   zTra -= 0.05;
}

void Scene3D::translate_up()
{
   zTra += 0.05;
}

void Scene3D::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glScalef(nSca, nSca, nSca);
   glTranslatef(0.0f, zTra, 0.0f);
   glRotatef(xRot, 1.0f, 0.0f, 0.0f);
   glRotatef(yRot, 0.0f, 1.0f, 0.0f);
   glRotatef(zRot, 0.0f, 0.0f, 1.0f);

   drawAxis();
   drawFigure();
}

void Scene3D::drawAxis()
{
   glLineWidth(3.0f);

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);
      glVertex3f( 1.0f,  0.0f,  0.0f);
      glVertex3f(-1.0f,  0.0f,  0.0f);
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}


void Scene3D::defaultScene()
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::my_getArrays()
{
    std::ifstream file ("../app2/database/pallas.txt", std::ifstream::in);
    if (!file)
            std::perror("ifstream");

    GLfloat R=0.01;

    if (!file)
    {
        std::cout << "file does not open" << std::endl;
    }

    std::string s;
    int a, b, n_, i;
    GLfloat n, max = 0, min = 1000, max_ = 0;
    file >> s;
    a = atoi(s.c_str());
    file >> s;
    b = atoi(s.c_str());

    StrMyIndexArray = new CFace[b];
    StrMyVertexArray = new CVertex3[a];
    StrMyColorArray = new CColor3[a];
    IndexSize = b;

    if (StrMyIndexArray == NULL){
        std::cout << "Could not allocate memory for StrMyIndexArray" << std::endl;
    }
    if (StrMyVertexArray == NULL){
        std::cout << "Could not allocate memory for StrMyVertexArray" << std::endl;
    }
    if (StrMyColorArray == NULL){
        std::cout << "Could not allocate memory for StrMyColorArray" << std::endl;
    }

    std::cout << "sizes: " << a << ' ' << b << std::endl;
    for(i = 0; i < a; i++){
        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n = atof(s.c_str());
        if(max < abs(n)) {
            max = abs(n);
        }
        StrMyVertexArray[i].x = n * R;

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n = atof(s.c_str());
        if(max < abs(n)) {
            max = abs(n);
        }
        StrMyVertexArray[i].y = n * R;

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n = atof(s.c_str());
        if(max < abs(n)) {
            max = abs(n);
        }
        StrMyVertexArray[i].z = n * R;


        n = sqrt(StrMyVertexArray[i].x *StrMyVertexArray[i].x + StrMyVertexArray[i].y *StrMyVertexArray[i].y + StrMyVertexArray[i].z *StrMyVertexArray[i].z);
        if(max_ < n) {
            max_ = n;
        }
        if (min > n){
            min = n;
        }
    }

    for(i = 0; i < b; i++) {
        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n_ = atoi(s.c_str());
        StrMyIndexArray[i].v1= n_ - 1;

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n_ = atoi(s.c_str());
        StrMyIndexArray[i].v2 = n_ - 1;

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n_ = atoi(s.c_str());
        StrMyIndexArray[i].v3 = n_ - 1;
    }

    R = 75/max;

    std::cout << max << ' ' << min << std::endl;
    for(i = 0; i < a; i++)
    {
        n = sqrt(StrMyVertexArray[i].x *StrMyVertexArray[i].x + StrMyVertexArray[i].y *StrMyVertexArray[i].y + StrMyVertexArray[i].z *StrMyVertexArray[i].z);
        n = (0.7f*(n - min) - 0.4f*(n-max_))/(max_ - min);
        StrMyColorArray[i].r=n;
        StrMyColorArray[i].g=n;
        StrMyColorArray[i].b=n;
        if ((n < 0.4f) || (n > 0.7f)){
            std::cout << n << std::endl;
        }

        StrMyVertexArray[i].x = StrMyVertexArray[i].x * R;
        StrMyVertexArray[i].y = StrMyVertexArray[i].y * R;
        StrMyVertexArray[i].z = StrMyVertexArray[i].z * R;
    }


    file.close();
}

void Scene3D::drawFigure()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, Textures[0]);

    glVertexPointer(3, GL_FLOAT, sizeof(CVertex3), StrMyVertexArray);
    glColorPointer(3, GL_FLOAT, sizeof(CVertex3), StrMyColorArray);

    glDrawElements(GL_TRIANGLES, 3 * IndexSize, GL_UNSIGNED_INT, StrMyIndexArray);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene3D::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL();
}
