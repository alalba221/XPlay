//
// Created by zy on 7/28/2018.
//

#include "IResample.h"
#include "XLog.h"

void IResample::Update(XData data){
    XData d = this->Resample(data);
    //XLOGE("IResample::Update %d",d.size);
    if(d.size>0){
        this->Notify(d);
    }
}