//
//  _win32_log.cpp
//  exam-demon
//
//  Created by fallen.ink on 26/02/2017.
//  Copyright © 2017 fallenink. All rights reserved.
//

#include "_log.hpp"
#ifdef _WIN32
#include <windows.h>

namespace suite_cpp {
    namespace log {
        std::ostream& blue(std::ostream &s) {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            return s;
        }
         
        std::ostream& red(std::ostream &s) {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
              SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_INTENSITY);
              return s;
        }
        std::ostream& green(std::ostream &s) {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            return s;
        }
         
        std::ostream& yellow(std::ostream &s) {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
            return s;
        }
         
        std::ostream& white(std::ostream &s) {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            return s;
        }
        
        struct color {
            color(WORD attribute): m_color(attribute){};
            WORD m_color;
        };
        
        template <class _Elem, class _Traits> std::basic_ostream<_Elem,_Traits>&
        operator<<(std::basic_ostream<_Elem,_Traits>& i, const color& c) {  HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);  SetConsoleTextAttribute(hStdout,c.m_color);  return i; }
    }
}

#endif
