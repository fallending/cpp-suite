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
        /**
         *  Constructor
         */
        Loop() {}
        
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
    class EventLoop : public Loop, public EventCallback, EventSourceOperator {
    private:
        struct Private;
        std::shared_ptr<Private> impl;
        void iteration();
        bool containsSource(EventSource *source) const;
        
    public:
        /**
         *  Constructor
         */
        EventLoop();// : Loop() {}
        
        /**
         *  Destructor
         */
        virtual ~EventLoop() {}
        
        // ---------------------------- implement Loop ------------------------------
        
        virtual bool run() override;
        virtual bool step(bool block = true) override;
        virtual bool stop() override;
        virtual void suspend() override;
        virtual void resume() override;
        
        // ----------------------- implement EventCallback ---------------------------
        
        virtual void onMessage(int eventId, const MessageCallback &callback) override;
        
        virtual void onReadable(int fd, const ReadCallback &callback) override;
        virtual void onWritable(int fd, const WriteCallback &callback) override;
        
        virtual void onTimeout(long timeout, const TimeoutCallback &callback) override;
        
        virtual void onSynchronize(const SynchronizeCallback &callback) override;
        
        virtual void onCleanup(const CleanupCallback &callback) override;
        
        // --------------------- implement EventSourceOperator ----------------------
        
        virtual bool addEventSource(EventSource *source, EventHandler handler = nullptr) override;
        virtual bool setSourceHandler(EventSource *source, EventHandler handler) override;
        virtual bool removeEventSource(EventSource *source) override;
        
    };
}


#endif /* _event_loop_hpp */
