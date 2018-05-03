cmake_minimum_required(VERSION 3.9)
project(VkSoftwareRender)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#设置GLFW库的头文件目录
set(GLFW3_INCLUDE_DIR /include/GLFW)
#设置GLFW库的库文件路径
set(GLFW3_LIBRARY /lib/libglfw.so)

#设置GLEW库的头文件目录
set(GLEW_INCLUDE_DIR /include/GLEW)
#设置GLEW库的库文件目录
set(GLEW_LIBRARY /lib/libGLEW.so)

#将上述的头文件目录添加到一个列表变量之中
list(APPEND SUMMARY_DEBUG_INCLUDE ${GLFW3_INCLUDE_DIR})
list(APPEND SUMMARY_DEBUG_INCLUDE ${GLEW_INCLUDE_DIR})

#将上述的库文件目录添加到一个列表变量之中
list(APPEND SUMMARY_DEBUG_LIBS ${GLFW3_LIBRARY})
list(APPEND SUMMARY_DEBUG_LIBS ${GLEW_LIBRARY})

#利用find_package命令找到OpenGL
find_package(OpenGL REQUIRED)
list(APPEND SUMMARY_DEBUG_LIBS ${OPENGL_gl_LIBRARY})

#设置项目的头文件包含目录
include_directories(${SUMMARY_DEBUG_INCLUDE})

#在当前目录下搜索头文件及源文件
file(GLOB_RECURSE CURRENT_HEADERS *.h *.hpp)
file(GLOB CURRENT_SOURCES *.cpp TextureLoader/*.cpp)
#为头文件和源文件进行分组

add_executable(VkSoftwareRender ${CURRENT_HEADERS} ${CURRENT_SOURCES})
#设置项目的外部依赖库
target_link_libraries(VkSoftwareRender -lglfw -lGLEW -lGLU -lGL -lfreeimage)