#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI w; 
    //w.resize(1280, 720);
    //w.setContentsMargins(0, 0,0,0);
    //w.statusBar()->hide();
    //w.centralWidget()->setStyleSheet("background-image:url(\"bg.jpg\"); background-position: center;");
    w.setStyleSheet("QMainWindow {background: 'white';}");
    w.show();
    return a.exec();
}
