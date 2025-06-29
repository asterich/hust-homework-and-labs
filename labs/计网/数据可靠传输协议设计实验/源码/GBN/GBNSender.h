#pragma once

#include "RdtSender.h"
#include <deque>

using namespace std;

class GBNSender :public RdtSender {
public:
	GBNSender();
	virtual ~GBNSender();
	bool getWaitingState();
	bool send(const Message& message);	// 发送应用层下来的Message
	void receive(const Packet& ackPkt);	// 接受确认Ack
	void timeoutHandler(int seqNum);	// Timeout handler
	
private:
	int expectnum;  // 下一个发送的序号
	bool isWaiting;  // 是否在等待
	int basenum;  // 窗口基序号
	int sequencelen;  // 序号宽度
	int windowlen;  // 窗口长度
	Packet waitackPacket;  // 已经发送的packet
	deque<Packet> window;  // 窗口
};