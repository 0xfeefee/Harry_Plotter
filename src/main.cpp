
#include <harry_plotter/Data.hpp>
#include <harry_plotter/Math.hpp>
#include <harry_plotter/Image.hpp>
using namespace harry_plotter;

int
main(int argc, const char* argv[]) {
    Data file_data  = Data::from_file("test.txt");
    Data image_data = Data::from_file("test.png");
    Data code_data   = Data::from_file("../src/main.cpp");

    print("file_data: {}\nimage_data: {}\n", file_data.byte_count, image_data.byte_count);

    {
        float a = Math::sqrt(4);
        float b = Math::sqrt(16);
        float c = Math::sqrt(128);
    }

    {
        int side = Math::sqrt(image_data.byte_count);
        print("Side: {}\n", side);

        EXPECT(side * side >= image_data.byte_count);
    }

    {
        Image image = Image::from_binary_data(image_data, 50, 100);
        Image::write_to_disk(image, "output.png");

        Image image2 = Image::from_binary_data(code_data);
        Image::write_to_disk(image2, "output3.png");
    }

    {
        std::vector<int> histogram = image_data.gen_histogram();

        for (int i = 0; i < histogram.size(); ++i) {
            print("{} ", histogram[i]);
        }
        print("\n");

        Image image = Image::from_histogram(histogram);
        Image::write_to_disk(image, "histogram.png");
    }

    {
        Data image_data = Data::from_file("lines.png");
        Image image = Image::from_binary_data_trail(image_data);
        Image::write_to_disk(image, "lines2.png");
    }

    return 0;
}
