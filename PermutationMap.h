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

struct CornerCubie {
    int ccIdx2Idx[8];             // the idx of the sample location on the full cube
                                  // of the ith cubie
    int idx2ccIdx[48];            // The cubieidx of the cubie given any idx of the face
    int face2Orientation[8][48];  // The orientation of cubie at position i if the face
                                  // at the sample location has idx j
};

struct SideCubie {
    int ccIdx2Idx[12];            // the idx of the sample location on the full cube
    int idx2ccIdx[48];            // The cubieidx of the cubie given any idx of the face
    int face2Orientation[12][48];
};
    
// These map an array to a label value and to the spacial positions
class PermutationMap {
 public:
    std::map<int, int> label2idx;
    std::map<int, int> idx2label;
    
    PermutationMap(int n, Face *array);

    std::map<int, int> c_idx2label;
    std::map<int, int> c_label2idx;
    std::map<int, int> s_idx2label;
    std::map<int, int> s_label2idx;

    std::map<int, int> face_opposites;
    std::map<int, int> c_label_clockwise;
    std::map<int, int> s_label_opposites;

    CornerCubie cornercubies;
    SideCubie sidecubies;
    
    int getCornerOrientation(int pos, int face);
    int getSideOrientation(int pos, int face);
    int sortDigits(int x);
    int flipDigits(int x);
    void dump();
};

extern PermutationMap RubiksMap;
extern PermutationMap CubeMapCorners;
