
cmake_minimum_required(VERSION 3.20)

# Basic configuration:
project(Harry_Plotter
	VERSION   0.1.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD   20)
set(SRC 			   "${CMAKE_CURRENT_LIST_DIR}/../src")
set(VENDOR             "${CMAKE_CURRENT_LIST_DIR}/../vendor")


# Sources & include dirs:
add_executable(${PROJECT_NAME}
	${SRC}/base.pch.cpp
	${SRC}/main.cpp
	${SRC}/harry_plotter/Data.cpp
	${SRC}/harry_plotter/Math.cpp
	${SRC}/harry_plotter/Image.cpp
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${SRC}
	${VENDOR}/stb
)

# Compile definitions:
set(INFO_STRING
	"${CMAKE_PROJECT_NAME} v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} (${CMAKE_BUILD_TYPE})"
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
	PROJECT_INFO_STRING="${INFO_STRING}"
)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE
	${SRC}/base.pch.hpp
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE
		PROJECT_BUILD_DEBUG=1
	)
else()
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE
		PROJECT_BUILD_RELEASE=1
	)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_COMPILER_FLAGS_DEBUG "-Wextra -Werror")
	set(CMAKE_CXX_COMPILER_FLAGS_RELEASE "-Wall -Wextra -Werror")
	target_compile_options(${PROJECT_NAME}
		PRIVATE
		-msse
	)
else()
	message(FATAL_ERROR "Unsupported compiler!")
endif()
