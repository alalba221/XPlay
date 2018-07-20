//
// Created by zy on 7/19/2018.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H

#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>
//包含观察者 和 主体
class IObserver: public XThread {
public:
    //观察者接收数据
    virtual void Update(XData data){}

    //主题函数 添加观察者（线程安全）
    void AddObs(IObserver* obs);

    //通知所有观察者
    void Notify(XData data);

protected:
    std::vector<IObserver*> obss;//观察者模式：给每个主题对象 添加一系列观察者
    std::mutex mux;
};


#endif //XPLAY_IOBSERVER_H
