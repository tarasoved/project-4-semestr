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

#include "tetgen.h"
#include "grav_calc.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

struct CFace{
     int v1,v2,v3;
};

/*!
    \brief Vertex of triangles

    Vertex of triangles for asteroid's triangulation
*/
struct CVertex3{
    GLfloat x,y,z;
};

/*!
    \brief Color of triangles

    Color of triangles for asteroid's triangulation
*/
struct CColor3{
    GLfloat r,g,b;
};

static unsigned long IndexSize; //!< Size of index

static CFace * StrMyIndexArray; //!< Array of all indexes (?)
static CVertex3 * StrMyVertexArray; //!< Array of all vertices
static CColor3 * StrMyColorArray;//!< Array of all colors


Scene3D::Scene3D(QWidget* parent) : QOpenGLWidget(parent)
{
   zTra=0; xRot=-90; yRot=0; zRot=0; nSca=1; xTra=0;
}

//!\brief Initialization of GL
void Scene3D::initializeGL()
{
   initializeOpenGLFunctions();
   glClearColor(1.0,1.0,1.0,1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
}

/*!
    \brief Resize of window and GLWidget

    GLWidhet is resizing here
*/

void Scene3D::resizeGL(int nWidth, int nHeight)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   double ratio= static_cast<double>(nHeight)/static_cast<double>(nWidth);

   if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

   glViewport(0, 0, static_cast<GLint>(nWidth), static_cast<GLint>(nHeight));
}

/*!
    \brief Reaction when some key is pressed

    Switch of reactions for some key pressed.
    Functions controling by keyboard are described later.
    \param[in] pe PressEvent - when one of keys is pressed
*/

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

   case Qt::Key_A:
      translate_left();
   break;

   case Qt::Key_D:
      translate_right();
   break;

   case Qt::Key_Space:
      defaultScene();
   break;

   case Qt::Key_Escape:
      this->close();
   break;
   }

   update();
}

//!\brief Zoom in
void Scene3D::scale_plus()
{
   nSca = nSca*1.1f;
}

//!\brief Zoom out
void Scene3D::scale_minus()
{
   nSca = nSca/1.1f;
}

//!\brief Rotation around the horizontal axis
void Scene3D::rotate_up()
{
   xRot += 1.0f;
}

//!\brief Rotation around the horizontal axis
void Scene3D::rotate_down()
{
   xRot -= 1.0f;
}

//!\brief Rotation around the vertical axis
void Scene3D::rotate_left()
{
   zRot += 1.0f;
}

//!\brief Rotation around the vertical axis
void Scene3D::rotate_right()
{
   zRot -= 1.0f;
}

//!\brief Translation down
void Scene3D::translate_down()
{
   zTra -= 0.05f;
}

//!\brief Translation up
void Scene3D::translate_up()
{
   zTra += 0.05f;
}
//!\brief Translation right
void Scene3D::translate_right()
{
   xTra += 0.05f;
}

//!\brief Translation left
void Scene3D::translate_left()
{
   xTra -= 0.05f;
}
/*!
    \brief Full drawing

*/

void Scene3D::paintGL()
{
   if (this->flag_pnt) {
       CalcPoint();
       flag_pnt = 0;
       flag_ans = 1;
   }
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glScalef(nSca, nSca, nSca);
   glTranslatef(xTra, zTra, 0.0f);
   glRotatef(xRot, 1.0f, 0.0f, 0.0f);
   glRotatef(yRot, 0.0f, 1.0f, 0.0f);
   glRotatef(zRot, 0.0f, 0.0f, 1.0f);

   drawAxis();
   if (this->flag_arr) drawArrow();
   drawFigure();
}

/*!
    \brief Drawing of axis

*/

void Scene3D::drawAxis()
{
   glLineWidth(3.0f);

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);
      glVertex3f( 1.0f,  0.0f,  0.0f);
      glVertex3f(-1.0f,  0.0f,  0.0f);
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   initializeOpenGLFunctions();
   glColor4f(0.00f, 1.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}
