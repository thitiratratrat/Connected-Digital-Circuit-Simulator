#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP
#include <QtWidgets>
#include <Qlabel.h>
#include <QImage>
#include <qwidget.h>
#include <QPushButton.h>
#include <QLineEdit.h>
#include <stdlib.h>
#include "CPP_ProjectFinal.h"
#include "OtherComponents.hpp"
#include <string>

class Connector;

class BoardComponentWidget : public QWidget {
public:
	BoardComponentWidget(QWidget *parent = 0);
	virtual void getInput(Input input, int n = 0) {};
	virtual void sendValue() {};
	virtual void deleteWidget(Connector *c);

protected:
	QLabel *label;
	QPushButton *btnDelete;
	QPoint mousemoved;
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);	

};

class BoardWidget : public QWidget {
public:
	BoardWidget(QWidget *parent = 0) : QWidget(parent) { setMouseTracking(true); clickedWidget = NULL; clickedWidget2 = NULL; }
	Board<Input> board;
	Connector *clickedWidget;
	Connector *clickedWidget2;
};

class WireWidget : public QWidget {
public:
	WireWidget(QWidget *parent = 0);
	Connector *input; //shouldn't be draggable
	Connector *output; //should be draggable
	QLabel *label;
	QLabel *labelD;
	//Wire<Gate*, Gate*>* wire;
	QPushButton *btnDelete;
	void getInput(Input input);
	void sendValue(Input input);
private:
	void mousePressEvent(QMouseEvent *event) override;
	string formula;

public slots:
	void deleteWire();
};


class InputWidget : public BoardComponentWidget {
public:
	InputWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	Connector *c;
	void sendValue();
	Input input;
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public slots:
	void deleteWidget();
};

class ButtonWidget : public InputWidget {
public:
	ButtonWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
private:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

//class ClockWidget : public InputWidget {
//public:
//	ClockWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
//private:
//	bool isOn;
//	void mousePressEvent(QMouseEvent *event);
//};


class OutputWidget : public BoardComponentWidget {
public:
	OutputWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	virtual void getInput(Input input, int n = 0);
	Connector *c;
protected:
	Output output;
	void mouseMoveEvent(QMouseEvent *event);
private slots:
	void deleteWidget();
};

class LedWidget : public OutputWidget {
public:
	LedWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void getInput(Input input, int n = 0);
private:
	QImage img;
	QImage img2;
};

class NotGateWidget : public BoardComponentWidget{
public:
	NotGateWidget(QWidget *parent = 0, BoardWidget *parentW = 0, string filename = "notGate.png");
	void mouseMoveEvent(QMouseEvent *event);
	virtual void getInput(Input input, int n = 0);
	virtual void sendValue();
private:
	NotGate gate;
protected:
	Connector *input;
	Connector *output;
	QImage img;
protected slots:
	virtual void deleteWidget();
};


class GateWidget : public NotGateWidget {
public:
	GateWidget(QWidget *parent = 0, BoardWidget *parentW = 0, string filename = "", Gate* g = NULL);
	void mouseMoveEvent(QMouseEvent *event);
	void getInput(Input input, int n = 0);
	void sendValue();
private:
	Gate* gate;
	Connector *input2;
private slots:
	void deleteWidget();

};

class HalfAddWidget: public BoardComponentWidget {
public:
	HalfAddWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void getInput(Input input, int n = 0);
	virtual void sendValue();
private:
	HalfAdder a;
protected:
	Connector *input1;
	Connector *input2;
	Connector *outputC;
	Connector *outputS;
protected slots:
	virtual void deleteWidget();
};

class FullAddWidget : public HalfAddWidget {
public:
	FullAddWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void mouseMoveEvent(QMouseEvent *event);
	void getInput(Input input, int n = 0);
	void sendValue();
private:
	FullAdder fa;
	Connector *inputCin;
private slots:
	void deleteWidget();

};

class HalfSubWidget : public BoardComponentWidget {
public:
	HalfSubWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void getInput(Input input, int n = 0);
	virtual void sendValue();
private:
	HalfSubtractor hs;
protected:
	Connector *input1;
	Connector *input2;
	Connector *outputD;
	Connector *outputB;
protected slots:
	virtual void deleteWidget();
};

class FullSubWidget : public HalfSubWidget {
public:
	FullSubWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void mouseMoveEvent(QMouseEvent *event);
	void getInput(Input input, int n = 0);
	void sendValue();
private:
	FullSubtractor fs;
	Connector *inputBin;
private slots:
	void deleteWidget();
};

class DecoderWidget : public BoardComponentWidget {
public:
	DecoderWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void mouseMoveEvent(QMouseEvent *event);
	void sendValue();
	void getInput(Input input, int n = 0);
private:
	Decoder d;
	Connector *input1;
	Connector *input2;
	Connector *enable;
	vector<Connector*> output;
	bool checkOutputConnect();
	
private slots:
	void deleteWidget();
};

class EncoderWidget : public BoardComponentWidget {
public:
	EncoderWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void mouseMoveEvent(QMouseEvent *event);
	void sendValue();
	void getInput(Input input, int n = 0);
private:
	Encoder e;
	vector<Connector*> inputs;
	vector<Connector*> output;
	bool checkInputConnect();
private slots:
	void deleteWidget();
};

class MultiplexerWidget : public BoardComponentWidget {
public:
	MultiplexerWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void mouseMoveEvent(QMouseEvent *event);
	void sendValue();
	void getInput(Input input, int n = 0);
private:
	QImage img;
	Multiplexer m;
	Connector *input1;
	Connector *input2;
	Connector *select;
	Connector *output;
private slots:
	void deleteWidget();
	
};

class DemultiplexerWidget:public BoardComponentWidget {
public:
	DemultiplexerWidget(QWidget *parent = 0, BoardWidget *parentW = 0);
	void mouseMoveEvent(QMouseEvent *event);
	void sendValue();
	void getInput(Input input, int n = 0);
private:
	QImage img;
	Demultiplexer dm;
	Connector *input;
	Connector *select2;
	Connector *select1;
	vector<Connector*> output;
	bool checkOutputConnect();
private slots:
	void deleteWidget();

};

class CreateComponentWidget : public QLabel {
public:
	CreateComponentWidget(QLabel *ti, QLabel *te, QWidget *parent = 0, QWidget *pC = 0, BoardWidget *pW = 0, string t = "", string img = "");
	void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
private:
	string type;
	QWidget *parentC;
	BoardWidget *parentW;
	string filename;
	QLabel *text;
	QLabel *title;
};

class InputName : public QDialog {
public:
	InputName(vector<string>* names, InputWidget *&i);
	string getName() { return nameQLine->text().toStdString(); }
	void okPressed();
	void cancelPressed() { reject(); };
	vector<string>* nameList;
	QLineEdit *nameQLine;
private:
	InputWidget* inputW;
	QLabel *lbl;	
	QPushButton *ok;
	QPushButton *cancel;
	bool checkSameName(string n);

};

#endif