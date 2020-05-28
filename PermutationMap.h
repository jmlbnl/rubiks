#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

struct ElementDescriptor {
    std::string name;
    int degeneracy;
};

// This defines the real space position of each face
// the positions are the positions of the cube...
struct Face {
    int id, xpos, ypos;
};


// These map an array to a label value and to the spacial positions
class PermutationMap {
 public:
    std::map<int, int> label2idx;
    std::map<int, int> idx2label;
    
    PermutationMap(int n, Face *array);

    int ncorners;
    int nsides;
    
    u_int8_t cornerIdx[8*3];
    u_int8_t sideIdx[12*2];
    
    void dump();
};

extern PermutationMap RubiksMap;
