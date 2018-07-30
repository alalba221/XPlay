//
// Created by zy on 7/30/2018.
//

#include "IAudioPlay.h"
#include "XLog.h"

void IAudioPlay::Update(XData data){
    XLOGE("IAudioPlay::Update %d",data.size);
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