/*!
    \brief Drawing of arrow

    After calculation of point and the garvity force in this point this function will draw a beautiful red arrow.
    Its direction will coincide with the direction of the gravity force's vector.
*/
void Scene3D::drawArrow()
{

   float l = sqrtf(grav_Arrow.x2*grav_Arrow.x2 +
                   grav_Arrow.y2*grav_Arrow.y2 +
                   grav_Arrow.z2*grav_Arrow.z2)*5;

   //std::cout << "l = " << l << std::endl;
   glLineWidth(100.0f);
   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);


      glVertex3f(grav_Arrow.x1,  grav_Arrow.y1,  grav_Arrow.z1);
      glVertex3f(grav_Arrow.x1 + grav_Arrow.x2/l,  grav_Arrow.y1 + grav_Arrow.y2/l,  grav_Arrow.z1 + grav_Arrow.z2/l);

      glVertex3f(grav_Arrow.x1 + grav_Arrow.x2/l,  grav_Arrow.y1 + grav_Arrow.y2/l,  grav_Arrow.z1 + grav_Arrow.z2/l);
      glVertex3f(grav_Arrow.x1 + grav_Arrow.x2/l - (grav_Arrow.x2 - grav_Arrow.z2)/(3*l),
                 grav_Arrow.y1 + grav_Arrow.y2/l - (grav_Arrow.y2)/(3*l),
                 grav_Arrow.z1 + grav_Arrow.z2/l - (grav_Arrow.x2 + grav_Arrow.z2)/(3*l));

      glVertex3f(grav_Arrow.x1 + grav_Arrow.x2/l,  grav_Arrow.y1 + grav_Arrow.y2/l,  grav_Arrow.z1 + grav_Arrow.z2/l);
      glVertex3f(grav_Arrow.x1 + grav_Arrow.x2/l - (grav_Arrow.x2 + grav_Arrow.z2)/(3*l),
                 grav_Arrow.y1 + grav_Arrow.y2/l - (grav_Arrow.y2)/(3*l),
                 grav_Arrow.z1 + grav_Arrow.z2/l - (-grav_Arrow.x2 + grav_Arrow.z2)/(3*l));
   glEnd();

}

/*!
    \brief Processing of information of mouse's wheel

    Processing of the mouse's wheel events. Zoom in and zoom out.
*/

void Scene3D::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   update();
}

/*!
    \brief Default settings for scene

    Give you an opportunity to return to the start scene, if you need to do it.
*/

void Scene3D::defaultScene()
{
   xRot=-90; yRot=0; zRot=0; xTra=0; zTra=0; nSca=1;
}

