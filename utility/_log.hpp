//
//  _log.hpp
//  exam-demon
//
//  Created by fallen.ink on 26/02/2017.
//  Copyright © 2017 fallenink. All rights reserved.
//

#include <iostream>

#ifndef _log_hpp
#define _log_hpp

namespace suite_cpp {
    namespace log {
        std::ostream& blue(std::ostream &s);
        std::ostream& red(std::ostream &s);
        std::ostream& green(std::ostream &s);
        std::ostream& yellow(std::ostream &s);
        std::ostream& white(std::ostream &s);
    }
}

#endif /* _log_hpp */
