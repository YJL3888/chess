CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = bishop.o board.o chesspiece.o computerplayer.o game.o gui.o humanplayer.o king.o knight.o main.o observer.o pawn.o player.o queen.o rook.o square.o textdisplay.o types.o level1.o level2.o level3.o level4.o level5.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -lXpm -lSDL2 -lSDL2_image
-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
