#pragma once // 防止头文件重复引用
#include "RdtSender.h" // 引入RdtSender类的声明
#include<deque> // 引入deque（双端队列）容器

using namespace std;

// TCPSender类，继承自RdtSender类
class TCPSender :public RdtSender
{
private:
    int expectnum;	// 期望发送的下一个序号
    bool state; // 发送状态，这个变量在代码中定义了但并未使用
    int acknum; // 用于记录冗余ACK的数量
    int basenum; // 窗口的基序号
    int windowlen; // 窗口大小
    int sequencelen; // 序号的范围
    deque<Packet> window; // 用deque容器来保存窗口中的数据包
    Packet waitpacket;	// 保存等待发送的数据包

public:
    // 判断发送方是否处于等待状态的函数
    bool getWaitingState();
    // 发送消息的函数，参数为Message类型的引用
    bool send(const Message& message);
    // 接收确认报文的函数，参数为Packet类型的引用
    void receive(const Packet& ackPkt);
    // 定时器超时处理函数，参数为整数，表示序列号
    void timeoutHandler(int seqNum);

public:
    // 构造函数
    TCPSender();
    // 虚析构函数
    virtual ~TCPSender();
};
