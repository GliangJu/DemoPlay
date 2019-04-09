#include "DemoPlay.h"
#include <QFileDialog>
#include <QDebug>
#include "JDemuxThread.h"
#include <QMessageBox>

static JDemuxThread dt;
DemoPlay::DemoPlay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	dt.Start();
	startTimer(40);


}
DemoPlay::~DemoPlay()
{
	dt.Close();
}

void DemoPlay::resizeEvent(QResizeEvent *e)
{
	ui.playPos->move(50, this->height() - 100);
	ui.playPos->resize(this->width() - 100, ui.playPos->height());
	ui.pushButton->move(100, this->height() - 150);
	ui.isPlay->move(ui.pushButton->x() + ui.pushButton->width() + 10, ui.pushButton->y());
	ui.video->resize(this->size());
}
void DemoPlay::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (isFullScreen())
	{
		this->showNormal();
	}
	else
	{
		this->showFullScreen();
	}
}
void DemoPlay::SetPause(bool isPause)
{
	if (isPause)
		ui.isPlay->setText(QString::fromLocal8Bit("播 放"));
	else
		ui.isPlay->setText(QString::fromLocal8Bit("暂 停"));
}
void DemoPlay::PlayOrPause()
{
	bool isPause = !dt.isPause;
	SetPause(isPause);
	dt.SetPause(isPause);
}
void DemoPlay::SliderPress()
{
	isSliderPress = true;
}
void DemoPlay::SliderRelease() 
{
	isSliderPress = false;
	double pos = 0.0;
	pos = (double)ui.playPos->value() / (double)ui.playPos->maximum();
	dt.Seek(pos);
}
void DemoPlay::timerEvent(QTimerEvent *e)
{
	if (isSliderPress)return;
	long long total = dt.totalMs;
	if (total > 0)
	{
		double pos = (double)dt.pts / (double)total;
		int v = ui.playPos->maximum() * pos;
		ui.playPos->setValue(v);
	}
}
void DemoPlay::OpenFile()
{
	//选择文件
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
	//qDebug() << name;
	if (name.isEmpty())return;
	this->setWindowTitle(name);
	if (!dt.Open(name.toLocal8Bit(), ui.video))
	{
		QMessageBox::information(0, "error", "open file failed!");
		return;
	}
	SetPause(dt.isPause);
}