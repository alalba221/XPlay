//
// Created by zy on 7/23/2018.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();

    //获取材质并映射到内存
    virtual void GetTexture(unsigned int index,int width,int height, unsigned char* buf);//index对应纹理层

    virtual void Draw();
protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;

    unsigned int texts[100]={0};
};


#endif //XPLAY_XSHADER_H
