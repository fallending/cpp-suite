//
//  _event_source.hpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include <iostream>
#include <functional>

#ifndef _event_source_hpp
#define _event_source_hpp

namespace suite_cpp {
    
    class EventLoop;
    class EventSource;
    
    typedef std::function<bool(EventSource&)> EventHandler;
    
    /**
     *
     */
    class EventSource {
    public:
        EventSource() : _quit(false) {}
        virtual ~EventSource() {}
        
        void drop() { _quit = true; }
        
        // ------------------------- need to be override --------------------------
        
        virtual bool prepare() = 0;
        virtual bool check() = 0;
        
        virtual bool dispatch(EventHandler& func) = 0;
        
    private:
        friend class EventLoop;
        
        bool quit() { return _quit; };
        
        bool _quit;
        EventHandler handler;
    };
    
    /**
     *
     */
    class EventSourceOperator {
        virtual bool addEventSource(EventSource *source, EventHandler handler = nullptr) = 0;
        virtual bool setSourceHandler(EventSource *source, EventHandler handler) = 0;
        virtual bool removeEventSource(EventSource *source) = 0;
        bool clearSourceHandler(EventSource *source) {
            return setSourceHandler(source, nullptr);
        }
    };
}

#endif /* _event_source_hpp */
