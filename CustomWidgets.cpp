#include <iostream>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <qcoreapplication.h>
#include "CustomWidgets.hpp"
#include "OtherComponents.hpp"
#include "CPP_ProjectFinal.h"
#include "Board.hpp"
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>

const int CONNECTORSIZE = 8;
const int MIDDLECONNECTOR = CONNECTORSIZE / 2 - 3;
const int WIRELENGTH = 120;
const int WIREWIDTH = 5;
const int BTNDELETESIZE = 15;
const int COMPONENTL = 60;
const int COMPONENTW = 60;

vector<string> names;
map<string, string> descrip;

void readDescription() {
	ifstream file;
	string line, temp;
	vector<string> split;
	stringstream s;
	int pos;
	file.open("Description.txt");
	while (!file.eof()) {
		getline(file, line);
		pos = line.find("/");
		split.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
		split.push_back(line);
		descrip.insert({ split[0], split[1]});
		split.clear();
	}
}


BoardComponentWidget::BoardComponentWidget(QWidget *parent) : QWidget(parent) {
	btnDelete = new QPushButton(this);
	btnDelete->setText("x");
	btnDelete->setEnabled(true);
	btnDelete->setStyleSheet("background-color: #fa9f0f; border: none");
	btnDelete->setVisible(false);
}

void BoardComponentWidget::deleteWidget(Connector *c) {
	vector<WireWidget*> temp = c->connectedW;
	for (int i = 0; i < temp.size(); i++) {
		temp[i]->deleteWire();
	}
	if (c->parentW->clickedWidget == c)
		c->parentW->clickedWidget = NULL;
	else if (c->parentW->clickedWidget2 == c)
		c->parentW->clickedWidget2 = NULL;
}

void BoardComponentWidget::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		mousemoved = event->globalPos();
		btnDelete->setVisible(false);
	}
	if (event->button() == Qt::RightButton) {
		btnDelete->setVisible(true);
		btnDelete->raise();
		btnDelete->setEnabled(true);
	}
}

void BoardComponentWidget::mouseMoveEvent(QMouseEvent *event) {
	QPoint currPos = this->mapToGlobal(this->pos());
	QPoint globalPos = event->globalPos();
	QPoint diff = globalPos - mousemoved;
	QPoint newPos = this->mapFromGlobal(currPos + diff);
	mousemoved = globalPos;
	move(newPos);
}

//--------------------------------------------CONNECTOR WIDGET--------------------------------------------------//

Connector::Connector(BoardComponentWidget *widget, BoardWidget *parent, string t, int n) : QLabel(widget) {
	parentW = parent;
	boardW = widget;
	type = t;
	num = n;
	
	image = QImage("./Pictures/Connector.png");
	image = image.scaled(CONNECTORSIZE, CONNECTORSIZE, Qt::KeepAspectRatio);
	this->setPixmap(QPixmap::fromImage(image));

	this->setGeometry(0, 0, CONNECTORSIZE, CONNECTORSIZE);

	this->installEventFilter(this);
	setMouseTracking(true);
	isConnected = false;
	
}

void Connector::enterEvent(QEvent *event) {
	QImage temp = QImage("./Pictures/ConnectorS.png");
	temp = temp.scaled(CONNECTORSIZE, CONNECTORSIZE, Qt::KeepAspectRatio);
	this->setPixmap(QPixmap::fromImage(temp));
}

void Connector::leaveEvent(QEvent *event) {
	this->setPixmap(QPixmap::fromImage(image));
}
bool Connector::checkInConnected(Connector *c) {
	for (int i = 0; i < connectedC.size(); i++) {
		if (connectedC[i] == c)
			return false;
	}
	return true;
}

