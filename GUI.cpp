#include "GUI.h"

#include <qdebug.h>
#include <qpainter.h>
#include <qfiledialog.h>

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Menu Bar
    connect(ui.actionOpen, &QAction::triggered, [this]() {
        QString filename = QFileDialog::getOpenFileName(
            nullptr,
            QObject::tr("Open Obj"),
            QDir::currentPath(),
            QObject::tr("Obj files (*.obj)"));
        //qDebug() << filename;
        QString filename_mtl = filename;
        filename_mtl = filename_mtl.remove(int(filename_mtl.size()) - 3, 3) + "mtl";
        ui.openGLWidget->loadmesh(filename.toLocal8Bit().data(), 
                                  filename_mtl.toLocal8Bit().data(), 
                                  ui.openGLWidget->mModelVAO_3,
                                  ui.openGLWidget->mModelVAO_4);
    });

    // Color Bar
    //ui.mColorBar->setFixedSize(GUIW * 0.1, GUIH);

    // Tables
    ui.mTable0->setColumnCount(mTableCol);
    ui.mTable0->setRowCount(mTableRow);

    ui.mTable1->setColumnCount(mTableCol);
    ui.mTable1->setRowCount(mTableRow);
}

GUI::~GUI()
{}

void GUI::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    // Your code here.
    int width = ui.centralWidget->width();
    int height = ui.centralWidget->height();
    qDebug() << width << " " << height;

    // Tables
    ui.mTableWidget->setFixedSize(width * 0.5, height);

    int gridw = float(width) * 0.5 / mTableCol;
    int gridh = float(height) * 0.5 / mTableRow;
    ui.mTable0->setFixedSize(gridw * mTableCol, gridh * mTableRow);
    ui.mTable1->setFixedSize(gridw * mTableCol, gridh * mTableRow);
    ui.mTable1->move(0, height * 0.5);

    // Mesh
    ui.openGLWidget->setFixedSize(width * 0.5, height * 0.5);
    ui.openGLWidget->move(width * 0.5, 0);
}

void GUI::paintEvent(QPaintEvent* event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    int width = ui.centralWidget->width();
    int height = ui.centralWidget->height();

    QImage img;
    img.load("bg.jpg");
    img = img.scaled(width * 0.5, height * 0.5);

    painter.drawImage(width * 0.5, height * 0.5, img);
}