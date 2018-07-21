//
// Created by zy on 7/20/2018.
//
extern"C"
{
    #include <libavcodec/avcodec.h>
}
#include "FFDecode.h"
#include "XLog.h"

bool FFDecode::Open(XParameter para){
    if(!para.para) return false;
    AVCodecParameters* p = para.para;
    //1. 查找解码器
    AVCodec* cd = avcodec_find_decoder(p->codec_id);
    if(!cd){
        XLOGE("avcodec_find_decoder %d failed!",p->codec_id);
        return false;
    }
    XLOGI("avcodec_find_decoder success!");
    //2. 创建解码上下文，并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec,p);

    codec->thread_count=8; //多线程解码
    //3. 打开解码器
    int re = avcodec_open2(codec,0,0);
    if(re != 0){
        char buff[1024] = {0};
        av_strerror(re,buff, sizeof(buff)-1);
        XLOGE("%s",buff);
        return false;
    }
    XLOGI("avcodec_open2 success");
    return true;
}

//future 模型， 发送数据到线程解码
bool FFDecode::SendPacket(XData pkt){

    if(pkt.size<=0 || !pkt.data) return false;
    if(!codec){
        return false;
    }
    int re = avcodec_send_packet(codec,(AVPacket*)pkt.data);
    if(re !=0){
        return false;
    }

    return true;
}
//从线程中获取解码结果
XData FFDecode::RecvFrame(){

    if(!codec){
        return XData();
    }
    if(!frame){
        frame = av_frame_alloc();
    }
    int re = avcodec_receive_frame(codec,frame);
    if(re!=0){
        return XData();
    }
    XData d;
    d.data = (unsigned char*)frame;
    if(codec->codec_type==AVMEDIA_TYPE_VIDEO)
        d.size = (frame->linesize[0]+frame->linesize[1]+frame->linesize[2])*frame->height;
    return d;
    //return XData();
}