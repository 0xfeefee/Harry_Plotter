
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
        for (int i = 0; i < image.area(); ++i) {
            u32& rgba = image[i];
            rgba = 0xFF << 24; // Alpha is always 255.

            u8 intensity = data_view.get_or<u8>(0);
            rgba |= intensity | intensity << 8 | intensity << 16;
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
