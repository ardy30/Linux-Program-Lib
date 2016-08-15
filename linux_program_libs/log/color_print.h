#ifndef __HVN_COLOR_PRINT_H__
#define __HVN_COLOR_PRINT_H__

#include <iostream>

#define BLINK_RED_START         "\033[1;4;31;40m"
#define BLINK_GREEN_START       "\033[1;40;32;40m"
#define BLINK_YELLOW_START      "\033[1;5;33;40m"
#define BLINK_BLUE_START        "\033[1;40;34;40m"

#define BLINK_RED_END           "\033[0m"
#define BLINK_GREEN_END         "\033[0m"
#define BLINK_YELLOW_END        "\033[0m"
#define BLINK_BLUE_END          "\033[0m"

#define WHITE_MSG(msg)          (std::cout << (msg) << std::endl)
#define RED_MSG(msg)            (std::cout << BLINK_RED_START << (msg) << BLINK_RED_END << std::endl)
#define GREEN_MSG(msg)          (std::cout << BLINK_GREEN_START << (msg) << BLINK_GREEN_END << std::endl)
#define YELLOW_MSG(msg)         (std::cout << BLINK_YELLOW_START << (msg) << BLINK_YELLOW_END << std::endl)
#define BLUE_MSG(msg)           (std::cout << BLINK_BLUE_START << (msg) << BLINK_BLUE_END <<std::endl)

#define SYS_PARA_MSG(msg1, msg2)            (std::cout << BLINK_GREEN_START << (msg1) << BLINK_GREEN_END << (msg2) << std::endl)
#define TASK_FINISH_MSG(msg1, msg2)         (std::cout << BLINK_YELLOW_START << (msg1) << BLINK_YELLOW_END << BLINK_RED_START << (msg2) << BLINK_GREEN_END << std::endl)
#define TASK_FALSE_MSG(msg1, msg2)          (std::cout << BLINK_RED_START << (msg1) << BLINK_RED_END << (msg2) << std::endl)

#endif
