cmake_minimum_required(VERSION 3.21)

# SFML
set(SFML_STATIC_LIBRARIES true)
set(SFML_BUILD_GRAPHICS true)
set(SFML_BUILD_WINDOW true)
set(SFML_BUILD_AUDIO false)
set(SFML_BUILD_NETWORK false)
set(SFML_BUILD_DOCS false)
add_subdirectory(SFML)

# imgui
set(IMGUI_SFML_FIND_SFML false)
set(IMGUI_DIR "../imgui")
add_subdirectory(imgui-sfml)