void Connector::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		if (parentW->clickedWidget == NULL)
			parentW->clickedWidget = this;
		else if (parentW->clickedWidget2 == NULL && parentW->clickedWidget != this)
			parentW->clickedWidget2 = this;

		//if two connectors has already been clicked, create a wire between them
		//one connector can be linked to many connectors
		if (parentW->clickedWidget != NULL && parentW->clickedWidget2 != NULL
			&& parentW->clickedWidget->parentWidget() != parentW->clickedWidget2->parentWidget()){

			if (parentW->clickedWidget->type == parentW->clickedWidget2->type) {
				parentW->clickedWidget = NULL;
				parentW->clickedWidget2 = NULL;
				return;
			}

			
			bool check;
			
			if (parentW->clickedWidget == this)
				check = checkInConnected(parentW->clickedWidget2);
			else
				check = checkInConnected(parentW->clickedWidget);

			if (check == true) {
				WireWidget *w = new WireWidget(parentW);
				Connector *c1;
				Connector *c2;
				QPoint wPos;
				QPoint lblDPos;

				if (parentW->clickedWidget->mapToGlobal(parentW->clickedWidget->pos()).x() < parentW->clickedWidget2->mapToGlobal(parentW->clickedWidget2->pos()).x()) {
					c1 = parentW->clickedWidget;
					c2 = parentW->clickedWidget2;
				}
				else {
					c1 = parentW->clickedWidget2;
					c2 = parentW->clickedWidget;
				}
				
				if (c1->mapToGlobal(c1->pos()).y() == c2->mapToGlobal(c2->pos()).y()) {
					if (c1->mapToGlobal(c1->pos()).x() == c2->mapToGlobal(c2->pos()).x()) {
						parentW->clickedWidget = NULL;
						parentW->clickedWidget2 = NULL;
						return;
					}
				}

				if (c1->mapToGlobal(c1->pos()).y() == c2->mapToGlobal(c2->pos()).y()) {
					wPos = c1->mapToGlobal(c1->pos());
					QPoint temp = c2->mapToGlobal(c2->pos());


					w->setGeometry(parentW->mapFromGlobal(wPos).x() - c1->x(),
						parentW->mapFromGlobal(wPos).y() - c1->y(),
						abs(wPos.x() - temp.x()) + CONNECTORSIZE + c1->x() - c2->x(),
						WIREWIDTH + BTNDELETESIZE + 5);

					int length = abs(wPos.x() - temp.x()) + CONNECTORSIZE + c1->x() - c2->x();

					w->label->setGeometry(MIDDLECONNECTOR + 1, MIDDLECONNECTOR, length - MIDDLECONNECTOR - 3, WIREWIDTH);
					w->btnDelete->setGeometry((length - MIDDLECONNECTOR + 2) / 2, WIREWIDTH + 3, BTNDELETESIZE - 3, BTNDELETESIZE);

					w->label->setVisible(true);
					w->labelD->setVisible(false);
					w->btnDelete->setVisible(false);
				}

				else if (c1->mapToGlobal(c1->pos()).x() == c2->mapToGlobal(c2->pos()).x()) {
					QPoint temp;
					//w->setStyleSheet("background-color: green");
					if (c1->mapToGlobal(c1->pos()).y() < c2->mapToGlobal(c2->pos()).y()) {
						wPos = c1->mapToGlobal(c1->pos());
						temp = c2->mapToGlobal(c2->pos());
						w->setGeometry(parentW->mapFromGlobal(wPos).x() - c1->x(),
							parentW->mapFromGlobal(wPos).y() - c1->y(),
							WIREWIDTH + BTNDELETESIZE + 5,
							abs(wPos.y() - temp.y()) + CONNECTORSIZE + c1->y() - c2->y());
					}
					else {
						wPos = c2->mapToGlobal(c2->pos());
						temp = c1->mapToGlobal(c1->pos());
						w->setGeometry(parentW->mapFromGlobal(wPos).x() - c2->x(),
							parentW->mapFromGlobal(wPos).y() - c2->y(),
							WIREWIDTH + BTNDELETESIZE + 5,
							abs(wPos.y() - temp.y()) + CONNECTORSIZE + c2->y() - c1->y());
					}

					int width = abs(wPos.y() - temp.y()) + CONNECTORSIZE + c2->y() - c1->y();

					w->labelD->setGeometry(MIDDLECONNECTOR + 1, MIDDLECONNECTOR, WIREWIDTH, width - MIDDLECONNECTOR - 1);
					w->btnDelete->setGeometry((width - MIDDLECONNECTOR) / 2 - BTNDELETESIZE + 3, (width - MIDDLECONNECTOR) / 2 - BTNDELETESIZE, BTNDELETESIZE - 3, BTNDELETESIZE);

					w->labelD->setVisible(true);
					w->label->setVisible(false);
				}

				else if (c1->mapToGlobal(c1->pos()).y() < c2->mapToGlobal(c2->pos()).y()) {
					wPos = c1->mapToGlobal(c1->pos());
					QPoint temp = c2->mapToGlobal(c2->pos());

					//w->setStyleSheet("background-color: green;");

					w->setGeometry(parentW->mapFromGlobal(wPos).x() - c1->x(),
						parentW->mapFromGlobal(wPos).y() - c1->y(),
						abs(abs(temp.x() - wPos.x()) + CONNECTORSIZE - c2->x() + c1->x()),
						abs(abs(temp.y() - wPos.y()) + CONNECTORSIZE - c2->y() + c1->y()));

					int width = abs(abs(temp.y() - wPos.y()) + CONNECTORSIZE - c2->y() + c1->y());
					int length = abs(abs(temp.x() - wPos.x()) + CONNECTORSIZE - c2->x() + c1->x());

					w->labelD->setGeometry(MIDDLECONNECTOR + 1, MIDDLECONNECTOR, WIREWIDTH, width - WIREWIDTH - 1);
					w->label->setGeometry(MIDDLECONNECTOR + 1, width - WIREWIDTH - 1, length - MIDDLECONNECTOR - 2, WIREWIDTH);
					w->btnDelete->setGeometry(length - MIDDLECONNECTOR - BTNDELETESIZE - 10, width - WIREWIDTH - 1 - BTNDELETESIZE - 3, BTNDELETESIZE - 3, BTNDELETESIZE);

					w->labelD->setVisible(true);
					w->label->setVisible(true);
				}
				else if (c1->mapToGlobal(c1->pos()).y() > c2->mapToGlobal(c2->pos()).y()) {
					wPos.setX(c1->mapToGlobal(c1->pos()).x());
					wPos.setY(c2->mapToGlobal(c2->pos()).y());
					QPoint temp = c2->mapToGlobal(c2->pos());

					//w->setStyleSheet("background-color: green;");

					w->setGeometry(parentW->mapFromGlobal(wPos).x() - c1->x(),
						parentW->mapFromGlobal(wPos).y() - c2->y(),
						abs(temp.x() - wPos.x()) + CONNECTORSIZE - c2->x() + c1->x(),
						abs(temp.y() - c1->mapToGlobal(c1->pos()).y()) + CONNECTORSIZE - c1->y() + c2->y());

					int width = abs(temp.y() - c1->mapToGlobal(c1->pos()).y()) + CONNECTORSIZE - c1->y() + c2->y();
					int length = abs(temp.x() - wPos.x()) + CONNECTORSIZE - c2->x() + c1->x();

					w->labelD->setGeometry(MIDDLECONNECTOR + 1, MIDDLECONNECTOR, WIREWIDTH, width - WIREWIDTH  - MIDDLECONNECTOR);
					w->label->setGeometry(MIDDLECONNECTOR + 1, MIDDLECONNECTOR, length - MIDDLECONNECTOR - 2, WIREWIDTH);
					w->btnDelete->setGeometry(length - MIDDLECONNECTOR - BTNDELETESIZE - 10, MIDDLECONNECTOR + 8, BTNDELETESIZE - 3, BTNDELETESIZE);

					w->labelD->setVisible(true);
					w->label->setVisible(true);
				}

				//check if it is input type
				if (parentW->clickedWidget->type == "input") {
					w->input = parentW->clickedWidget2;
					w->output = parentW->clickedWidget;
				}
				else {
					w->input = parentW->clickedWidget;
					w->output = parentW->clickedWidget2;
				}

				w->setVisible(true);
				w->raise();
				parentW->clickedWidget->parentWidget()->raise();
				parentW->clickedWidget2->parentWidget()->raise();
				parentW->clickedWidget->isConnected = true;
				parentW->clickedWidget2->isConnected = true;

				if (parentW->clickedWidget == this) {
					connectedC.push_back(parentW->clickedWidget2);
					parentW->clickedWidget2->connectedC.push_back(parentW->clickedWidget);
					parentW->clickedWidget2->connectedW.push_back(w);
					connectedW.push_back(w);
				}
				else {
					connectedC.push_back(parentW->clickedWidget);
					parentW->clickedWidget->connectedC.push_back(parentW->clickedWidget2);
					parentW->clickedWidget->connectedW.push_back(w);
					connectedW.push_back(w);
				}

				//updatewidget when wire is connect here
				w->input->boardW->sendValue();

				parentW->clickedWidget = NULL;
				parentW->clickedWidget2 = NULL;

			}
		}
	}
}

