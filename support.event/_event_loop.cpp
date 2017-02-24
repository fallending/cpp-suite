//
//  _event_loop.cpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include "_event_loop.hpp"

namespace suite_cpp {

    bool EventLoop::run() {
        _running = true;
        
        return _running;
    }
    
    bool EventLoop::step(bool block) {
        return true;
    }
    
    bool EventLoop::stop() {
        return true;
    }
    
    void EventLoop::suspend() {
        return;
    }
    
    void EventLoop::resume() {
        return;
    }
    
    
    /////
    
    
    void EventLoop::onMessage(int eventId, const MessageCallback &callback) {
        
    }
    
    void EventLoop::onReadable(int fd, const ReadCallback &callback) {
        
    }
    
    void EventLoop::onWritable(int fd, const WriteCallback &callback ) {
        
    }
    
    void EventLoop::onTimeout(long timeout, const TimeoutCallback &callback) {
        
    }
    
    void EventLoop::onSynchronize(const SynchronizeCallback &callback) {
        
    }
    
    void EventLoop::onCleanup(const CleanupCallback &callback) {
        
    }
}
