//
// Created by zy on 7/18/2018.
//

#include "XThread.h"
#include<thread>
#include "XLog.h"
using namespace std;//命名空间不要放头文件

void XSleep(int mis){
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}
//启动线程
bool XThread::Start(){
    isExit=false;
    thread th(&XThread::ThreadMain,this);
    th.detach();
    return true;
//    th.join();
}
void XThread::ThreadMain(){

    isRunning = true;
    XLOGI("Enter the thread function");
    Main();
    XLOGI("Quit the thread function");
    isRunning = false;
}
//通过控制isExit安全停止线程（不一定成功）
void XThread::Stop(){
    isExit = true;
    for(int i=0;i<200;i++){
        if(!isRunning) {
            XLOGI("Stop Thread success");
            return;
        }
        XSleep(1);
    }
    XLOGI("Stop Thread overtime");
}