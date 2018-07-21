//
// Created by zy on 7/20/2018.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode: public IDecode {
public:
    virtual bool Open(XParameter para);

    //future 模型， 发送数据到线程解码
    virtual bool SendPacket(XData pkt);
    //从线程中获取解码结果
    virtual XData RecvFrame();
protected:
    AVCodecContext* codec=0;
    AVFrame *frame = 0;
};


#endif //XPLAY_FFDECODE_H
