//
//  _ticker_source.cpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include <iostream>

#include "_system.hpp"
#include "_ticker_source.hpp"

namespace suite_cpp {
    using namespace std;
    
    TickerSource::TickerSource(int duration) : EventSource(), _duration(duration), _nextTrigger(time_now() + duration), _triggeredCount(0) {
        
    }
    
    uint64_t TickerSource::timelast() {
        return _triggeredCount * _duration;
    }
    
    /////
    
    bool TickerSource::isReady() {
        uint64_t now = time_now();
        if (now >= _nextTrigger) {
            _nextTrigger = _duration + _nextTrigger;
            
            _triggeredCount ++;
            
            return true;
        }
        
        return false;
    }
    
    bool TickerSource::prepare() {
        return isReady();
    }
    
    bool TickerSource::check() {
        return isReady();
    }
}
