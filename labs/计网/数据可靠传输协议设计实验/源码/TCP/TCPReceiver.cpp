#include "stdafx.h"
#include "Global.h"
#include "TCPReceiver.h"

void switchtolog() {
	freopen("E:\\hyf network\\TCP\\log.txt", "a", stdout);
}

void switchtocmd() {
	fclose(stdout);
	freopen("CON", "a", stdout);
}

// ���캯��
TCPReceiver::TCPReceiver() : sequencenum(0), expectednum(0) {
	// ��ʼ�����һ�����յ���ȷ�ϵ����ݰ��ĸ����ֶ�
	lastpacket.acknum = -1;
	lastpacket.checksum = 0;
	lastpacket.seqnum = -1;
	// ��ʼ��payload�ֶΣ�����ȫ����ʼ��Ϊ'.'�ַ�
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastpacket.payload[i] = '.';
	}
	// ���㲢����У���
	lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);
}

// ��������
TCPReceiver::~TCPReceiver() {}

// ���ձ��ĵĺ���
void TCPReceiver::receive(const Packet& packet) {
	// ���ȼ�����յ��ı��ĵ�У���
	int checksum = pUtils->calculateCheckSum(packet);

	// �ж�У����Ƿ���ȷ�����ұ�������Ƿ������������
	if (checksum == packet.checksum && expectednum == packet.seqnum) {
		// У�����ȷ���������Ҳ���ڴ������
		// ��ӡ��־��˵�����շ���ȷ�ؽ��յ��˷��ͷ��ı���
		pUtils->printPacket("���շ���ȷ���յ��˷��ͷ��ı���", packet);

		// ����Message���󣬲������յ���payload���Ƶ�Message��data�ֶ�
		Message message;
		memcpy(message.data, packet.payload, sizeof(packet.payload));

		// ����pns->delivertoAppLayer�����������յ������ݴ��ݸ�Ӧ�ò�
		pns->delivertoAppLayer(RECEIVER, message);

		// ����lastpacketΪ��ǰ���յ���packet
		lastpacket.acknum = packet.seqnum;
		lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);

		// ��ӡ��־��˵�����շ���Ҫ����ȷ�ϱ���
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastpacket);

		// ����pns->sendToNetworkLayer��������ȷ�ϱ��ķ��͸����ͷ�
		pns->sendToNetworkLayer(SENDER, lastpacket);

		// �����ڴ�����ţ����������ſռ���0-7
		expectednum = (expectednum + 1) % 8;
	}
	else {
		// У��ʹ��������Ų����ڴ���
		if (checksum != packet.checksum) {
			// �����У��ʹ��󣬴�ӡ�����־
			pUtils->printPacket("���շ����յ��ı���У��ʹ���", packet);
		}
		else {
			// ����Ǳ�����Ų��ԣ���ӡ�����־
			pUtils->printPacket("���շ����յ��ı�����Ŵ���", packet);
		}

		// ��������ΪУ��ʹ�������Ŵ��󣬽��շ�����Ҫ���·�����һ��ȷ�ϱ���
		pUtils->printPacket("���շ����·�����һ��ȷ�ϱ���", lastpacket);
		pns->sendToNetworkLayer(SENDER, lastpacket);
	}
}
