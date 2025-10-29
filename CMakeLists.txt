cmake_minimum_required(VERSION 3.21)
project(rupa-parichay)

add_subdirectory(extlibs)

set(
    src_files 
    "src/main.cpp"
    "src/renderer.cpp"
    "src/canvas.cpp"
)

add_executable(${PROJECT_NAME} ${src_files})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system ImGui-SFML::ImGui-SFML)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
