#pragma once

#include <QtWidgets/QWidget>
#include "ui_DemoPlay.h"

class DemoPlay : public QWidget
{
	Q_OBJECT

public:
	DemoPlay(QWidget *parent = Q_NULLPTR);
	~DemoPlay();

	//��ʱ��,��������ʾ
	void timerEvent(QTimerEvent *e);
	//���ڳߴ�仯
	void resizeEvent(QResizeEvent *e);
	//˫��ȫ��
	void mouseDoubleClickEvent(QMouseEvent *e);
	//������ͣ
	void SetPause(bool isPause);

public slots:
	void OpenFile();
	void PlayOrPause();
	void SliderPress();
	void SliderRelease();
private:
	bool isSliderPress = false;

	Ui::DemoPlayClass ui;
};
