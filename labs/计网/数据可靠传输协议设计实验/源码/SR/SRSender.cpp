#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"

// ��������
SRSender::~SRSender() {}

// ���캯������ʼ���������кų���Ϊ8�����ڳ���Ϊ4�������Ϊ0��״̬Ϊ�ǵȴ�״̬���������Ϊ0
SRSender::SRSender() :sequencelen(8), windowlen(4), basenum(0), state(false), expectednum(0) {}

void switchtolog1() {
	freopen("E:\\hyf network\\SR\\log.txt", "a", stdout);
}

void switchtocmd1() {
	fclose(stdout);
	freopen("CON", "a", stdout);
}
// ��ȡ���ͷ��ĵȴ�״̬
bool SRSender::getWaitingState() {
	// ������������������õȴ�״̬Ϊtrue����������Ϊfalse
	if (windowlen == window.size()) {
		state = true;
	}
	else {
		state = false;
	}
	// ���صȴ�״̬
	return state;
}

// ��ʱ������
void SRSender::timeoutHandler(int seqNum) {
	// ���㳬ʱ���ĵ��������ڻ���ŵ�ƫ����
	int offset = (seqNum - basenum + sequencelen) % sequencelen;
	// ֹͣ��ʱ��
	pns->stopTimer(SENDER, seqNum);
	// ����������ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	// ���·��ͱ���
	pns->sendToNetworkLayer(RECEIVER, window.at(offset).packet);
	// ��ӡ�ط����ĵ���Ϣ
	pUtils->printPacket("���ͷ�ʱ���жϣ��ط�����", window.at(offset).packet);
}

// ���ͺ���
bool SRSender::send(const Message& message) {
	// ���������������ܾ����Ͳ�����false
	if (getWaitingState()) {
		return false;
	}

	// ׼�����͵ı���
	waitpacket.acknum = -1; // ����ȷ�Ϻ�Ϊ��Чֵ
	waitpacket.checksum = 0; // ��ʼ��У���Ϊ0
	waitpacket.seqnum = expectednum; // �������Ϊ���������

	// ����Ϣ�����ݸ��Ƶ����ĵĸ�����
	memcpy(waitpacket.payload, message.data, sizeof(message.data));
	// ���㱨�ĵ�У���
	waitpacket.checksum = pUtils->calculateCheckSum(waitpacket);
	// ����һ�����ڴ洢���ĺͽ���״̬�Ľṹ��ʵ��
	getpacket temp;
	temp.receive = false;
	temp.packet = waitpacket;
	// �����ĺͽ���״̬��ӵ�������
	window.push_back(temp);

	// ��ӡ���ͱ��ĵ���Ϣ
	pUtils->printPacket("���ͷ����ͱ���", waitpacket);
	// ������ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, expectednum);
	// ͨ������㷢�ͱ���
	pns->sendToNetworkLayer(RECEIVER, waitpacket);
	// �����������
	expectednum = (expectednum + 1) % sequencelen;

	// ����true����ʾ���ͳɹ�
	return true;
}

// ���պ���
void SRSender::receive(const Packet& ackPkt) {
	// ����ȷ�ϱ��ĵ��������ڻ���ŵ�ƫ����
	int offset = (ackPkt.acknum - basenum + sequencelen) % sequencelen;
	// �ٴ�ȷ��ƫ������һ���Ǹ���
	offset = (offset + sequencelen) % sequencelen;
	// ���㱨�ĵ�У���
	int checksum = pUtils->calculateCheckSum(ackPkt);

	// ���ȷ�ϱ��ĵ�����ڴ����У��ñ�����δ��ȷ�ϣ�����У�����ȷ
	if (offset < window.size() && window.at(offset).receive == false && checksum == ackPkt.checksum) {
		// ֹͣ��ʱ��
		pns->stopTimer(SENDER, ackPkt.acknum);
		// ��Ǳ���Ϊ��ȷ��
		window.at(offset).receive = true;

		// ��ӡ���ͷ����ڵ���Ϣ
		// ��ӡ����ȷ�ϱ��ĵ���Ϣ
		printf("���ͷ�����:[");
		for (int i = 0; i < windowlen; i++) {
			if (window.size() > i) {
				if (window.at(i).receive == true) {
					printf("%dY ", (basenum + i) % sequencelen);
				}
				else {
					printf("%dN ", (basenum + i) % sequencelen);
				}
			}
			else {
				printf("%d ", (basenum + i) % sequencelen);
			}
		}
		printf("]\n");
		// ��ӡ����ȷ�ϱ��ĵ���Ϣ
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ�ϱ���", ackPkt);
		// ��������
		while (!window.empty() && window.front().receive == true) {
			window.pop_front();
			basenum = (basenum + 1) % sequencelen;
		}

		// ��ӡ������Ĵ�����Ϣ
		printf("���ͷ���������:[");
		for (int i = 0; i < windowlen; i++) {
			if (i < window.size()) {
				if (window.at(i).receive == true) {
					printf("%dY ", (basenum + i) % sequencelen);
				}
				else {
					printf("%dN ", (basenum + i) % sequencelen);
				}
			}
			else {
				printf("%d ", (basenum + i) % sequencelen);
			}
		}
		printf("]\n");
	}
	// ���У��ʹ���
	else if (ackPkt.checksum != checksum) {
		pUtils->printPacket("���ͷ�����ȷ�ϱ���ʧ��,corrupt", ackPkt);

	}
	// ���ȷ�ϱ��ĵ���Ų��ڴ����л�ñ����Ѿ���ȷ��
	else {
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ�ϱ���", ackPkt);
	}
}
