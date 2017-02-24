//
//  _ticker_source.hpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include <cstdint>

#include "_event_source.hpp"

#ifndef _ticker_source_hpp
#define _ticker_source_hpp

namespace suite_cpp {
    class TickerSource : public EventSource {
    public:
        TickerSource(int duration = 1000);
        
        std::uint64_t timelast();
        
    protected:
        bool prepare() override;
        bool check() override;
        bool dispatch(EventHandler &func) override { return func(*this); }

    private:
        int _duration; // as second
        std::uint64_t _triggeredCount;
        std::uint64_t _nextTrigger;
        
        bool isReady();
    };
}

#endif /* _ticker_source_hpp */
