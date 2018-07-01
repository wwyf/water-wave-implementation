cmake_minimum_required(VERSION 3.0.0)

project(water-wave) VERSION 0.1.0)

###################################################
# include
###################################################

# include目录
# include_directories ("${PROJECT_SOURCE_DIR}/")
include_directories("E:/0code/learn_opengl/include")

###################################################
# library
###################################################

# lib目录
link_directories("../lib")

# 连接库
set (EXTRA_LIBS ${EXTRA_LIBS} glfw3 opengl32 gdi32 GLAD assimp)

###################################################
# source
###################################################

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(source DIR_SRCS)

# 指定生成目标
add_executable(hw5-teapot ${DIR_SRCS})


###################################################
# option,编译选项
###################################################

target_link_libraries (hw5-teapot  ${EXTRA_LIBS})