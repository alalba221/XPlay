//
// Created by zy on 7/18/2018.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H
//sleep 毫秒
void XSleep(int mis);
//线程的处理和FFMpeg无关，所以放在接口类继承
//采用c++ 11 线程库
class XThread {
public:
    //启动线程
    virtual void Start();
    //通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();
    //入口主函数
//protected:
    virtual void Main(){};
protected:
    bool isExit = false;
    bool isRunning = false;
private:
    virtual void ThreadMain();

};


#endif //XPLAY_XTHREAD_H
