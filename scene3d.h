#ifndef SCENE3D_H
#define SCENE3D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class Scene3D : public QOpenGLWidget, protected QOpenGLFunctions
{
    private:

    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;

    QPoint ptrMousePosition;
    
    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();

    void drawAxis();
    void defaultScene();
    void my_getArrays();
    void drawFigure();

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void keyPressEvent(QKeyEvent* pe);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);

   public:
      Scene3D(QWidget* parent = 0);
};
#endif
