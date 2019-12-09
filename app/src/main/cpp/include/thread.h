//
// Created by Macro on 2019-12-05.
//

#ifndef CAMERAPREVIEW_THREAD_H
#define CAMERAPREVIEW_THREAD_H

#include "CommonTools.h"
#include <pthread.h>
class Thread {
public:
    Thread();
    ~Thread();

    void start();
    void startAsync();
    int wait();

    void waitOnNotify();
    void notify();
    virtual void stop();

protected:
    bool mRunning;

    virtual void handleRun(void* ptr);

protected:
    pthread_t mThread;
    pthread_mutex_t mLock;
    pthread_cond_t mCondition;

    static void* startThread(void* ptr);
};

#endif //CAMERAPREVIEW_THREAD_H
