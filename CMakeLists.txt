cmake_minimum_required(VERSION 3.0.0)

project(water-wave VERSION 0.1.0)

###################################################
# include
###################################################

# include目录
include_directories ("${PROJECT_SOURCE_DIR}/")
# include_directories("E:/0code/learn_opengl/include")

###################################################
# library
###################################################

# 包
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# lib目录
# link_directories("../lib")

# 连接库
# set (EXTRA_LIBS ${EXTRA_LIBS} glfw3 glew32 opengl32)

###################################################
# source
###################################################

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(src DIR_SRCS)

# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})


###################################################
# option,编译选项
###################################################

target_link_libraries (${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glfw ${GLEW_LIBRARIES}) # 跟 find_package 配合使用

# 是否静态编译
# 注意！只能工作于GCC编译器（Clang未测试，理论上兼容）
# 即使开了静态编译，还是会有部分库是动态链接的
IF(0)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
ENDIF()

# 是否静态编译
# 注意！只能工作于MSVC编译器，且需要跟VCPKG配合使用
IF(0)
    set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
ENDIF()
set(VCPKG_CRT_LINKAGE "static")
set(VCPKG_LIBRARY_LINKAGE "static")