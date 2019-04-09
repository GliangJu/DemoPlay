#pragma once
struct AVPacket;
class JDecode;
#include <list>
#include <mutex>
#include <QThread>
class JDecodeThread:public QThread
{
public:
	JDecodeThread();
	virtual ~JDecodeThread();
	virtual void Push(AVPacket *pkt);
	//ȡ��һ֡����,����ջ,���û�з���NULL
	virtual AVPacket *Pop();
	//�������
	virtual void Clear();
	//������Դ,ֹͣ�߳�
	virtual void Close();

	//������
	int maxList = 100;
	bool isExit = false;
protected:
	JDecode *decode = 0;
	std::list <AVPacket *> packs;
	std::mutex mux;

};

