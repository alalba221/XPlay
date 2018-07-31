#include <jni.h>
#include <string>


#include"FFDemux.h"
#include "XLog.h"
//#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include <android/native_window_jni.h>
class TestObserver:public IObserver{
public:
    void Update(XData data){
 //       XLOGI("TestObs Updata data size is %d",data.size);
    }
};
IVideoView* view=NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM* vm,void* res){
    FFDecode::InitHard(vm);

    //////////////////////////////////////////////////////////////
    /////////////////测试代码
    TestObserver* testObserver = new TestObserver();
    IDemux* de = new FFDemux();
    //de->AddObs(testObserver);
    de->Open("/sdcard/example.mp4");

    IDecode* vdecode = new FFDecode();
    vdecode->Open(de->GetVPara(), true);

    IDecode* adecode = new FFDecode();
    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample* resample = new FFResample();
    XParameter outPara = de->GetAPara();

    resample->Open(de->GetAPara(),outPara);
    adecode->AddObs(resample);

    IAudioPlay* audioPlay = new SLAudioPlay();
    audioPlay->StartPlay(outPara);
    resample->AddObs(audioPlay);

    de->Start();

    //XSleep(3000);
    //de->Stop();
    vdecode->Start();
    adecode->Start();
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
    view->SetRender(win);
//    XEGL::Get()->Init(win);
 //   XShader shader;
 //   shader.Init();

}