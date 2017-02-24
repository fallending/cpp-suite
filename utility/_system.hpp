//
//  _system.hpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include <chrono>
#include <cstdint>

#ifndef _system_hpp
#define _system_hpp

namespace suite_cpp {
    
    static inline std::uint64_t time_now() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                                                                     std::chrono::system_clock::now().time_since_epoch()).count();
    }
    
} // namespace Grinder

#endif /* _system_hpp */
