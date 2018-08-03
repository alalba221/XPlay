#include <jni.h>
#include <string>


#include "XLog.h"
//#include "FFPlayerBuilder.h"
#include "IPlayerProxy.h"
#include <android/native_window_jni.h>
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM* vm,void* res){


    //////////////////////////////////////////////////////////////
    /////////////////测试代码
    IPlayerProxy::Get()->Init(vm);

   // IPlayerProxy::Get()->Open("/sdcard/example.mp4");
   // IPlayerProxy::Get()->Start();
   // IPlayerProxy::Get()->Open("/sdcard/xample.mp4");
   // IPlayerProxy::Get()->Start();

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_xplay_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    ANativeWindow* win = ANativeWindow_fromSurface(env,surface);
    IPlayerProxy::Get()->InitView(win);

}extern "C"
JNIEXPORT void JNICALL
Java_xplay_xplay_OpenUrl_Open(JNIEnv *env, jobject instance, jstring url_) {
    const char *url = env->GetStringUTFChars(url_, 0);

    IPlayerProxy::Get()->Open(url);
    IPlayerProxy::Get()->Start();


    env->ReleaseStringUTFChars(url_, url);
}