//
// Created by zy on 7/30/2018.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver{
public:
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
};


#endif //XPLAY_IAUDIOPLAY_H
