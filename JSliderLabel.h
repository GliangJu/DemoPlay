#pragma once
#include "Overlay.h"
#include <QColor>
#include <QLabel>
class QPaintEvent;
class JSliderLabel :
	public Overlay
{
	Q_OBJECT
public:
	explicit JSliderLabel(QWidget *parent = 0,
		QColor color = QColor(255, 0, 0, 128),
		int wId = 0);

	void mouseMoveEvent(QMouseEvent *e);
	void setNextOverlay(Overlay *overlay);
	void init(QString str);
public slots:
	void setPercent(float p);
protected:
	void paintEvent(QPaintEvent *paintEvent);
	bool isValidPressPos(const QPoint &p);
private:
	Overlay *nextOverlay;
	float drawPercent;
	QString str;
	float error;
	QLabel*	m_displayLabel;
	int id;
};