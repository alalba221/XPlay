#include <jni.h>
#include <string>


#include"FFDemux.h"
#include "XLog.h"

class TestObserver:public IObserver{
public:
    void Update(XData data){
        XLOGI("TestObs Updata data size is %d",data.size);
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
    IDemux* de = new FFDemux();
    de->Open("/sdcard/example.mp4");
    /*for(;;){
        XData d = de->Read();
        XLOGI("Read data size is %d",d.size);

    }*/
    TestObserver* testObserver = new TestObserver();
    de->AddObs(testObserver);
    de->Start();
    XSleep(3000);
    de->Stop();
    return env->NewStringUTF(hello.c_str());
}
