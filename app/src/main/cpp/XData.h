//
// Created by zy on 7/17/2018.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
    unsigned char* data = 0;
    unsigned  char* datas[8] = {0};//用于显示的数组,解码后的数据,对应AVFrame->data

    int width = 0;
    int height = 0;

    int size =0;
    bool isAudio = false;
    void Drop();

};


#endif //XPLAY_XDATA_H
