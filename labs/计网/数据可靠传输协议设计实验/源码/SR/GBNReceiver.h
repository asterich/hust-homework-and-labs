#pragma once
#include "RdtReceiver.h"

class GBNReceiver :public RdtReceiver {
public:
	GBNReceiver();
	virtual ~GBNReceiver();
	void receive(const Packet& packet);  // ��NetworkService���õĽ���API


private:
	Packet last; // �ϴη��͵�ȷ�ϱ���
	int len;  // ��ų���
	int expectnum;  // �ڴ��յ�����һ���������
};