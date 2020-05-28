#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

// 5040 corner position permutations (Assume 1 corner fixed: n = 7! ).
// 11 million corner permutations (Assume 1 corner fixed:  n = 7! * 3^7 ).
// 10 million side permutations  (Assume corners fixed:    n = 8! * 2^8 ).

// This defines the real space position of each face
// the positions are the positions of the cube...
struct Face {
    int id, xpos, ypos;
};


struct ElementDescriptor {
    std::string name;
    int degeneracy;
};

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




// The slow permutation class
class Permutation {
 private:
    std::vector<std::vector<int> > cycles;
    std::string name;
    
 public:
    static Permutation ODr, ODf, ODt;
    
    // predefined full transformations
    static Permutation Pf, Px, Pr, Pl, Pt, Pb;
    static Permutation PF, PX, PR, PL, PT, PB;

    // predefined corner transformations
    static Permutation Cf, Cx, Cr, Cl, Ct, Cb;
    static Permutation CF, CX, CR, CL, CT, CB;

    // predefined unrotated corner transformations
    static Permutation UCf, UCx, UCr, UCl, UCt, UCb;
    static Permutation UCF, UCX, UCR, UCL, UCT, UCB;
    
    // Physics positions of each face...
    static Face FacesFull[54];
    static Face FacesCorners[24];
    static Face FacesUnrotatedCorners[8];
    
    Permutation(std::string cycle_string, std::string nm="");
    Permutation(std::vector<std::vector<int>> x, std::string nm="");

    // Note name is assembled backwards!
    Permutation operator* (Permutation B);
    Permutation operator- ();
    
    std::string getName() { return name; }

    void sortedorder(std::vector<std::vector<int>> &vec);
    std::vector<std::vector<int>> pairRepresentation(std::vector<std::vector<int>> base_cycles);
    std::vector<std::vector<int>> fullRepresentation(std::vector<std::vector<int>> pairRep);



    std::vector<int> spinToMin(std::vector<int> cyc);
    Permutation cycleIndexValues(Permutation idxcycle);
    // 1->3->2->5, 3->4->5->6, 1->4->2->6
    std::vector<std::vector<int>> cycleIndexValues(std::vector<std::vector<int>> cyc, std::vector<std::vector<int>> idxcyc);
    
    std::vector<std::vector<int>> decompose(std::vector<int> cyc);
    std::string cycleString(std::vector<std::vector<int>> _cyc);
 

    void dump() {
	printf("(%20s) (%d): ", name.c_str(), order());
	dump(cycles);
    }

    void dumpPair() {
	std::vector<std::vector<int>> cyc = pairRepresentation(cycles);
	dump(cyc);
    }

    std::string dump2Str() { return cycleString(cycles); }
    
    
    void dump(std::vector<std::vector<int>> _cyc) { printf("%s\n", cycleString(_cyc).c_str()); }

    std::vector<std::vector<int>> getCycles() {	return cycles; }
    void reduceName();
    static std::string reduceName(std::string n);

    
    int order();
    int nswaps();
  
    int countInvolvedCubes(int &corners, int &edges);

    int getSourcePosition(int x);
 private:
    std::vector<int> readSingleCycle(std::string cycle_string);
 
};

// TransTable acting on Permutation's
// Automatically excludes permutations that are equivalent under rotations...
class TransTable {
    std::map<std::string, std::string> transtab;
    std::vector<Permutation> face_permutations;
    std::vector<Permutation> face_renames;

 public:
    TransTable(); 

    std::map<std::string, std::string> &getMap() { return transtab; }
    bool add(Permutation &p);
    int nFacePermutations() { return face_permutations.size(); }
    Permutation getFacePermutation(int idx) { return face_permutations[idx]; }
    Permutation getFace_rename(int idx) { return face_renames[idx]; }
    Permutation applyFacePermutation(int idx, Permutation &P);
    void writeTransTable(char *filename, std::map<std::string, std::string> &transtab); 
    void readTransTable(char *filename, std::vector<Permutation> &perms);
};



