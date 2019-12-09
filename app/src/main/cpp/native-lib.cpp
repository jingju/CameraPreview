#include <jni.h>
#include <string>
#include <mv_recording_preview_controller.h>
#include "include/CommonTools.h"
#define LOG_TAG "ChangbaRecordingPreviewScheduler"

static MVRecordingPreviewController *previewController = 0;
extern "C" JNIEXPORT jstring JNICALL
Java_com_jingju_camerapreview_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}





extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_switchCameraFacing(JNIEnv *env,
                                                                                   jobject instance) {

    // TODO
    if(NULL != previewController) {
        previewController->switchCameraFacing();
    }
}



extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_prepareEGLContext(JNIEnv *env,
                                                                                  jobject instance,
                                                                                  jobject surface,
                                                                                  jint width,
                                                                                  jint height,
                                                                                  jint cameraFacingId) {

    // TODO

    previewController = new MVRecordingPreviewController();
    JavaVM *g_jvm = NULL;
    env->GetJavaVM(&g_jvm);
    jobject g_obj = env->NewGlobalRef(instance);
    if (surface != 0 && NULL != previewController) {
        ANativeWindow* window = ANativeWindow_fromSurface(env, surface);
        if (window != NULL) {
            previewController->prepareEGLContext(window, g_jvm, g_obj, width, height, cameraFacingId);
        }
    }

}



extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_createWindowSurface(JNIEnv *env,
                                                                                    jobject instance,
                                                                                    jobject surface) {

    // TODO
    if (surface != 0 && NULL != previewController) {
        ANativeWindow* window = ANativeWindow_fromSurface(env, surface);
        if (window != NULL) {
            previewController->createWindowSurface(window);
        }
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_resetRenderSize(JNIEnv *env,
                                                                                jobject instance,
                                                                                jint width,
                                                                                jint height) {

    // TODO
    if(NULL != previewController) {
        previewController->resetRenderSize(width, height);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_destroyWindowSurface(JNIEnv *env,
                                                                                     jobject instance) {

    // TODO
    if(NULL != previewController) {
        previewController->destroyWindowSurface();
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_destroyEGLContext(JNIEnv *env,
                                                                                  jobject instance) {

    // TODO
    if(NULL != previewController) {
        previewController->destroyEGLContext();
        delete previewController;
        previewController = NULL;
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jingju_camerapreview_preview_RecordingPreviewScheduler_notifyFrameAvailable(JNIEnv *env,
                                                                                     jobject instance) {

    // TODO
    if(NULL != previewController) {
        previewController->notifyFrameAvailable();
    }
}