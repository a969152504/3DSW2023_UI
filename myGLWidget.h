#pragma once

#include <qopengl.h>
#include <qopenglfunctions.h>
#include <qmatrix4x4.h>
#include <qvector3d.h>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QtOpenGL/qopenglvertexarrayobject.h>
#include <QtOpenGL/qopenglbuffer.h>
#include <QtOpenGL/qopenglshaderprogram.h>
#include <QtOpenGL/qopengltexture.h>
#include <QtOpenGL/qopenglframebufferobject.h>


class myGLWidget : public QOpenGLWidget
{
public:
    explicit myGLWidget(QWidget* parent = nullptr);
    virtual ~myGLWidget();

    void loadmesh(const char* filename,
                  const char* filename_mtl,
                  std::vector<std::array<float, 9>>& vao3,
                  std::vector<std::array<float, 9>>& vao4);

    std::vector<std::array<float, 9>> mModelVAO_3;
    std::vector<std::array<float, 9>> mModelVAO_4;

private:
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram* m_program = nullptr;

    QVector3D mModelPos, mCam, mCamup;
    QVector3D mModelBB_min, mModelBB_max;
    QMatrix4x4 m_view, m_projection;
    std::vector<uint> mModelF3, mModelF4;
    const float mModelScale = 10.0;
    float mModel_Nearplane = 1000.0, mModel_Farplane = 3000.0;
    bool init_BB = false;

    int mousex, mousey;
    float mVerticalAngle = 45.0;

    bool mInitialized = false;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
};