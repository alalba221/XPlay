//
// Created by zy on 7/17/2018.
//

#ifndef XPLAY_XLOG_H
#define XPLAY_XLOG_H
#include<android/log.h>

class XLog {

};
#define XLOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"XPlay",__VA_ARGS__)
#define XLOGI(...) __android_log_print(ANDROID_LOG_INFO,"XPlay",__VA_ARGS__)
#define XLOGE(...) __android_log_print(ANDROID_LOG_ERROR,"XPlay",__VA_ARGS__)
#endif //XPLAY_XLOG_H
