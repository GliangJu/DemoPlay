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
	//取出一帧数据,并出栈,如果没有返回NULL
	virtual AVPacket *Pop();
	//清理队列
	virtual void Clear();
	//清理资源,停止线程
	virtual void Close();

	//最大队列
	int maxList = 100;
	bool isExit = false;
protected:
	JDecode *decode = 0;
	std::list <AVPacket *> packs;
	std::mutex mux;

};

