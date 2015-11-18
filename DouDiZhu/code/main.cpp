#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    AppDelegate *pAppDelegate = new AppDelegate();
}
