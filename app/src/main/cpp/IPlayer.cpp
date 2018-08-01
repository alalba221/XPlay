//
// Created by zy on 7/31/2018.
//

#include "IPlayer.h"
#include "IDecode.h"
#include "IDemux.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "IResample.h"
#include "XLog.h"

IPlayer* IPlayer::Get(unsigned char index){
    static IPlayer p[256];
    return &p[index];
}

bool IPlayer::Open(const char* path){
    //解封装
    if(!demux || !demux->Open(path)){
        XLOGE("demux->Open %s failed",path);
        return false;
    }
    //解码 解码可能不需要，因为解封后可能就是原始数据
    if(!vdecode||!vdecode->Open(demux->GetVPara(),isHardDecode)){
        XLOGE("vdecode->Open FAILED");
        //return false;
    }
    if(!adecode||!adecode->Open(demux->GetAPara())){
        XLOGE("adecode->Open FAILED");
        //return false;
    }

    //重采样，可能不需要，解码或解封后就是可以播放的数据
    if(outPara.sample_rate<=0)
        outPara = demux->GetAPara();
    if(!resample||!resample->Open(demux->GetAPara(),outPara)){
        XLOGE("resample->Open FAILED");
        //return false;
    }


    return true;
}
bool IPlayer::Start(){
    if(!demux||!demux->Start()){
        XLOGE("demux->Start() FAILED");
        return false;
    }
    //音频启动,播放
    if(adecode){
        adecode->Start();
    }
    if(audioPlay){
        audioPlay->StartPlay(outPara);
    }
    //
    if(vdecode){
        vdecode->Start();
    }
    return true;
}

void IPlayer::InitView(void* win){
    if(videoView){
        videoView->SetRender(win);
    }
}
