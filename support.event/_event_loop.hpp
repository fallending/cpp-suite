//
//  _event_loop.hpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#ifndef _event_loop_hpp
#define _event_loop_hpp

#include "_event_callback.hpp"
#include "_event_source.hpp"

namespace suite_cpp {
    /**
     *  Class definition
     */
    class Loop {
    public:
        bool _running;
        
        inline bool running() {
            return _running;
        }
        /**
         *  Constructor
         */
        Loop() : _running(false) {}
        
        /**
         * Cannot be copied
         */
        Loop(const Loop& that) = delete;
        
        /**
         *  Nor can be moved
         */
        Loop(Loop&& that) = delete;
        
        /**
         *  Destructor
         */
        virtual ~Loop() { }
        
        // ---------------------------- not implement ------------------------------
        
        virtual bool run() = 0;
        
        /**
         *  Run a single iteration of the event loop
         *
         *  This will check once all the filedescriptors and timers, and will notify
         *  the appropriate callbacks.
         *
         *  With the boolean parameter you can specify if the operation should block
         *  or not. If you set it to true, the method will wait until at least one
         *  callback can be called. If set to false, it will not wait and immediately
         *  return if no methods can be called
         *
         *  @param  block   block return until the step was completed
         *  @return bool
         */
        virtual bool step(bool block = true) = 0;
        
        /**
         *  Stop running the event loop
         *
         *  Normally, the event loop runs until no more filedescriptors and timers
         *  are active. This function will terminate the event loop prematurely.
         *
         *  @return bool
         */
        virtual bool stop() = 0;
        
        /**
         *  Suspend the loop. While the loop is suspended, timers will not be processed,
         *  and the time for the timers does not proceed. Once the loop is resumed, the
         *  timers continue to run.
         */
        virtual void suspend() = 0;
        
        /**
         *  Resume the loop after it was suspended
         */
        virtual void resume() = 0;
    };
    
    
    /**
     *  Class definition
     */
    class EventLoop : public Loop, public EventCallback {
    public:
        /**
         *  Constructor
         */
        EventLoop() : Loop() {}
        
        /**
         *  Destructor
         */
        virtual ~EventLoop() {}
        
        // ---------------------------- implement Loop ------------------------------
        
        virtual bool run();
        virtual bool step(bool block = true);
        virtual bool stop();
        virtual void suspend();
        virtual void resume();
        
        // ----------------------- implement EventCallback ---------------------------
        virtual void onMessage(int eventId, const MessageCallback &callback) = 0;
        
        virtual void onReadable(int fd, const ReadCallback &callback) = 0;
        virtual void onWritable(int fd, const WriteCallback &callback) = 0;
        
        virtual void onTimeout(long timeout, const TimeoutCallback &callback) = 0;
        
        virtual void onSynchronize(const SynchronizeCallback &callback) = 0;
        
        virtual void onCleanup(const CleanupCallback &callback) = 0;
    };
}


#endif /* _event_loop_hpp */
