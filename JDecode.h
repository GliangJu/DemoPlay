#pragma once
struct AVCodecParameters;
struct AVCodecContext;
struct AVFrame;
struct AVPacket;
#include <mutex>
extern void JFreePacket(AVPacket **pkt);
extern void JFreeFrame(AVFrame **frame);
class JDecode
{
public:
	bool isAudio = false;
	//当前解码到的pts
	long long pts = 0;
	//打开解码器,不管成功和失败都释放para空间
	virtual bool Open(AVCodecParameters *para);
	//发送到解码线程,不管成功和失败都释放pkt空间(对象和媒体内容)
	virtual bool Send(AVPacket *pkt);
	//获取解码后数据,一次send可能需要多次Recv,获取缓冲中的数据Send NulL在Recv多次
	//每次复制一份,由调用者释放 av_frame_free
	virtual AVFrame* Recv();
	//清空读取缓存
	virtual void Close();
	virtual void Clear();
	JDecode();
	virtual ~JDecode();
protected:
	AVCodecContext *codec = 0;
	std::mutex mux;
};

