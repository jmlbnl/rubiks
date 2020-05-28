CXXFLAGS += -std=c++11
CXX = g++
CPP = g++
CC = g++

OBJS = Permutation.o PermutationMap.o ArrayRep.o

LDLIBS += -lm -lglut -lGL -lGLU

EXE = full getSymmetry

all: ${EXE}

full:  ${OBJS}

getSymmetry: ${OBJS}

clean:
	rm *.o *~ ${EXE}

depend:
	makedepend *.C 2> /dev/null

# DO NOT DELETE

ArrayRep.o: ArrayRep.h /usr/include/string.h /usr/include/features.h
ArrayRep.o: /usr/include/stdc-predef.h /usr/include/xlocale.h Permutation.h
ArrayRep.o: PermutationMap.h /usr/include/assert.h
Permutation.o: /usr/include/string.h /usr/include/features.h
Permutation.o: /usr/include/stdc-predef.h /usr/include/xlocale.h
Permutation.o: Permutation.h
PermutationMap.o: PermutationMap.h /usr/include/string.h
PermutationMap.o: /usr/include/features.h /usr/include/stdc-predef.h
PermutationMap.o: /usr/include/xlocale.h
full.o: Permutation.h /usr/include/string.h /usr/include/features.h
full.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
full.o: PermutationMap.h
getSymmetry.o: Permutation.h /usr/include/string.h /usr/include/features.h
getSymmetry.o: /usr/include/stdc-predef.h /usr/include/xlocale.h ArrayRep.h
getSymmetry.o: PermutationMap.h
perm.o: /usr/include/string.h /usr/include/features.h
perm.o: /usr/include/stdc-predef.h /usr/include/xlocale.h perm.h
