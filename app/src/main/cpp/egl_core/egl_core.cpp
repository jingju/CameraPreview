//
// Created by Macro on 2019-12-02.
//

#include <egl_share_context.h>
#include "../include/egl_core.h"
#define LOG_TAG "EglCore"
/**
 * EGL管理类
 */
EglCore::EglCore() {
    pfneglPresentationTimeANDROID=0;
    display=EGL_NO_DISPLAY;
    context=EGL_NO_CONTEXT;
}

EglCore::~EglCore() {

}

void EglCore::release() {
    if(EGL_NO_DISPLAY!=display && EGL_NO_CONTEXT !=context){
        eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
        LOGI("after make current");
        eglDestroyContext(display,context);
        LOGI("after destroy context");
    }

    display=EGL_NO_DISPLAY;
    context=EGL_NO_CONTEXT;
}


void EglCore::releaseSurface(EGLSurface eglSurface) {
    eglDestroySurface(display,eglSurface);
    eglSurface=EGL_NO_SURFACE;
}


EGLContext EglCore::getContext() {
    return context;
}

EGLContext EglCore::getConfigure() {
    return config;
}


EGLDisplay EglCore::getDisplay() {
    return display;
}


EGLSurface EglCore::creatWindowSurface(ANativeWindow *_window) {
    EGLSurface surface=NULL;
    EGLint format;
    if(!(eglGetConfigAttrib(display,config,EGL_NATIVE_VISUAL_ID,&format))){
        LOGI("eglGetConfigAttrib error %d",eglGetError());
        release();
        return surface;
    }


    ANativeWindow_setBuffersGeometry(_window,0,0,format);

    if(!(surface=eglCreateWindowSurface(display,config,_window,0))){
        LOGI("eglCreateWindowSurface error %d",eglGetError());
    }
    return surface;
}


/**
 * 设置呈现时间
 * @param eglSurface
 * @param ncsec
 */
void EglCore::setPresentationTime(EGLSurface eglSurface, khronos_stime_nanoseconds_t ncsec) {
    pfneglPresentationTimeANDROID(display,eglSurface,ncsec);//函数指针
}


/**
 * 查找surface
 * @param eglSurface
 * @param what
 * @return
 */
int EglCore::querySurface(EGLSurface eglSurface, int what) {

    int value = -1;
    eglQuerySurface(display,eglSurface,what,&value);
    return value;
}

/**
 * 输出缓冲区数据
 * @param eglSurface
 * @return
 */
bool EglCore::swapBuffers(EGLSurface eglSurface) {
    return eglSwapBuffers(display,eglSurface);
}

/**
 * todo 该方法作用？
 * @param eglSurface
 * @return
 */
bool EglCore::makeCurrent(EGLSurface eglSurface) {
    return eglMakeCurrent(display,eglSurface,eglSurface,context);
}


void EglCore::downCurrent() {
    eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
}


bool EglCore::init() {
    return init(NULL);
}

bool EglCore::initWithSharedContext() {

    EGLContext context = EglShareContext::getShareContext();
    if(context==EGL_NO_CONTEXT){
        return false;
    }
    return init(context);
}


/**
 * 初始化上下文
 * @param sharedContext
 * @return
 */
bool EglCore::init(EGLContext sharedContext) {
    EGLint numConfigs;
    EGLint width;
    EGLint height;

    const EGLint attribs[] = { EGL_BUFFER_SIZE, 32, EGL_ALPHA_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                               EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };
    /** display 代表系统的物理屏幕*/
    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0)) {
        LOGE("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        LOGE("eglChooseConfig() returned error %d", eglGetError());
        release();
        return false;
    }

    EGLint eglContextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    if (!(context = eglCreateContext(display, config, NULL == sharedContext ? EGL_NO_CONTEXT : sharedContext, eglContextAttributes))) {
        LOGE("eglCreateContext() returned error %d", eglGetError());
        release();
        return false;
    }

    pfneglPresentationTimeANDROID = (PFNEGLPRESENTATIONTIMEANDROIDPROC)eglGetProcAddress("eglPresentationTimeANDROID");
    if (!pfneglPresentationTimeANDROID) {
        LOGE("eglPresentationTimeANDROID is not available!");
    }

    return true;
}





