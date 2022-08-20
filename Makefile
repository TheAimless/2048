SRC = src
BIN = bin
INC = -I include
LIBS = -L bin/libs
EXT_LIBS = -L libs/SDL2/lib
EXT_LIBS_LIST = -lSDL2
CFLAGS = ${INC} ${LIBS} ${EXT_LIBS} ${EXT_LIBS_LIST}
OBJ_DIR = ${BIN}/libs

obj := ${wildcard ${OBJ_dir}/*.o}

all: ${BIN}/main

${BIN}/main: ${OBJ_DIR}/tile.o ${OBJ_DIR}/grid.o ${SRC}/temp.cpp 
	${CXX} ${CFLAGS} -o $@ $?

${OBJ_DIR}/grid.o: ${OBJ_DIR}/tile.o ${SRC}/grid.cpp
	${CXX} ${CFLAGS} -c -o $@ $?

${OBJ_DIR}/tile.o: ${SRC}/tile.cpp
	${CXX} ${CFLAGS} -c -o $@ $?