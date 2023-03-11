cmake_minimum_required(VERSION 3.5)

project(algorithmic_questions_ground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOLUTION_LIBRARY_LIB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SOLUTION_LIBRARY_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/solution)
set(APP_BINARY_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Protobuf REQUIRED)
if (Protobuf_FOUND)
    message("Protobuf found")
elseif()
    message(FATAL_ERROR "Please install Protobuf package.")
endif()

find_package(Boost)
if (Protobuf_FOUND)
    message("Boost found")
elseif()
    message(FATAL_ERROR "Please install Boost package.")
endif()

find_package (Threads)

enable_testing()

add_subdirectory(solution)
add_subdirectory(tests)

add_executable(simple_server main.cpp)

target_include_directories(simple_server PRIVATE
       ${SOLUTION_LIBRARY_INCLUDE_DIRECTORY}/server ${CoreIncludePath})

target_link_libraries(simple_server PRIVATE server)

install(TARGETS simple_server
                DESTINATION ${APP_BINARY_DIRECTORY})
