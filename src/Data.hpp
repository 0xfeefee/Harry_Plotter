
#pragma once

namespace harry_plotter {

    class Data_View;

    /*
        A chunk of binary data, to which we can take views.
    */
    struct Data {
        const int       byte_count;
        const u8* const ptr;

        explicit
        Data(int byte_count, u8* ptr);

        ~Data();

        Data_View
        view(int start_pos);
    };

    /*
        Non-owning pointer to binary data, used to traverse it and convert it to useful things.
    */
    class Data_View {
        int byte_count;
        u8* ptr;

    public:
        explicit Data_View(const Data& data, int start = 0);

        void
        move(int amount);

        u8
        operator[](int index);

        u8*
        get() {
            return ptr;
        }

        template <typename T>
        T*
        get() {
            T* value = reinterpret_cast<T*>(ptr);
            move(static_cast<int>(sizeof(T)));

            return value;
        }

        template <typename T>
        T*
        get_array(int array_size) {
            EXPECT(array_size > 0);

            T* value = reinterpret_cast<T*>(ptr);
            move(static_cast<int>(sizeof(T) * array_size));

            return value;
        }
    };

}