/*!
    \brief Creation of arrow with verteices and colors for triangles

    Always calling after improting of file. Create an arrow with the location of all vertices. Furthermore, define colors for triangles, depending on their location.
*/
void Scene3D::my_getArrays(std::string path)
{
    std::ifstream file (path, std::ifstream::in);
    if (!file)
            std::perror("ifstream");

    R=static_cast<double>(1.0);

    if (!file)
    {
        std::cout << "file does not open" << std::endl;
    }

    fin.open(path);
    tetrahedralization(&in, &out, &behavior, &fin);
    fin.close();


    std::string s;
    int a, b, n_, i;
    GLfloat n, max = 0, min = 1000, max_ = 0;
    file >> s;
    a = atoi(s.c_str());
    file >> s;
    b = atoi(s.c_str());

    StrMyIndexArray = new CFace[static_cast<unsigned long long>(b)];
    StrMyVertexArray = new CVertex3[static_cast<unsigned long long>(a)];
    StrMyColorArray = new CColor3[static_cast<unsigned long long>(a)];
    IndexSize =static_cast<unsigned long long>(b);

    if (StrMyIndexArray == nullptr){
        std::cout << "Could not allocate memory for StrMyIndexArray" << std::endl;
    }
    if (StrMyVertexArray == nullptr){
        std::cout << "Could not allocate memory for StrMyVertexArray" << std::endl;
    }
    if (StrMyColorArray == nullptr){
        std::cout << "Could not allocate memory for StrMyColorArray" << std::endl;
    }

    std::cout << "sizes: " << a << ' ' << b << std::endl;
    for(i = 0; i < a; i++){
        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n = static_cast <GLfloat> (atof(s.c_str()));
        if(max < abs(n)) {
            max = abs(n);
        }
        StrMyVertexArray[i].x = n * R;

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n = static_cast <GLfloat>(atof(s.c_str()));
        if(max < abs(n)) {
            max = abs(n);
        }
        StrMyVertexArray[i].y = n * R;

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n = static_cast <GLfloat> (atof(s.c_str()));
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
        StrMyIndexArray[i].v1= (n_ - 1);

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n_ = atoi(s.c_str());
        StrMyIndexArray[i].v2 = (n_ - 1);

        file >> s;
        if (file.eof()){
            std::cout << "wrong number of vertexes";
        }
        n_ = atoi(s.c_str());
        StrMyIndexArray[i].v3 =(n_ - 1);
    }
    R = 0.75f/max;
    std::cout << "max = " << max << ", R = " << R << std::endl;

    std::cout << max << ' ' << min << std::endl;
    for(i = 0; i < a; i++)
    {
        n = sqrt(StrMyVertexArray[i].x *StrMyVertexArray[i].x + StrMyVertexArray[i].y *StrMyVertexArray[i].y + StrMyVertexArray[i].z *StrMyVertexArray[i].z);
        n = (0.7f*(n - min) - 0.4f*(n-max_))/(max_ - min);
          StrMyColorArray[i].r=n;
          StrMyColorArray[i].g=n;
          StrMyColorArray[i].b=n;
        if ((n < 0.4f) || (n > 0.7f)){
            std::cout << n << std::endl; //shader texture vertex освещение - цвета
        }

        StrMyVertexArray[i].x = StrMyVertexArray[i].x * R;
        StrMyVertexArray[i].y = StrMyVertexArray[i].y * R;
        StrMyVertexArray[i].z = StrMyVertexArray[i].z * R;
    }
    file.close();
}

/*!
    \brief Calculation of the point

    Processing of the data that was given by user. Result is given in the field: "Answer"
*/
void Scene3D::CalcPoint() {

     grav_in_point(&out, p, v);
     grav_Arrow.x1 = static_cast <GLfloat> (p[0])*(R);
     grav_Arrow.y1 = static_cast <GLfloat>(p[1])*R;
     grav_Arrow.z1 = static_cast <GLfloat>(p[2])*R;
     grav_Arrow.x2 = static_cast <GLfloat>(v[0])*R;
     grav_Arrow.y2 = static_cast <GLfloat>(v[1])*R;
     grav_Arrow.z2 = static_cast <GLfloat> (v[2])*R;


}

/*!
    \brief Drawing the triangles

    This function draw an asteroid using GL function for drawing triangles.
*/

void Scene3D::drawFigure()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, sizeof(CVertex3), StrMyVertexArray);
    glColorPointer(3, GL_FLOAT, sizeof(CVertex3), StrMyColorArray);

    glDrawElements(GL_TRIANGLES, static_cast <GLsizei>(3 * IndexSize), GL_UNSIGNED_INT, StrMyIndexArray);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/*!
    \brief Processing of mouse events

    Processing of the mouse events when it is pressed
*/
void Scene3D::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

/*!
    \brief Processing of mouse moves

*/

void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*static_cast<GLfloat>(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*static_cast<GLfloat>(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   update();
}

/*!
    \brief Avoiding memory leaks

    Ths function will free tetgenio arrows.
*/

void Scene3D::free_scene3D() {
   delete[] StrMyIndexArray;
   delete[] StrMyVertexArray;
   delete[] StrMyColorArray;
}


