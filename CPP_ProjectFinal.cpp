
#include <QWidget>
#include <Qlabel.h>
#include "CPP_ProjectFinal.h"
#include "CustomWidgets.hpp"
#include "OtherComponents.hpp"
#include "Board.hpp"

const int WSIZE = 40;

CPP_ProjectFinal::CPP_ProjectFinal(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(ui.titlePage->size());
	QWidget *q(this);
	BoardWidget *board = new BoardWidget(ui.BoardPage);
	board->setGeometry(180, 10, 881,501);

	//initialize title page
	ui.BoardPage->setVisible(false);
	ui.titlePage->setGeometry(0, 0, ui.titlePage->width(), ui.titlePage->height());
	connect(ui.startBtn, &QPushButton::clicked, this, &CPP_ProjectFinal::openMain);
	QImage img("./Pictures/title.png");
	img = img.scaled(ui.titlePage->width(), ui.titlePage->height());
	ui.bgImg->setPixmap(QPixmap::fromImage(img));
	ui.bgImg->lower();

	QLabel *bg = new QLabel(board);
	bg->setGeometry(0, 0, board->width(), board->height());
	img = QImage("./Pictures/bg2.png");

	bg->setPixmap(QPixmap::fromImage(img));
	bg->lower();
	ui.lblDescT->setText("CONNECTED");
	ui.lblDesc->setText(" .    .\n   |  \n   ___");

	ui.frame->setStyleSheet("background-color: #e2e1df;");
	CreateComponentWidget* inputLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Switch");
	inputLbl->setGeometry(10,40, WSIZE, WSIZE);
	CreateComponentWidget* btnLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Button", "./Pictures/button.png");
	btnLbl->setGeometry(52, 40, WSIZE, WSIZE);
	CreateComponentWidget* outputLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Output");
	outputLbl->setGeometry(10, 120, WSIZE, WSIZE);
	CreateComponentWidget* ledLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "LED", "./Pictures/ledL.png");
	ledLbl->setGeometry(52, 120, WSIZE, WSIZE);
	CreateComponentWidget* notGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "NotGate", "./Pictures/notGateC.png");
	notGateLbl->setGeometry(10, 200, WSIZE, WSIZE);
	CreateComponentWidget* orGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "OrGate", "./Pictures/orGate.png");
	orGateLbl->setGeometry(52, 200, WSIZE, WSIZE);
	CreateComponentWidget* andGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "AndGate", "./Pictures/andGateC.png");
	andGateLbl->setGeometry(94, 200, WSIZE, WSIZE);
	CreateComponentWidget* xorGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "XorGate", "./Pictures/xorGateC.png");
	xorGateLbl->setGeometry(10, 242, WSIZE, WSIZE);
	CreateComponentWidget* nandGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "NandGate", "./Pictures/nandGateC.png");
	nandGateLbl->setGeometry(52, 242, WSIZE, WSIZE);
	CreateComponentWidget* norGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "NorGate", "./Pictures/norGateC.png");
	norGateLbl->setGeometry(94, 242, WSIZE, WSIZE);
	CreateComponentWidget* xnorGateLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "XnorGate", "./Pictures/xnorGateC.png");
	xnorGateLbl->setGeometry(10, 284, WSIZE, WSIZE);
	CreateComponentWidget* haLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "HalfAdder");
	haLbl->setGeometry(10, 360, WSIZE, WSIZE);
	CreateComponentWidget* hsLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "HalfSubtractor");
	hsLbl->setGeometry(52, 360, WSIZE, WSIZE);
	CreateComponentWidget* faLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "FullAdder");
	faLbl->setGeometry(10, 402, WSIZE, WSIZE);
	CreateComponentWidget* fsLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "FullSubtractor");
	fsLbl->setGeometry(52, 402, WSIZE, WSIZE);
	CreateComponentWidget* encoderLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Encoder");
	encoderLbl->setGeometry(10, 480, WSIZE, WSIZE);
	CreateComponentWidget* decoderLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Decoder");
	decoderLbl->setGeometry(52, 480, WSIZE, WSIZE);
	CreateComponentWidget* muxLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Multiplexer", "./Pictures/muxC.png");
	muxLbl->setGeometry(10, 522, WSIZE, WSIZE);
	CreateComponentWidget* demuxLbl = new CreateComponentWidget(ui.lblDescT, ui.lblDesc, ui.frame, board, board, "Demultiplexer", "./Pictures/demuxC.png");
	demuxLbl->setGeometry(52, 522, WSIZE, WSIZE);

}

void CPP_ProjectFinal::openMain() {
	ui.titlePage->setVisible(false);
	ui.BoardPage->setVisible(true);
	this->setFixedSize(ui.BoardPage->size());
	this->setGeometry(
		QStyle::alignedRect(
			Qt::LeftToRight,
			Qt::AlignCenter,
			this->size(),
			qApp->desktop()->availableGeometry()
		)
	);
}
