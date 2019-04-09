#pragma once
#include <mutex>
struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;
class JDemux
{
public:
	//��ý���ļ�,������ý�� rtmp http rstp
	virtual bool Open(const char *url);
	//�ռ���Ҫ�������ͷ�,�ͷ�AVPacket����ռ�,�����ݿռ� av_packet_free
	virtual AVPacket *Read();
	//ֻ����Ƶ,��Ƶ�����ռ��ͷ�
	virtual AVPacket *ReadVideo();
	virtual bool IsAudio(AVPacket *pkt);
	//��ȡ��Ƶ����,���صĿռ���Ҫ���� avcodec_parameters_free
	virtual AVCodecParameters *CopyVPara();
	//��ȡ��Ƶ����,���صĿռ���Ҫ���� avcodec_parameters_free
	virtual AVCodecParameters *CopyAPara();
	//seek λ�� pos 0.0 ~1.0
	virtual bool Seek(double pos);
	//��ն�ȡ����
	virtual void Clear();
	virtual void Close();

	JDemux();
	virtual ~JDemux();

	//ý����ʱ��(����)
	int totalMs = 0;
	int width = 0;
	int height = 0;
	int sampleRate = 0;
	int channels = 0;
protected:
	//�������
	std::mutex mux;
	//���װ������
	AVFormatContext *ic = NULL;
	//����Ƶ��������ȡʱ��������Ƶ
	int videoStream = 0;
	int audioStream = 1;
};