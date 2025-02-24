
#pragma once
#include <iostream> // IWYU pragma: keep
#include <format>   // IWYU pragma: keep
#include <fstream>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep
#include <algorithm> // IWYU pragma: keep

#define EXPECT(condition, ...)   if (!(condition)) \
    harry_plotter::terminate(__FILE__, __LINE__, #condition, __VA_ARGS__)
#define ERROR_IF(condition, ...) if ((condition))  \
    harry_plotter::terminate(__FILE__, __LINE__, #condition, __VA_ARGS__)

#define print(fmt, ...) std::cout << std::format(fmt, __VA_ARGS__);

namespace harry_plotter {

    typedef uint8_t  u8;
    typedef int16_t  s16;
    typedef uint32_t u32;
    typedef float    f32;

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

} // harry_plotter