//---------------------------------------------------WIRE WIDGET------------------------------------------------------//

WireWidget::WireWidget(QWidget *parent) :QWidget(parent) {
	Wire<Gate*, Gate*>* wire; //might have to change
	this->setGeometry(0, 20, WIRELENGTH, WIREWIDTH + 20);
	input = NULL;
	output = NULL;

	btnDelete = new QPushButton(this);
	label = new QLabel(this);
	labelD = new QLabel(this);
	
	//initialize label
	label->setStyleSheet("background-color: black");
	label->setGeometry(0, WIREWIDTH - CONNECTORSIZE + 1, WIRELENGTH, WIREWIDTH);
	labelD->setStyleSheet("background-color: black");
	labelD->setGeometry(0, WIREWIDTH - CONNECTORSIZE + 1, WIREWIDTH, WIRELENGTH);
	labelD->setVisible(false);

	//initialize btnDelete
	btnDelete->setText("x");
	btnDelete->setEnabled(true);
	btnDelete->setStyleSheet("background-color: #fa9f0f; border: none");
	btnDelete->setVisible(false);
	btnDelete->setVisible(false);
	btnDelete->setGeometry(WIRELENGTH - BTNDELETESIZE,0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &WireWidget::deleteWire);
	
}

void WireWidget::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		btnDelete->setVisible(false);
	}
	if (event->button() == Qt::RightButton) {
		btnDelete->setVisible(true);
		btnDelete->raise();
		btnDelete->setEnabled(true);
	}
}

void WireWidget::deleteWire() {
	input->connectedW.erase(remove(input->connectedW.begin(), input->connectedW.end(), this), input->connectedW.end());
	output->connectedW.erase(remove(output->connectedW.begin(), output->connectedW.end(), this), output->connectedW.end());
	input->connectedC.erase(remove(input->connectedC.begin(), input->connectedC.end(), output), input->connectedC.end());
	output->connectedC.erase(remove(output->connectedC.begin(), output->connectedC.end(), input), output->connectedC.end());
	if (input->connectedC.size() == 0 || input->connectedW.size() == 0) {
		input->isConnected = false;
	}
	if (output->connectedC.size() == 0 || output->connectedW.size() == 0) {
		output->isConnected = false;
	}
	deleteLater();
}

void WireWidget::getInput(Input input) {
	formula = input.getName();
	sendValue(input);
}

void WireWidget::sendValue(Input input) {
	output->boardW->getInput(input, output->num);
}

//-----------------------------------------INPUT OUTPUT WIDGET------------------------------------------//

InputWidget::InputWidget(QWidget *parent, BoardWidget *parentW): BoardComponentWidget(parent) {
	this->setGeometry(280, 140 , 30 + CONNECTORSIZE, 30 + BTNDELETESIZE + 3);
	this->setMouseTracking(true);
	setToolTip(QString::fromStdString(input.getName()));

	label = new QLabel(this);
	label->setGeometry(0, BTNDELETESIZE + 3, 30, 30);
	label->setText("0");
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("background-color: #ffaa39; Font: 13 pt;");

	c = new Connector(this, parentW, "output");
	c->setGeometry(30, (30 + BTNDELETESIZE + 3)/2 + CONNECTORSIZE, CONNECTORSIZE, CONNECTORSIZE);

	btnDelete->setGeometry(30 - BTNDELETESIZE + CONNECTORSIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &InputWidget::deleteWidget);
}

void InputWidget::mousePressEvent(QMouseEvent *event) {
	BoardComponentWidget::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		input.changeValue();
		label->setText(QString::number(input.getValue()));
		sendValue();
	}
}

void InputWidget::mouseMoveEvent(QMouseEvent* event) {
	if (event->buttons() == Qt::LeftButton) {
		if (c->isConnected == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void InputWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(c);
	names.erase(remove(names.begin(), names.end(), input.getName()), names.end());
	deleteLater();
}

void InputWidget::sendValue() {
	//send value to wire then wire send to connected connector's widget
	for (int i = 0; i < c->connectedW.size(); i++) {
		c->connectedW[i]->getInput(input);
	}
}

ButtonWidget::ButtonWidget(QWidget *parent, BoardWidget *parentW) : InputWidget(parent, parentW) {
	label->setText("0");
	label->setStyleSheet("background-color:none;");
	c->setGeometry(26, (30 + BTNDELETESIZE + 3) / 2 + CONNECTORSIZE, CONNECTORSIZE, CONNECTORSIZE);
	QImage img("./Pictures/button.png");
	img = img.scaled(30, 30);
	label->setPixmap(QPixmap::fromImage(img));
}

void ButtonWidget::mousePressEvent(QMouseEvent *event) {
	BoardComponentWidget::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		input.setValue(1);
		sendValue();
	}
}

void ButtonWidget::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		input.setValue(0);
		sendValue();
	}
}

//ClockWidget::ClockWidget(QWidget *parent, BoardWidget *parentW) : InputWidget(parent, parentW) {
//
//}
//
//void ClockWidget:: mousePressEvent(QMouseEvent *event) {
//	if (isOn == false) {
//		while (1) {
//			Sleep(10000);
//			InputWidget::mousePressEvent(event);
//			isOn = true;
//		}
//	}
//	else {
//		isOn = false;
//	}
//}

OutputWidget::OutputWidget(QWidget *parent, BoardWidget *parentW) : BoardComponentWidget(parent) {
	this->setGeometry(280, 140, 30 + CONNECTORSIZE, 30 + BTNDELETESIZE + 3);
	this->setMouseTracking(true);

	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, 30, 30);
	label->setText("0");
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("background-color: #ffaa39; Font: 13 pt;");

	c = new Connector(this, parentW, "input");
	c->setGeometry(0, (30 + BTNDELETESIZE + 3) / 2 + CONNECTORSIZE, CONNECTORSIZE, CONNECTORSIZE);

	btnDelete->setGeometry(30 - BTNDELETESIZE + CONNECTORSIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &OutputWidget::deleteWidget);
}

void OutputWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(c);
	deleteLater();
}

void OutputWidget::mouseMoveEvent(QMouseEvent *event){
	if (event->buttons() == Qt::LeftButton) {
		if (c->isConnected == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void OutputWidget::getInput(Input input, int n) {
	output.setFormula(input.getName());
	output.setValue(input.getValue());
	label->setText(QString::number(output.getValue()));
	setToolTip(QString::fromStdString(input.getName()));
}

LedWidget::LedWidget(QWidget *parent, BoardWidget *parentW): OutputWidget(parent, parentW) {
	this->setGeometry(280, 140, 40, 40 + BTNDELETESIZE + 10);
	label->setText("");
	label->setGeometry(0, BTNDELETESIZE + 3, 40, 40);
	label->setStyleSheet("background-color: none;");
	img =  QImage("./Pictures/ledU.png");
	img = img.scaled(40,40);
	img2 = QImage("./Pictures/ledL.png");
	img2 = img2.scaled(40, 40);
	label->setPixmap(QPixmap::fromImage(img));
	c->setGeometry(40/2- 5, 40 + BTNDELETESIZE + 7 - CONNECTORSIZE, CONNECTORSIZE, CONNECTORSIZE);
}

void LedWidget::getInput(Input input, int n) {
	OutputWidget::getInput(input, n);
	label->setText("");
	if (output.getValue() == 1) {
		label->setPixmap(QPixmap::fromImage(img2));
	}
	else {
		label->setPixmap(QPixmap::fromImage(img));
	}
}


//----------------------------------------------------GATE WIDGET------------------------------------------------------------//

NotGateWidget::NotGateWidget(QWidget *parent, BoardWidget *parentW, string filename):BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 3 + 10);

	QString imagefile = QString::fromStdString(filename);
	img = QImage(imagefile);
	img = img.scaled(COMPONENTL, COMPONENTW + 10, Qt::KeepAspectRatio);

	label = new QLabel(this);
	label->setGeometry(0, BTNDELETESIZE + 3, COMPONENTL, COMPONENTW + 10);
	label->setPixmap(QPixmap::fromImage(img));

	input = new Connector(this, parentW, "input", 1);
	input->setGeometry(0, (COMPONENTL + BTNDELETESIZE + 3) / 2 + CONNECTORSIZE + 3, CONNECTORSIZE, CONNECTORSIZE);

	output = new Connector(this, parentW, "output");
	output->setGeometry(COMPONENTL - CONNECTORSIZE / 2, (COMPONENTL + BTNDELETESIZE + 3) / 2 + CONNECTORSIZE + 3, CONNECTORSIZE, CONNECTORSIZE);

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &NotGateWidget::deleteWidget);
}

void NotGateWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input->isConnected == false && output->isConnected == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void NotGateWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(input);
	BoardComponentWidget::deleteWidget(output);
	deleteLater();
}

void NotGateWidget::getInput(Input input, int n ) {
	gate.setInput1(input.getValue(), input.getName());
	sendValue();
}

void NotGateWidget::sendValue() {
	if (input->isConnected == true) {
		int val = gate.getOutput();
		string f = gate.getFormula();
		for (int i = 0; i < output->connectedW.size(); i++) {
			Input temp(f, val);
			output->connectedW[i]->getInput(temp);
		}
		setToolTip(QString::fromStdString(f));
	}
	else
		setToolTip("");
}

GateWidget::GateWidget(QWidget *parent, BoardWidget *parentW, string filename, Gate* g): NotGateWidget(parent, parentW, filename) {
	gate = g;

	input->setGeometry(0, 40, CONNECTORSIZE, CONNECTORSIZE);

	input2 = new Connector(this, parentW, "input", 2);
	input2->setGeometry(0, COMPONENTL, CONNECTORSIZE, CONNECTORSIZE);

	connect(btnDelete, &QPushButton::clicked, this, &GateWidget::deleteWidget);
}

void GateWidget::deleteWidget(){
	BoardComponentWidget::deleteWidget(input2);
	NotGateWidget::deleteWidget();
}

void GateWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input2->isConnected == false) {
			NotGateWidget::mouseMoveEvent(event);
		}
	}
}

void GateWidget::getInput(Input input, int n) {
	if (n == 1)
		gate->setInput1(input.getValue(), input.getName());
	else
		gate->setInput2(input.getValue(), input.getName());
	sendValue();
}

void GateWidget::sendValue() {
	if (input->isConnected == true && input2->isConnected == true) {
		int val = gate->getOutput();
		string f = gate->getFormula();
		for (int i = 0; i < output->connectedW.size(); i++) {				
			Input temp(f, val);
			output->connectedW[i]->getInput(temp);
		}
		this->setToolTip(QString::fromStdString(f));
	}
}


//---------------------------------ADDERSUBTRACTOR WIDGETS--------------------------------------------------//
HalfAddWidget::HalfAddWidget(QWidget *parent, BoardWidget *parentW): BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 3);

	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE/2, BTNDELETESIZE + 3, COMPONENTL - CONNECTORSIZE/2, COMPONENTW);
	label->setText("HA");
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("background-color: #ffaa39; Font: 13 pt;");

	input1 = new Connector(this, parentW, "input", 1);
	input1->setGeometry(0, 40, CONNECTORSIZE, CONNECTORSIZE);

	input2 = new Connector(this, parentW, "input", 2);
	input2->setGeometry(0, COMPONENTL, CONNECTORSIZE, CONNECTORSIZE);

	outputS = new Connector(this, parentW, "output");
	outputS->setGeometry(COMPONENTL - CONNECTORSIZE / 2, 40, CONNECTORSIZE, CONNECTORSIZE);
	
	outputC = new Connector(this, parentW, "output");
	outputC->setGeometry(COMPONENTL - CONNECTORSIZE / 2,COMPONENTL, CONNECTORSIZE, CONNECTORSIZE);

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &HalfAddWidget::deleteWidget);

}

void HalfAddWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input1->isConnected == false && input2->isConnected == false && outputC->isConnected == false && outputS->isConnected == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void HalfAddWidget::getInput(Input input, int  n) {
	if (n == 1)
		a.setInput1(input.getValue(), input.getName());
	else if (n == 2)
		a.setInput2(input.getValue(), input.getName());
	sendValue();
}

