#include "Voice.h"
#include "cocos2d.h"
#include "IconvString.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni.h"
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC；

void onSpeechRecognizer(const char* data)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo jmi;
    // java的类名
    const char * jniClass = "org/cocos2dx/cpp/AppActivity";
    //获取java部分的方法,具体參数请參考JniMethodInfo类的源代码，參数分别为，类对象，java类，java类的方法，方法的參数和返回值，V表示void类型返回值（即无返回值，括号中面的表示參数，參数是一个字符串【详见JNI签名规范】）
    bool isHave = JniHelper::getStaticMethodInfo(jmi,jniClass,"onVoiceStart","(Ljava/lang/String;)V");
    if (isHave)
    {
        //转换字符串以及格式
        jstring jdata = jmi.env->NewStringUTF(GBKToUTF8(data));
        //调用java的方法，前面2个參数是固定的，后面的參数是在java的方法中的參数
        jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID, jdata);
    }
#endif
}




