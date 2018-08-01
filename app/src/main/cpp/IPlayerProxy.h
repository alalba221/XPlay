//
// Created by zy on 8/1/2018.
//

#ifndef XPLAY_IPLAYERPROXY_H
#define XPLAY_IPLAYERPROXY_H


#include <mutex>
#include "IPlayer.h"

class IPlayerProxy: public IPlayer {
public:
    static IPlayerProxy* Get(){
        static IPlayerProxy px;
        return &px;
    }
    void Init(void* vm = 0);


    virtual bool Open(const char* path);
    virtual bool Start();
    virtual void InitView(void* win);

protected:
    std::mutex mux;
    IPlayer* player = 0;
    IPlayerProxy(){}
};


#endif //XPLAY_IPLAYERPROXY_H
