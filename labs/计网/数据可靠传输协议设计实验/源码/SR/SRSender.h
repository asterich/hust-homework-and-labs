#pragma once
#include <deque>
#include "RdtSender.h"

using namespace std;

// ����ṹ��getpacket�����ڱ����ѷ��͵����ݰ��������״̬
struct getpacket {
	bool receive;  // ��־�����ݰ��Ƿ��ѱ����շ���ȷ����
	Packet packet; // ���ݰ�
};

// �̳���RdtSender��SRSender�࣬ʵ����SRЭ��ķ��ͷ�
class SRSender : public RdtSender {
public:
	bool getWaitingState(); // ��ȡ���ͷ���ǰ�Ƿ��ڵȴ�״̬
	bool send(const Message& message); // ������Ϣ
	void receive(const Packet& ackPkt); // ����ȷ�ϰ�
	void timeoutHandler(int seqNum); // ��ʱ������
	virtual ~SRSender(); // ��������
	SRSender(); // ���캯��

private:
	int expectednum; // ��һ���������͵����к�
	bool state; // ���ͷ���ǰ��״̬��trueΪ�ȴ�״̬��falseΪ����״̬
	int basenum; // ���ڵĻ����
	int windowlen; // ���ڴ�С
	int sequencelen; // ���кŵ�ȡֵ��Χ
	deque<getpacket> window; // ���ʹ��ڣ���˫�˶���ʵ��
	Packet waitpacket; // �����ͷ����ڵȴ�״̬ʱ������ȴ����͵����ݰ�
};
