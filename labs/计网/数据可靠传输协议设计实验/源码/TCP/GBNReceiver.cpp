#include "stdafx.h"
#include "Global.h"
#include "GBNReceiver.h"

// GBNReceiver类的析构函数
GBNReceiver::~GBNReceiver()
{
    // 当对象被销毁时执行的操作
}

// GBNReceiver类的构造函数
GBNReceiver::GBNReceiver() :len(8), expectnum(0) {
    // 初始化上次接收的数据包的checksum为0
    last.checksum = 0;

    // 设置初始状态下，上次ack的确认序号为-1
    last.seqnum = last.acknum = -1;

    // 获取配置中的载荷大小
    int len = Configuration::PAYLOAD_SIZE;

    // 初始化payload数据
    for (int i = 0; i < len; i++) {
        last.payload[i] = '.';
    }

    // 计算初始化后的数据包的checksum
    last.checksum = pUtils->calculateCheckSum(last);
}

// GBNReceiver的接收方法
void GBNReceiver::receive(const Packet& packet) {
    // 计算接收到的数据包的checksum
    int checksum = pUtils->calculateCheckSum(packet);

    // 如果接收到的数据包的checksum与期望的checksum相匹配，且序列号也匹配
    if (checksum == packet.checksum && expectnum == packet.seqnum) {
        // 打印日志，表示正确接收到了数据包
        pUtils->printPacket("接收得到正确报文", packet);

        // 创建一个消息对象
        Message msg;
        // 将数据包的payload复制到消息中
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        // 将消息传递给应用层
        pns->delivertoAppLayer(RECEIVER, msg);

        // 更新上次接收到的数据包的ack序列号
        last.acknum = packet.seqnum;
        // 更新上次接收到的数据包的checksum
        last.checksum = pUtils->calculateCheckSum(last);
        // 打印日志，表示发送确认报文
        pUtils->printPacket("发送确认报文", last);
        // 发送确认报文到网络层
        pns->sendToNetworkLayer(SENDER, last);
        // 更新期望接收的序列号
        expectnum = (expectnum + 1) % len;
    }
    // 如果数据包不匹配
    else {
        // 如果接收到的数据包的checksum与计算的checksum不匹配
        if (packet.checksum != checksum) {
            pUtils->printPacket("接收发送报文失败，corrupt!", packet);
        }
        // 如果序列号不匹配
        else {
            pUtils->printPacket("接收发送报文失败, 序号有误", packet);
        }
        // 打印日志，表示重发确认报文
        pUtils->printPacket("接收方重发确认报文", last);
        // 重发确认报文到网络层
        pns->sendToNetworkLayer(SENDER, last);
    }
}
