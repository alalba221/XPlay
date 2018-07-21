//
// Created by zy on 7/20/2018.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"

//解码接口，支持硬解码
class IDecode: public IObserver {
public:
    //打开解码器
    virtual bool Open(XParameter para)=0;

    //future 模型， 发送一帧数据到线程解码
    virtual bool SendPacket(XData pkt)=0;
    //从线程中获取一帧解码结果
    virtual XData RecvFrame()=0;
};


#endif //XPLAY_IDECODE_H
