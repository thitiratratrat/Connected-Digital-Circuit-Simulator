#pragma once
#ifndef CUSTOMWIDGETS_HPP
#define	CUSTOMWIDGETS_HPP
#define slots Q_SLOTS

#include <QtWidgets>
#include <Qlabel.h>
#include <QImage>
#include <qwidget.h>
#include <QPushButton.h>
#include <vector>
#include "CPP_ProjectFinal.h"
#include "OtherComponents.hpp"

using namespace std;

class BoardWidget;
class WireWidget;
class BoardComponentWidget;


class Connector : public QLabel {
public:
	Connector(BoardComponentWidget *widget = 0, BoardWidget *parent = 0, string t = "", int n = 0);
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	BoardWidget *parentW;
	BoardComponentWidget *boardW;
	bool isConnected;
	vector<Connector*> connectedC;
	vector<WireWidget*> connectedW;
	bool checkInConnected(Connector *c);
	string type;
	int num;

private:
	QImage image;
	QPoint position;
	QLabel *temp;
	void mousePressEvent(QMouseEvent *event);
};



#endif