#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"

#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qimage.h>


class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUIClass ui;

    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);

    int GUIW = 1280, GUIH = 720;
    int mTableRow = 30, mTableCol = 42;
};