template <int N> class FastPermutation {
 public:
    u_int8_t data[N];

    ~FastPermutation<N>() {};
    
    FastPermutation<N>() {};      // returns an unusable permutation!  must be set!
    FastPermutation<N>(const FastPermutation &p);
    FastPermutation<N>(Permutation &p, PermutationMap &pm);
    FastPermutation<N>(std::string s, PermutationMap &pm);

    FastPermutation<N>(std::string twistnames,
		       std::vector<FastPermutation<N>> &bases,
		       std::vector<char> &basenames) {
	FastPermutation<N> x = FastPermutation<N>::origin();
	
	for(int i = 0;i<twistnames.size();i++) {
	    int twist=-1;
	    for(int j=0;j<basenames.size();j++) {
		if(basenames[j] == twistnames[i]) {
		    twist = j;
		}
	    }
	    assert(twist >= 0);
	    
	    x = bases[twist] * x;
	    
	}
	
	*this = x;
    }
    
    
    static FastPermutation<N> origin();

    FastPermutation<N> operator* (const FastPermutation<N> &b);
    void multInto(FastPermutation<N> &b, FastPermutation<N> &r);
    FastPermutation<N> operator- ();

    bool isOrigin() const;
    bool areCornersOrigin(const PermutationMap &pm) const;
    bool areSidesOrigin(const PermutationMap &pm) const;
    
    int calculateOrder(const PermutationMap &pm) const;
    int calculateCornerOrder(const PermutationMap &pm) const;
    int calculateSideOrder(const PermutationMap &pm) const;
    int nSwaps() const;
    int minSwaps(const std::vector<FastPermutation<N>> &symetries, int &whichsym) const;
    
    bool operator< (const FastPermutation<N> &b) const;
    bool operator== (const FastPermutation<N> &b) const;
    bool operator!= (const FastPermutation<N> &b) const;
    std::string dump2StrRaw();
    std::string dump2Str(const PermutationMap &pm) const;
    void dumpRaw() { printf("%s\n", dump2StrRaw().c_str()); }
    void dump(PermutationMap &pm) { printf("%s\n", dump2Str(pm).c_str()); }

    std::vector<std::vector<int>> getCycles(const PermutationMap &pm);
    std::vector<std::vector<int>> getSwaps(const PermutationMap &pm);
    
    static void getSymmetryGroup(std::vector<FastPermutation<N>> &bases,
				 std::vector<std::string> &names,
				 std::map<FastPermutation<N>, ElementDescriptor> &symgrp);


    static std::string getNameForCube(FastPermutation<N> &cube,
			       std::vector<FastPermutation<N>> &bases,
			       std::vector<char> &basenames);
    
    
    static std::vector<std::string> getAllNamesForCube(FastPermutation<N> &cube,
						std::vector<FastPermutation<N>> &bases,
						std::vector<char> &basenames);
    
    static void getSymmetryReplacements(std::vector<FastPermutation<N>> &bases,
				 std::vector<char> &basenames,
				 std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
				 std::vector<std::vector<char>> &replacements);

    static void getGeneratedGroup(std::vector<FastPermutation<N>> &bases,
				  std::vector<char> &basenames,
				  std::map<FastPermutation<N>, ElementDescriptor> &results);

    static void getGeneratedGroup(std::vector<FastPermutation<N>> &bases,
				  std::vector<char> &basenames,
				  std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
				  std::map<FastPermutation<N>, ElementDescriptor> &results);
       
    static void getGeneratedGroup(std::vector<FastPermutation<N>> &bases,
				  std::vector<char> &basenames,
				  std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
				  std::map<FastPermutation<N>, ElementDescriptor> &results,
				  std::vector<std::string> &origins);
    
 
    
    static std::pair<FastPermutation<N>, ElementDescriptor> findConjugateFromList(std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
				       std::map<FastPermutation<N>, ElementDescriptor> &conjugates,
				       FastPermutation<N> &cube);
    /*
    static int getDistanceFromConjugates(std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
					 std::map<FastPermutation<N>, ElementDescriptor> &conjugates,
					 FastPermutation<N> x, FastPermutation<N> y) {
	FastPermutation<N> z = (-x) * y;
	auto p = FastPermutation<N>::findConjugateFromList(symgrp, conjugates, z);

	return (int)p.second.name.size();
    }
    */
    
    static int getDistanceFromSearch(std::vector<FastPermutation<N>> &bases,
				     std::vector<char> &basenames,
				     FastPermutation<N> x, FastPermutation<N> y) {
	FastPermutation<N> z = (-x) * y;

	std::string nm = getNameForCube(z, bases, basenames);
	
	//printf("%s %lu\n", nm.c_str(), nm.size());
	return (int)nm.size();
    }
    
};


class FastName {
 public:
    char name[50];
    u_int8_t len;

    ~FastName() {};
    FastName() { len=0; name[0]='\0'; };
    FastName(const char *s);
    FastName(const FastName &fn);
    FastName(FastName &fn, char nxt);
    FastName operator+ (FastName &b);
    
    // Don't do anything to reduce the length of the string....
    //
    // don't add xX or Xx
    // don't add x to xx
    // don't add (l or L) following (r or R)   (l first!)
    //           (t or T) following (b or B)   (t first)
    //           (f or F) following (x or X)   (f first)
    //
    // don't add X to X (all double rotations via xx)
    //
    bool isAddValid(char nxt);
    void add(char nxt);
};

