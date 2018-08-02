//
// Created by zy on 7/17/2018.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


//#include <libavformat/avformat.h>//如果有这句就错了？？？？？
//没有用引用的同文件，反而自己定义了这个结构体，设计模式参考了qt 因为是指针所以无所谓
struct AVFormatContext;
#include "IDemux.h"
#include<mutex>
class FFDemux: public IDemux {
public:

    //打开文件或者流媒体 rmtp,http,rtsp
    virtual bool Open(const char* url);
    virtual void Close();
    //读取一帧数据，数据由调用者清理
    virtual XData Read();

    //获取视频参数
    virtual XParameter GetVPara();
    //获取音频参数->音频解码器,重采样
    virtual XParameter GetAPara();
    FFDemux();

private:
    AVFormatContext* ic = 0;
    std::mutex mux;//针对Open Read 对ic的访问
    //音视频流的标号
    int audioStream = 1;
    int videoStream = 0;
};


#endif //XPLAY_FFDEMUX_H
