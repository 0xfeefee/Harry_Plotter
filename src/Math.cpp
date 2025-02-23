
#include <Math.hpp>

#include <xmmintrin.h>

namespace harry_plotter {

    f32
    Math::sqrt(f32 n) {
        __m128 wf = _mm_set_ss(n);
        wf        = _mm_sqrt_ss(wf);

    #if PROJECT_BUILD_RELEASE
        return _mm_cvtss_f32(wf);
    #else
        f32 result = _mm_cvtss_f32(wf);
        print("Math::sqrt({}) -> {}\n", n, result);
        return result;
    #endif
    }

    int
    Math::sqrt(int n) {
        f32 result_f = Math::sqrt(static_cast<f32>(n));
        int result = static_cast<int>(result_f);

        if (result_f > result) {
            result += 1;
        }

    #if PROJECT_BUILD_DEBUG
        print("Math::sqrt<int>({}) -> {}\n", n, result);
    #endif
        return result;
    }

} // harry_plotter
