//
// Created by zy on 7/17/2018.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while(!isExit){
        XData d = Read();
//        XLOGI("IDemux Read %d",d.size);
        if(d.size>0){
            this->Notify(d);
        }
    }
}
