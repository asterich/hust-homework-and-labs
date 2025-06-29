#include "stdafx.h"
#include "Global.h"
#include "TCPSender.h"

// 构造函数
TCPSender::TCPSender() : expectnum(0), state(false), basenum(0), windowlen(4), sequencelen(8), acknum(0) {
}

// 析构函数
TCPSender::~TCPSender() {
}

// 判断发送方是否处于等待状态
bool TCPSender::getWaitingState() {
    // 当窗口大小等于窗口长度时，返回true，表示发送方正在等待确认报文
    return window.size() == windowlen;
}

// 发送数据包
bool TCPSender::send(const Message& message) {
    // 如果处于等待状态，则不能发送数据，直接返回false
    if (getWaitingState()) {
        return false;
    }

    // 初始化待发送的数据包
    waitpacket.acknum = -1;  // acknum字段在发送数据包时被忽略
    waitpacket.seqnum = expectnum;  // 设置数据包的序号为期待的序号
    waitpacket.checksum = 0;  // 初始化校验和为0
    // 将消息的内容复制到数据包的payload字段
    memcpy(waitpacket.payload, message.data, sizeof(message.data));
    // 计算并设置数据包的校验和
    waitpacket.checksum = pUtils->calculateCheckSum(waitpacket);

    // 将数据包添加到窗口中
    window.push_back(waitpacket);
    // 打印日志，显示发送的数据包
    pUtils->printPacket("发送方发送报文", waitpacket);

    // 如果窗口的基序号等于期待的序号，则启动定时器
    if (basenum == expectnum) {
        pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
    }
    // 发送数据包到网络层
    pns->sendToNetworkLayer(RECEIVER, waitpacket);

    // 更新期待的序号
    expectnum = (expectnum + 1) % sequencelen;

    // 返回true，表示数据包发送成功
    return true;
}

// 接收确认报文
void TCPSender::receive(const Packet& ackPkt) {
    // 计算接收到的确认报文的校验和
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    // 计算偏移量，即确认报文的序号和窗口基序号的差值
    int offset = (ackPkt.acknum - basenum + sequencelen) % sequencelen;

    // 判断校验和是否正确，并且确认报文的序号是否在窗口中
    if (checkSum == ackPkt.checksum && offset < window.size()) {

        printf("发送方窗口:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ", (basenum + i) % sequencelen);
        }
        printf("]\n");


        // 校验和正确，序号也在窗口中
        // 打印日志，显示接收到的确认报文
        pUtils->printPacket("发送方正确收到确认", ackPkt);
        // 停止定时器
        pns->stopTimer(SENDER, basenum);

        // 更新窗口
        while (basenum != (ackPkt.acknum + 1) % sequencelen) {
            window.pop_front();
            basenum = (basenum + 1) % sequencelen;
        }

        printf("发送方滑动窗口:[");
        for (int i = 0; i < windowlen; i++) {
            printf("%d ", (basenum + i) % sequencelen);
        }
        printf("]\n");

        // 重置冗余ACK计数器
        acknum = 0;
        // 如果窗口不为空，启动定时器
        if (!window.empty()) {
            pns->startTimer(SENDER, Configuration::TIME_OUT, basenum);
        }
    }
    else if (checkSum != ackPkt.checksum) {
        // 如果校验和错误，打印日志
        pUtils->printPacket("发送方没有正确收到确认，校验和错误", ackPkt);
    }
    else if (ackPkt.acknum == (basenum + sequencelen - 1) % sequencelen) {
        // 如果收到的是之前已经确认的包，更新冗余ACK计数器
        pUtils->printPacket("发送方收到了之前已经确认的包", ackPkt);
        acknum++;
        // 如果冗余ACK计数器达到3，触发快速重传，重发窗口中最早的数据包
        if (acknum == 3 && !window.empty()) {
            pUtils->printPacket("发送方触发快速重传，重发最早的未被确认的报文段", window.front());
            pns->sendToNetworkLayer(RECEIVER, window.front());
            acknum = 0;  // 重置冗余ACK计数器
        }
    }
}

// 定时器超时处理函数
void TCPSender::timeoutHandler(int seqNum) {
    // 打印日志，显示重发的数据包
    pUtils->printPacket("发送方定时器时间到，重发最早的未被确认的报文段", window.front());
    // 停止并重启定时器
    pns->stopTimer(SENDER, seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
    // 重发窗口中最早的数据包
    pns->sendToNetworkLayer(RECEIVER, window.front());
}
