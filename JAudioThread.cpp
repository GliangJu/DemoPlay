#include "JAudioThread.h"
#include "JDecode.h"
#include "JAudioPlay.h"
#include "JResample.h"
#include <iostream>
using namespace std;
void JAudioThread::Clear()
{
	JDecodeThread::Clear();
	mux.lock();
	if (ap)ap->Clear();
	mux.unlock();
}
void JAudioThread::Close()
{
	JDecodeThread::Close();
	if (res)
	{
		res->Close();
		amux.lock();
		delete res;
		res = NULL;
		amux.unlock();
	}
	if (ap)
	{
		ap->Close();
		amux.lock();
		ap = NULL;
		amux.unlock();
	}
}
bool JAudioThread::Open(AVCodecParameters *para, int sampleRate, int channels)
{
	if (!para)return false;
	Clear();
	amux.lock();
	pts = 0;

	bool re = true;
	if (!res->Open(para, false))
	{
		cout << "JResample open failed!" << endl;
		re = false;
	}
	ap->sampleRate = sampleRate;
	ap->channels = channels;
	if (!ap->Open())
	{
		re = false;
		cout << "JAudioPlay open failed!" << endl;
	}
	if (!decode->Open(para))
	{
		cout << "audio JDecode open failed!" << endl;
		re = false;
	}
	amux.unlock();
	cout << "JAudioThread::Open :" << re << endl;
	return re;
}
void JAudioThread::SetPause(bool isPause)
{
	//amux.lock();
	this->isPause = isPause;
	if (ap)
		ap->SetPause(isPause);
	//amux.unlock();
}
void JAudioThread::run()
{
	unsigned char *pcm = new unsigned char[1024 * 1024 * 10];
	while (!isExit)
	{
		amux.lock();
		if (isPause)
		{
			amux.unlock();
			msleep(5);
			continue;
		}
		//û������
		/*if (packs.empty() || !decode || !res || !ap)
		{
			amux.unlock();
			msleep(1);
			continue;
		}*/

		//AVPacket *pkt = packs.front();
		//packs.pop_front();
		AVPacket *pkt = Pop();
		bool re = decode->Send(pkt);
		if (!re)
		{
			amux.unlock();
			msleep(1);
			continue;
		}
		//һ��send ���recv
		while (!isExit)
		{
			AVFrame * frame = decode->Recv();
			if (!frame) break;
			//��ȥ������δ���ŵ�ʱ��
			pts = decode->pts - ap->GetNoPlayMs();
			//cout << "audio pts = " << pts << endl;
			//�ز��� 
			int size = res->Resample(frame, pcm);
			//������Ƶ
			while (!isExit)
			{
				if (size <= 0)break;
				//����δ���꣬�ռ䲻��
				if (ap->GetFree() < size || isPause)
				{
					msleep(1);
					continue;
				}
				ap->Write(pcm, size);
				break;
			}
		}
		amux.unlock();
	}
	delete pcm;
}


JAudioThread::JAudioThread()
{
	if (!res) res = new JResample();
	if (!ap) ap = JAudioPlay::Get();
}


JAudioThread::~JAudioThread()
{
	//�ȴ��߳��˳�
	isExit = true;
	wait();
}
