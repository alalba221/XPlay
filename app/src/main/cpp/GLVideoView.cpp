//
// Created by zy on 7/23/2018.
//

#include "GLVideoView.h"
#include "XTexture.h"

void GLVideoView::SetRender(void* win){
    view = win;
}
void GLVideoView::Render(XData data) {
    if(!view) return;
    if(!txt){
        //XTexture 是一个抽象类，所以不能直接new
        txt = XTexture::Create();
        txt->Init(view,(XTextureType)data.format);
    }
    txt->Draw(data.datas,data.width,data.height);
}
