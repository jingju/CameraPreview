//
// Created by Macro on 2019-12-03.
//

#include "../include/egl_share_context.h"

#define LOG_TAG "EglShareContext"

EglShareContext* EglShareContext::instance_ = new EglShareContext();

EglShareContext::EglShareContext() {
    init();
}

void EglShareContext::init() {
    LOGI("Create EGLContext EGLCore ::init() ");
    shareContext=EGL_NO_CONTEXT;
    EGLint numConfigs;
    shareDisplay=EGL_NO_DISPLAY;
    EGLConfig config;
    const EGLint attris[]={EGL_BUFFER_SIZE,32,EGL_ALPHA_SIZE,8,
                           EGL_BLUE_SIZE,8,EGL_GREEN_SIZE,8,EGL_RED_SIZE,8,
                           EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,EGL_SURFACE_TYPE,
                           EGL_WINDOW_BIT,EGL_NONE};

    if((shareDisplay=eglGetDisplay(EGL_DEFAULT_DISPLAY))==EGL_NO_DISPLAY){
        LOGE("eglGetDisplay returned error %d ",eglGetError());
        return;
    }

    if(!eglInitialize(shareDisplay,0,0)){
        LOGE("eglInitialize get error %d ",eglGetError());
        return;
    }

    if(!eglChooseConfig(shareDisplay,attris,&config,1,&numConfigs)){
        LOGE("eglChoose Config error %d ",eglGetError());
        return;
    }

    EGLint eglContextAttris[]={EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE};

    if(!(shareContext=eglCreateContext(shareDisplay,config,NULL==shareContext?
    EGL_NO_CONTEXT:shareContext,eglContextAttris))){
        LOGE("eglCreate Context error %d",eglGetError());
        return;
    }
}