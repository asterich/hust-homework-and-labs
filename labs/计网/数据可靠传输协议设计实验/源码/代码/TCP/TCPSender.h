#pragma once // ��ֹͷ�ļ��ظ�����
#include "RdtSender.h" // ����RdtSender�������
#include<deque> // ����deque��˫�˶��У�����

using namespace std;

// TCPSender�࣬�̳���RdtSender��
class TCPSender :public RdtSender
{
private:
    int expectnum;	// �������͵���һ�����
    bool state; // ����״̬����������ڴ����ж����˵���δʹ��
    int acknum; // ���ڼ�¼����ACK������
    int basenum; // ���ڵĻ����
    int windowlen; // ���ڴ�С
    int sequencelen; // ��ŵķ�Χ
    deque<Packet> window; // ��deque���������洰���е����ݰ�
    Packet waitpacket;	// ����ȴ����͵����ݰ�

public:
    // �жϷ��ͷ��Ƿ��ڵȴ�״̬�ĺ���
    bool getWaitingState();
    // ������Ϣ�ĺ���������ΪMessage���͵�����
    bool send(const Message& message);
    // ����ȷ�ϱ��ĵĺ���������ΪPacket���͵�����
    void receive(const Packet& ackPkt);
    // ��ʱ����ʱ������������Ϊ��������ʾ���к�
    void timeoutHandler(int seqNum);

public:
    // ���캯��
    TCPSender();
    // ����������
    virtual ~TCPSender();
};
