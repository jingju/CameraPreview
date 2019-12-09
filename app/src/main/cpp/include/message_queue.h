//
// Created by Macro on 2019-12-03.
//

#ifndef CAMERAPREVIEW_MESSAGE_QUEUE_H
#define CAMERAPREVIEW_MESSAGE_QUEUE_H

#include <pthread.h>
#include "CommonTools.h"

#define MESSAGE_QUEUE_LOOP_QUIT_FLAG        19900909


class Handler;
/**
 * 类似Android使用的消息队列
 */
class Message{
private:
    int what;
    int arg1;
    int arg2;
    void* obj;
public:
    Message();
    Message(int whtat);
    Message(int what,int arg1,int arg2);
    Message(int what,void* obj);
    Message(int what,int arg1,int arg2,void* obj);
    ~Message();

    int execute();
    int getWhat(){
        return what;
    }

    int getArg1(){
        return arg1;
    }

    int getArg2(){
        return arg2;
    }

    void* getObj(){
        return obj;
    }

    Handler* handler;

};

typedef struct MessageNode{
    Message* msg;
    struct MessageNode* next;
    MessageNode(){
        msg=NULL;
        next=NULL;
    }

};
class MessageQueue {
private:
    MessageNode* mFirst;
    MessageNode* mLast;
    int mNbPackets;
    bool mAbortRequest;
    pthread_mutex_t mLock;//互斥量，又叫互斥所，使用前必须进行初始化
    pthread_cond_t  mCondition;//锁的条件变量
    const char * queueName;

public:
    MessageQueue();
    MessageQueue(const char * queueNameParam);
    ~MessageQueue();
    void init();
    void flush();
    int enqueueMessage(Message *msg);
    int dequeueMessage(Message **msg, bool block);
    int size();
    void abort();
};


#endif //CAMERAPREVIEW_MESSAGE_QUEUE_H
