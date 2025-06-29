#pragma once // 防止头文件重复引用
#include "RdtReceiver.h" // 引入RdtReceiver类的声明

// TCPReceiver类，继承自RdtReceiver类
class TCPReceiver :public RdtReceiver {
public:
    // 构造函数
    TCPReceiver();
    // 虚析构函数
    virtual ~TCPReceiver();
    // 接收数据包的函数，参数为Packet类型的引用
    void receive(const Packet& packet);

private:
    Packet lastpacket; // 用于保存上一次发送的确认包
    int sequencenum; // 序号
    int expectednum; // 期望接收的下一个数据包的序号
};
