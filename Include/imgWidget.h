#ifndef IMGWIDGET_H
#define IMGWIDGET_H

#include <qwidget.h>
#include <QVTKWidget.h>
#include <opencv2/viz.hpp>

class imgWidget : public QVTKWidget
{
	Q_OBJECT
public:
	imgWidget(QWidget* parent);

private:
	
};




#endif