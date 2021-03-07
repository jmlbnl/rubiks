#pragma once

#include "Permutation.h"
#include "ArrayRep.h"

class ArrayRepCnt {
 public:
 ArrayRepCnt(u_int8_t *buff) : x(buff), cnt(buff[48]) {};
    ArrayRep x;
    int cnt;
};

class Heuristic {

 public:
    void loadCubes(std::vector<ArrayRepCnt> &cubes);
    void loadSideStore(const char *fn, std::vector<SideStore> &cornerStore);
    void loadCornerStore(std::vector<CornerStore> &cornerStore);
 public:
    std::vector<ArrayRep> Svec;
    std::vector<ArrayRepCnt> cubeWithCountsSymSuppressed;
    std::vector<CornerStore> cornerStore;
    std::vector<SideStore> sideStoreFront;
    std::vector<SideStore> sideStoreBack;

    Heuristic() {};

    void init();
  int CornerTurnsToSolve(ArrayRep &x);
    int Manhatten(ArrayRep &x);
    //int BackManhatten(const ArrayRep &x);
};

	
