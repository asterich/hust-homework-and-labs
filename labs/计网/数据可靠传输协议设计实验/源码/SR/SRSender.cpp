#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"

// 析构函数
SRSender::~SRSender() {}

// 构造函数：初始化发送序列号长度为8，窗口长度为4，基序号为0，状态为非等待状态，期望序号为0
SRSender::SRSender() :sequencelen(8), windowlen(4), basenum(0), state(false), expectednum(0) {}

void switchtolog1() {
	freopen("E:\\hyf network\\SR\\log.txt", "a", stdout);
}

void switchtocmd1() {
	fclose(stdout);
	freopen("CON", "a", stdout);
}
// 获取发送方的等待状态
bool SRSender::getWaitingState() {
	// 如果窗口已满，则设置等待状态为true；否则设置为false
	if (windowlen == window.size()) {
		state = true;
	}
	else {
		state = false;
	}
	// 返回等待状态
	return state;
}

// 超时处理函数
void SRSender::timeoutHandler(int seqNum) {
	// 计算超时报文的序号相对于基序号的偏移量
	int offset = (seqNum - basenum + sequencelen) % sequencelen;
	// 停止定时器
	pns->stopTimer(SENDER, seqNum);
	// 重新启动定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	// 重新发送报文
	pns->sendToNetworkLayer(RECEIVER, window.at(offset).packet);
	// 打印重发报文的信息
	pUtils->printPacket("发送方时钟中断，重发报文", window.at(offset).packet);
}

// 发送函数
bool SRSender::send(const Message& message) {
	// 如果窗口已满，则拒绝发送并返回false
	if (getWaitingState()) {
		return false;
	}

	// 准备发送的报文
	waitpacket.acknum = -1; // 设置确认号为无效值
	waitpacket.checksum = 0; // 初始化校验和为0
	waitpacket.seqnum = expectednum; // 设置序号为期望的序号

	// 将消息的内容复制到报文的负载中
	memcpy(waitpacket.payload, message.data, sizeof(message.data));
	// 计算报文的校验和
	waitpacket.checksum = pUtils->calculateCheckSum(waitpacket);
	// 创建一个用于存储报文和接收状态的结构体实例
	getpacket temp;
	temp.receive = false;
	temp.packet = waitpacket;
	// 将报文和接收状态添加到窗口中
	window.push_back(temp);

	// 打印发送报文的信息
	pUtils->printPacket("发送方发送报文", waitpacket);
	// 启动定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, expectednum);
	// 通过网络层发送报文
	pns->sendToNetworkLayer(RECEIVER, waitpacket);
	// 更新期望序号
	expectednum = (expectednum + 1) % sequencelen;

	// 返回true，表示发送成功
	return true;
}

// 接收函数
void SRSender::receive(const Packet& ackPkt) {
	// 计算确认报文的序号相对于基序号的偏移量
	int offset = (ackPkt.acknum - basenum + sequencelen) % sequencelen;
	// 再次确保偏移量是一个非负数
	offset = (offset + sequencelen) % sequencelen;
	// 计算报文的校验和
	int checksum = pUtils->calculateCheckSum(ackPkt);

	// 如果确认报文的序号在窗口中，该报文尚未被确认，并且校验和正确
	if (offset < window.size() && window.at(offset).receive == false && checksum == ackPkt.checksum) {
		// 停止定时器
		pns->stopTimer(SENDER, ackPkt.acknum);
		// 标记报文为已确认
		window.at(offset).receive = true;

		// 打印发送方窗口的信息
		// 打印接收确认报文的信息
		printf("发送方窗口:[");
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
		// 打印接收确认报文的信息
		pUtils->printPacket("发送方正确收到确认报文", ackPkt);
		// 滑动窗口
		while (!window.empty() && window.front().receive == true) {
			window.pop_front();
			basenum = (basenum + 1) % sequencelen;
		}

		// 打印滑动后的窗口信息
		printf("发送方滑动窗口:[");
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
	// 如果校验和错误
	else if (ackPkt.checksum != checksum) {
		pUtils->printPacket("发送方接收确认报文失败,corrupt", ackPkt);

	}
	// 如果确认报文的序号不在窗口中或该报文已经被确认
	else {
		pUtils->printPacket("发送方正确收到确认报文", ackPkt);
	}
}