void HalfAddWidget::sendValue() {
	if (input1->isConnected == true && input2->isConnected == true) {
		Input temp(a.getFormulaCarry(), a.getOutputCarry());
		for (int i = 0; i < outputC->connectedW.size(); i++) {
			outputC->connectedW[i]->getInput(temp);
		}
		Input temp2(a.getFormulaSum(), a.getOutputSum());
		for (int i = 0; i < outputS->connectedW.size(); i++) {
			outputS->connectedW[i]->getInput(temp2);
		}
	}
	setToolTip(QString::fromStdString("S: " + a.getFormulaSum() + "\nC: " + a.getFormulaCarry()));
}

void HalfAddWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(input2);
	BoardComponentWidget::deleteWidget(input1);
	BoardComponentWidget::deleteWidget(outputC);
	BoardComponentWidget::deleteWidget(outputS);
	deleteLater();
}

FullAddWidget::FullAddWidget(QWidget *parent, BoardWidget *parentW): HalfAddWidget(parent, parentW) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE +  13);

	label->setText("FA");
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, COMPONENTL - CONNECTORSIZE / 2, COMPONENTW + 10);

	input1->setGeometry(0, 30, CONNECTORSIZE, CONNECTORSIZE);
	input2->setGeometry(0, 50, CONNECTORSIZE, CONNECTORSIZE);
	
	inputCin = new Connector(this, parentW, "input", 3);
	inputCin->setGeometry(0, 70, CONNECTORSIZE, CONNECTORSIZE);

	connect(btnDelete, &QPushButton::clicked, this, &FullAddWidget::deleteWidget);
}

void FullAddWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(inputCin);
	HalfAddWidget::deleteWidget();
}

void FullAddWidget::mouseMoveEvent(QMouseEvent *event) {
	if (inputCin->isConnected == false)
		HalfAddWidget::mouseMoveEvent(event);
}

void FullAddWidget::getInput(Input input, int n) {
	if (n == 1)
		fa.setInput1(input.getValue(), input.getName());
	else if (n == 2)
		fa.setInput2(input.getValue(), input.getName());
	else if (n == 3)
		fa.setInputCin(input.getValue(), input.getName());
	sendValue();
}

void FullAddWidget::sendValue() {
	if (input1->isConnected == true && input2->isConnected == true && inputCin->isConnected == true) {
		Input temp(fa.getFormulaCarry(), fa.getOutputCarry());
		for (int i = 0; i < outputC->connectedW.size(); i++) {
			outputC->connectedW[i]->getInput(temp);
		}
		Input temp2(fa.getFormulaSum(), fa.getOutputSum());
		for (int i = 0; i < outputS->connectedW.size(); i++) {
			outputS->connectedW[i]->getInput(temp2);
		}
		setToolTip(QString::fromStdString("S: " + fa.getFormulaSum() + "\nC: " + fa.getFormulaCarry()));
	}
}

HalfSubWidget::HalfSubWidget(QWidget *parent, BoardWidget *parentW) :BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 13);
	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, COMPONENTL - CONNECTORSIZE / 2, COMPONENTW);
	label->setText("HS");
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("background-color: #ffaa39; Font: 13 pt;");

	input1 = new Connector(this, parentW, "input", 1);
	input1->setGeometry(0, 40, CONNECTORSIZE, CONNECTORSIZE);

	input2 = new Connector(this, parentW, "input", 2);
	input2->setGeometry(0, COMPONENTL, CONNECTORSIZE, CONNECTORSIZE);

	outputD = new Connector(this, parentW, "output");
	outputD->setGeometry(COMPONENTL - CONNECTORSIZE / 2, 40, CONNECTORSIZE, CONNECTORSIZE);

	outputB = new Connector(this, parentW, "output");
	outputB->setGeometry(COMPONENTL - CONNECTORSIZE / 2, COMPONENTL, CONNECTORSIZE, CONNECTORSIZE);

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &HalfSubWidget::deleteWidget);

}

void HalfSubWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input1->isConnected == false && input2->isConnected == false && outputD->isConnected == false && outputB->isConnected == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}

}

void HalfSubWidget::getInput(Input input, int n) {
	if (n == 1)
		hs.setInput1(input.getValue(), input.getName());
	else if (n == 2)
		hs.setInput2(input.getValue(), input.getName());
	sendValue();
}

void HalfSubWidget::sendValue() {
	if (input1->isConnected == true && input2->isConnected == true) {
		Input temp(hs.getFormulaDiff(), hs.getOutputDiff());
		for (int i = 0; i < outputD->connectedW.size(); i++) {
			outputD->connectedW[i]->getInput(temp);
		}
		Input temp2(hs.getFormulaBorrow(), hs.getOutputBorrow());
		for (int i = 0; i < outputB->connectedW.size(); i++) {
			outputB->connectedW[i]->getInput(temp2);
		}
		setToolTip(QString::fromStdString("D: " + hs.getFormulaDiff() + "\nB: " + hs.getFormulaBorrow()));
	}
}

void HalfSubWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(input1);
	BoardComponentWidget::deleteWidget(input2);
	BoardComponentWidget::deleteWidget(outputD);
	BoardComponentWidget::deleteWidget(outputB);
	deleteLater();
}

FullSubWidget::FullSubWidget(QWidget *parent, BoardWidget *parentW) : HalfSubWidget(parent, parentW) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 13);

	label->setText("FS");
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, COMPONENTL - CONNECTORSIZE / 2, COMPONENTW + 10);

	input1->setGeometry(0, 30, CONNECTORSIZE, CONNECTORSIZE);
	input2->setGeometry(0, 50, CONNECTORSIZE, CONNECTORSIZE);

	inputBin = new Connector(this, parentW, "input", 3);
	inputBin->setGeometry(0, 70, CONNECTORSIZE, CONNECTORSIZE);

	connect(btnDelete, &QPushButton::clicked, this, &FullSubWidget::deleteWidget);
}

void FullSubWidget:: mouseMoveEvent(QMouseEvent *event) {
	if (inputBin->isConnected == false)
		HalfSubWidget::mouseMoveEvent(event);
}

void FullSubWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(inputBin);
	HalfSubWidget::deleteWidget();
}

