// TCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "TCPSender.h"
#include "TCPReceiver.h"


int main(int argc, char* argv[])
{
	RdtSender* ps = new TCPSender();
	RdtReceiver* pr = new TCPReceiver();
	//	pns->setRunMode(0);  //VERBOS模式
	pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("E:\\hyf network\\TCP\\input.txt");
	pns->setOutputFile("E:\\hyf network\\TCP\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete

	return 0;
}

