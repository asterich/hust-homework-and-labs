#pragma once
#include <deque>
#include "RdtSender.h"

using namespace std;

// 定义结构体getpacket，用于保存已发送的数据包及其接收状态
struct getpacket {
	bool receive;  // 标志该数据包是否已被接收方正确接收
	Packet packet; // 数据包
};

// 继承自RdtSender的SRSender类，实现了SR协议的发送方
class SRSender : public RdtSender {
public:
	bool getWaitingState(); // 获取发送方当前是否处于等待状态
	bool send(const Message& message); // 发送消息
	void receive(const Packet& ackPkt); // 接收确认包
	void timeoutHandler(int seqNum); // 超时处理函数
	virtual ~SRSender(); // 析构函数
	SRSender(); // 构造函数

private:
	int expectednum; // 下一个期望发送的序列号
	bool state; // 发送方当前的状态，true为等待状态，false为发送状态
	int basenum; // 窗口的基序号
	int windowlen; // 窗口大小
	int sequencelen; // 序列号的取值范围
	deque<getpacket> window; // 发送窗口，用双端队列实现
	Packet waitpacket; // 当发送方处于等待状态时，保存等待发送的数据包
};
