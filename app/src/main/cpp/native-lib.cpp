#include <jni.h>
#include <string>


#include "XLog.h"
#include "FFPlayerBuilder.h"
#include <android/native_window_jni.h>

//IVideoView* view=NULL;
static IPlayer* player = NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM* vm,void* res){
    //FFDecode::InitHard(vm);

    //////////////////////////////////////////////////////////////
    /////////////////测试代码
    FFPlayerBuilder::InitHard(vm);
    player = FFPlayerBuilder::Get()->BuilderPlayer();


    player->Open("/sdcard/example.mp4");
    player->Start();
    //de->Start();

    //XSleep(3000);
    //de->Stop();
    //vdecode->Start();
    //adecode->Start();
    return JNI_VERSION_1_4;
}


extern "C" JNIEXPORT jstring

JNICALL
Java_xplay_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";



    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_xplay_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    ANativeWindow* win = ANativeWindow_fromSurface(env,surface);
    if(player)
        player->InitView(win);
    //view->SetRender(win);
//    XEGL::Get()->Init(win);
 //   XShader shader;
 //   shader.Init();

}