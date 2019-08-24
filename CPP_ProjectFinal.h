#pragma once

#include <QtWidgets/QWidget>
#include "ui_CPP_ProjectFinal.h"

class CPP_ProjectFinal : public QWidget
{
	Q_OBJECT

public:
	CPP_ProjectFinal(QWidget *parent = Q_NULLPTR);

private:
	Ui::CPP_ProjectFinalClass ui;
	
private slots:
	void openMain();
};
