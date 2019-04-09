#pragma once

#include <QObject>
#include <QMouseEvent>
#include <QSlider>

#include<QEvent>  
#include <QList>
class QResizeEvent;
class JSliderLabel;
class JSlider : public QSlider
{
	Q_OBJECT

public:
	JSlider(QWidget *parent = NULL);
	~JSlider();
	//鼠标按下
	void mousePressEvent(QMouseEvent *e);
	//鼠标松开
	//void mouseReleaseEvent(QMouseEvent *e);

	//鼠标移动，拖动按下左键的事件
	//void mouseMoveEvent(QMouseEvent *e);
	//鼠标移入
	//void enterEvent(QEvent *);
	//鼠标移出
	//void leaveEvent(QEvent *);
	void resizeEvent(QResizeEvent *e);
	void initSliders();
protected:
	QList<JSliderLabel *> sliders;
};
