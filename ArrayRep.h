#pragma once

#include <bits/stdc++.h>
#include <string.h>
#include "Permutation.h"
#include "PermutationMap.h"

// An array representation of a rubiks cube
// that allows for wildcards in the face positions
// the - will fail if called on a wildcard containing object
// the * operator will fail if multiplied by a wildcard containing object

class ArrayRep {
 public:

    static ArrayRep Af, Ax, Ar, Al, At, Ab, Am, Ae, As;
    static ArrayRep AF, AX, AR, AL, AT, AB, AM, AE, AS;
    
    static PermutationMap &pm;
    static ArrayRep origin;  
    u_int8_t data[48];

    
    // standard permuations
    ArrayRep();
    ArrayRep(const Permutation &p);
    ArrayRep(const ArrayRep &p);
    ArrayRep(const std::string s);
    void initFromPermutation(const Permutation &p);
    //
    // map showing the position of each face.   This is for cube definitions only
    // not valid as twist operators!
    // map of [position_label, face_label] 
    ArrayRep(std::vector<std::pair<int, int>> &label_positions);

    bool operator<(const ArrayRep &b) const;
    bool operator==(const ArrayRep &b) const;
    bool operator!=(const ArrayRep &b) const;
    ArrayRep operator*(const ArrayRep &b) const;
    ArrayRep operator-() const;

    std::string dump2DStr();
    std::string dump2CStr();

    void searchForConjigisor(int nconjigisors,
			     ArrayRep &conjugate,
			     std::vector<ArrayRep> &bases,
			     std::vector<char> &basenames,
			     std::map<ArrayRep, ElementDescriptor> &results);
    
    // generates groups from the existing ArrayRep, which may
    // have wildcards!  (0xff's)
    void getGeneratedGroup(std::vector<ArrayRep> &bases,
			   std::vector<char> &basenames,
			   std::map<ArrayRep, ElementDescriptor> &result);
    
    void searchForMe(std::vector<ArrayRep> &bases,
		     std::vector<char> &basenames,
		     std::map<ArrayRep, ElementDescriptor> &results);
};
