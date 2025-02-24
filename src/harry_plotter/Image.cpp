
#include <harry_plotter/Image.hpp>
#include <harry_plotter/Math.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace harry_plotter {

    Image::Image(int width)
    : width(width), height(width), data(new u8[width*width*4]) {
    }

    Image::Image(int width, int height)
    : width(width), height(height), data(new u8[width*height*4]) {
    }

    Image::~Image() {
        /*
            @memory: no stall, leak it
        */
        // delete[] data;
    }

    int
    Image::area() {
        return width * height;
    }

    int
    Image::size() {
        return width * height * 4;
    }

    u32&
    Image::operator[](int index) {
        u32* val = (u32*)&(data[index*4]);
        return *val;
    }

    Image
    Image::from_binary_data(const Data& data) {
        Image image(Math::sqrt(data.byte_count));
        Data_View data_view = data.view(0);

        u8 intensity;
        for (int i = 0; i < image.area(); ++i) {
            intensity = data_view.value_or<u8>(0);
            image[i]  = intensity | intensity << 8 | intensity << 16 | 0xFF << 24;
        }

        return image;
    }

    Image
    Image::from_binary_data(const Data& data, u8 min_treshold, u8 max_treshold) {
        Image image(Math::sqrt(data.byte_count));
        Data_View data_view = data.view(0);

        u8 intensity;
        for (int i = 0; i < image.area(); ++i) {
            intensity = data_view.value_or<u8>(0);

            if (intensity < max_treshold)      intensity = 0;
            else if (intensity < min_treshold) intensity = 0;

            image[i] = intensity | intensity << 8 | intensity << 16 | 0xFF << 24;
        }

        return image;
    }

    Image
    Image::from_binary_data_trail(const Data& data) {
        Image image(Math::sqrt(data.byte_count));
        Data_View data_view = data.view(0);

        u8 intensity, k;
        for (int i = 0; i < image.area(); ++i) {
            intensity = data_view.value_or<u8>(0);

            if (k < 0) k = intensity;
            else k       -= intensity/32;

            intensity = k % 255;

            image[i] = intensity | intensity << 8 | intensity << 16 | 0xFF << 24;
        }

        return image;
    }

    Image
    Image::from_histogram(std::vector<int> histogram) {
        EXPECT(histogram.size() > 1);

        // Prepare the data:
        int min_val = histogram[0];
        int max_val = histogram[0];

        for (int i = 1; i < histogram.size(); ++i) {
            int val = histogram[i];

            if      (val < min_val) min_val = val;
            else if (val > max_val) max_val = val;
        }

        // Generate an image of desired width:
        constexpr int IMAGE_WIDTH = 256;
        int step                  = 1 + max_val / IMAGE_WIDTH;

        Image image(IMAGE_WIDTH, histogram.size());

        // Draw the histogram:
        int num_steps;
        u8  red;

        for (int i = 0; i < image.height; ++i) {
            num_steps = 1 + histogram[i] / step;
            red       = num_steps < IMAGE_WIDTH/2 ? 0 : 200;

            for (int k = 0; k < num_steps; ++k) {
                image[i * image.width + k] = red | 50 << 8 | 50 << 16 | 0xFF << 24;
            }
        }

        return image;
    }

    void
    Image::write_to_disk(Image& image, const std::string& image_path) {
        stbi_write_png(
            image_path.c_str(),
            image.width,
            image.height,
            4,
            (void*)image.data,
            image.width*4
        );
    }

}
