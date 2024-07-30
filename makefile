CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = bishop.o board.o chesspiece.o computerplayer.o game.o gui.o humanplayer.o king.o knight.o main.o observer.o pawn.o player.o queen.o rook.o square.o textdisplay.o types.o level1.o level2.o level3.o level4.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lSDL2 -lSDL2_ttf -lX11
-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
