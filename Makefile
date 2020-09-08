CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = sorcery
OBJECTS =  main.o enchantment.o spell.o player.o players.o minion.o ritual.o card.o ascii_graphics.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
