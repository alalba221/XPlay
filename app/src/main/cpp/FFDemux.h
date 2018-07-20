//
// Created by zy on 7/17/2018.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


//#include <libavformat/avformat.h>//如果有这句就错了？？？？？
//没有用引用的同文件，反而自己定义了这个结构体，设计模式参考了qt 因为是指针所以无所谓
struct AVFormatContext;
#include "IDemux.h"

class FFDemux: public IDemux {
public:

    //打开文件或者流媒体 rmtp,http,rtsp
    virtual bool Open(const char* url);
    //读取一帧数据，数据由调用者清理
    virtual XData Read();
    FFDemux();

private:
    AVFormatContext* ic = 0;
};


#endif //XPLAY_FFDEMUX_H
