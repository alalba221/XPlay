#include <jni.h>
#include <string>


#include"FFDemux.h"
#include "XLog.h"
//#include "IDecode.h"
#include "FFDecode.h"

class TestObserver:public IObserver{
public:
    void Update(XData data){
 //       XLOGI("TestObs Updata data size is %d",data.size);
    }
};

extern "C" JNIEXPORT jstring

JNICALL
Java_xplay_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    //////////////////////////////////////////////////////////////
    /////////////////测试代码
    TestObserver* testObserver = new TestObserver();
    IDemux* de = new FFDemux();
    //de->AddObs(testObserver);
    de->Open("/sdcard/example.mp4");

    IDecode* vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode* adecode = new FFDecode();
    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);

    de->Start();

    //XSleep(3000);
    //de->Stop();
    vdecode->Start();
    adecode->Start();
    return env->NewStringUTF(hello.c_str());
}
