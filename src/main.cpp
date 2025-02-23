
#include <Data.hpp>
#include <Math.hpp>
using namespace harry_plotter;

Data
read_entire_file(const std::string& file_name) {
    std::ifstream input_file(file_name, std::ios::binary | std::ios::ate);
    EXPECT(input_file.is_open());

    int size   = static_cast<int>(input_file.tellg());
    u8* buffer = new u8[size];

    input_file.seekg(0, std::ios::beg);
    input_file.read(reinterpret_cast<char*>(buffer), size);

    return Data(size, buffer);
}


int
main(int argc, const char* argv[]) {
    Data file_data  = read_entire_file("test.txt");
    Data image_data = read_entire_file("test.png");

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

    return 0;
}
