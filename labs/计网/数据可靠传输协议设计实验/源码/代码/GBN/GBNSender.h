#pragma once

#include "RdtSender.h"
#include <deque>

using namespace std;

class GBNSender :public RdtSender {
public:
	GBNSender();
	virtual ~GBNSender();
	bool getWaitingState();
	bool send(const Message& message);	// ����Ӧ�ò�������Message
	void receive(const Packet& ackPkt);	// ����ȷ��Ack
	void timeoutHandler(int seqNum);	// Timeout handler
	
private:
	int expectnum;  // ��һ�����͵����
	bool isWaiting;  // �Ƿ��ڵȴ�
	int basenum;  // ���ڻ����
	int sequencelen;  // ��ſ��
	int windowlen;  // ���ڳ���
	Packet waitackPacket;  // �Ѿ����͵�packet
	deque<Packet> window;  // ����
};