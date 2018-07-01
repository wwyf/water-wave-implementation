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

# lib目录
# link_directories("../lib")

# 连接库
set (EXTRA_LIBS ${EXTRA_LIBS} glfw3 glew32 opengl32)

###################################################
# source
###################################################

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(src DIR_SRCS)

# 指定生成目标
add_executable(water-wave ${DIR_SRCS})


###################################################
# option,编译选项
###################################################

target_link_libraries (water-wave  ${EXTRA_LIBS})