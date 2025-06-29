#include <deque>
#include "stdafx.h"
#include "Global.h"
#include "GBNSender.h"

using namespace std;

// GBNSender�����������
GBNSender::~GBNSender()
{
    // ����������ʱִ�еĲ���
}

// GBNSender��Ĺ��캯��
GBNSender::GBNSender() :sequencelen(8), windowlen(4), basenum(0), isWaiting(false), expectnum(0)
{
    // ��ʼ�����ʹ��ڵĸ������
}

// ��ȡ��ǰ���ʹ��ڵ�״̬���Ƿ����ڵȴ�
bool GBNSender::getWaitingState() {
    if (windowlen != window.size())  // ��������е����ݰ��������ڴ��ڳ���
        isWaiting = false;           // ���ڵȴ�״̬
    else
        isWaiting = true;            // �����ڵȴ�״̬

    return isWaiting;
}

// ��ʱ������
void GBNSender::timeoutHandler(int seqNum) {
    pns->stopTimer(SENDER, seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
    int len = window.size();
    for (int i = 0; i < len; i++) {
        // ��ӡ��ʱ��־�������·��ʹ����ڵ��������ݰ�
        pUtils->printPacket("��ʱ���жϣ����·������ڵı���", window.at(i));
        pns->sendToNetworkLayer(RECEIVER, window.at(i));
    }
}

// ������Ϣ
bool GBNSender::send(const Message& message) {
    if (getWaitingState())  // �����ǰ�ڵȴ�״̬����ֱ�ӷ���false
        return false;

    waitackPacket.acknum = -1;
    waitackPacket.seqnum = expectnum;
    waitackPacket.checksum = 0;
    // ������Ϣ���ݵ����������ݰ����غɲ���
    memcpy(waitackPacket.payload, message.data, sizeof(message.data));
    // �������ݰ���checksum
    waitackPacket.checksum = pUtils->calculateCheckSum(waitackPacket);
    window.push_back(waitackPacket);  // �����ݰ���ӵ����ʹ���
    pUtils->printPacket("���ͷ����ͱ���", this->waitackPacket);

    // �����ǰ���͵��Ǵ��ڵĵ�һ�����ݰ���������ʱ��
    if (expectnum == basenum) {
        pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
    }

    // �������ݰ��������
    pns->sendToNetworkLayer(RECEIVER, waitackPacket);
    expectnum = (expectnum + 1) % sequencelen;  // ������һ���������͵����к�

    return true;
}

// ����ȷ�����ݰ�
void GBNSender::receive(const Packet& packet) {
    int notacknum = (packet.acknum - basenum + sequencelen) % sequencelen;
    int checkSum = pUtils->calculateCheckSum(packet);

    // ������յ���ȷ�����ݰ������к��ڷ��ʹ����ڣ�����checksumƥ��
    if (notacknum < window.size() && checkSum == packet.checksum) {
        printf("���ʹ���:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ,", (basenum + i) % sequencelen);
        }
        printf("]\n");
        pUtils->printPacket("�յ�ȷ�ϱ���", packet);
        // ֹͣ��ʱ�������Ƴ��������ѱ�ȷ�ϵ����ݰ�
        pns->stopTimer(SENDER, basenum);
        while (basenum != (packet.acknum + 1) % sequencelen) {
            window.pop_front();
            basenum = (basenum + 1) % sequencelen;
        }
        printf("���ͷ����ͱ��ĺ󴰿�:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ,", (basenum + i) % sequencelen);
        }
        printf("]\n");
        // ��������л���δ��ȷ�ϵ����ݰ��������¿�����ʱ��
        if (!window.empty()) {
            pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
        }
    }
    else if (packet.checksum != checkSum) {  // ���checksum��ƥ��
        pUtils->printPacket("���ͷ����յ���ȷ�ϱ���corrupt", packet);
    }
    else {  // ���checksumƥ�䣬�����кŲ��ڴ�����
        pUtils->printPacket("���ͷ���ȷ�յ���ȷ�ϱ���", packet);
    }
}
