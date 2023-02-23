#include "myGLWidget.h"

#include <qfile.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <QMouseEvent>
#include <QWheelEvent>

myGLWidget::myGLWidget(QWidget* parent) : QOpenGLWidget(parent), m_program(0)
{
    // No OpenGL resource initialization is done here.
}

myGLWidget::~myGLWidget()
{
    // Make sure the context is current and then explicitly
    // destroy all underlying OpenGL resources.
    makeCurrent();

    delete m_program;

    m_vbo.destroy();

    init_BB = false;
    mInitialized = false;

    doneCurrent();
}

void myGLWidget::loadmesh(const char* filename,
                          const char* filename_mtl,
                          std::vector<std::array<float, 9>>& vao3,
                          std::vector<std::array<float, 9>>& vao4)
{
    init_BB = false;

    QString qs;

    QFile fin_mtl(filename_mtl);
    if (!fin_mtl.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file " << filename_mtl;
        return;
    }
    QTextStream in_mtl(&fin_mtl);

    std::vector<std::array<float, 3>> Ka, Kd;

    while (!in_mtl.atEnd())
    {
        qs = in_mtl.readLine();
        auto l = qs.split(' ');
        if ("Ka" == l[0]) {
            Ka.push_back({ l[1].toFloat(), l[2].toFloat(), l[3].toFloat() });
        }
        else if ("Kd" == l[0]) {
            Kd.push_back({ l[1].toFloat(), l[2].toFloat(), l[3].toFloat() });
        }
        else {
            qDebug() << "Unknown element : " << qs;
        }
    }
    fin_mtl.close();

    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file " << filename;
        return;
    }
    QTextStream in(&fin);

    std::vector<std::array<int, 3>> fids_3;
    std::vector<std::array<int, 4>> fids_4;
    int tmpMat_id;
    std::vector<std::array<float, 3>> Ka3, Kd3, Ka4, Kd4;
    std::vector<QVector3D> verts;

    float x_min = 0.0, x_max = 0.0,
          y_min = 0.0, y_max = 0.0,
          z_min = 0.0, z_max = 0.0;

    while (!in.atEnd())
    {
        qs = in.readLine();
        auto l = qs.split(' ');
        if ("v" == l[0]) {
            float l1_scaled = l[1].toFloat() * mModelScale;
            float l2_scaled = l[2].toFloat() * mModelScale;
            float l3_scaled = l[3].toFloat() * mModelScale;
            verts.emplace_back(l1_scaled, l2_scaled, l3_scaled);
            if (!init_BB) {
                x_min = l1_scaled;
                x_max = l1_scaled;
                y_min = l2_scaled;
                y_max = l2_scaled;
                z_min = l3_scaled;
                z_max = l3_scaled;
                init_BB = true;
            }
            if (l1_scaled < x_min) {
                x_min = l1_scaled;
            }
            else if (l1_scaled > x_max) {
                x_max = l1_scaled;
            }
            if (l2_scaled < y_min) {
                y_min = l2_scaled;
            }
            else if (l2_scaled > y_max) {
                y_max = l2_scaled;
            }
            if (l3_scaled < z_min) {
                z_min = l3_scaled;
            }
            else if (l3_scaled > z_max) {
                z_max = l3_scaled;
            }
        }
        else if ("usemtl" == l[0]) {
            tmpMat_id = l[1].remove(0, 3).toInt();
        }
        else if ("f" == l[0]) {
            if (l.size() == 4) {
                fids_3.push_back({ l[1].toInt(), l[2].toInt(), l[3].toInt() });
                Ka3.push_back(Ka[tmpMat_id]);
                Kd3.push_back(Kd[tmpMat_id]);
            }
            else {
                fids_4.push_back({ l[1].toInt(), l[2].toInt(), l[3].toInt(), l[4].toInt() });
                Ka4.push_back(Ka[tmpMat_id]);
                Kd4.push_back(Kd[tmpMat_id]);
            }
        }
        else {
            qDebug() << "Unknown element : " << qs;
        }
    }
    fin.close(); 

    std::transform(fids_3.begin(), fids_3.end(), fids_3.begin(), [](std::array<int, 3>& i) {
        --i[0]; --i[1]; --i[2];
        return i;
    });
    std::transform(fids_4.begin(), fids_4.end(), fids_4.begin(), [](std::array<int, 4>& i) {
        --i[0]; --i[1]; --i[2]; --i[3];
    return i;
        });

    const int nFs3 = int(fids_3.size());
    const int nFs4 = int(fids_4.size());

    vao3.clear();
    vao4.clear();
    vao3.resize(nFs3*3);
    vao4.resize(nFs4*4);
    for (int i = 0; i < nFs3; i++) {
        std::array<float, 9> va;

        const auto fv = fids_3[i];

        const auto& tKa = Ka3.at(i);
        const auto& tKd = Kd3.at(i);

        for (int j = 0; j < 3; j++) {
            mModelF3.push_back(i * 3 + j);

            const auto &v = verts.at(fv[j]);

            //Setting VAO
            va[0] = v.x(); va[1] = v.y(); va[2] = v.z();
            va[3] = tKa[0]; va[4] = tKa[1]; va[5] = tKa[2];
            va[6] = tKd[0]; va[7] = tKd[1]; va[8] = tKd[2];
            vao3[i * 3 + j] = va;
        }
    }
    for (int i = 0; i < nFs4; i++) {
        std::array<float, 9> va;

        const auto fv = fids_4[i];

        const auto& tKa = Ka4.at(i);
        const auto& tKd = Kd4.at(i);

        for (int j = 0; j < 4; j++) {
            mModelF4.push_back(i * 4 + j);

            const auto& v = verts.at(fv[j]);

            //Setting VAO
            va[0] = v.x(); va[1] = v.y(); va[2] = v.z();
            va[3] = tKa[0]; va[4] = tKa[1]; va[5] = tKa[2];
            va[6] = tKd[0]; va[7] = tKd[1]; va[8] = tKd[2];
            vao4[i * 4 + j] = va;
        }
    }

    mModelBB_min = QVector3D(x_min - 0.1 * (x_max - x_min), y_min - 0.1 * (y_max - y_min), z_min - 0.1 * (z_max - z_min));
    mModelBB_max = QVector3D(x_max + 0.1 * (x_max - x_min), y_max + 0.1 * (y_max - y_min), z_max + 0.1 * (z_max - z_min));

    QVector3D posi = QVector3D((mModelBB_min.x() + mModelBB_max.x()) * 0.5,
                               (mModelBB_min.y() + mModelBB_max.y()) * 0.5,
                               (mModelBB_min.z() + mModelBB_max.z()) * 0.5);
    mModelPos = posi;
    mModel_Nearplane = 2.0 * (mModelBB_max.z() - mModelBB_min.z());
    mModel_Farplane = mModelBB_max.z() + mModel_Nearplane;
    mCam = QVector3D(posi.x(), posi.y(), mModelBB_max.z() + mModel_Nearplane);
    mCamup = QVector3D(0.0, 1.0, 0.0);
    if (mModel_Farplane - mModel_Nearplane < mModelBB_max.z() - mModelBB_min.z()) {
        mModel_Farplane = mModelBB_max.z() - mModelBB_min.z() + mModel_Nearplane;
    }

    qDebug() << "Model position: " << mModelPos << "\n"
             << "Camera position: " << mCam << "\n"
             << "Bounding box min: " << mModelBB_min << "\n"
             << "Bounding box max: " << mModelBB_max << "\n"
             << "Near plane: " << mModel_Nearplane << "\n"
             << "Far plane: " << mModel_Farplane << "\n";
    
    qDebug() << filename << " loaded";
}

