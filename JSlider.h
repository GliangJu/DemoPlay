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
	//��갴��
	void mousePressEvent(QMouseEvent *e);
	//����ɿ�
	//void mouseReleaseEvent(QMouseEvent *e);

	//����ƶ����϶�����������¼�
	//void mouseMoveEvent(QMouseEvent *e);
	//�������
	//void enterEvent(QEvent *);
	//����Ƴ�
	//void leaveEvent(QEvent *);
	void resizeEvent(QResizeEvent *e);
	void initSliders();
protected:
	QList<JSliderLabel *> sliders;
};
