#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"

SRReceiver::~SRReceiver() {}

SRReceiver::SRReceiver() : windowlen(4), basenum(0), sequencelen(8), expectednum(0) {
	// 初始化最后一个接收到的确认包的数据
	lastpacket.checksum = 0;
	lastpacket.acknum = -1;
	lastpacket.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastpacket.payload[i] = '.';
	}
	// 计算确认包的校验和
	lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);

	// 初始化滑动窗口
	for (int i = 0; i < windowlen; i++) {
		receivePacket temp;
		temp.packet.seqnum = -1;
		temp.occupied = false;
		window.push_back(temp);
	}
}


void SRReceiver::receive(const Packet& packet) {
	// 计算接收到的报文的序列号在窗口中的偏移量
	int offset = (packet.seqnum - basenum + sequencelen) % sequencelen;
	offset = (offset + sequencelen) % sequencelen;
	// 计算接收到的报文的校验和
	int checksum = pUtils->calculateCheckSum(packet);

	// 判断报文是否在窗口内并且该位置上没有接收到报文，并且报文没有损坏
	if (offset < windowlen && window.at(offset).occupied == false && checksum == packet.checksum) {
		// 将报文保存在窗口的正确位置
		window.at(offset).occupied = true;
		window.at(offset).packet = packet;

		// 打印当前窗口的状态
		printf("接收方窗口:[ ");
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

		// 输出报文接收情况
		pUtils->printPacket("接收方正确完好收到报文", packet);

		// 如果窗口中最前面的报文已经接收，则将其逐一交付给上层，并滑动窗口
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

		// 打印滑动窗口滑动后的状态
		printf("接收方滑动窗口:[");
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

		// 设置确认报文的序列号，并计算校验和
		lastpacket.acknum = packet.seqnum;
		lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);
		// 发送确认报文
		pUtils->printPacket("接收方发送报文", lastpacket);
		pns->sendToNetworkLayer(SENDER, lastpacket);
	}
	// 如果报文损坏或已经被确认
	else {
		if (packet.checksum != checksum) {
			// 报文损坏，打印错误信息
			pUtils->printPacket("接收方接收报文错误，corrupt", packet);
		}
		else {
			// 报文已经被确认，重新发送确认报文
			pUtils->printPacket("接收方接收到了一个已经确认的报文", packet);
			lastpacket.acknum = packet.seqnum;
			lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);
			pUtils->printPacket("接收方重新发送确认报文", lastpacket);
			pns->sendToNetworkLayer(SENDER, lastpacket);
		}
	}
}


