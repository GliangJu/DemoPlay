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
	//��ǰ���뵽��pts
	long long pts = 0;
	//�򿪽�����,���ܳɹ���ʧ�ܶ��ͷ�para�ռ�
	virtual bool Open(AVCodecParameters *para);
	//���͵������߳�,���ܳɹ���ʧ�ܶ��ͷ�pkt�ռ�(�����ý������)
	virtual bool Send(AVPacket *pkt);
	//��ȡ���������,һ��send������Ҫ���Recv,��ȡ�����е�����Send NulL��Recv���
	//ÿ�θ���һ��,�ɵ������ͷ� av_frame_free
	virtual AVFrame* Recv();
	//��ն�ȡ����
	virtual void Close();
	virtual void Clear();
	JDecode();
	virtual ~JDecode();
protected:
	AVCodecContext *codec = 0;
	std::mutex mux;
};