void FullSubWidget::getInput(Input input, int n) {
	if (n == 1)
		fs.setInput1(input.getValue(), input.getName());
	else if (n == 2)
		fs.setInput2(input.getValue(), input.getName());
	else if (n == 3)
		fs.setInputBin(input.getValue(), input.getName());
	sendValue();
}

void FullSubWidget::sendValue() {
	if (input1->isConnected == true && input2->isConnected == true && inputBin->isConnected == true) {
		Input temp(fs.getFormulaDiff(), fs.getOutputDiff());
		for (int i = 0; i < outputD->connectedW.size(); i++) {
			outputD->connectedW[i]->getInput(temp);
		}
		Input temp2(fs.getFormulaBorrow(), fs.getOutputBorrow());
		for (int i = 0; i < outputB->connectedW.size(); i++) {
			outputB->connectedW[i]->getInput(temp2);
		}
		setToolTip(QString::fromStdString("D: " + fs.getFormulaDiff() + "\nB: " + fs.getFormulaBorrow()));
	}
}

//--------------------------------------------------CODE CONVERTER WIDGET----------------------------------------------------//

DecoderWidget::DecoderWidget(QWidget *parent, BoardWidget *parentW) : BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 25);

	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, COMPONENTL - CONNECTORSIZE / 2, COMPONENTW + 25);
	label->setText("2-4 Dec");
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("background-color: #ffaa39; Font: 13 pt;");

	input1 = new Connector(this, parentW, "input", 1);
	input1->setGeometry(0, 35, CONNECTORSIZE, CONNECTORSIZE);
	
	input2 = new Connector(this, parentW, "input", 2);
	input2->setGeometry(0, 55, CONNECTORSIZE, CONNECTORSIZE);

	enable = new Connector(this, parentW, "input", 3);
	enable->setGeometry(0, 75, CONNECTORSIZE, CONNECTORSIZE);

	int space = 25;
	for (int i = 0; i < 4; i++) {
		Connector *temp = new Connector(this, parentW, "output", i);
		temp->setGeometry(COMPONENTL - CONNECTORSIZE / 2, space, CONNECTORSIZE, CONNECTORSIZE);
		output.push_back(temp);
		space += 20;
	}

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &DecoderWidget::deleteWidget);
}

bool DecoderWidget::checkOutputConnect() {
	for (int i = 0; i < output.size(); i++) {
		if (output[i]->isConnected == true) {
			return true;
		}
	}
	return false;
}

void DecoderWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input1->isConnected == false && input2->isConnected == false && enable->isConnected == false && checkOutputConnect() == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void DecoderWidget::getInput(Input input, int n) {
	if (n == 1)
		d.setInput1(input.getValue(), input.getName());
	else if (n == 2)
		d.setInput2(input.getValue(), input.getName());
	else if (n == 3)
		d.setEnable(input.getValue(), input.getName());
	sendValue();
}

void DecoderWidget::sendValue() {
	if (input1->isConnected == true && input2->isConnected == true && enable->isConnected == true) {
		string f = "";
		vector<int> val = d.getOutput();
		vector<string> form = d.getFormula();
		for (int i = 0; i < output.size(); i++) {
			Input temp(form[i], val[i]);
			f += form[i] + "\n";
			for (int j = 0; j < output[i]->connectedW.size(); j++) {
				output[i]->connectedW[j]->getInput(temp);
			}
		}
		setToolTip(QString::fromStdString(f));
	}
}

void DecoderWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(input1);
	BoardComponentWidget::deleteWidget(input2);
	BoardComponentWidget::deleteWidget(enable);
	for (int i = 0; i < output.size(); i++) {
		BoardComponentWidget::deleteWidget(output[i]);
	}
	deleteLater();
}

EncoderWidget::EncoderWidget(QWidget *parent, BoardWidget *parentW) : BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 25);

	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, COMPONENTL - CONNECTORSIZE / 2, COMPONENTW + 25);
	label->setText("4-2 Enc");
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("background-color: #ffaa39; Font: 13 pt;");

	int space = 25;
	for (int i = 0; i < 4; i++) {
		Connector *temp = new Connector(this, parentW, "input", i);
		temp->setGeometry(0, space, CONNECTORSIZE, CONNECTORSIZE);
		inputs.push_back(temp);
		space += 20;
	}
	
	space = 50;
	for (int i = 0; i < 2; i++) {
		Connector *temp2 = new Connector(this, parentW, "output");
		temp2->setGeometry(COMPONENTL - CONNECTORSIZE / 2, space, CONNECTORSIZE, CONNECTORSIZE);
		output.push_back(temp2);
		space += 20;
	}

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &EncoderWidget::deleteWidget);
}

bool EncoderWidget:: checkInputConnect() {
	for (int i = 0; i < inputs.size(); i++) {
		if (inputs[i]->isConnected == true)
			return true;
	}
	return false;
}

void EncoderWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (output[0]->isConnected == false && output[1]->isConnected == false && checkInputConnect() == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void EncoderWidget::getInput(Input input, int n) {
	e.setInput(input.getValue(), input.getName(), n );
	sendValue();
}

void EncoderWidget::sendValue() {
	if (inputs[0]->isConnected == true && inputs[1]->isConnected == true
		&& inputs[2]->isConnected == true && inputs[3]->isConnected == true) {
		string f = "";
		vector<int> val = e.getOutput();
		vector<string> form = e.getFormula();
		for (int i = 0; i < output.size(); i++) {
			Input temp(form[i], val[i]);
			f += form[i] + "\n";
			for (int j = 0; j < output[i]->connectedW.size(); j++) {
				output[i]->connectedW[j]->getInput(temp);
			}
		}
		setToolTip(QString::fromStdString(f));
	}
}

void EncoderWidget::deleteWidget() {
	for (int i = 0; i < inputs.size(); i++)
		BoardComponentWidget::deleteWidget(inputs[i]);
	for (int i = 0; i < output.size(); i++)
		BoardComponentWidget::deleteWidget(output[i]);
	deleteLater();
}

MultiplexerWidget::MultiplexerWidget(QWidget *parent, BoardWidget *parentW) : BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 25 + CONNECTORSIZE/2);

	img = QImage("./Pictures/mux.png");
	img = img.scaled(COMPONENTL + 10, COMPONENTW + 10, Qt::KeepAspectRatio);

	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE/2, BTNDELETESIZE + 3, COMPONENTL, COMPONENTW + 25);
	label->setPixmap(QPixmap::fromImage(img));

	input1 = new Connector(this, parentW, "input", 1);
	input2 = new Connector(this, parentW, "input", 2);
	select = new Connector(this, parentW, "input", 3);
	output = new Connector(this, parentW, "output");

	input1->setGeometry(0, 45, CONNECTORSIZE, CONNECTORSIZE);
	input2->setGeometry(0, 70, CONNECTORSIZE, CONNECTORSIZE);
	select->setGeometry(COMPONENTL/ 2 , COMPONENTW + BTNDELETESIZE - CONNECTORSIZE / 2 + 13, CONNECTORSIZE, CONNECTORSIZE);
	output->setGeometry(COMPONENTL - 10, (COMPONENTW + BTNDELETESIZE + 25 + CONNECTORSIZE / 2)/2 + 3, CONNECTORSIZE, CONNECTORSIZE);

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &MultiplexerWidget::deleteWidget);
}

void MultiplexerWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input1->isConnected == false && input2->isConnected == false && select->isConnected == false && output->isConnected == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void MultiplexerWidget::sendValue() {
	if (input1->isConnected == true && input2->isConnected == true && select->isConnected == true && output->isConnected == true) {
		for (int i = 0; i < output->connectedW.size(); i++) {
			Input temp(m.getFormula(), m.getOutput());
			output->connectedW[i]->getInput(temp);
		}
		setToolTip(QString::fromStdString(m.getFormula()));
	}
}

void MultiplexerWidget::getInput(Input input, int n) {
	if (n == 1)
		m.setInput1(input.getValue(), input.getName());
	else if (n == 2)
		m.setInput2(input.getValue(), input.getName());
	else
		m.setSelect(input.getValue(), input.getName());
	sendValue();
}

void MultiplexerWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(input1);
	BoardComponentWidget::deleteWidget(input2);
	BoardComponentWidget::deleteWidget(select);
	BoardComponentWidget::deleteWidget(output);
	deleteLater();
}

DemultiplexerWidget::DemultiplexerWidget(QWidget *parent, BoardWidget *parentW) : BoardComponentWidget(parent) {
	this->setGeometry(280, 140, COMPONENTL + CONNECTORSIZE, COMPONENTW + BTNDELETESIZE + 25 + CONNECTORSIZE / 2);

	img = QImage("./Pictures/demux.png");
	img = img.scaled(COMPONENTL + 10, COMPONENTW + 20, Qt::KeepAspectRatio);

	label = new QLabel(this);
	label->setGeometry(CONNECTORSIZE / 2, BTNDELETESIZE + 3, COMPONENTL + 10, COMPONENTW + 35);
	label->setPixmap(QPixmap::fromImage(img));

	input = new Connector(this, parentW, "input", 1);
	input->setGeometry(0, 60, CONNECTORSIZE, CONNECTORSIZE);
	select2 = new Connector(this, parentW, "input", 3);
	select2->setGeometry(COMPONENTL / 2 + 10, COMPONENTW + BTNDELETESIZE - CONNECTORSIZE / 2 + 25, CONNECTORSIZE, CONNECTORSIZE);
	select1 = new Connector(this, parentW, "input", 2);
	select1->setGeometry(COMPONENTL / 2 - 10, COMPONENTW + BTNDELETESIZE - CONNECTORSIZE / 2 + 18, CONNECTORSIZE, CONNECTORSIZE);
	
	int space = 30;
	for (int i = 0; i < 4; i++) {
		Connector *temp = new Connector(this, parentW, "output");
		temp->setGeometry(COMPONENTL - 5, space, CONNECTORSIZE, CONNECTORSIZE);
		output.push_back(temp);
		space += 20;
	}

	btnDelete->setGeometry(COMPONENTL + CONNECTORSIZE - BTNDELETESIZE, 0, BTNDELETESIZE - 3, BTNDELETESIZE);
	connect(btnDelete, &QPushButton::clicked, this, &DemultiplexerWidget::deleteWidget);
}

bool DemultiplexerWidget:: checkOutputConnect() {
	for (int i = 0; i < output.size(); i++) {
		if (output[i]->isConnected == true)
			return true;
	}
	return false;
}

void DemultiplexerWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		if (input->isConnected == false && select2->isConnected == false && select1->isConnected == false && checkOutputConnect() == false) {
			BoardComponentWidget::mouseMoveEvent(event);
		}
	}
}

void DemultiplexerWidget::sendValue() {
	if (input->isConnected == true && select2->isConnected == true && select1->isConnected == true) {
		string f = "";
		vector<int> val = dm.getOutput();
		vector<string> form = dm.getFormula();
		for (int i = 0; i < output.size(); i++) {
			Input temp(form[i], val[i]);
			f += form[i] + "\n";
			for (int j = 0; j < output[i]->connectedW.size(); j++) {
				output[i]->connectedW[j]->getInput(temp);
			}
		}
		setToolTip(QString::fromStdString(f));
	}
	else
		setToolTip("");
}

void DemultiplexerWidget::getInput(Input input, int n) {
	if (n == 1)
		dm.setInput(input.getValue(), input.getName());
	else if (n == 2)
		dm.setSelect1(input.getValue(), input.getName());
	else
		dm.setSelect2(input.getValue(), input.getName());
	sendValue();
}

void DemultiplexerWidget::deleteWidget() {
	BoardComponentWidget::deleteWidget(input);
	BoardComponentWidget::deleteWidget(select1);
	BoardComponentWidget::deleteWidget(select2);
	for (int i = 0; i < output.size(); i++) {
		BoardComponentWidget::deleteWidget(output[i]);
	}
	deleteLater();
}

//--------------------------------------------------CUSTOM LABEL---------------------------------------------------------//

