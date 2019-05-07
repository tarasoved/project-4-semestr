#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget>

class Scene3D : public QGLWidget
{
    private:

    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

   public:
      Scene3D(QWidget* parent = 0);
};
#endif
