cmake_minimum_required(VERSION 3.10)
project(RayCaster)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 package
if(WIN32)
    # Specify SDL2 path for Windows
    set(SDL2_DIR "C:/SDL2/cmake")
    set(SDL2_PATH "C:/SDL2")
endif()

find_package(SDL2 REQUIRED)

# Add executable
add_executable(raycaster main.cpp)

# Include directories
target_include_directories(raycaster PRIVATE ${SDL2_INCLUDE_DIRS})

# Link libraries
target_link_libraries(raycaster PRIVATE ${SDL2_LIBRARIES})

# Copy SDL2.dll to output directory on Windows
if(WIN32)
    add_custom_command(TARGET raycaster POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:raycaster>
    )
endif()
