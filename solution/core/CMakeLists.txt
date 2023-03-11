cmake_minimum_required(VERSION 3.5)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES config_service/ConfigurationService.cpp
    config_service/ServerConfiguration.cpp logging_service/Logger.cpp
    config_service/WriterConfiguration.cpp
    writer_service/WriterThread.cpp)

file(GLOB ProtoFiles "protobuf/*.proto")

PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})

set(ProtobufIncludePath ${CMAKE_CURRENT_BINARY_DIR}
    CACHE INTERNAL "Path to generated protobuf files.")

add_library(core ${SOURCE_FILES} ${ProtoSources} ${ProtoHeaders})
target_link_libraries(core ${PROTOBUF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

set(CoreIncludePath ${CMAKE_CURRENT_SOURCE_DIR}/config_service/
    ${CMAKE_CURRENT_SOURCE_DIR}/logging_service/
    ${CMAKE_CURRENT_SOURCE_DIR}/writer_service/
    ${CMAKE_CURRENT_SOURCE_DIR}/utility
     CACHE INTERNAL "Path core include files.")

target_include_directories(core PUBLIC ${CoreIncludePath} ${CMAKE_CURRENT_BINARY_DIR})