template<int N> class CubeCounter {
 public:
    int id2CornerCube[N];   // Maps every id to -1 (no corner) or 0...7
    int id2SideCube[N];     // Maps every id to -1 (no side) or 0...7
    int id2FixedCube[N];
    
    CubeCounter<N>(PermutationMap &pm) {
	std::vector<int> cornerIds;
	std::vector<int> sideIds;
	
	for(int i=0;i<N;i++) {
	    id2CornerCube[i] = -1;
	    id2SideCube[i] = -1;
	    id2FixedCube[i] = -1;
	}
	
	for(int i=0;i<N;i++) {
	    int label = pm.idx2label.at(i);
	    int digit1 = label/100;
	    int digit2 = (label/10) % 10;
	    int digit3 = label % 10;

	    std::vector<int> digits = { digit1, digit2, digit3 };
	    std::sort(digits.begin(), digits.end());
	    int slabel = digits[0] * 100 + digits[1] * 10 + digits[2];

	    //printf("constructing:  slabel=%d\n", slabel);
	    
	    if(slabel > 100) {
		std::vector<int>::iterator it = std::find(cornerIds.begin(), cornerIds.end(), slabel);
		if(it == cornerIds.end()) {
		    cornerIds.push_back(slabel);
		    it = std::find(cornerIds.begin(), cornerIds.end(), slabel);
		}
		int idx = std::distance(cornerIds.begin(), it);
		id2CornerCube[i] = idx;
	    }
	    else if(slabel > 10) {
		std::vector<int>::iterator it = std::find(sideIds.begin(), sideIds.end(), slabel);
		if(it == sideIds.end()) {
		    sideIds.push_back(slabel);
		    it = std::find(sideIds.begin(), sideIds.end(), slabel);
		}
		int idx = std::distance(sideIds.begin(), it);
		id2SideCube[i] = idx;
	    }
	}
    }

    
    void setFixedCubes(std::vector<std::pair<int,int>> fixedFaceTransform, const PermutationMap &pm) {
	for(int i=0;i<N;i++) {
	    id2FixedCube[i] = -1;
	}
	
	for(int i=0; i<fixedFaceTransform.size(); i++) {
	    int slabel_from = fixedFaceTransform[i].first;
	    int slabel_to = fixedFaceTransform[i].second;

	    printf("ccc %d %d\n", slabel_from, slabel_to);
	    
	    int id_from = pm.label2idx.at(slabel_from);
	    int id_to = pm.label2idx.at(slabel_to);
	    id2FixedCube[id_from] = id_to;
	}
    }
    
    void dump(PermutationMap &pm) {
	for(int i=0;i<N;i++) {
	    printf("[%d] label=%d cornerIdx=%d sideIdx=%d\n",
		   i, pm.idx2label.at(i), id2CornerCube[i], id2SideCube[i]);
	}
    }

    bool checkFixedCubes(FastPermutation<N> &p) {
	for(int i=0;i<N;i++) {
	    if(id2FixedCube[i] != -1) {
		if(p.data[i] != id2FixedCube[i]) return false;
	    }
	}
	return true;
    }
    
    int count(int &cornerCubes, int &sideCubes, FastPermutation<N> &p) {
	cornerCubes = sideCubes = 0;

	u_int8_t sides[12];
	u_int8_t corners[8];
	
	memset(sides, 0, sizeof(sides));
	memset(corners, 0, sizeof(corners));
	
	for(int i=0;i<N;i++) {
	    if(p.data[i] != i) {   // Cube is involved!
		int sideIdx = id2SideCube[i];
		int cornerIdx = id2CornerCube[i];
		if(sideIdx >= 0) {
		    sides[sideIdx]++;
		}
		if(cornerIdx >= 0) {
		    corners[cornerIdx]++;
		}
	    }
	}

	for(int i=0;i<12;i++) {
	    if(sides[i] > 0) {
		sideCubes++;
	    }
	}
	for(int i=0;i<8;i++) {
	    if(corners[i] > 0) {
		cornerCubes++;
	    }
	}

	return sideCubes + cornerCubes;
    }
    
};

class fglb {
 public:
    static PermutationMap CubeMapFull;
    static PermutationMap CubeMapCorners;
    static PermutationMap CubeMapUnrotatedCorners;
    
    // predefined full transformations
    static FastPermutation<54> Pf, Px, Pr, Pl, Pt, Pb;
    static FastPermutation<54> PF, PX, PR, PL, PT, PB;

    // predefined corner transformations
    static FastPermutation<24> Cf, Cx, Cr, Cl, Ct, Cb;
    static FastPermutation<24> CF, CX, CR, CL, CT, CB;

    // predefined unrotated corner transformations
    static FastPermutation<8> UCf, UCx, UCr, UCl, UCt, UCb;
    static FastPermutation<8> UCF, UCX, UCR, UCL, UCT, UCB;
};

bool incrementIdx(int *idx, int depth, int nbases);






