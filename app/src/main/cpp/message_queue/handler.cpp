//
// Created by Macro on 2019-12-03.
//

#include "../include/handler.h"
Handler::Handler(MessageQueue* queue) {
    this->mQueue = queue;
}

Handler::~Handler() {
}

int Handler::postMessage(Message* msg){
    msg->handler = this;
//	LOGI("enqueue msg what is %d", msg->getWhat());
    return mQueue->enqueueMessage(msg);
}
