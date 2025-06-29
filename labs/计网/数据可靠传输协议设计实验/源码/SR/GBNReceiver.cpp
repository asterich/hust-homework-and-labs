#include "stdafx.h"
#include "Global.h"
#include "GBNReceiver.h"

// GBNReceiver�����������
GBNReceiver::~GBNReceiver()
{
    // ����������ʱִ�еĲ���
}

// GBNReceiver��Ĺ��캯��
GBNReceiver::GBNReceiver() :len(8), expectnum(0) {
    // ��ʼ���ϴν��յ����ݰ���checksumΪ0
    last.checksum = 0;

    // ���ó�ʼ״̬�£��ϴ�ack��ȷ�����Ϊ-1
    last.seqnum = last.acknum = -1;

    // ��ȡ�����е��غɴ�С
    int len = Configuration::PAYLOAD_SIZE;

    // ��ʼ��payload����
    for (int i = 0; i < len; i++) {
        last.payload[i] = '.';
    }

    // �����ʼ��������ݰ���checksum
    last.checksum = pUtils->calculateCheckSum(last);
}

// GBNReceiver�Ľ��շ���
void GBNReceiver::receive(const Packet& packet) {
    // ������յ������ݰ���checksum
    int checksum = pUtils->calculateCheckSum(packet);

    // ������յ������ݰ���checksum��������checksum��ƥ�䣬�����к�Ҳƥ��
    if (checksum == packet.checksum && expectnum == packet.seqnum) {
        // ��ӡ��־����ʾ��ȷ���յ������ݰ�
        pUtils->printPacket("���յõ���ȷ����", packet);

        // ����һ����Ϣ����
        Message msg;
        // �����ݰ���payload���Ƶ���Ϣ��
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        // ����Ϣ���ݸ�Ӧ�ò�
        pns->delivertoAppLayer(RECEIVER, msg);

        // �����ϴν��յ������ݰ���ack���к�
        last.acknum = packet.seqnum;
        // �����ϴν��յ������ݰ���checksum
        last.checksum = pUtils->calculateCheckSum(last);
        // ��ӡ��־����ʾ����ȷ�ϱ���
        pUtils->printPacket("����ȷ�ϱ���", last);
        // ����ȷ�ϱ��ĵ������
        pns->sendToNetworkLayer(SENDER, last);
        // �����������յ����к�
        expectnum = (expectnum + 1) % len;
    }
    // ������ݰ���ƥ��
    else {
        // ������յ������ݰ���checksum������checksum��ƥ��
        if (packet.checksum != checksum) {
            pUtils->printPacket("���շ��ͱ���ʧ�ܣ�corrupt!", packet);
        }
        // ������кŲ�ƥ��
        else {
            pUtils->printPacket("���շ��ͱ���ʧ��, �������", packet);
        }
        // ��ӡ��־����ʾ�ط�ȷ�ϱ���
        pUtils->printPacket("���շ��ط�ȷ�ϱ���", last);
        // �ط�ȷ�ϱ��ĵ������
        pns->sendToNetworkLayer(SENDER, last);
    }
}
