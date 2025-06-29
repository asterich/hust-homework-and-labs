#pragma once
#include "RdtReceiver.h"

class GBNReceiver :public RdtReceiver {
public:
	GBNReceiver();
	virtual ~GBNReceiver();
	void receive(const Packet& packet);  // 被NetworkService调用的接收API


private:
	Packet last; // 上次发送的确认报文
	int len;  // 序号长度
	int expectnum;  // 期待收到的下一个报文序号
};