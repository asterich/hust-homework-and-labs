#include <deque>
#include "stdafx.h"
#include "Global.h"
#include "GBNSender.h"

using namespace std;

// GBNSender类的析构函数
GBNSender::~GBNSender()
{
    // 当对象被销毁时执行的操作
}

// GBNSender类的构造函数
GBNSender::GBNSender() :sequencelen(8), windowlen(4), basenum(0), isWaiting(false), expectnum(0)
{
    // 初始化发送窗口的各项参数
}

// 获取当前发送窗口的状态：是否正在等待
bool GBNSender::getWaitingState() {
    if (windowlen != window.size())  // 如果窗口中的数据包数不等于窗口长度
        isWaiting = false;           // 不在等待状态
    else
        isWaiting = true;            // 否则，在等待状态

    return isWaiting;
}

// 超时处理函数
void GBNSender::timeoutHandler(int seqNum) {
    pns->stopTimer(SENDER, seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
    int len = window.size();
    for (int i = 0; i < len; i++) {
        // 打印超时日志，并重新发送窗口内的所有数据包
        pUtils->printPacket("定时器中断，重新发窗口内的报文", window.at(i));
        pns->sendToNetworkLayer(RECEIVER, window.at(i));
    }
}

// 发送消息
bool GBNSender::send(const Message& message) {
    if (getWaitingState())  // 如果当前在等待状态，则直接返回false
        return false;

    waitackPacket.acknum = -1;
    waitackPacket.seqnum = expectnum;
    waitackPacket.checksum = 0;
    // 复制消息内容到待发送数据包的载荷部分
    memcpy(waitackPacket.payload, message.data, sizeof(message.data));
    // 计算数据包的checksum
    waitackPacket.checksum = pUtils->calculateCheckSum(waitackPacket);
    window.push_back(waitackPacket);  // 将数据包添加到发送窗口
    pUtils->printPacket("发送方发送报文", this->waitackPacket);

    // 如果当前发送的是窗口的第一个数据包，则开启定时器
    if (expectnum == basenum) {
        pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
    }

    // 发送数据包到网络层
    pns->sendToNetworkLayer(RECEIVER, waitackPacket);
    expectnum = (expectnum + 1) % sequencelen;  // 更新下一个期望发送的序列号

    return true;
}

// 接收确认数据包
void GBNSender::receive(const Packet& packet) {
    int notacknum = (packet.acknum - basenum + sequencelen) % sequencelen;
    int checkSum = pUtils->calculateCheckSum(packet);

    // 如果接收到的确认数据包的序列号在发送窗口内，并且checksum匹配
    if (notacknum < window.size() && checkSum == packet.checksum) {
        printf("发送窗口:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ,", (basenum + i) % sequencelen);
        }
        printf("]\n");
        pUtils->printPacket("收到确认报文", packet);
        // 停止定时器，并移除窗口中已被确认的数据包
        pns->stopTimer(SENDER, basenum);
        while (basenum != (packet.acknum + 1) % sequencelen) {
            window.pop_front();
            basenum = (basenum + 1) % sequencelen;
        }
        printf("发送方发送报文后窗口:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ,", (basenum + i) % sequencelen);
        }
        printf("]\n");
        // 如果窗口中还有未被确认的数据包，则重新开启定时器
        if (!window.empty()) {
            pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
        }
    }
    else if (packet.checksum != checkSum) {  // 如果checksum不匹配
        pUtils->printPacket("发送方接收到的确认报文corrupt", packet);
    }
    else {  // 如果checksum匹配，但序列号不在窗口内
        pUtils->printPacket("发送方正确收到了确认报文", packet);
    }
}
