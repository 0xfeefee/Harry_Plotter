
#include <harry_plotter/Data.hpp>

namespace harry_plotter {

    /*
    ## Data: impl
    */

    Data
    Data::from_file(const std::string& file_name) {
        std::ifstream input_file(file_name, std::ios::binary | std::ios::ate);
        EXPECT(input_file.is_open());

        int size   = static_cast<int>(input_file.tellg());
        u8* buffer = new u8[size];

        input_file.seekg(0, std::ios::beg);
        input_file.read(reinterpret_cast<char*>(buffer), size);

        return Data(size, buffer);
    }

    Data::Data(int byte_count, u8* ptr)
    : byte_count(byte_count),
      ptr(ptr) {
        EXPECT(byte_count > 0);
        EXPECT(ptr != nullptr);
    }

    Data::~Data() {
        /*
            @memory: This memory will not be re-used in the program, so this is commented out to
            avoid stalling the exit for no reason. OS will handle it.
        */
        // delete ptr;
    }

    Data_View
    Data::view(int start_pos) const {
        return Data_View(*this, start_pos);
    }


    /*
    ## Data_View: impl
    */

    Data_View::Data_View(const Data& data, int start)
    : byte_count(data.byte_count-start),
      ptr(const_cast<u8*>(data.ptr)) {
        EXPECT(data.ptr != nullptr);
        EXPECT(data.byte_count > start);
    }

    void
    Data_View::move(int amount) {
        EXPECT(byte_count >= amount);

        byte_count -= amount;
        ptr        += amount;
    }

    u8
    Data_View::operator[](int index) {
        EXPECT(index >= 0 && index <= byte_count);

        return ptr[index];
    }


}