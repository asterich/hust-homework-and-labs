#pragma once

#include <deque>
#include "RdtReceiver.h"

using namespace std;

// ����ṹ��receivePacket�����ڱ�����մ����е����ݰ�����ռ��״̬
struct receivePacket {
	Packet packet;    // ���ݰ�
	bool occupied;    // �Ƿ���ռ�ã��Ƿ��ѽ��յ���Ч���ݰ���
};

// �̳���RdtReceiver��SRReceiver�࣬ʵ����SRЭ��Ľ��շ�
class SRReceiver : public RdtReceiver {
public:
	virtual ~SRReceiver(); // ��������
	SRReceiver(); // ���캯��
	void receive(const Packet& packet); // �������ݰ�

private:
	int expectednum; // ��һ���������յ����к�
	int basenum; // ���ڵĻ����
	int windowlen; // ���ڴ�С
	int sequencelen; // ���кŵ�ȡֵ��Χ
	Packet lastpacket; // ���ڱ�����һ�η��͵�ȷ�ϰ�
	deque<receivePacket> window; // ���մ��ڣ���˫�˶���ʵ��
};
