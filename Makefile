CXXFLAGS += -std=c++11
CXX = g++
CPP = g++
CC = g++

OBJS = Permutation.o PermutationMap.o ArrayRep.o heuristic.o 

LDLIBS += -lm -lglut -lGL -lGLU

EXE = display full getSymmetry test generateDeep generateManhatten solve testPermutationOrder solveLame countTwoByTwo

all: ${EXE}

full: ${OBJS}

getSymmetry: ${OBJS}

test: ${OBJS}

generateDeep: ${OBJS}

generateManhatten: ${OBJS}

solve: ${OBJS}

testPermutationOrder: ${OBJS}

solveLame: ${OBJS}

countTwoByTwo: ${OBJS}

display: ${OBJS}

clean:
	rm *.o *~ ${EXE}

depend:
	makedepend *.C 2> /dev/null

# DO NOT DELETE

ArrayRep.o: ArrayRep.h /usr/include/string.h Permutation.h PermutationMap.h
ArrayRep.o: /usr/include/assert.h /usr/include/features.h
ArrayRep.o: /usr/include/stdc-predef.h /usr/include/unistd.h
Permutation.o: /usr/include/string.h Permutation.h
PermutationMap.o: PermutationMap.h /usr/include/string.h
full.o: Permutation.h /usr/include/string.h ArrayRep.h PermutationMap.h
generateDeep.o: Permutation.h /usr/include/string.h ArrayRep.h
generateDeep.o: PermutationMap.h /usr/include/unistd.h
generateDeep.o: /usr/include/features.h /usr/include/stdc-predef.h
generateDeep.o: /usr/include/fcntl.h
generateManhatten.o: Permutation.h /usr/include/string.h ArrayRep.h
generateManhatten.o: PermutationMap.h /usr/include/unistd.h
generateManhatten.o: /usr/include/features.h /usr/include/stdc-predef.h
generateManhatten.o: /usr/include/fcntl.h
getSymmetry.o: Permutation.h /usr/include/string.h ArrayRep.h
getSymmetry.o: PermutationMap.h
heuristic.o: Permutation.h /usr/include/string.h ArrayRep.h PermutationMap.h
heuristic.o: heuristic.h /usr/include/unistd.h /usr/include/features.h
heuristic.o: /usr/include/stdc-predef.h /usr/include/fcntl.h
solve.o: Permutation.h /usr/include/string.h ArrayRep.h PermutationMap.h
solve.o: /usr/include/unistd.h /usr/include/features.h
solve.o: /usr/include/stdc-predef.h /usr/include/fcntl.h
test.o: Permutation.h /usr/include/string.h ArrayRep.h PermutationMap.h
test.o: heuristic.h /usr/include/unistd.h /usr/include/features.h
test.o: /usr/include/stdc-predef.h /usr/include/fcntl.h
