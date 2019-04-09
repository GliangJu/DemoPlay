#pragma once
#include <mutex>
struct AVCodecParameters;
struct AVFrame;
struct SwrContext;
class JResample
{
public:
	//����������������һ�³��˲�����ʽ,����ΪS16,���ͷ�para	
	virtual bool Open(AVCodecParameters *para, bool isClearPara = false);
	virtual void Close();
	//�����ز������С,���ܳɹ�����ͷ�indata�ռ�
	virtual int Resample(AVFrame *indata, unsigned char *data);
	JResample();
	~JResample();
	//AV_SAMPLE_FMT_S16
	int outFormat = 1;
protected:
	std::mutex mux;
	SwrContext *actx = 0;
};

