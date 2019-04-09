#pragma once
#include <QThread>
#include <mutex>
#include <list>
struct AVCodecParameters;
class JAudioPlay;
class JResample;
#include "JDecodeThread.h"
class JAudioThread:public JDecodeThread
{
public:
	//当前音频播放的pts
	long long pts = 0;
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters *para, int sampleRate, int channels);
	//停止线程,清理资源
	virtual void Close();
	virtual void Clear();
	void run();
	JAudioThread();
	virtual ~JAudioThread();

	void SetPause(bool isPause);
	bool isPause = false;
protected:
	std::mutex amux;
	JAudioPlay *ap = 0;
	JResample *res = 0;
};

