/********************************************************************************
** Form generated from reading UI file 'DemoPlay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOPLAY_H
#define UI_DEMOPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "JSlider.h"
#include "JVideoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DemoPlayClass
{
public:
    JVideoWidget *video;
    QPushButton *pushButton;
    JSlider *playPos;
    QPushButton *isPlay;

    void setupUi(QWidget *DemoPlayClass)
    {
        if (DemoPlayClass->objectName().isEmpty())
            DemoPlayClass->setObjectName(QStringLiteral("DemoPlayClass"));
        DemoPlayClass->resize(1280, 720);
        video = new JVideoWidget(DemoPlayClass);
        video->setObjectName(QStringLiteral("video"));
        video->setGeometry(QRect(0, 0, 1280, 720));
        pushButton = new QPushButton(DemoPlayClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(300, 560, 93, 28));
        playPos = new JSlider(DemoPlayClass);
        playPos->setObjectName(QStringLiteral("playPos"));
        playPos->setGeometry(QRect(20, 610, 1231, 101));
        playPos->setStyleSheet(QLatin1String("QSlider::add-page{   \n"
"    background-color: rgb(87, 97, 106);\n"
"	height:4px;\n"
"}\n"
"QSlider::sub-page {\n"
"    background-color: rgb(37, 168, 198);\n"
"	height:4px;\n"
"}\n"
"QSlider::groove {\n"
"	background:transparent;\n"
"	height:6px;\n"
"	border-radius:5px;\n"
"}\n"
"QSlider::handle {\n"
"    height: 30px;\n"
"    width:13px;\n"
"    border-image: url(:/DemoPlay/Resources/ic_volume_thumb.png);\n"
"    margin: -4 0px; \n"
"}"));
        playPos->setMaximum(999);
        playPos->setOrientation(Qt::Horizontal);
        isPlay = new QPushButton(DemoPlayClass);
        isPlay->setObjectName(QStringLiteral("isPlay"));
        isPlay->setGeometry(QRect(450, 560, 93, 28));

        retranslateUi(DemoPlayClass);
        QObject::connect(pushButton, SIGNAL(clicked()), DemoPlayClass, SLOT(OpenFile()));
        QObject::connect(isPlay, SIGNAL(clicked()), DemoPlayClass, SLOT(PlayOrPause()));
        QObject::connect(playPos, SIGNAL(sliderPressed()), DemoPlayClass, SLOT(SliderPress()));
        QObject::connect(playPos, SIGNAL(sliderReleased()), DemoPlayClass, SLOT(SliderRelease()));

        QMetaObject::connectSlotsByName(DemoPlayClass);
    } // setupUi

    void retranslateUi(QWidget *DemoPlayClass)
    {
        DemoPlayClass->setWindowTitle(QApplication::translate("DemoPlayClass", "DemoPlay", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DemoPlayClass", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        isPlay->setText(QApplication::translate("DemoPlayClass", "\346\222\255\346\224\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DemoPlayClass: public Ui_DemoPlayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOPLAY_H