CreateComponentWidget::CreateComponentWidget(QLabel *ti, QLabel *te, QWidget *parent, QWidget *pC, BoardWidget *pW, string t, string img) : QLabel(parent) {
	this->setGeometry(0,0, 40,40);
	this->setStyleSheet("background-color: white; border: 1px solid #b7b6b5;");
	readDescription();

	type = t;
	filename = img;
	parentC = pC;
	parentW = pW;
	title = ti;
	text = te;
	
	if (filename == "") {
		if (type == "Switch" || type == "Output") {
			this->setText("0");
		}
		else if (type == "HalfAdder") {
			this->setText("HA");
		}
		else if (type == "HalfSubtractor") {
			this->setText("HS");
		}
		else if (type == "FullAdder") {
			this->setText("FA");
		}
		else if (type == "FullSubtractor") {
			this->setText("FS");
		}
		else if (type == "Encoder") {
			this->setText("Enc");
		}
		else if (type == "Decoder") {
			this->setText("Dec");
		}
		this->setAlignment(Qt::AlignCenter);
		this->setStyleSheet("background-color: #ffaa39; border: 1px solid #b7b6b5;");
	}
	else {
		QString imagefile = QString::fromStdString(filename);
		QImage image = QImage(imagefile);
		image = image.scaled(40, 40, Qt::KeepAspectRatio);
		this->setPixmap(QPixmap::fromImage(image));
	}

}

void CreateComponentWidget::mousePressEvent(QMouseEvent *event) {
	BoardComponentWidget *bW = NULL;
	if (type == "Switch") {
		InputWidget *iw = new InputWidget(parentC, parentW);
		InputName *n = new InputName(&names, iw);
		n->setWindowModality(Qt::ApplicationModal);
		if (n->exec() == QDialog::Rejected)
			delete iw;
		else
			bW = iw;
	}
	else if (type == "Output")
		bW = new OutputWidget(parentC, parentW);
	else if (type == "NotGate")
		bW = new NotGateWidget(parentC, parentW);
	else if (type == "AndGate") {
		AndGate *a = new AndGate();
		bW = new GateWidget(parentC, parentW, "./Pictures/andGate.png", a);
	}
	else if (type == "OrGate") {
		OrGate *o = new OrGate();
		bW = new GateWidget(parentC, parentW, "./Pictures/orGate.png", o);
	}
	else if (type == "XorGate") {
		XorGate *x = new XorGate();
		bW = new GateWidget(parentC, parentW, "./Pictures/xorGate.png", x);
	}
	else if (type == "NandGate") {
		NandGate *n = new NandGate();
		bW = new GateWidget(parentC, parentW, "./Pictures/nandGate.png", n);
	}
	else if (type == "NorGate") {
		NorGate *nor = new NorGate();
		bW = new GateWidget(parentC, parentW, "./Pictures/norGate.png", nor);
	}
	else if (type == "XnorGate") {
		XnorGate *xn = new XnorGate();
		bW = new GateWidget(parentC, parentW, "./Pictures/xnorGate.png", xn);
	}
	else if (type == "HalfAdder")
		bW = new HalfAddWidget(parentC, parentW);
	else if (type == "HalfSubtractor")
		bW = new HalfSubWidget(parentC, parentW);
	else if (type == "FullAdder")
		bW = new FullAddWidget(parentC, parentW);
	else if (type == "FullSubtractor")
		bW = new FullSubWidget(parentC, parentW);
	else if (type == "Decoder")
		bW = new DecoderWidget(parentC, parentW);
	else if (type == "Encoder")
		bW = new EncoderWidget(parentC, parentW);
	else if (type == "Multiplexer")
		bW = new MultiplexerWidget(parentC, parentW);
	else if (type == "Demultiplexer")
		bW = new DemultiplexerWidget(parentC, parentW);
	else if (type == "LED")
		bW = new LedWidget(parentC, parentW);
	else if (type == "Button")
		bW = new ButtonWidget(parentC, parentW);

	if (bW != NULL)
		bW->setVisible(true);
}

void CreateComponentWidget::enterEvent(QEvent *event) {
	setStyleSheet("background-color:#b7b6b5;");
	title->setText(QString::fromStdString(type));
	text->setText(QString::fromStdString(descrip[type]));
}

void CreateComponentWidget::leaveEvent(QEvent *event) {
	if (filename == "")
		this->setStyleSheet("background-color: #ffaa39; border: 1px solid #b7b6b5;");
	else
		setStyleSheet("background-color:white; border: 1px solid #b7b6b5;");
	title->setText(QString::fromStdString("CONNECTED"));
	text->setText(QString::fromStdString(" .    .\n   |  \n   ___"));
}

InputName::InputName(vector<string>* names, InputWidget *&i) : QDialog() {
	this->setFixedHeight(130);
	this->setFixedWidth(250);
	this->setStyleSheet("background-color: #717fac;");
	nameList = names;
	inputW = i;

	lbl = new QLabel(this);
	lbl->setGeometry(0, 20, 250, 20);
	lbl->setText("Enter the variable name for this input:");
	lbl->setAlignment(Qt::AlignCenter);
	lbl->setStyleSheet("background-color: #717fac; color: white;");

	nameQLine = new QLineEdit(this);
	nameQLine->setGeometry(75, 55, 100, 20);
	nameQLine->setStyleSheet("background-color: white;");
	
	ok = new QPushButton(this);
	ok->setGeometry(60, 90, 51, 23);
	ok->setText("Ok");
	ok->setStyleSheet("background-color: #ffaa39; border:none; selection-background-color: #e69830");
	connect(ok, &QPushButton::clicked, this, &InputName::okPressed);

	cancel = new QPushButton(this);
	cancel->setGeometry(140, 90, 51, 23);
	cancel->setText("Cancel");
	cancel->setStyleSheet("background-color: #ffaa39; border:none;");
	connect(cancel, &QPushButton::clicked, this, &InputName::cancelPressed);
}

bool InputName::checkSameName(string n) {
	char temp = n[0];
	char temp2;
	for (int i = 0; i < nameList->size(); i++) {
		temp2 = (*nameList)[i][0];
		if (toupper(temp) == toupper(temp2))
			return true;
	}
	return false;
}

void InputName::okPressed() {
	string in = getName();
	if (in.length() != 1) {
		lbl->setText("The variable name should be only one letter.");
	}
	else if (in.find(" ") != string::npos ) {
		lbl->setText("No spaces are allowed.");
	}
	else if (!isalpha(in[0])) {
		lbl->setText("Only alphabet letters are allowed.");
	}
	else if (checkSameName(in) == true) {
		lbl->setText("This name has already been used.");
	}
	else {
		inputW->input.setName(in);
		inputW->setToolTip(QString::fromStdString(inputW->input.getName()));
		nameList->push_back(in);
		accept(); 
	}
}

