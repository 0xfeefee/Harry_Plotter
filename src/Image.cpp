
#include <Image.hpp>
#include <Math.hpp>

namespace harry_plotter {

    Image::Image(int width)
    : width(width), height(width), data(nullptr) {}

    Image
    Image::from_binary_data(Data& data) {
        Image i(Math::sqrt(data.byte_count));
        return i;
    }

}