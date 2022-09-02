SRC = src
BIN = bin
INC = include
EXT_INC = libs/SDL2/include
LIBS = bin/libs
EXT_LIBS = -L libs/SDL2/lib -L libs/SDL2_ttf/lib -L libs/SDL2_image/lib
EXT_LIBS_LIST = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
CFLAGS = -g -I ${INC} -I ${EXT_INC} -L ${LIBS} ${EXT_LIBS} 
OBJ_DIR = ${BIN}/libs

obj := ${wildcard ${OBJ_dir}/*.o}

all: ${BIN}/main

${BIN}/main: ${OBJ_DIR}/titleScreen.o ${OBJ_DIR}/tile.o ${OBJ_DIR}/grid.o ${SRC}/main.cpp 
	${CXX} ${CFLAGS} -o $@ $? ${EXT_LIBS_LIST}

${OBJ_DIR}/grid.o: ${OBJ_DIR}/tile.o ${SRC}/grid.cpp
	${CXX} ${CFLAGS} -c -o $@ $? ${EXT_LIBS_LIST}

${OBJ_DIR}/tile.o: ${SRC}/tile.cpp
	${CXX} ${CFLAGS} -c -o $@ $? ${EXT_LIBS_LIST}

${OBJ_DIR}/titleScreen.o: ${SRC}/titleScreen.cpp
	${CXX} ${CFLAGS} -c -o $@ $? ${EXT_LIBS_LIST}

clean:
	del /Q /S *.o
	del /Q /S *.exe