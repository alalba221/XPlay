//
// Created by zy on 7/28/2018.
//

#include "IResample.h"
void IResample::Update(XData data){
    XData d = this->Resample(data);
    if(d.size>0){
        this->Notify(d);
    }
}