cmake_minimum_required(VERSION 3.20)
project(BzrNetProtocolTests LANGUAGES CXX)

add_executable(bzrnet_protocol_tests
    bzrnet_protocol_tests.cpp
    ../src/patches/bzrnet_protocol.cpp
)

target_include_directories(bzrnet_protocol_tests PRIVATE ../include)
target_compile_features(bzrnet_protocol_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(bzrnet_protocol_tests PRIVATE /W4 /WX)
else()
    target_compile_options(bzrnet_protocol_tests PRIVATE -Wall -Wextra -Werror)
endif()
