#include "DemoPlay.h"
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
#include "JDemux.h"
#include "JDecode.h"
#include "JResample.h"
#include "JAudioPlay.h"
#include "JAudioThread.h"
#include "JVideoThread.h"
#include <QThread>
class TestThread:public QThread
{
public:
	JAudioThread at;
	JVideoThread vt;
	void Init()
	{
		//char *url = "rtmp://live.hkstv.hk.lxdns.com/live/hks1";
		//cout << "demux.Open = " << demux.Open(url);
		demux.Read();
		demux.Clear();
		demux.Close();
		char *url = "video.mp4";
		cout << "demux.Open = " << demux.Open(url);
		/*cout << "CopyVPara = " << demux.CopyVPara();
		cout << "CopyAPara = " << demux.CopyAPara();*/
		//cout << " Seek = " << demux.Seek(0.99) << endl;

		
		//cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
		/*vdecode.Clear();
		vdecode.Close();*/
		/*cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;

		cout << "resample.Open() = " << resample.Open(demux.CopyAPara()) << endl;
		JAudioPlay::Get()->channels = demux.channels;
		JAudioPlay::Get()->sampleRate = demux.sampleRate;
		cout << "JAudioPlay::Get()->Open() = " << JAudioPlay::Get()->Open() << endl;*/
		cout << "at.Open = " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels) << endl;
		vt.Open(demux.CopyVPara(), video, demux.width, demux.height);
		at.start();
		vt.start();

	}
	unsigned char *pcm = new unsigned char[1024 * 1024];
	void run()
	{
		for (;;)
		{
			AVPacket *pkt = demux.Read();
			if (demux.IsAudio(pkt))
			{
				at.Push(pkt);
				/*adecode.Send(pkt);
				AVFrame *frame = adecode.Recv();
				int len = resample.Resample(frame, pcm);
				cout << "Resample:" << len << " ";
				while (len > 0)
				{
					if (JAudioPlay::Get()->GetFree() >= len)
					{
						JAudioPlay::Get()->Write(pcm, len);
						break;
					}
					msleep(1);
				}*/
				//cout << "Audio:" << frame << endl;
			} 
			else
			{
				vt.Push(pkt);
				/*vdecode.Send(pkt);
				AVFrame *frame = vdecode.Recv();
				video->Repaint(frame);*/
				//msleep(40);
				//cout << "Video:" << frame << endl;
			}
			if (!pkt) break;
		}
	}
	//²âÊÔJDemux
	JDemux demux;
	//½âÂë²âÊÔ
	/*JDecode vdecode;
	JDecode adecode;
	JResample resample;*/
	JVideoWidget *video;
};
#include "JDemuxThread.h"
int main(int argc, char *argv[])
{
	//TestThread tt;
	
	QApplication a(argc, argv);
	DemoPlay w;
	w.show();
	//³õÊ¼»¯gl´°¿Ú
	//w.ui.video->Init(tt.demux.width, tt.demux.height);
	/*tt.video = w.ui.video;
	tt.Init();
	tt.start();*/
	//JDemuxThread dt;
	//char *url = "rtmp://live.hkstv.hk.lxdns.com/live/hks1";
	////url = "video.mp4";
	//dt.Open(url, w.ui.video);
	//dt.Start();
	return a.exec();
}
