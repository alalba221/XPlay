//
// Created by xinhu on 7/23/2018.
//

#include "XTexture.h"
#include "XLog.h"
#include "XEGL.h"
#include "XShader.h"

class CXTexture:public XTexture{
public:
    XShader sh;
    virtual bool Init(void* win){
        if(!win){
            XLOGE("XTexture Init failed, win is null");
            return false;
        }
        //EGL 初始化 因为EGL为单件模式
        if(!XEGL::Get()->Init(win)){
            return false;
        }
        //Shader初始化
        sh.Init();
        return true;
    }
};
XTexture* XTexture::Create(){
    return new CXTexture();
}