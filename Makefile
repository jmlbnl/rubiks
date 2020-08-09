CXXFLAGS += -std=c++11
CXX = g++
CPP = g++
CC = g++

OBJS = Permutation.o PermutationMap.o ArrayRep.o heuristic.o

LDLIBS += -lm -lglut -lGL -lGLU

EXE = full getSymmetry test generateDeep generateManhatten solve

all: ${EXE}

full: ${OBJS}

getSymmetry: ${OBJS}

test: ${OBJS}

generateDeep: ${OBJS}

generateManhatten: ${OBJS}

solve: ${OBJS}

clean:
	rm *.o *~ ${EXE}

depend:
	makedepend *.C 2> /dev/null

# DO NOT DELETE

ArrayRep.o: ArrayRep.h /usr/include/string.h /usr/include/features.h
ArrayRep.o: /usr/include/stdc-predef.h /usr/include/xlocale.h Permutation.h
ArrayRep.o: PermutationMap.h /usr/include/assert.h /usr/include/unistd.h
ArrayRep.o: /usr/include/getopt.h
Permutation.o: /usr/include/string.h /usr/include/features.h
Permutation.o: /usr/include/stdc-predef.h /usr/include/xlocale.h
Permutation.o: Permutation.h
PermutationMap.o: PermutationMap.h /usr/include/string.h
PermutationMap.o: /usr/include/features.h /usr/include/stdc-predef.h
PermutationMap.o: /usr/include/xlocale.h
full.o: Permutation.h /usr/include/string.h /usr/include/features.h
full.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
full.o: PermutationMap.h
generateDeep.o: Permutation.h /usr/include/string.h /usr/include/features.h
generateDeep.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
generateDeep.o: PermutationMap.h /usr/include/unistd.h /usr/include/getopt.h
generateDeep.o: /usr/include/fcntl.h /usr/include/time.h
generateManhatten.o: Permutation.h /usr/include/string.h
generateManhatten.o: /usr/include/features.h /usr/include/stdc-predef.h
generateManhatten.o: /usr/include/xlocale.h ArrayRep.h PermutationMap.h
generateManhatten.o: /usr/include/unistd.h /usr/include/getopt.h
generateManhatten.o: /usr/include/fcntl.h /usr/include/time.h
getSymmetry.o: Permutation.h /usr/include/string.h /usr/include/features.h
getSymmetry.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
getSymmetry.o: PermutationMap.h
heuristic.o: Permutation.h /usr/include/string.h /usr/include/features.h
heuristic.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
heuristic.o: PermutationMap.h /usr/include/unistd.h /usr/include/getopt.h
heuristic.o: /usr/include/fcntl.h /usr/include/time.h
solve.o: Permutation.h /usr/include/string.h /usr/include/features.h
solve.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
solve.o: PermutationMap.h /usr/include/unistd.h /usr/include/getopt.h
solve.o: /usr/include/fcntl.h /usr/include/time.h
test.o: Permutation.h /usr/include/string.h /usr/include/features.h
test.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
test.o: PermutationMap.h heuristic.h /usr/include/unistd.h
test.o: /usr/include/getopt.h /usr/include/fcntl.h /usr/include/time.h
