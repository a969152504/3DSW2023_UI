#include "myTableWidget.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QtConcurrent/QtConcurrent>
#include <qrandom.h>
#include <QDebug>

myTableWidget::myTableWidget(QWidget* parent) : QTableWidget(parent)
{
	//verticalHeader()->setStretchLastSection(1);
	//horizontalHeader()->setStretchLastSection(1);

	mFnt.setPointSize(7);
	mFnt.setFamily("Arial");
}

myTableWidget::~myTableWidget()
{

}

void myTableWidget::resizeEvent(QResizeEvent* e)
{
	const int tw = width();
	const int th = height();

	verticalHeader()->setDefaultSectionSize(th / rowCount());
	horizontalHeader()->setDefaultSectionSize(tw / columnCount());

	for (int i = 0; i < rowCount(); ++i) {
		for (int j = 0; j < columnCount(); ++j) {
			auto tmp = item(i, j);
			if (!tmp) {
				tmp = new QTableWidgetItem;
				setItem(i, j, tmp);
			}
			if (th > 450) {
				item(i, j)->setFont(mFnt);
				item(i, j)->setTextAlignment(Qt::AlignCenter);
				item(i, j)->setText(QString::number(i+j));
			}
			else {
				item(i, j)->setText("");
			}
		}
	}

	//qDebug() << tr("%1 x %2").arg(tw).arg(th);
}

void myTableWidget::mouseMoveEvent(QMouseEvent* event) {

	auto future = QtConcurrent::run([this]() {
		const int tw = width();
		const int th = height();

		const int rc = rowCount();
		const int cc = columnCount();
		for (int i = 0; i < rc; ++i) {
			int r = QRandomGenerator::global()->bounded(0, 255);
			for (int j = 0; j < cc; ++j) {
				int g = QRandomGenerator::global()->bounded(0, 255);
				int b = QRandomGenerator::global()->bounded(0, 255);
				item(i, j)->setBackground(QBrush(QColor(r, g, b)));
				/*if (th > 450) {
					item(i, j)->setFont(mFnt);
					item(i, j)->setTextAlignment(Qt::AlignCenter);
					item(i, j)->setText(QString::number(r));
				}
				else {
					item(i, j)->setText("");
				}*/
			}
		}
	});


}