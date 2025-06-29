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

// 构造函数
TCPReceiver::TCPReceiver() : sequencenum(0), expectednum(0) {
	// 初始化最后一个接收到并确认的数据包的各个字段
	lastpacket.acknum = -1;
	lastpacket.checksum = 0;
	lastpacket.seqnum = -1;
	// 初始化payload字段，这里全部初始化为'.'字符
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastpacket.payload[i] = '.';
	}
	// 计算并设置校验和
	lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);
}

// 析构函数
TCPReceiver::~TCPReceiver() {}

// 接收报文的函数
void TCPReceiver::receive(const Packet& packet) {
	// 首先计算接收到的报文的校验和
	int checksum = pUtils->calculateCheckSum(packet);

	// 判断校验和是否正确，并且报文序号是否是期望的序号
	if (checksum == packet.checksum && expectednum == packet.seqnum) {
		// 校验和正确，报文序号也是期待的序号
		// 打印日志，说明接收方正确地接收到了发送方的报文
		pUtils->printPacket("接收方正确接收到了发送方的报文", packet);

		// 构造Message对象，并将接收到的payload复制到Message的data字段
		Message message;
		memcpy(message.data, packet.payload, sizeof(packet.payload));

		// 调用pns->delivertoAppLayer函数，将接收到的数据传递给应用层
		pns->delivertoAppLayer(RECEIVER, message);

		// 更新lastpacket为当前接收到的packet
		lastpacket.acknum = packet.seqnum;
		lastpacket.checksum = pUtils->calculateCheckSum(lastpacket);

		// 打印日志，说明接收方将要发送确认报文
		pUtils->printPacket("接收方发送确认报文", lastpacket);

		// 调用pns->sendToNetworkLayer函数，将确认报文发送给发送方
		pns->sendToNetworkLayer(SENDER, lastpacket);

		// 更新期待的序号，这里假设序号空间是0-7
		expectednum = (expectednum + 1) % 8;
	}
	else {
		// 校验和错误或报文序号不是期待的
		if (checksum != packet.checksum) {
			// 如果是校验和错误，打印相关日志
			pUtils->printPacket("接收方接收到的报文校验和错误", packet);
		}
		else {
			// 如果是报文序号不对，打印相关日志
			pUtils->printPacket("接收方接收到的报文序号错误", packet);
		}

		// 不管是因为校验和错误还是序号错误，接收方都需要重新发送上一个确认报文
		pUtils->printPacket("接收方重新发送上一个确认报文", lastpacket);
		pns->sendToNetworkLayer(SENDER, lastpacket);
	}
}
