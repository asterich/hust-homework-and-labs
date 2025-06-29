#include "stdafx.h"
#include "Global.h"
#include "TCPSender.h"

// ���캯��
TCPSender::TCPSender() : expectnum(0), state(false), basenum(0), windowlen(4), sequencelen(8), acknum(0) {
}

// ��������
TCPSender::~TCPSender() {
}

// �жϷ��ͷ��Ƿ��ڵȴ�״̬
bool TCPSender::getWaitingState() {
    // �����ڴ�С���ڴ��ڳ���ʱ������true����ʾ���ͷ����ڵȴ�ȷ�ϱ���
    return window.size() == windowlen;
}

// �������ݰ�
bool TCPSender::send(const Message& message) {
    // ������ڵȴ�״̬�����ܷ������ݣ�ֱ�ӷ���false
    if (getWaitingState()) {
        return false;
    }

    // ��ʼ�������͵����ݰ�
    waitpacket.acknum = -1;  // acknum�ֶ��ڷ������ݰ�ʱ������
    waitpacket.seqnum = expectnum;  // �������ݰ������Ϊ�ڴ������
    waitpacket.checksum = 0;  // ��ʼ��У���Ϊ0
    // ����Ϣ�����ݸ��Ƶ����ݰ���payload�ֶ�
    memcpy(waitpacket.payload, message.data, sizeof(message.data));
    // ���㲢�������ݰ���У���
    waitpacket.checksum = pUtils->calculateCheckSum(waitpacket);

    // �����ݰ���ӵ�������
    window.push_back(waitpacket);
    // ��ӡ��־����ʾ���͵����ݰ�
    pUtils->printPacket("���ͷ����ͱ���", waitpacket);

    // ������ڵĻ���ŵ����ڴ�����ţ���������ʱ��
    if (basenum == expectnum) {
        pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
    }
    // �������ݰ��������
    pns->sendToNetworkLayer(RECEIVER, waitpacket);

    // �����ڴ������
    expectnum = (expectnum + 1) % sequencelen;

    // ����true����ʾ���ݰ����ͳɹ�
    return true;
}

// ����ȷ�ϱ���
void TCPSender::receive(const Packet& ackPkt) {
    // ������յ���ȷ�ϱ��ĵ�У���
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    // ����ƫ��������ȷ�ϱ��ĵ���źʹ��ڻ���ŵĲ�ֵ
    int offset = (ackPkt.acknum - basenum + sequencelen) % sequencelen;

    // �ж�У����Ƿ���ȷ������ȷ�ϱ��ĵ�����Ƿ��ڴ�����
    if (checkSum == ackPkt.checksum && offset < window.size()) {

        printf("���ͷ�����:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ", (basenum + i) % sequencelen);
        }
        printf("]\n");


        // У�����ȷ�����Ҳ�ڴ�����
        // ��ӡ��־����ʾ���յ���ȷ�ϱ���
        pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
        // ֹͣ��ʱ��
        pns->stopTimer(SENDER, basenum);

        // ���´���
        while (basenum != (ackPkt.acknum + 1) % sequencelen) {
            window.pop_front();
            basenum = (basenum + 1) % sequencelen;
        }

        printf("���ͷ���������:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ", (basenum + i) % sequencelen);
        }
        printf("]\n");

        // ��������ACK������
        acknum = 0;
        // ������ڲ�Ϊ�գ�������ʱ��
        if (!window.empty()) {
            pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
        }
    }
    else if (checkSum != ackPkt.checksum) {
        // ���У��ʹ��󣬴�ӡ��־
        pUtils->printPacket("���ͷ�û����ȷ�յ�ȷ�ϣ�У��ʹ���", ackPkt);
    }
    else if (ackPkt.acknum == (basenum + sequencelen - 1) % sequencelen) {
        // ����յ�����֮ǰ�Ѿ�ȷ�ϵİ�����������ACK������
        pUtils->printPacket("���ͷ��յ���֮ǰ�Ѿ�ȷ�ϵİ�", ackPkt);
        acknum++;
        // �������ACK�������ﵽ3�����������ش����ط���������������ݰ�
        if (acknum == 3 && !window.empty()) {
            pUtils->printPacket("���ͷ����������ش����ط������δ��ȷ�ϵı��Ķ�", window.front());
            pns->sendToNetworkLayer(RECEIVER, window.front());
            acknum = 0;  // ��������ACK������
        }
    }
}

// ��ʱ����ʱ������
void TCPSender::timeoutHandler(int seqNum) {
    // ��ӡ��־����ʾ�ط������ݰ�
    pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط������δ��ȷ�ϵı��Ķ�", window.front());
    // ֹͣ��������ʱ��
    pns->stopTimer(SENDER, seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
    // �ط���������������ݰ�
    pns->sendToNetworkLayer(RECEIVER, window.front());
}
