cmake_minimum_required(VERSION 3.21)

set(
    mastishk_src_files
    "src/Layer.cpp"
)

add_library(mastishk STATIC ${mastishk_src_files})
target_include_directories(mastishk PUBLIC include)