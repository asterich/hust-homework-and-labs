#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"

SRReceiver::~SRReceiver() {}

SRReceiver::SRReceiver() : windowlen(4), basenum(0), sequencelen(8), expectednum(0) {
	// ��ʼ�����һ�����յ���ȷ�ϰ�������
	lastpacket.checksum = 0;
	lastpacket.acknum = -1;
	lastpacket.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastpacket.payload[i] = '.';
	}
	// ����ȷ�ϰ���У���
	lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);

	// ��ʼ����������
	for (int i = 0; i < windowlen; i++) {
		receivePacket temp;
		temp.packet.seqnum = -1;
		temp.occupied = false;
		window.push_back(temp);
	}
}


void SRReceiver::receive(const Packet& packet) {
	// ������յ��ı��ĵ����к��ڴ����е�ƫ����
	int offset = (packet.seqnum - basenum + sequencelen) % sequencelen;
	offset = (offset + sequencelen) % sequencelen;
	// ������յ��ı��ĵ�У���
	int checksum = pUtils->calculateCheckSum(packet);

	// �жϱ����Ƿ��ڴ����ڲ��Ҹ�λ����û�н��յ����ģ����ұ���û����
	if (offset < windowlen && window.at(offset).occupied == false && checksum == packet.checksum) {
		// �����ı����ڴ��ڵ���ȷλ��
		window.at(offset).occupied = true;
		window.at(offset).packet = packet;

		// ��ӡ��ǰ���ڵ�״̬
		printf("���շ�����:[ ");
		int len = window.size();
		for (int i = 0; i < len; i++) {
			if (window.at(i).occupied == true) {
				printf("%dY ", (basenum + i) % sequencelen);
			}
			else {
				printf("%dN ", (basenum + i) % sequencelen);
			}
		}
		printf("]\n");

		// ������Ľ������
		pUtils->printPacket("���շ���ȷ����յ�����", packet);

		// �����������ǰ��ı����Ѿ����գ�������һ�������ϲ㣬����������
		while (true == window.front().occupied) {
			Message message;
			memcpy(message.data, window.front().packet.payload, sizeof(window.front().packet.payload));
			pns->delivertoAppLayer(RECEIVER, message);
			basenum = (basenum + 1) % sequencelen;
			receivePacket temp;
			temp.occupied = false;
			temp.packet.seqnum = -1;
			window.pop_front();
			window.push_back(temp);
		}

		// ��ӡ�������ڻ������״̬
		printf("���շ���������:[");
		len = window.size();
		for (int i = 0; i < len; i++) {
			if (window.at(i).occupied == true) {
				printf("%dY ", (basenum + i) % sequencelen);
			}
			else {
				printf("%dN ", (basenum + i) % sequencelen);
			}
		}
		printf("]\n");

		// ����ȷ�ϱ��ĵ����кţ�������У���
		lastpacket.acknum = packet.seqnum;
		lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);
		// ����ȷ�ϱ���
		pUtils->printPacket("���շ����ͱ���", lastpacket);
		pns->sendToNetworkLayer(SENDER, lastpacket);
	}
	// ��������𻵻��Ѿ���ȷ��
	else {
		if (packet.checksum != checksum) {
			// �����𻵣���ӡ������Ϣ
			pUtils->printPacket("���շ����ձ��Ĵ���corrupt", packet);
		}
		else {
			// �����Ѿ���ȷ�ϣ����·���ȷ�ϱ���
			pUtils->printPacket("���շ����յ���һ���Ѿ�ȷ�ϵı���", packet);
			lastpacket.acknum = packet.seqnum;
			lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);
			pUtils->printPacket("���շ����·���ȷ�ϱ���", lastpacket);
			pns->sendToNetworkLayer(SENDER, lastpacket);
		}
	}
}


