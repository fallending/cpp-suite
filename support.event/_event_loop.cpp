//
//  _event_loop.cpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <unistd.h>
#include <unordered_set>

#include "_event_loop.hpp"
#include "_suite_predefine.h"

using namespace std;

namespace suite_cpp {

    struct EventLoop::Private {
        static const int STATE_STOPPED = 0;
        static const int STATE_RUNNING = 1;
        static const int STATE_SUSPEND = 2;
        static const int STATE_BLOCK   = 3;
        
        int state;
        
        uint64_t time_last;
        vector<EventSource *> sources;
        vector<EventSource *> remove_sources;

        unordered_set<EventSource *> source_set;
        
        Private() {}
        
        ~Private() {
            for (auto source : sources)
                delete source;
        }
    };
    
    EventLoop::EventLoop()
    : Loop(), impl(make_shared<Private>()) {
        
    }
    
    bool EventLoop::run() {
        bool alive = true;
        
        impl->state = Private::STATE_RUNNING;
        
        while (alive) {
            
            switch (impl->state) {
                case Private::STATE_RUNNING: {
                    iteration();
                }
                    break;
                    
                case Private::STATE_STOPPED: {
                    alive = false;
                }
                    
                default: {
                    sleep(1);
                }
            }
        }
        
        return true;
    }
    
    bool EventLoop::containsSource(EventSource *source) const {
        return (impl->source_set.count(source) > 0);
    }
    
    void EventLoop::iteration() {
        impl->remove_sources.clear();

        for (auto source : impl->sources) {
            if ( source->check() && source->handler ) {
                source->dispatch(source->handler);
            }
            
            if ( source->quit() ) {
                impl->remove_sources.emplace_back(source);
            }
        }
        
        // purge event sources which requested to be removed
        for (auto source : impl->remove_sources)
            removeEventSource(source);
    }
    
    /////
    
    
    bool EventLoop::step(bool block) {
        iteration();
        
        if (block) {
            impl->state = Private::STATE_BLOCK;
        }
        
        return true;
    }
    
    bool EventLoop::stop() {
        
        impl->state = Private::STATE_STOPPED;
        
        return true;
    }
    
    void EventLoop::suspend() {
        impl->state = Private::STATE_SUSPEND;
        
        return;
    }
    
    void EventLoop::resume() {
        impl->state = Private::STATE_RUNNING;
        
        return;
    }
    
    
    /////
    
    
    void EventLoop::onMessage(int eventId, const MessageCallback &callback) {
        
    }
    
    void EventLoop::onReadable(int fd, const ReadCallback &callback) {
//        TODO("还没实现")
    }
    
    void EventLoop::onWritable(int fd, const WriteCallback &callback ) {
        //        TODO("还没实现")
    }
    
    void EventLoop::onTimeout(long timeout, const TimeoutCallback &callback) {
        //        TODO("还没实现")
    }
    
    void EventLoop::onSynchronize(const SynchronizeCallback &callback) {
        //        TODO("还没实现")
    }
    
    void EventLoop::onCleanup(const CleanupCallback &callback) {
        //        TODO("还没实现")
    }
    
    
    /////
    
    
    bool EventLoop::addEventSource(suite_cpp::EventSource *source, EventHandler handler) {
        if (containsSource(source))
            return false;
        
//        source->loop_data.ready = false;
        source->handler = handler ? move(handler) : nullptr;
        impl->sources.emplace_back(source);
        impl->source_set.emplace(source);
        
        return true;
    }
    
    bool EventLoop::setSourceHandler(suite_cpp::EventSource *source, EventHandler handler) {
        if (containsSource(source)) {
            source->handler = handler;
        }
        
        return true;
    }
    
    bool EventLoop::removeEventSource(suite_cpp::EventSource *source) {
        
        if (! containsSource(source))
            return false;
    
        impl->sources.erase(remove(begin(impl->sources), end(impl->sources), source), end(impl->sources));
        
        impl->source_set.erase(source);
        
        delete source;
        
        return true;
    }
}
