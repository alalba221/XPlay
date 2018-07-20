//
// Created by zy on 7/17/2018.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include"XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

class IDemux :public IObserver{
    //线程的处理和FFMepg无关，所以放在接口类
public:
    //打开文件或者流媒体 rmtp,http,rtsp
    virtual bool Open(const char* url)=0;

    //获取视频参数
    virtual XParameter GetVPara()=0;
    //读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;
    //总时长（ms）
    int totalMs = 0;
protected:
    virtual void Main();
};


#endif //XPLAY_IDEMUX_H
