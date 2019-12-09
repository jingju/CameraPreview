//
// Created by Macro on 2019-12-03.
//

#ifndef CAMERAPREVIEW_EGL_SHARE_CONTEXT_H
#define CAMERAPREVIEW_EGL_SHARE_CONTEXT_H


#include <EGL/egl.h>
#include "CommonTools.h"

class EglShareContext {

public:
    ~EglShareContext();
    //单利模式
    static EGLContext getShareContext(){
        if(instance_->shareDisplay==EGL_NO_DISPLAY){
            instance_->init();
        }
        return instance_->shareContext;
    }

protected:
    EglShareContext();
    void init();

private:
    static EglShareContext* instance_;
    EGLContext shareContext;
    EGLDisplay shareDisplay;
};


#endif //CAMERAPREVIEW_EGL_SHARE_CONTEXT_H
