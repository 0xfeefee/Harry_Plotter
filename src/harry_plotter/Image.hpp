
#pragma once
#include <harry_plotter/Data.hpp>

namespace harry_plotter {

    struct Image {
        s16 width;
        s16 height;
        u8* data;

        Image(int width);
        Image(int width, int height);

        ~Image();

        int
        size();

        int
        area();

        u32&
        operator[](int index);

        static Image
        from_binary_data(const Data& data);

        static Image
        from_binary_data(const Data& data, u8 min_treshold, u8 max_treshold = 255);

        static Image
        from_binary_data_trail(const Data& data);

        static Image
        from_histogram(std::vector<int> histogram);

        static void
        write_to_disk(Image& image, const std::string& image_path);
    };

}