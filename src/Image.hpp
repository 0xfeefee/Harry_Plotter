
#pragma once
#include <Data.hpp>

namespace harry_plotter {

    struct Image {
        s16 width;
        s16 height;
        u8* data;

        Image(int width);

        static Image
        from_binary_data(Data& data);
    };

}