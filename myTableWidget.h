#pragma once

#include <qtablewidget.h>

class myTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit myTableWidget(QWidget* parent = nullptr);
    virtual ~myTableWidget();

protected:
    void resizeEvent(QResizeEvent* e);
    void mouseMoveEvent(QMouseEvent* event);

    QFont mFnt;
};