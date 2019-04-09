#include "JSlider.h"
#include "JSliderLabel.h"
#include<QDebug>  
#include <QPalette>
#include <QMouseEvent>
JSlider::JSlider(QWidget *parent)
	: QSlider(parent)
{
	initSliders();
}

JSlider::~JSlider()
{
}
void JSlider::resizeEvent(QResizeEvent *e)
{
	foreach(auto *slider, sliders) {
		slider->setGeometry(rect());
	}
}

void JSlider::initSliders()
{
	auto *slider = new JSliderLabel(this,
		QColor(255, 0, 0, 128),
		0);
	slider->setPercent(0.9);
	slider->init(QString::fromLocal8Bit("��һ����ǩ!"));
	sliders.append(slider);

	slider = new JSliderLabel(this,
		QColor(0, 255, 0, 128),
		1);

	slider->setPercent(0.5);
	slider->init(QString::fromLocal8Bit("�ڶ�����ǩ!"));
	sliders.append(slider);

	slider = new JSliderLabel(this,
		QColor(0, 0, 255, 128),
		2);
	slider->setPercent(0.1);
	slider->init(QString::fromLocal8Bit("��������ǩ!"));
	sliders.append(slider);

	for (int i = sliders.size() - 1; i > 0; --i) {
		sliders[i]->setNextOverlay(sliders[i - 1]);
	}
}

void JSlider::mousePressEvent(QMouseEvent *e)
{
	
	double pos = (double)e->pos().x() / (double)width();
	setValue(pos * this->maximum());

	//ԭ�����ݴ���
	QSlider::sliderReleased();
}