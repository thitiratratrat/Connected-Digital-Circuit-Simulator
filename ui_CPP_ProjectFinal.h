/********************************************************************************
** Form generated from reading UI file 'CPP_ProjectFinal.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPP_PROJECTFINAL_H
#define UI_CPP_PROJECTFINAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPP_ProjectFinalClass
{
public:
    QWidget *BoardPage;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_13;
    QLabel *label_18;
    QLabel *lblDescT;
    QLabel *lblDesc;
    QWidget *titlePage;
    QPushButton *startBtn;
    QLabel *bgImg;

    void setupUi(QWidget *CPP_ProjectFinalClass)
    {
        if (CPP_ProjectFinalClass->objectName().isEmpty())
            CPP_ProjectFinalClass->setObjectName(QString::fromUtf8("CPP_ProjectFinalClass"));
        CPP_ProjectFinalClass->resize(1082, 598);
        BoardPage = new QWidget(CPP_ProjectFinalClass);
        BoardPage->setObjectName(QString::fromUtf8("BoardPage"));
        BoardPage->setGeometry(QRect(0, 0, 1081, 601));
        frame = new QFrame(BoardPage);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 161, 581));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 131, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Tw Cen MT Condensed"));
        font.setPointSize(14);
        label->setFont(font);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 90, 131, 20));
        label_2->setFont(font);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 170, 131, 20));
        label_5->setFont(font);
        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 330, 131, 20));
        label_13->setFont(font);
        label_18 = new QLabel(frame);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 450, 131, 20));
        label_18->setFont(font);
        lblDescT = new QLabel(BoardPage);
        lblDescT->setObjectName(QString::fromUtf8("lblDescT"));
        lblDescT->setGeometry(QRect(180, 520, 131, 20));
        lblDescT->setFont(font);
        lblDesc = new QLabel(BoardPage);
        lblDesc->setObjectName(QString::fromUtf8("lblDesc"));
        lblDesc->setGeometry(QRect(180, 539, 881, 41));
        titlePage = new QWidget(CPP_ProjectFinalClass);
        titlePage->setObjectName(QString::fromUtf8("titlePage"));
        titlePage->setGeometry(QRect(10, 610, 481, 301));
        startBtn = new QPushButton(titlePage);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setGeometry(QRect(180, 250, 101, 23));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tw Cen MT Condensed"));
        font1.setPointSize(11);
        startBtn->setFont(font1);
        startBtn->setMouseTracking(false);
        startBtn->setStyleSheet(QString::fromUtf8("background-color: #ffaa39; border:none;"));
        startBtn->setFlat(false);
        bgImg = new QLabel(titlePage);
        bgImg->setObjectName(QString::fromUtf8("bgImg"));
        bgImg->setGeometry(QRect(0, 0, 481, 301));

        retranslateUi(CPP_ProjectFinalClass);

        QMetaObject::connectSlotsByName(CPP_ProjectFinalClass);
    } // setupUi

    void retranslateUi(QWidget *CPP_ProjectFinalClass)
    {
        CPP_ProjectFinalClass->setWindowTitle(QApplication::translate("Connected", "Connected", nullptr));
        label->setText(QApplication::translate("CPP_ProjectFinalClass", "INPUT", nullptr));
        label_2->setText(QApplication::translate("CPP_ProjectFinalClass", "OUTPUT", nullptr));
        label_5->setText(QApplication::translate("CPP_ProjectFinalClass", "GATE", nullptr));
        label_13->setText(QApplication::translate("CPP_ProjectFinalClass", "ADDER SUBTRACTOR", nullptr));
        label_18->setText(QApplication::translate("CPP_ProjectFinalClass", "CODE CONVERTER", nullptr));
        lblDescT->setText(QString());
        lblDesc->setText(QString());
        startBtn->setText(QApplication::translate("CPP_ProjectFinalClass", "START CONNECTING", nullptr));
        bgImg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CPP_ProjectFinalClass: public Ui_CPP_ProjectFinalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPP_PROJECTFINAL_H
