//
// Created by zy on 7/20/2018.
//

#include "IDecode.h"
#include "XLog.h"

//生产者
void IDecode::Update(XData pkt){//把数据压进队列
    if(pkt.isAudio !=isAudio){
        return;
    }
    while(!isExit){ //不可以用IF语句
        packsMutex.lock();//update往队列里写

        if(packs.size() < maxList){
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        //阻塞功能
        XSleep(1);
    }

}


//消费者
void IDecode::Main() {

    while (!isExit) {
        packsMutex.lock();//main从队列里面读
        if(packs.empty()){
            packsMutex.unlock();
            XSleep(1);
            continue;
        }
        //取出packet
        XData pack = packs.front();
        packs.pop_front();

        //开始解码：发送数据到解码线程，此线程是ffmepg内部实现
        // 一个数据包可能解码出多个结果(音频)
        if(this->SendPacket(pack)){
            while(!isExit){
                //获取解码数据
                XData frame = RecvFrame();
                if(!frame.data) break; //因为不是一对一，所以要一直读，直到读不出来
               // XLOGE("Receive frame %d",frame.size);
                //发送数据给观察者,数据接着往下传
                this->Notify(frame);//frame传给XTexture
            }

        }
        pack.Drop();//这一步不能省
        packsMutex.unlock();
    }
}