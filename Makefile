SRC = src
BIN = bin
INC = -I include
EXT_INC = -I libs/SDL2/include
LIBS = -L bin/libs
EXT_LIBS = -L libs/SDL2/lib
EXT_LIBS_LIST = -lmingw32 -lSDL2main -lSDL2
CFLAGS = -g ${INC} ${EXT_INC} ${LIBS} ${EXT_LIBS} 
OBJ_DIR = ${BIN}/libs

obj := ${wildcard ${OBJ_dir}/*.o}

all: ${BIN}/main

${BIN}/main: ${OBJ_DIR}/tile.o ${OBJ_DIR}/grid.o ${SRC}/main.cpp 
	${CXX} ${CFLAGS} -o $@ $? ${EXT_LIBS_LIST}

${OBJ_DIR}/grid.o: ${OBJ_DIR}/tile.o ${SRC}/grid.cpp
	${CXX} ${CFLAGS} -c -o $@ $? ${EXT_LIBS_LIST}

${OBJ_DIR}/tile.o: ${SRC}/tile.cpp
	${CXX} ${CFLAGS} -c -o $@ $? ${EXT_LIBS_LIST}