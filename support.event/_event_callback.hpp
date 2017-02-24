//
//  _event_callback.hpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#ifndef _event_callback_hpp
#define _event_callback_hpp

#include <iostream>

namespace suite_cpp {
    
    /**
     *  Callback functions definition.
     */
    using MessageCallback = std::function<void()>;
    using ReadCallback = std::function<bool()>;
    using WriteCallback = std::function<bool()>;
    using TimeoutCallback = std::function<void()>;
    using SynchronizeCallback = std::function<void()>;
    using CleanupCallback = std::function<void()>;
    using SignalCallback = std::function<bool()>;
    using StatusCallback = std::function<bool(pid_t, int)>; // process 's status
    
    /**
     *  Callback class definition.
     */
    class EventCallback {
        /**
         * User message.
         */
        virtual void onMessage(int eventId, const MessageCallback &callback) = 0;
        
        /**
         * File IO.
         */
        virtual void onReadable(int fd, const ReadCallback &callback) = 0;
        virtual void onWritable(int fd, const WriteCallback &callback) = 0;
        
        /**
         *  Timer operation.
         */
        virtual void onTimeout(long timeout, const TimeoutCallback &callback) = 0;
        
        /**
         *  Synchronize function
         *
         *  In a multi threaded environment, you may have multiple threads that you
         *  sometimes want to synchronize. With the onSychronize() method you can
         *  register a function that is going to be called when the thread is
         *  synchronized from a different thread.
         *
         */
        virtual void  onSynchronize(const SynchronizeCallback &callback) = 0;
        
        /**
         *  Register a cleanup function
         *
         *  This method takes a callback to be executed right before the event loop
         *  gets destroyed.
         *
         *  @param  callback    Function to invoke before destroying the loop
         */
        virtual void  onCleanup(const CleanupCallback &callback) = 0;
    };
    
}

#endif /* _event_callback_hpp */
