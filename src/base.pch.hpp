
#pragma once

#define EXPECT(condition, ...)   if (!(condition)) \
    drumstick::terminate(__FILE__, __LINE__, #condition, __VA_ARGS__)
#define ERROR_IF(condition, ...) if ((condition))  \
    drumstick::terminate(__FILE__, __LINE__, #condition, __VA_ARGS__
#define print(fmt, ...) std::cout << std::format(fmt, __VA_ARGS__);

namespace harry_plotter {

    /*
        Print out the caller location and terminate the application.
    */
    void
    terminate(
        const char* file_name,
        int line,
        const char* condition_str,
        const char* message = nullptr
    );

}
