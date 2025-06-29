#pragma once

#include <deque>
#include "RdtReceiver.h"

using namespace std;

// 定义结构体receivePacket，用于保存接收窗口中的数据包及其占用状态
struct receivePacket {
	Packet packet;    // 数据包
	bool occupied;    // 是否已占用（是否已接收到有效数据包）
};

// 继承自RdtReceiver的SRReceiver类，实现了SR协议的接收方
class SRReceiver : public RdtReceiver {
public:
	virtual ~SRReceiver(); // 析构函数
	SRReceiver(); // 构造函数
	void receive(const Packet& packet); // 接收数据包

private:
	int expectednum; // 下一个期望接收的序列号
	int basenum; // 窗口的基序号
	int windowlen; // 窗口大小
	int sequencelen; // 序列号的取值范围
	Packet lastpacket; // 用于保存上一次发送的确认包
	deque<receivePacket> window; // 接收窗口，用双端队列实现
};