void myGLWidget::mousePressEvent(QMouseEvent* event) {
    //qDebug() << "mousePressEvent";
    //qDebug() << event->pos();

    mousex = event->pos().x();
    mousey = event->pos().y();
}

void myGLWidget::mouseReleaseEvent(QMouseEvent* event) {
    //qDebug() << "mouseReleaseEvent";
}

void myGLWidget::mouseMoveEvent(QMouseEvent* event) {
    //qDebug() << "mouseMoveEvent";
    //qDebug() << event->pos();

    int movex = event->pos().x() - mousex;
    int movey = event->pos().y() - mousey;
    mousex = event->pos().x();
    mousey = event->pos().y();
    
    QMatrix4x4 R;
    R.setToIdentity();
    R.rotate(-movex * 0.7, 0.0, 1.0);
    R.rotate(-movey * 0.7, 1.0, 0.0);

    mCam = R * mCam;
    mCamup = R * mCamup;
    mCamup.normalize();

    update();
}

void myGLWidget::wheelEvent(QWheelEvent* event) {
    qDebug() << "wheelEvent";
    qDebug() << event->angleDelta();

    mVerticalAngle += event->angleDelta().y() * 0.1;

    update();
}

void myGLWidget::resizeGL(int w, int h)
{
    // Update projection matrix and other size related settings:
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, float(w) / h, mModel_Nearplane, mModel_Farplane);

    //qDebug() << width() << " " << height();
}

