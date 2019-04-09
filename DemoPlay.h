#pragma once

#include <QtWidgets/QWidget>
#include "ui_DemoPlay.h"

class DemoPlay : public QWidget
{
	Q_OBJECT

public:
	DemoPlay(QWidget *parent = Q_NULLPTR);
	~DemoPlay();

	//定时器,滑动条显示
	void timerEvent(QTimerEvent *e);
	//窗口尺寸变化
	void resizeEvent(QResizeEvent *e);
	//双击全屏
	void mouseDoubleClickEvent(QMouseEvent *e);
	//播放暂停
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
