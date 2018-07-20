//
// Created by zy on 7/20/2018.
//

#ifndef XPLAY_XPARAMETER_H
#define XPLAY_XPARAMETER_H

struct AVCodecParameters;

//用于IDemux 和IDecode 之间参数传递
class XParameter {
public:
    AVCodecParameters* para=0;
};


#endif //XPLAY_XPARAMETER_H
