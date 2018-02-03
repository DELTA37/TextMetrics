cmake_minimum_required(VERSION 3.9.5)
find_package(Boost REQUIRED)
add_definitions("-std=c++17")
include_directories(include)

add_executable(evaluate src/bin/main.cpp)

add_subdirectory(src)
target_link_libraries(BLEU ${Boost_LIBRARIES})
target_link_libraries(evaluate BLEU)
