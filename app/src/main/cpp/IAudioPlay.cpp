//
// Created by zy on 7/30/2018.
//

#include "IAudioPlay.h"
#include "XLog.h"

//获取缓冲数据，如果没有则阻塞
XData IAudioPlay::GetData(){
    XData d;
    while(!isExit){
        framesMutex.lock();
        if(!frames.empty()){
            d=frames.front();
            frames.pop_front();
            framesMutex.unlock();
            return d;
        }
        framesMutex.unlock();
        XSleep(1);
    }
    return d;
}

void IAudioPlay::Update(XData data){
    //XLOGE("IAudioPlay::Update %d",data.size);
    //压入缓冲队列
    if(data.size<=0||!data.data) return;
    while(!isExit){

        framesMutex.lock();
        if(frames.size()>maxFrame) {
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        break;
    }
}