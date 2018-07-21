//
// Created by zy on 7/20/2018.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"
#include<list>

//解码接口，支持硬解码
class IDecode: public IObserver {
public:
    //打开解码器
    virtual bool Open(XParameter para)=0;

    //future 模型， 发送一帧数据到线程解码
    virtual bool SendPacket(XData pkt)=0;
    //从线程中获取一帧解码结果,从线程中解码出数据会复用上次空间
    //线程不安全(取出的数据只能在当前线程用，其他线程用不了)
    virtual XData RecvFrame()=0;

    //由主体notidy的数据通过update来接受数据，阻塞
    virtual void Update(XData pkt);
    bool isAudio = false;//判断当前是否是音频解码器
    int maxList = 100;//解码队列最大长度
protected:
    virtual void Main();
    //解码队列,缓冲帧,UPdate 会往里面插入数据
    std::list<XData> packs;
    std::mutex packsMutex;
};


#endif //XPLAY_IDECODE_H
