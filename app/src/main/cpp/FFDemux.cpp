//
// Created by zy on 7/17/2018.
//

#include "FFDemux.h"
#include "XLog.h"
extern"C"{
#include<libavformat/avformat.h>
}

static double r2d(AVRational r){
    return r.num==0|| r.den==0? 0.:(double)r.num/(double)r.den;
}

void FFDemux::Close(){
    mux.lock();
    if(ic)
        avformat_close_input(&ic);
    mux.unlock();
}

//打开文件或者流媒体 rmtp,http,rtsp
bool FFDemux::Open(const char* url){
    XLOGI("Open file %s begin",url);
    Close();
    mux.lock();
    int re = avformat_open_input(&ic,url,0,0);
    if(re!=0){
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDemux open %s failed!",url);
        return false;
    }
    XLOGI("FFDemux open %s success!",url);

    //读取文件信息
    re = avformat_find_stream_info(ic,0);
    if(re!=0){
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("avformat_find_stream_info %s failed!",url);
        return false;
    }

    this->totalMs = ic->duration/(AV_TIME_BASE/1000);
    XLOGI("total ms = %d",totalMs);
    mux.unlock(); //GetVPara GetAPara里面可能还会有锁，锁两次会造成死锁
    // 就是为了获取音视频流index
    GetVPara();
    GetAPara();
    return true;
}


//读取一帧数据，数据由调用者清理
XData FFDemux::Read(){
    mux.lock();
    if(!ic) {
        mux.unlock();
        return XData();
    }
    XData d;
    AVPacket* pkt = av_packet_alloc();
    int re = av_read_frame(ic,pkt);
    if(re!=0){
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }
//    XLOGI("pack size is %d, pts is %lld",pkt->size,pkt->pts);
    d.data = (unsigned char*)pkt;
    d.size = pkt->size;

    if(pkt->stream_index == audioStream){
        d.isAudio = true;
    } else if(pkt->stream_index == videoStream) {
        d.isAudio = false;
    }else{
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }

    //转换pts
    pkt->pts = pkt->pts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    d.pts = (int) pkt->pts;
    //XLOGE("demux pts is %d",d.pts);
    mux.unlock();
    return d;
}
//获取视频参数
XParameter FFDemux::GetVPara(){
    mux.lock();
    if(!ic){
        mux.unlock();
        XLOGE("GetVPara failed, ic is null");
        return XParameter();
    }
    //获取视频流索引
    int re = av_find_best_stream(ic,AVMEDIA_TYPE_VIDEO,-1,-1,0,0);
    if(re<0){
        mux.unlock();
        XLOGE("av_find_best_stream failed");
        return XParameter();
    }
    videoStream = re;//通知解封装器 视频流的index
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    mux.unlock();
    return para;
}

//获取音频参数->音频解码器,重采样
XParameter FFDemux::GetAPara(){
    mux.lock();
    if(!ic){
        mux.unlock();
        XLOGE("GetAPara failed, ic is null");
        return XParameter();
    }
    //获取音频流索引
    int re = av_find_best_stream(ic,AVMEDIA_TYPE_AUDIO,-1,-1,0,0);
    if(re<0){
        mux.unlock();
        XLOGE("av_find_best_stream failed");
        return XParameter();
    }
    audioStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    para.channels = ic->streams[re]->codecpar->channels;
    para.sample_rate = ic->streams[re]->codecpar->sample_rate;
    mux.unlock();
    return para;
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if(isFirst){
        isFirst = false;
        //注册所有封装器
        av_register_all();
        //注册所有解码器
        avcodec_register_all();
        //初始化网络
        avformat_network_init();
        XLOGI("register ffmpeg");
    }
 }