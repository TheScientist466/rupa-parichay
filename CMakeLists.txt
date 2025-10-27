cmake_minimum_required(VERSION 3.21)
project(rupa-parichay)

add_subdirectory(extlibs)

add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system ImGui-SFML::ImGui-SFML)
