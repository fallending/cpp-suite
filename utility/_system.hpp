//
//  _system.hpp
//  exam-demon
//
//  Created by fallen on 17/2/24.
//  Copyright © 2017年 fallenink. All rights reserved.
//

#include <chrono>
#include <cstdint>

#import <sys/sysctl.h>
#import <arpa/inet.h>
#import <net/if.h>
#import <ifaddrs.h>

#ifndef _system_hpp
#define _system_hpp

namespace suite_cpp {
    
    namespace system {
        static inline std::uint64_t time_now() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                                                                         std::chrono::system_clock::now().time_since_epoch()).count();
        }

        static inline char *ip() {
            char *local_ip = NULL;
            struct ifaddrs *addrs;
            if (getifaddrs(&addrs)==0) {
                const struct ifaddrs *cursor = addrs;
                while (cursor != NULL) {
                    if (cursor->ifa_addr->sa_family == AF_INET && (cursor->ifa_flags & IFF_LOOPBACK) == 0) {
                        //NSString *name = [NSString stringWithUTF8String:cursor->ifa_name];
                        //if ([name isEqualToString:@"en0"]) // Wi-Fi adapter
                        {
                            local_ip = inet_ntoa(((struct sockaddr_in *)cursor->ifa_addr)->sin_addr);
                            break;
                        }
                    }
                    cursor = cursor->ifa_next;
                }
                freeifaddrs(addrs);
            }
            return local_ip;
        }

    }
    
    
} // namespace Grinder

#endif /* _system_hpp */
