#include "JDecode.h"
extern "C"
{
#include <libavcodec/avcodec.h>
}
#include <iostream>
using namespace std;
void JFreePacket(AVPacket **pkt)
{
	if (!pkt || !(*pkt))return;
	av_packet_free(pkt);
}
void JFreeFrame(AVFrame **frame)
{
	if (!frame || !(*frame))return;
	av_frame_free(frame);
}
bool JDecode::Open(AVCodecParameters *para)
{
	if (!para) return false;
	Close();
	//////////////////////////////////////////////////////////
	///视频解码器打开
	///找到视频解码器
	AVCodec *vcodec = avcodec_find_decoder(para->codec_id);
	if (!vcodec)
	{
		avcodec_parameters_free(&para);
		cout << "can't find the codec id " << para->codec_id << endl;
		return false;
	}
	cout << "find the AVCodec " << para->codec_id << endl;
	mux.lock();
	codec = avcodec_alloc_context3(vcodec);

	///配置解码器上下文参数
	avcodec_parameters_to_context(codec, para);
	avcodec_parameters_free(&para);
	//八线程解码
	codec->thread_count = 8;

	///打开解码器上下文
	int re = avcodec_open2(codec, 0, 0);
	if (re != 0)
	{
		avcodec_free_context(&codec);
		mux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "avcodec_open2  failed! :" << buf << endl;
		return false;
	}
	mux.unlock();
	cout << "video avcodec_open2 success!" << endl;
	return true;
}
void JDecode::Close()
{
	mux.lock();

	if (codec)
	{
		avcodec_close(codec);
		avcodec_free_context(&codec);
	}
	pts = 0;
	mux.unlock();
}
void JDecode::Clear()
{
	mux.lock();
	//清理解码缓冲
	if (codec)
	{
		avcodec_flush_buffers(codec);
	}
	mux.unlock();
}
bool JDecode::Send(AVPacket *pkt)
{
	if (!pkt || pkt->size <= 0 || !pkt->data) return false;
	mux.lock();
	if (!codec)
	{
		mux.unlock();
		return false;
	}
	int re = avcodec_send_packet(codec, pkt);
	mux.unlock();
	av_packet_free(&pkt);
	if (re != 0) return false;
	return true;
}
AVFrame* JDecode::Recv()
{
	mux.lock();
	if (!codec)
	{
		mux.unlock();
		return NULL;
	}
	AVFrame *frame = av_frame_alloc();
	int re = avcodec_receive_frame(codec, frame);
	mux.unlock();
	if (re != 0)
	{
		av_frame_free(&frame);
		return NULL;
	}
	//cout << " [" << frame->linesize[0] << "] " << flush;
	pts = frame->pts;
	return frame;
}
JDecode::JDecode()
{
}


JDecode::~JDecode()
{
}
