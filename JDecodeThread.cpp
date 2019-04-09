#include "JDecodeThread.h"
#include "JDecode.h"
void JDecodeThread::Close()
{
	Clear();
	//�ȴ��߳��˳�
	isExit = true;
	wait();
	decode->Close();
	mux.lock();
	delete decode;
	decode = NULL;
	mux.unlock();
}
void JDecodeThread::Clear()
{
	mux.lock();
	decode->Clear();
	while (!packs.empty())
	{
		AVPacket *pkt = packs.front();
		JFreePacket(&pkt);
		packs.pop_front();
	}
	mux.unlock();
}
AVPacket *JDecodeThread::Pop()
{
	mux.lock();
	if (packs.empty())
	{
		mux.unlock();
		return NULL;
	}
	AVPacket *pkt = packs.front();
	packs.pop_front();
	mux.unlock();
	return pkt;
}
void JDecodeThread::Push(AVPacket *pkt)
{
	if (!pkt)return;
	//����
	while (!isExit)
	{
		mux.lock();
		if (packs.size() < maxList)
		{
			packs.push_back(pkt);
			mux.unlock();
			break;
		}
		mux.unlock();
		msleep(1);
	}
}
JDecodeThread::JDecodeThread()
{
	//�򿪽�����
	if (!decode) decode = new JDecode();
}


JDecodeThread::~JDecodeThread()
{
	//�ȴ��߳��˳�
	isExit = true;
	wait();
}
