/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "myGLWidget.h"
#include "mytablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QWidget *mTableWidget;
    myTableWidget *mTable1;
    myTableWidget *mTable0;
    myGLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName("GUIClass");
        GUIClass->resize(840, 600);
        actionOpen = new QAction(GUIClass);
        actionOpen->setObjectName("actionOpen");
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName("centralWidget");
        mTableWidget = new QWidget(centralWidget);
        mTableWidget->setObjectName("mTableWidget");
        mTableWidget->setGeometry(QRect(0, 0, 431, 501));
        mTable1 = new myTableWidget(mTableWidget);
        if (mTable1->columnCount() < 42)
            mTable1->setColumnCount(42);
        if (mTable1->rowCount() < 30)
            mTable1->setRowCount(30);
        mTable1->setObjectName("mTable1");
        mTable1->setGeometry(QRect(0, 248, 421, 251));
        mTable1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mTable1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mTable1->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        mTable1->setAutoScroll(false);
        mTable1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mTable1->setShowGrid(true);
        mTable1->setRowCount(30);
        mTable1->setColumnCount(42);
        mTable1->horizontalHeader()->setVisible(false);
        mTable1->horizontalHeader()->setMinimumSectionSize(5);
        mTable1->horizontalHeader()->setDefaultSectionSize(25);
        mTable1->horizontalHeader()->setHighlightSections(true);
        mTable1->verticalHeader()->setVisible(false);
        mTable1->verticalHeader()->setMinimumSectionSize(5);
        mTable1->verticalHeader()->setDefaultSectionSize(23);
        mTable0 = new myTableWidget(mTableWidget);
        if (mTable0->columnCount() < 42)
            mTable0->setColumnCount(42);
        if (mTable0->rowCount() < 30)
            mTable0->setRowCount(30);
        mTable0->setObjectName("mTable0");
        mTable0->setGeometry(QRect(0, 0, 421, 247));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mTable0->sizePolicy().hasHeightForWidth());
        mTable0->setSizePolicy(sizePolicy);
        mTable0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mTable0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mTable0->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        mTable0->setAutoScroll(false);
        mTable0->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mTable0->setRowCount(30);
        mTable0->setColumnCount(42);
        mTable0->horizontalHeader()->setVisible(false);
        mTable0->horizontalHeader()->setMinimumSectionSize(5);
        mTable0->horizontalHeader()->setDefaultSectionSize(25);
        mTable0->verticalHeader()->setVisible(false);
        mTable0->verticalHeader()->setMinimumSectionSize(5);
        mTable0->verticalHeader()->setDefaultSectionSize(23);
        openGLWidget = new myGLWidget(centralWidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setGeometry(QRect(430, 0, 461, 251));
        GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 840, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        GUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUIClass);
        mainToolBar->setObjectName("mainToolBar");
        GUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUIClass);
        statusBar->setObjectName("statusBar");
        GUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(GUIClass);

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QCoreApplication::translate("GUIClass", "GUI", nullptr));
        actionOpen->setText(QCoreApplication::translate("GUIClass", "Open", nullptr));
        menuFile->setTitle(QCoreApplication::translate("GUIClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
