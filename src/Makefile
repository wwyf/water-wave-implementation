default_target: all
ROOT=..
INCLUDE=ROOT/external/glfw-3.1.2/include/
LINK= -lGL -lGLEW
CC_FLAGS=`pkg-config --cflags glfw3`
GLFW_LINK=`pkg-config --static --libs glfw3`
STD_FLAGS=-std=c++11
# OBJ=../common/build/shader.o ../common/build/objloader.o

# SHADER=../common/build/shader.o
EXEC=gerstner-water
UTIL=util
all: $(EXEC).out 

# run_obj:
# 	./${EXEC_OBJ}.out
# run_off:
# 	./${EXEC_OFF}.out
# run_ply:
# 	./${EXEC_PLY}.out
run:
	./$(EXEC).out

${EXEC}.o: ${EXEC}.cpp 
	g++ -c $< -I ${ROOT} ${LINK} $(STD_FLAGS) -o $@
$(UTIL).o: $(UTIL).cpp
	g++ -c $< -I $(ROOT) $(LINK) $(STD_FLAGS) -o $@
${EXEC}.out: ${EXEC}.o $(UTIL).o
	g++ ${CC_FLAGS} -o $@ $^ -I {ROOT} ${LINK} ${GLFW_LINK} $(STD_FLAGS)


${SHADER}: ../common/shader.cpp ../common/shader.hpp
	make -C ../common/ build/shader.o
../common/build/objloader.o: ../common/objloader.cpp
	make -C ../common/ build/objloader.o
clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.gch" -delete