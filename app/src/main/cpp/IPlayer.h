//
// Created by zy on 7/31/2018.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H


#include "XThread.h"
#include "XParameter.h"

class IDemux;
class IDecode;
class IResample;
class IVideoView;
class IAudioPlay;

class IPlayer : public XThread{
public:
    static IPlayer* Get(unsigned char index=0);
    virtual bool Open(const char* path);
    virtual bool Start();

    virtual void InitView(void* win);
    //是否硬解码
    bool isHardDecode = true;
    IDemux* demux=0;
    IDecode* vdecode = 0;
    IDecode* adecode = 0;
    IResample* resample = 0;
    IVideoView* videoView = 0;
    IAudioPlay* audioPlay = 0;
//音频输出参数
    XParameter outPara;
protected:
    IPlayer(){};
};


#endif //XPLAY_IPLAYER_H
