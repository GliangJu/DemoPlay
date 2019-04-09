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
	//��ǰ��Ƶ���ŵ�pts
	long long pts = 0;
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para, int sampleRate, int channels);
	//ֹͣ�߳�,������Դ
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

