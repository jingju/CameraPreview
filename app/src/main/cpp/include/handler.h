//
// Created by Macro on 2019-12-03.
//

#ifndef CAMERAPREVIEW_HANDLER_H
#define CAMERAPREVIEW_HANDLER_H


#include "message_queue.h"

class Handler {
private:
    MessageQueue* mQueue;
public:
    Handler(MessageQueue *queue);
    ~Handler();
    int postMessage(Message *message);
    virtual void handleMessage(Message *message){};

};


#endif //CAMERAPREVIEW_HANDLER_H
