
namespace harry_plotter {

constexpr const char* TERMINATE_MESSAGE_FORMAT = R"(
[ERROR]
* File: {}
* Line: {}
* Cond: {}
)";

    void
    terminate(
        const char* file_name,
        int line,
        const char* condition_str,
        const char* message
    ) {
        print(TERMINATE_MESSAGE_FORMAT, file_name, line, condition_str);
        if (message) {
            print("* {}\n", message);
        }

        std::terminate();
    }

} // harry_plotter
