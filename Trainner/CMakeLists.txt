# cmake_minimum_required(VERSION 3.21)
# project(TrainerRunner)

# set(CMAKE_CXX_STANDARD 17)

# # Include directories for mastishk headers
# include_directories(include)

# # Source files
# # We need trainer.cpp and Layer.cpp because trainer uses Layer class
# set(SOURCES
#     src/main.cpp
#     src/Layer.cpp
# )

# add_executable(TrainerRunner ${SOURCES})
cmake_minimum_required(VERSION 3.21)
project(TrainerRunner)

set(
    trainer_src_files
    "src/Layer.cpp"
    "src/main.cpp"
)

add_executable(trainer ${trainer_src_files})
target_include_directories(trainer PUBLIC include)