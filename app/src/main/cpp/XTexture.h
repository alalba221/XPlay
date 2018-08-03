//
// Created by zy on 7/23/2018.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H
enum XTextureType{
    XTEXTURE_YUV420P = 0,
    XTEXTURE_NV12 = 25,
    XTEXTURE_NV21 = 26
};

class XTexture {
public:
    static  XTexture* Create();
    virtual bool Init(void* win,XTextureType type = XTEXTURE_YUV420P)=0;
    virtual void Draw(unsigned char* data[],int width, int height)=0;
    virtual void Drop()= 0;
    virtual ~XTexture(){};
protected:
    XTexture(){};
};


#endif //XPLAY_XTEXTURE_H
