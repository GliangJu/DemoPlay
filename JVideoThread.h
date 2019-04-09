#pragma once
///�������ʾ��Ƶ
struct AVPacket;
struct AVCodecParameters;
class JDecode;
#include <list>
#include <mutex>
#include <QThread>
#include "IVideoCall.h"
#include "JDecodeThread.h"
class JVideoThread:public JDecodeThread
{
public:
	//����pts,������յ��Ľ�������pts >= seekpts return true ������ʾ����
	virtual bool RepaintPts(AVPacket *pkt, long long seekpts);
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para, IVideoCall *call, int width, int height);
	void run();
	JVideoThread();
	virtual ~JVideoThread();
	//ͬ��ʱ��,���ⲿ����
	long long synpts = 0;

	void SetPause(bool isPause);
	bool isPause = false;
protected:
	std::mutex vmux;
	IVideoCall *call = 0;
};

