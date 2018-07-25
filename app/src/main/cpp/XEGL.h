//
// Created by xinhu on 7/23/2018.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


class XEGL {
public:
    virtual bool Init(void* win)=0;
    static XEGL* Get();
protected:
    XEGL(){};
};


#endif //XPLAY_XEGL_H
