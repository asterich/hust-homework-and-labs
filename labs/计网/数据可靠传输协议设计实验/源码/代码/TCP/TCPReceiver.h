#pragma once // ��ֹͷ�ļ��ظ�����
#include "RdtReceiver.h" // ����RdtReceiver�������

// TCPReceiver�࣬�̳���RdtReceiver��
class TCPReceiver :public RdtReceiver {
public:
    // ���캯��
    TCPReceiver();
    // ����������
    virtual ~TCPReceiver();
    // �������ݰ��ĺ���������ΪPacket���͵�����
    void receive(const Packet& packet);

private:
    Packet lastpacket; // ���ڱ�����һ�η��͵�ȷ�ϰ�
    int sequencenum; // ���
    int expectednum; // �������յ���һ�����ݰ������
};
