
#include <Data.hpp>

namespace harry_plotter {

    /*
    ## Data: impl
    */

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
    Data::view(int start_pos) {
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