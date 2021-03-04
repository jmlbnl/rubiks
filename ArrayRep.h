#pragma once

#include <bits/stdc++.h>
#include <string.h>
#include "Permutation.h"
#include "PermutationMap.h"
    
// An array representation of a rubiks cube
// that allows for wildcards in the face positions
// the - will fail if called on a wildcard containing object
// the * operator will fail if multiplied by a wildcard containing object
class ArrayRepCount;
class ArrayRep;

// 0-3,4-8,44-47    face idx (0-12) in position [12]
// 48  ... 59       orientation [12]
// 60-63                      number of turns to solve. (< 15!)

// Must have wildcard capability!
//
// face_in_position[ccIdx] (1 ... 12) (4 bits, wildcard is 0xf)
// orientation[ccIdx]      (1 ... 12) (1 bit, wildcard is  0x0)
//

class SideStore {
 public:
    static PermutationMap &pm;
    
    u_int64_t data;

    SideStore() {};
    SideStore(u_int64_t data);
    SideStore(ArrayRep &x, u_int64_t cnt);
    
    void set(ArrayRep &x, u_int64_t cnt);
    ArrayRep build();
    int getCount();
    bool operator<(const SideStore &b) const;
    bool operator>(const SideStore &b) const;
    bool operator==(const SideStore &b) const;
    bool operator!=(const SideStore &b) const;
};

// No wildcard capability because it isn't needed!
//
// 0-2, 3-5, 6-9 ... 21-23  cubie idx (0-7)
// 24-25, 26-27  ... 38-39  cubie orientation
// 40-64                    number of turns to solve.
//
class CornerStore {
 public:
    static PermutationMap &pm;
    
    u_int64_t data;

    CornerStore() {};
    CornerStore(u_int64_t data);
    CornerStore(ArrayRep &x, u_int64_t cnt);
    
    void set(ArrayRep &x, u_int64_t cnt);
    ArrayRep build();
    int getCount();
    bool operator<(const CornerStore &b) const;
    bool operator>(const CornerStore &b) const;
    bool operator==(const CornerStore &b) const;
    bool operator!=(const CornerStore &b) const;
};

// wildcard has face_position_idx == 0xff
class ArrayRep {
 public:
    static ArrayRep Af, Ax, Ar, Al, At, Ab, Am, Ae, As;
    static ArrayRep AF, AX, AR, AL, AT, AB, AM, AE, AS;
    
    static PermutationMap &pm;
    static ArrayRep origin;  
    u_int8_t data[48];    // data[position_idx] = face_position_idx
    
    // standard permuations
    ArrayRep();
    ArrayRep(const u_int8_t *data);
    ArrayRep(const Permutation &p);
    ArrayRep(const ArrayRep &p);
    ArrayRep(const std::string s);
    void initFromPermutation(const Permutation &p);
    //
    // map showing the position of each face.   This is for cube definitions only
    // not valid as twist operators!
    // map of [position_label, face_label] 
    ArrayRep(std::vector<std::pair<int, int>> &label_positions);
    void maskLabelPositions(std::vector<int> &invalid_label_positions);
    
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

    static void getGeneratedGroupLevelCntsSym(u_int8_t level,
					      std::vector<ArrayRep> &bases,
					      std::map<ArrayRep, u_int8_t> &result,
					      std::vector<ArrayRep> &todo,
					      std::vector<ArrayRep> &todo_next,
					      std::vector<ArrayRep> &Svec,
					      bool savenext);
    
    static void getGeneratedGroupLevelCnts(u_int8_t level,
					   std::vector<ArrayRep> &bases,
					   std::map<ArrayRep, u_int8_t> &result,
					   std::vector<ArrayRep> &todo,
					   std::vector<ArrayRep> &todo_next);
    
    static void getGeneratedGroupCnts(std::vector<ArrayRep> &bases,
				      std::map<ArrayRep, u_int8_t> &result);
    
    // generates groups from the existing ArrayRep, which may
    // have wildcards!  (0xff's)
    void getGeneratedGroup(std::vector<ArrayRep> &bases,
			   std::vector<char> &basenames,
			   std::map<ArrayRep, ElementDescriptor> &result);
    
    void searchForMe(std::vector<ArrayRep> &bases,
		     std::vector<char> &basenames,
		     std::map<ArrayRep, ElementDescriptor> &results);

 
    Permutation getPermutation();

    // test validity...
    static bool isValid(ArrayRep x);
    static ArrayRep _random(std::default_random_engine &e);
    static ArrayRep random(std::default_random_engine &e);

    int getPositionOf(int face);
    int getFaceAt(int position);
    int getPositionOfIdx(int face_idx);
    int getFaceAtIdx(int position_idx) { return data[position_idx]; }
};

class ArrayRepCount : public ArrayRep {
 public:
    u_int8_t cnt;
    
    ArrayRepCount(const u_int8_t *data, u_int8_t cnt) : ArrayRep(data)
    {
	this->cnt = cnt;
    };

    int getCount(std::vector<ArrayRepCount> &arc);
};
