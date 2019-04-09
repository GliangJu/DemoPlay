#include "JSliderLabel.h"

#include <QApplication>
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QDebug>
JSliderLabel::JSliderLabel(QWidget *parent, QColor color, int wId) :
	Overlay(parent), drawPercent(0.5f),
	nextOverlay(nullptr), id(wId)
{
	setMouseTracking(true);
	init(str);
}
void JSliderLabel::init(QString str)
{
	m_displayLabel = new QLabel(this);
	//m_displayLabel->setFixedSize(QSize(66, 40));
	//设置游标背景为白色
	m_displayLabel->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, Qt::white);
	m_displayLabel->setPalette(palette);
	m_displayLabel->setAlignment(Qt::AlignCenter);
	m_displayLabel->setVisible(false);
	m_displayLabel->move(0, 3);
	//QString str = QString::fromLocal8Bit(str);
	m_displayLabel->setText(str);
	QFont font("Microsoft YaHei", 13, 65);
	m_displayLabel->setFont(font);
}
void JSliderLabel::setNextOverlay(Overlay *overlay)
{
	nextOverlay = overlay;
}

void JSliderLabel::setPercent(float p)
{
	drawPercent = std::max(p, 0.f);
	drawPercent = std::min(p, 100.f);
	update();
}
void JSliderLabel::paintEvent(QPaintEvent *paintEvent)
{
	QPainter p(this);
	QRect drawArea = rect();
	auto drawX = drawArea.width() * drawPercent;
	QPen pen(Qt::white);
	p.setPen(pen);
	p.drawEllipse(QPoint(drawX, height() / 2), 8, 8);
	p.setBrush(QBrush(Qt::white));
	p.drawEllipse(QPoint(drawX, height() / 2), 6, 6);
}
void JSliderLabel::mouseMoveEvent(QMouseEvent *e)
{
	if (isValidPressPos(e->pos()))
	{
		m_displayLabel->setVisible(true);
		QRect drawArea = rect();
		int width = m_displayLabel->width();
		int height = m_displayLabel->height();
		m_displayLabel->adjustSize();
		auto drawX = drawArea.width() * drawPercent;
		if (drawX < width / 2)
		{
			m_displayLabel->move(drawX - (width / 2 - drawX), 3);
		}
		else if ((drawArea.width() - drawX) < width / 2)
		{
			m_displayLabel->move(drawX - (width / 2 + (drawArea.width() - drawX)), 3);
		}
		else
		{
			m_displayLabel->move(drawX - width / 2, 3);
		}
	}
	else
	{
		m_displayLabel->setVisible(false);
		if (nextOverlay) {
			qApp->sendEvent(nextOverlay, e);
		}
	}
	update();
}
bool JSliderLabel::isValidPressPos(const QPoint &p)
{
	error = p.x();
	error = fabs(error - drawPercent * width());
	if (error < 8) {
		return true;
	}
	return false;
}
