//
// Created by zy on 7/20/2018.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
class FFDecode: public IDecode {
public:
    virtual bool Open(XParameter para);

protected:
    AVCodecContext* codec=0;
};


#endif //XPLAY_FFDECODE_H
