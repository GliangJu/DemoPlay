#pragma once
#include <QThread>
#include "IVideoCall.h"
#include <mutex>
class JDemux;
class JVideoThread;
class JAudioThread;
class JDemuxThread:public QThread
{
public:
	//�������󲢴�
	virtual bool Open(const char *url, IVideoCall *call);
	//���������߳�
	virtual void Start();
	//�ر��߳�������Դ
	virtual void Close();
	virtual void Clear();
	virtual void Seek(double pos);

	void run();
	JDemuxThread();
	virtual ~JDemuxThread();

	bool isExit = false;
	long long pts = 0;
	long long totalMs = 0;
	void SetPause(bool isPause);
	bool isPause = false;
protected:
	std::mutex mux;
	JDemux *demux = 0;
	JVideoThread *vt = 0;
	JAudioThread *at = 0;
};