void myGLWidget::initializeGL()
{
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    std::string vsh, fsh;

    vsh =
        "attribute vec3 a_pos;\n"       //The position of a point in 3D that used in FunctionRender()
        "attribute vec3 a_ka;\n"
        "attribute vec3 a_kd;\n"
        "uniform mat4 m4_mvp;\n"        //The Model-View-Matrix
        "uniform mat4 m4_view;\n"
        "uniform float f_pointSize;\n"  //Point size determined in FunctionRender()
        "varying vec3 Ka;\n"
        "varying vec3 Kd;\n"
        "varying vec3 pos;\n"
        "void main(){\n"
        "   pos = vec3( m4_view * vec4(a_pos, 1.0));\n"
        "   gl_Position = m4_mvp * vec4(a_pos, 1.0);\n" //Output the OpenGL position
        "   gl_PointSize = f_pointSize; \n"
        "   Ka = a_ka;\n"
        "   Kd = a_kd;\n"
        "}";
    fsh =
        "varying vec3 Ka;\n"
        "varying vec3 Kd;\n"
        "varying vec3 pos;\n"
        "void main(){\n"
        "   vec3 lightPos = vec3(0.0, 1000.0, 0.0);\n"
        "   vec3 viewDir = normalize( - pos);\n"
        "   vec3 lightDir = normalize(lightPos - pos);\n"
        "   vec3 ambi = Ka * vec3(0.1, 0.1, 0.1);\n"
        "   vec3 diff = Kd;\n"
        "   vec3 color = ambi + diff;\n"
        "   gl_FragColor = vec4(color, 1.0);\n" //Output the fragment color;
        "}";

    auto prog = new QOpenGLShaderProgram;   //Intialize the Shader with the above GLSL codes
    prog->addShaderFromSourceCode(QOpenGLShader::Vertex, vsh.c_str());
    prog->addShaderFromSourceCode(QOpenGLShader::Fragment, fsh.data());
    if (!prog->create() || !prog->link()) {  //Check whether the GLSL codes are valid
        qDebug() << prog->log();
        return;
    }
    m_program = prog;            //If everything is fine, assign to the member variable

    mInitialized = true;
}

void myGLWidget::paintGL()
{
    if (!mInitialized) {
        initializeGL();
    }

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

    //Clear the FBO
    f->glViewport(0, 0, width(), height());
    f->glClearColor(1.f, 1.f, 1.f, 1.f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glDisable(GL_BLEND);
    f->glEnable(GL_CULL_FACE);
    f->glCullFace(GL_BACK);
    GLenum bufs[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

    m_view.setToIdentity();
    m_view.lookAt(mCam,
                  mModelPos,
                  mCamup);

    m_projection.setToIdentity();
    float aspectRatio = float(width()) / height();
    m_projection.perspective(mVerticalAngle,
                             aspectRatio,
                             mModel_Nearplane,
                             mModel_Farplane);

    // Draw the scene:
    m_vbo.bind();

    m_program->bind();
    m_program->enableAttributeArray("a_pos");
    m_program->enableAttributeArray("a_ka");
    m_program->enableAttributeArray("a_kd");
    m_program->setUniformValue("m4_mvp", m_projection * m_view);
    m_program->setUniformValue("m4_view", m_view);

    m_program->setAttributeArray("a_pos", GL_FLOAT, mModelVAO_3.data(), 3, 36);
    m_program->setAttributeArray("a_ka", GL_FLOAT, 3 + &mModelVAO_3.data()->at(0), 3, 36);
    m_program->setAttributeArray("a_kd", GL_FLOAT, 6 + &mModelVAO_3.data()->at(0), 3, 36);
    f->glDrawElements(GL_TRIANGLES, GLsizei(mModelF3.size()), GL_UNSIGNED_INT, mModelF3.data());
    
    m_program->setAttributeArray("a_pos", GL_FLOAT, mModelVAO_4.data(), 3, 36);
    m_program->setAttributeArray("a_ka", GL_FLOAT, 3 + &mModelVAO_4.data()->at(0), 3, 36);
    m_program->setAttributeArray("a_kd", GL_FLOAT, 6 + &mModelVAO_4.data()->at(0), 3, 36);
    f->glDrawElements(GL_QUADS, GLsizei(mModelF4.size()), GL_UNSIGNED_INT, mModelF4.data());

    m_program->disableAttributeArray("a_kd");
    m_program->disableAttributeArray("a_ka");
    m_program->disableAttributeArray("a_pos");
    m_program->release();

    m_vbo.release();
}