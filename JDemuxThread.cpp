#include "JDemuxThread.h"
#include "JDemux.h"
#include "JDecode.h"
#include "JVideoThread.h"
#include "JAudioThread.h"
#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}

using namespace std;
void JDemuxThread::Clear()
{
	mux.lock();
	if (demux)demux->Clear();
	if (vt)vt->Clear();
	if (at)at->Clear();
	mux.unlock();
}
void JDemuxThread::Seek(double pos)
{
	//清理缓存
	Clear();
	mux.lock();
	bool status = this->isPause;
	mux.unlock();
	//暂停
	SetPause(true);
	mux.lock();
	if (demux)
		demux->Seek(pos);
	//实际要显示的位置pts
	long long seekPts = pos*demux->totalMs;
	while (!isExit)
	{
		AVPacket *pkt = demux->ReadVideo();
		if (!pkt)break;
		//如果解码到seekPts
		if (vt->RepaintPts(pkt, seekPts))
		{
			this->pts = seekPts;
			break;
		}
	}
	mux.unlock();
	//seek是否暂停状态
	if (!status)
		SetPause(false);
}
void JDemuxThread::SetPause(bool isPause)
{
	mux.lock();
	this->isPause = isPause;
	if (at)at->SetPause(isPause);
	if (vt)vt->SetPause(isPause);
	mux.unlock();
}
void JDemuxThread::run()
{
	while (!isExit)
	{
		mux.lock();
		if (isPause)
		{
			mux.unlock();
			msleep(5);
			continue;
		}
		if (!demux)
		{
			mux.unlock();
			msleep(5);
			continue;
		}
		//音视频同步
		if (vt && at)
		{
			pts = at->pts;
			vt->synpts = at->pts;
		}
		AVPacket *pkt = demux->Read();
		if (!pkt)
		{
			mux.unlock();
			msleep(5);
			continue;
		}
		//判断数据是音频
		if (demux->IsAudio(pkt))
		{
			if (at)at->Push(pkt);
		}
		else //视频
		{
			if (vt)vt->Push(pkt);
		}
		mux.unlock();
		msleep(1);
	}
}
bool JDemuxThread::Open(const char *url, IVideoCall *call)
{
	if (url == 0 || url[0] == '\0')
		return false;
	mux.lock();
	if (!demux) demux = new JDemux();
	if (!vt) vt = new JVideoThread();
	if (!at) at = new JAudioThread();
	//打开解封装
	bool re = demux->Open(url);
	if (!re)
	{
		cout << "demux->Open(url) failed!" << endl;
		return false;
	}
	//打开视频解码器和处理线程
	if (!vt->Open(demux->CopyVPara(), call, demux->width, demux->height)) 
	{
		re = false;
		cout << "vt->Open failed!" << endl;
	}
	//打开音频解码器和处理线程
	if (!at->Open(demux->CopyAPara(),demux->sampleRate,demux->channels))
	{
		re = false;
		cout << "at->Open failed!" << endl;
	}
	totalMs = demux->totalMs;
	mux.unlock();
	cout << "JDemuxThread::Open " << re << endl;
	return re;
}
void JDemuxThread::Close()
{
	isExit = true;
	wait();
	if (vt) vt->Close();
	if (at) at->Close();
	mux.lock();
	delete vt;
	delete at;
	vt = NULL;
	at = NULL;
	mux.unlock();
}
void JDemuxThread::Start()
{
	mux.lock();
	if (!demux) demux = new JDemux();
	if (!vt) vt = new JVideoThread();
	if (!at) at = new JAudioThread();
	//启动当前线程
	QThread::start();
	if (vt) vt->start();
	if (at) at->start();
	mux.unlock();
}
JDemuxThread::JDemuxThread()
{
}


JDemuxThread::~JDemuxThread()
{
	isExit = true;
	wait();
}
