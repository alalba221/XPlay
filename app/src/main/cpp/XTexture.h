//
// Created by xinhu on 7/23/2018.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H


class XTexture {
public:
    static  XTexture* Create();
    virtual bool Init(void* win)=0;
};


#endif //XPLAY_XTEXTURE_H
