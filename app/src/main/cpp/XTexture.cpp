//
// Created by zy on 7/23/2018.
//

#include "XTexture.h"
#include "XLog.h"
#include "XEGL.h"
#include "XShader.h"

class CXTexture:public XTexture{
public:
    XShader sh;
    XTextureType type;
    std::mutex mux;
    virtual void Drop(){
        mux.lock();
        // clear egl
        XEGL::Get()->Close();
        //clear shader
        sh.Close();
        mux.unlock();
        //clear texture itself
        delete this;
    }
    virtual bool Init(void* win,XTextureType type){
        mux.lock();

        XEGL::Get()->Close();
        sh.Close();

        this->type = type;
        if(!win){
            mux.unlock();
            XLOGE("XTexture Init failed, win is null");
            return false;
        }
        //EGL 初始化 因为EGL为单件模式
        if(!XEGL::Get()->Init(win)){
            mux.unlock();
            return false;
        }
        //Shader初始化
        sh.Init((XShaderType)type);
        mux.unlock();
        return true;
    }
    virtual void Draw(unsigned char* data[],int width, int height){
        mux.lock();
        sh.GetTexture(0,width,height,data[0]); //y
        if(type==XTEXTURE_YUV420P){
            sh.GetTexture(1,width/2,height/2,data[1]); //u
            sh.GetTexture(2,width/2,height/2,data[2]); //v
        }
        else{
            sh.GetTexture(1,width/2,height/2,data[1],true);//uv
        }
        sh.Draw();
        XEGL::Get()->Draw();
        mux.unlock();
    }
};
XTexture* XTexture::Create(){
    return new CXTexture();
}