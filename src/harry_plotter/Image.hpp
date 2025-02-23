
#pragma once
#include <harry_plotter/Data.hpp>

namespace harry_plotter {

    struct Image {
        s16 width;
        s16 height;
        u8* data;

        Image(int width);

        int
        size();

        int
        area();

        u32&
        operator[](int index);

        static Image
        from_binary_data(const Data& data);

        static void
        write_to_disk(Image& image, const std::string& image_path);
    };

}