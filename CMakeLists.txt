cmake_minimum_required(VERSION 3.9)
project(VkSoftwareRender)

set(CMAKE_CXX_STANDARD 11)

add_executable(VkSoftwareRender
        main.cpp
        VirtualScreen.h VirtualScreen.cpp MathUtility.h MathUtility.cpp Rasterisation.h Rasterisation.cpp)