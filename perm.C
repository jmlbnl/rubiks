#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include "perm.h"

Permutation Permutation::ODr("(1 3 2 5)","r");
Permutation Permutation::ODf("(3 4 5 6)","f");
Permutation Permutation::ODt("(1 4 2 6)","t");

// Define Static transformations!
Permutation Permutation::Cf("(134 145 156 136)(314 415 516 613)(316 413 514 615)","f");
Permutation Permutation::Cx("(234 236 256 245)(324 623 526 425)(326 625 524 423)","x");
Permutation Permutation::Cr("(413 423 425 415)(134 324 245 514)(145 314 234 524)","r");
Permutation Permutation::Cl("(623 613 615 625)(136 516 256 326)(156 526 236 316)","l");
Permutation Permutation::Ct("(314 316 326 324)(134 613 236 423)(136 623 234 413)", "t");
Permutation Permutation::Cb("(516 514 524 526)(156 415 245 625)(145 425 256 615)", "b");

Permutation Permutation::CF = -Cf;
Permutation Permutation::CX = -Cx;
Permutation Permutation::CR = -Cr;
Permutation Permutation::CL = -Cl;
Permutation Permutation::CT = -Ct;
Permutation Permutation::CB = -Cb;

//Permutation Permutation::UCf("(1 2 4 3)","f");
//Permutation Permutation::UCx("(5 6 8 7)","x");
//Permutation Permutation::UCr("(2 5 7 4)","r");
//Permutation Permutation::UCl("(1 3 8 6)","l");
//Permutation Permutation::UCt("(1 6 5 2)", "t");
//Permutation Permutation::UCb("(3 4 7 8)", "b");

Permutation Permutation::UCf("(136 134 145 156)","f");
Permutation Permutation::UCx("(234 236 256 245)","x");
Permutation Permutation::UCr("(134 234 245 145)","r");
Permutation Permutation::UCl("(236 136 156 256)","l");
Permutation Permutation::UCt("(236 234 134 136)","t");
Permutation Permutation::UCb("(156 145 245 256)","b");

Permutation Permutation::UCF = -UCf;
Permutation Permutation::UCX = -UCx;
Permutation Permutation::UCR = -UCr;
Permutation Permutation::UCL = -UCl;
Permutation Permutation::UCT = -UCt;
Permutation Permutation::UCB = -UCb;

Permutation Permutation::Pf("(13 14 15 16)(134 145 156 136)(31 41 51 61)(314 415 516 613)(316 413 514 615)","f");
Permutation Permutation::Px("(23 26 25 24)(234 236 256 245)(32 62 52 42)(324 623 526 425)(326 625 524 423)","x");
Permutation Permutation::Pr("(41 43 42 45)(413 423 425 415)(14 34 24 54)(134 324 245 514)(145 314 234 524)","r");
Permutation Permutation::Pl("(61 65 62 63)(615 625 623 613)(16 56 26 36)(136 516 256 326)(156 526 236 316)","l");
Permutation Permutation::Pt("(31 36 32 34)(314 316 326 324)(13 63 23 43)(134 613 236 423)(136 623 234 413)", "t");
Permutation Permutation::Pb("(51 54 52 56)(514 524 526 516)(15 45 25 65)(145 425 256 615)(156 415 245 625)", "b");

Permutation Permutation::PF = -Pf;
Permutation Permutation::PX = -Px;
Permutation Permutation::PR = -Pr;
Permutation Permutation::PL = -Pl;
Permutation Permutation::PT = -Pt;
Permutation Permutation::PB = -Pb;

Face Permutation::FacesFull[54] = {
    { 156, 0,0 }, { 15,  1,0 }, { 145, 2,0 }, { 16,  0,1 }, { 1,   1,1 }, { 14,  2,1 }, { 136, 0,2 }, { 13,  1,2 }, { 134, 2,2 },
    { 256, 2,0 }, { 25,  1,0 }, { 245, 0,0 }, { 26,  2,1 }, { 2,   1,1 }, { 24,  0,1 }, { 236, 2,2 }, { 23,  1,2 }, { 234, 0,2 },
    { 326, 0,0 }, { 36,  1,0 }, { 316, 2,0 }, { 32,  0,1 }, { 3,   1,1 }, { 31,  2,1 }, { 324, 0,2 }, { 34,  1,2 }, { 314, 2,2 },
    { 415, 0,0 }, { 45,  1,0 }, { 425, 2,0 }, { 41,  0,1 }, { 4,   1,1 }, { 42,  2,1 }, { 413, 0,2 }, { 43,  1,2 }, { 423, 2,2 },
    { 516, 0,0 }, { 51,  0,1 }, { 514, 0,2 }, { 56,  1,0 }, { 5,   1,1 }, { 54,  1,2 }, { 526, 2,0 }, { 52,  2,1 }, { 524, 2,2 },
    { 615, 0,0 }, { 65,  0,1 }, { 625, 0,2 }, { 61,  1,0 }, { 6,   1,1 }, { 62,  1,2 }, { 613, 2,0 }, { 63,  2,1 }, { 623, 2,2 } 
};

Face Permutation::FacesCorners[24] = {
    { 156, 0,0 }, { 145, 2,0 }, { 136, 0,2 }, { 134, 2,2 },
    { 256, 2,0 }, { 245, 0,0 }, { 236, 2,2 }, { 234, 0,2 },
    { 326, 0,0 }, { 316, 2,0 }, { 324, 0,2 }, { 314, 2,2 },
    { 415, 0,0 }, { 425, 2,0 }, { 413, 0,2 }, { 423, 2,2 },
    { 516, 0,0 }, { 514, 0,2 }, { 526, 2,0 }, { 524, 2,2 },
    { 615, 0,0 }, { 625, 0,2 }, { 613, 2,0 }, { 623, 2,2 } 
};

Face Permutation::FacesUnrotatedCorners[8] = {
    { 136, 0,0 }, { 134, 2,0 }, { 156, 0,2 }, { 145, 2,2 },
    { 234, 2,0 }, { 236, 0,0 }, { 245, 2,2 }, { 256, 0,2 }
};

PermutationMap::PermutationMap(int n, Face *array) {
    std::vector<Face> faces;
    for(int i=0;i<n;i++) {
	faces.push_back(array[i]);
    }
    // std::sort(faces.begin(), faces.end(), [](Face &a, Face &b) { return (a.id < b.id); });
    
    for(int i=0;i<n;i++) {
	idx2label.insert({ i, faces[i].id });
	label2idx.insert({faces[i].id, i });
    }

    // build corner indeces
    ncorners=0;
    nsides=0;
    for(int i=0;i<n;i++) {
	int id = idx2label.at(i);
	if(id > 100) {
	    cornerIdx[ncorners] = i;
	    ncorners++;
	}
	else if (id > 10) {
	    sideIdx[nsides] = i;
	    nsides++;
	}
    }

    //printf("nsides = %d\n", nsides);
    //printf("ncorners = %d\n", ncorners);
	    
}

void PermutationMap::dump() {
    printf("idx2label.size() = %lu     label2idx.size() = %lu\n", idx2label.size(), label2idx.size());
    for(int i=0;i<idx2label.size();i++) {
	printf("idx2label[%d] = %d       label2idx[%d] = %d\n", i, idx2label.at(i), idx2label.at(i), label2idx.at(idx2label.at(i)));
    }
}



PermutationMap fglb::CubeMapFull(54, Permutation::FacesFull);
PermutationMap fglb::CubeMapCorners(24, Permutation::FacesCorners);
PermutationMap fglb::CubeMapUnrotatedCorners(8, Permutation::FacesUnrotatedCorners);

FastPermutation<54> fglb::Pf(Permutation::Pf, fglb::CubeMapFull);
FastPermutation<54> fglb::Px(Permutation::Px, fglb::CubeMapFull);
FastPermutation<54> fglb::Pr(Permutation::Pr, fglb::CubeMapFull);
FastPermutation<54> fglb::Pl(Permutation::Pl, fglb::CubeMapFull);
FastPermutation<54> fglb::Pt(Permutation::Pt, fglb::CubeMapFull);
FastPermutation<54> fglb::Pb(Permutation::Pb, fglb::CubeMapFull);
FastPermutation<54> fglb::PF(Permutation::PF, fglb::CubeMapFull);
FastPermutation<54> fglb::PX(Permutation::PX, fglb::CubeMapFull);
FastPermutation<54> fglb::PR(Permutation::PR, fglb::CubeMapFull);
FastPermutation<54> fglb::PL(Permutation::PL, fglb::CubeMapFull);
FastPermutation<54> fglb::PT(Permutation::PT, fglb::CubeMapFull);
FastPermutation<54> fglb::PB(Permutation::PB, fglb::CubeMapFull);

FastPermutation<24> fglb::Cf(Permutation::Cf, fglb::CubeMapCorners);
FastPermutation<24> fglb::Cx(Permutation::Cx, fglb::CubeMapCorners);
FastPermutation<24> fglb::Cr(Permutation::Cr, fglb::CubeMapCorners);
FastPermutation<24> fglb::Cl(Permutation::Cl, fglb::CubeMapCorners);
FastPermutation<24> fglb::Ct(Permutation::Ct, fglb::CubeMapCorners);
FastPermutation<24> fglb::Cb(Permutation::Cb, fglb::CubeMapCorners);
FastPermutation<24> fglb::CF(Permutation::CF, fglb::CubeMapCorners);
FastPermutation<24> fglb::CX(Permutation::CX, fglb::CubeMapCorners);
FastPermutation<24> fglb::CR(Permutation::CR, fglb::CubeMapCorners);
FastPermutation<24> fglb::CL(Permutation::CL, fglb::CubeMapCorners);
FastPermutation<24> fglb::CT(Permutation::CT, fglb::CubeMapCorners);
FastPermutation<24> fglb::CB(Permutation::CB, fglb::CubeMapCorners);

FastPermutation<8> fglb::UCf(Permutation::UCf, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCx(Permutation::UCx, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCr(Permutation::UCr, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCl(Permutation::UCl, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCt(Permutation::UCt, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCb(Permutation::UCb, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCF(Permutation::UCF, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCX(Permutation::UCX, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCR(Permutation::UCR, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCL(Permutation::UCL, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCT(Permutation::UCT, fglb::CubeMapUnrotatedCorners);
FastPermutation<8> fglb::UCB(Permutation::UCB, fglb::CubeMapUnrotatedCorners);


template<int N> FastPermutation<N> FastPermutation<N>::origin() {
    FastPermutation<N> res;
    for(int i=0;i<N;i++) {
	res.data[i] = i;
    }
    return res;
}

template<int N> FastPermutation<N>::FastPermutation(const FastPermutation &p) {
    for(int i=0;i<N;i++) {
	data[i] = p.data[i];
    }
}

template<int N> FastPermutation<N>::FastPermutation(Permutation &p, PermutationMap &pm) {
    std::string s = p.getName();
    
    //printf("Constructing %s\n", s.c_str());
    for(int i=0;i<N;i++) data[i] = i;

    std::vector<std::vector<int>> cycles = p.getCycles();
    for(std::vector<int> cyc : cycles) {
	for(int i=0; i<cyc.size(); i++) {
	    
	    int j = (i+1)%cyc.size();
	    int l1 = cyc[i];
	    int l2 = cyc[j];

	    int idx2 = pm.label2idx.at(l2);
	    int idx1 = pm.label2idx.at(l1);

	   
	    data[idx1] = idx2;
	}
    }
}

template<int N> FastPermutation<N>::FastPermutation(std::string str, PermutationMap &pm) {
    Permutation p(str);
    //std::string s = p.getName();
    
    //printf("Constructing %s\n", s.c_str());
    for(int i=0;i<N;i++) data[i] = i;

    std::vector<std::vector<int>> cycles = p.getCycles();
    for(std::vector<int> cyc : cycles) {
	for(int i=0; i<cyc.size(); i++) {
	    
	    int j = (i+1)%cyc.size();
	    int l1 = cyc[i];
	    int l2 = cyc[j];

	    int idx2 = pm.label2idx.at(l2);
	    int idx1 = pm.label2idx.at(l1);

	   
	    data[idx1] = idx2;
	}
    }
}

template<int N> std::vector<std::vector<int>> FastPermutation<N>::getCycles(const PermutationMap &pm) {
    std::vector<std::vector<int>> cycles;

    u_int8_t used[N];
    memset(used, 0, sizeof(used));
    
    for(int i=0;i<N;i++) {
	if(data[i] == i) continue;
	if(used[i]) continue;

	std::vector<int> cycle;
	cycle.push_back(pm.idx2label.at(i));
	int j = data[i];
	while(j != i) {
	    used[j] = 1;
	    cycle.push_back(pm.idx2label.at(j));
	    j = data[j];
	}

	cycles.push_back(cycle);
    }
    return cycles;
}

template<int N> std::vector<std::vector<int>> FastPermutation<N>::getSwaps(const PermutationMap &pm) {
    std::vector<std::vector<int>> cycles = getCycles(pm);

    std::vector<std::vector<int>> swaps;

    for(auto v : cycles) {
	for(int i=v.size()-1;i>0;i--) {
	    std::vector<int> swap;
	    swap.push_back(v[0]);
	    swap.push_back(v[i]);
	    swaps.push_back(swap);
	}
    }
    return swaps;
}


template<int N> FastPermutation<N> FastPermutation<N>::operator* (const FastPermutation<N> &b) {
    FastPermutation r;
    for(int i=0;i<N;i++) {
	//r.data[data[b.data[i]]] = i;
	r.data[i] = data[b.data[i]];
    }
    return r;
}

template<int N> FastPermutation<N> FastPermutation<N>::operator-() {
    FastPermutation r;
    for(int i=0;i<N;i++) {
	r.data[data[i]] = i;
    }
    return r;
}
	    
// May be faster???
template<int N> void FastPermutation<N>::multInto(FastPermutation<N> &b, FastPermutation<N> &r)
{
    for(int i=0;i<N;i++) {
	r.data[data[b.data[i]]] = i;
    }
}

template<int N> bool FastPermutation<N>::areCornersOrigin(const PermutationMap &pm) const {
    for(int i=0;i<pm.ncorners;i++) {
	//printf("areCornersOrigin %s: ", dump2Str(pm).c_str());
	//printf("pm.ncorners=%d cornerIdx[%d]=%d   data[ci]=%d\n",
	//       pm.ncorners, i, pm.cornerIdx[i], data[pm.cornerIdx[i]]);
	       
	if(data[pm.cornerIdx[i]] != pm.cornerIdx[i]) return false;
    }
    return true;
}

template<int N> bool FastPermutation<N>::areSidesOrigin(const PermutationMap &pm) const {
    for(int i=0;i<pm.nsides;i++) {
	if(data[pm.sideIdx[i]] != pm.sideIdx[i]) return false;
    }
    return true;
}
      
template<int N> bool FastPermutation<N>::isOrigin() const {
    for(int i=0;i<N;i++) {
	if(data[i] != i) return false;
    }
    return true;
}

template<int N> int FastPermutation<N>::calculateSideOrder(const PermutationMap &pm) const {
    int order = 1;
    FastPermutation<N> x = *this;
    FastPermutation<N> y = *this;
    
    while(!x.areSidesOrigin(pm)) {
	x = y * x;
	order++;
    }

    return order;  
}

template<int N> int FastPermutation<N>::calculateCornerOrder(const PermutationMap &pm) const {
    int order = 1;
    FastPermutation<N> x = *this;
    FastPermutation<N> y = *this;
    
    while(!x.areCornersOrigin(pm)) {
	x = y * x;
	order++;
    }

    return order;
}

template<int N> int FastPermutation<N>::calculateOrder(const PermutationMap &pm) const {
    int order = 1;
    FastPermutation<N> x = *this;
    FastPermutation<N> y = *this;

    //printf("%s :  %d %d %d\n", x.dump2Str(pm).c_str(), x.data[0], x.data[1], x.data[2]);
    
    while(!x.isOrigin()) {
	x = y * x;

	order++;
    }

    return order;
}

template<int N> int FastPermutation<N>::nSwaps() const {  
    u_int8_t used[N];
    memset(used, 0, sizeof(used));

    int swaps = 0;
    
    for(int i=0;i<N;i++) {
	if(data[i] == i) continue;
	if(used[i]) continue;
	
	int j = data[i];
	while(j != i) {
	    used[j] = 1;
	    swaps++;
	    j = data[j];
	}
    }
    
    return swaps;
}

template<int N> int FastPermutation<N>::minSwaps(const std::vector<FastPermutation<N>> &symetries, int &whichsym) const {
    int minswaps = nSwaps();
    whichsym = -1;
    
    for(int i=0;i<symetries.size();i++) {
	auto s = symetries[i];
	FastPermutation<N> x = s * (*this);
	int nswaps = x.nSwaps();
	if(nswaps <= minswaps) {
	    minswaps = nswaps;
	    whichsym = i;
	}
    }
    return minswaps;
}

template<int N> bool FastPermutation<N>::operator< (const FastPermutation<N> &b) const {
    for(int i=0;i<N;i++) {
	if(data[i] < b.data[i]) return true;
	if(data[i] > b.data[i]) return false;
    }
    return false;
}


template<int N> bool FastPermutation<N>::operator== (const FastPermutation<N> &b) const {
    if(memcmp(data, b.data, sizeof(data)) == 0) return true;
    return false;
}

template<int N> bool FastPermutation<N>::operator!= (const FastPermutation<N> &b) const {
    if(memcmp(data, b.data, sizeof(data)) != 0) return true;
    return false;
}
	
template<int N> std::string FastPermutation<N>::dump2StrRaw() {
    std::string res = "{ ";

    for(int i=0;i<N;i++) {
	if(data[i] != i) {
	    if(i > 0) res += " ";
	    res += std::to_string(i) + "->" + std::to_string(data[i]);
	}
    }

    res += " }";
    return res;
}

template<int N> std::string FastPermutation<N>::dump2Str(const PermutationMap &pm) const {
    std::string res;
    
    u_int8_t used[N];
    memset(used, 0, sizeof(used));
    for(int i=0;i<N;i++) {
	if(data[i] == i) continue;
	if(used[i]) continue;

	res += "(" + std::to_string(pm.idx2label.at(i));
	//res += "(" + std::to_string(i);
	int j = data[i];
	while(j != i) {
	    //printf("i=%d j=%d\n",i,j);
	    used[j] = 1;
	    res += " " + std::to_string(pm.idx2label.at(j));
	    //res += " " + std::to_string(j);
	    j = data[j];
	}
	res += ")";
    }
    if(res.size() == 0) res += "()";
    return res;        // automatically sorted (smallest x x x)(nextsmallest x x x)
}

template<int N> void FastPermutation<N>::getSymmetryGroup(std::vector<FastPermutation<N>> &bases, std::vector<std::string> &names, std::map<FastPermutation<N>, ElementDescriptor> &symgrp)
{


    FastPermutation<N> origin = FastPermutation<N>::origin();
    
    //std::vector<std::string> names = { "tB", "lR", "HH" };
 
    symgrp.insert({origin, {"", 1}});
    
    std::vector<std::pair<FastPermutation<N>, ElementDescriptor>> todo;
    todo.push_back({ origin, { "", 1 }});
     
    for(;;) {
	fflush(stdout);

	std::vector<std::pair<FastPermutation<N>, ElementDescriptor>> todo_now = todo;
	todo.clear();
	
	for(auto p : todo_now) {
	    for(int i=0;i<bases.size();i++) {
		FastPermutation<N> np = bases[i] * p.first;
		ElementDescriptor nd;
		nd.name = p.second.name + names[i];

		
		// Do the insert	
		auto res = symgrp.insert({ np, nd });
		    
		if(res.second) {
		    todo.push_back({ np, nd });

		    printf("%s\n", nd.name.c_str());
		}
	    }
	}     
	if(todo.size() == 0) break;
    }
}


template<int N> std::string FastPermutation<N>::getNameForCube(FastPermutation<N> &cube,
							       std::vector<FastPermutation<N>> &bases,
							       std::vector<char> &basenames)
{
    int idx[20];
    memset(idx, 0, sizeof(idx));

    if(cube == FastPermutation<N>::origin()) return "";
    
    for(int depth=1;depth<20;depth++) {
	memset(idx, 0, sizeof(idx));
	do {
	    FastPermutation<N> tmp = bases[idx[0]];
	    std::string name;
	    name += basenames[idx[0]];
	    
	    for(int i=1;i<depth;i++) {
		tmp = bases[idx[i]] * tmp;
		name += basenames[idx[i]];
	    }

	    //printf("%d %s\n", depth, name.c_str());
	    
	    if(tmp == cube) {
		//printf("Depth: %d %d %s", depth, bases.size(), name.c_str());
		return name;
	    }
	} while(incrementIdx(idx, depth, bases.size()));
    }
    return "NONE";
}

template<int N> // all names at min level...
std::vector<std::string> FastPermutation<N>::getAllNamesForCube(FastPermutation<N> &cube,
								std::vector<FastPermutation<N>> &bases,
								std::vector<char> &basenames)
{
    std::vector<std::string> names;
    int idx[20];
    memset(idx, 0, sizeof(idx));

    if(cube == FastPermutation<N>::origin()) return names;
    
    for(int depth=1;depth<20;depth++) {
	if(names.size() > 0) {
	    return names;
	}
	memset(idx, 0, sizeof(idx));
	do {
	    FastPermutation<N> tmp = bases[idx[0]];
	    std::string name;
	    name += basenames[idx[0]];
	    
	    for(int i=1;i<depth;i++) {
		tmp = bases[idx[i]] * tmp;
		name += basenames[idx[i]];
	    }

	    //printf("%d %s\n", depth, name.c_str());
	    
	    if(tmp == cube) {
		//printf("Depth: %d %d %s", depth, bases.size(), name.c_str());
		names.push_back(name);
	    }
	} while(incrementIdx(idx, depth, bases.size()));
    }
    return names;;
}

template<int N> std::pair<FastPermutation<N>, ElementDescriptor>
FastPermutation<N>::findConjugateFromList(std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
					  std::map<FastPermutation<N>, ElementDescriptor> &conjugates,
					  FastPermutation<N> &y) {
    for(auto cp : conjugates) {
	FastPermutation<N> x = cp.first;
	for(auto sp : symgrp) {
	    FastPermutation<N> S = sp.first;

	    if(x == (-S) * y * S) {
		return cp;
	    }
	   
	}
    }

    std::pair<FastPermutation<N>, ElementDescriptor> z;
    return z;
}

// get generated group
//
// bases            :The generators
// basenames        :The names of the generators
// symgrp           :The symmetry group, if size()>0 then supress results conjugate through symgrp
// result           :The result
template<int N> void FastPermutation<N>::getGeneratedGroup(std::vector<FastPermutation<N>> &bases,
							   std::vector<char> &basenames,
							   std::map<FastPermutation<N>, ElementDescriptor> &result) {
    std::map<FastPermutation<N>, ElementDescriptor> symgrp;
    getGeneratedGroup(bases, basenames, symgrp, result);
}

// get generated group
//
// bases            :The generators
// basenames        :The names of the generators
// symgrp           :The symmetry group, if size()>0 then supress results conjugate through symgrp
// result           :The result
template<int N> void FastPermutation<N>::getGeneratedGroup(std::vector<FastPermutation<N>> &bases,
							   std::vector<char> &basenames,
							   std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
							   std::map<FastPermutation<N>, ElementDescriptor> &result) {
    std::vector<std::string> origins;
    getGeneratedGroup(bases, basenames, symgrp, result, origins);
}


// get generated group
//
// bases            :The generators
// basenames,       :Names for the bases
// symgrp           :symetry group, if size()>0 then supress results conjugate through symgrp
// conjugates       :the results
// origins          :elements conjugate to the origin

template<int N> void FastPermutation<N>::getGeneratedGroup(std::vector<FastPermutation<N>> &bases,
						       std::vector<char> &basenames,
						       std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
						       std::map<FastPermutation<N>, ElementDescriptor> &result,
						       std::vector<std::string> &origins) {

    FastPermutation<N>  origin = FastPermutation<N>::origin();
    
    std::vector<FastPermutation<N>> symvec;
    for(auto p : symgrp) {
	symvec.push_back(p.first);
    }
    
    bool testSymmetry = true;
    if(symgrp.size() == 0) {
	testSymmetry = false;
    }
    
    result.insert({FastPermutation<N>::origin(), { "", 1 }});
    std::vector<std::pair<FastPermutation<N>, ElementDescriptor>> todo;
    todo.push_back({ FastPermutation<N>::origin(), { "", 1}});
    int level = 0;
    
    for(;;) {
	level++;
	
	std::vector<std::pair<FastPermutation<N>, ElementDescriptor>> todo_now = todo;
	todo.clear();

	for(auto p : todo_now) {
	    for(int i=0;i<bases.size();i++) {
		FastPermutation<N> np = bases[i] * p.first;

		std::string nn;
		if(basenames.size() > 0) {
		    nn = p.second.name + basenames[i];
		}

		//printf("%s\n", nn.c_str());
		if(np == origin) {
		    //printf("origin: %s\n", nn.c_str());
		    origins.push_back(nn);
		}
		
		// Do the insert
		bool existss = false;
		std::vector<FastPermutation<N>> count_sym;
		
		if(testSymmetry) {		    
		    for(auto sym : symgrp) {
			FastPermutation<N> ss = sym.first;
			FastPermutation<N> check = (-ss) * np * ss;
			auto exists = result.find(check);
			if(exists != result.end()) {
			    //printf(" %s is conjugate to %s \n", np.dump2Str(pm).c_str(), check.dump2Str(pm).c_str());
			    existss = true;
			}

			auto it = std::find(count_sym.begin(), count_sym.end(), check);
			if(it == count_sym.end()) {
			    count_sym.push_back(check);
			}
		    }

		}
		
		if(!existss) {
		 
		    int deg = count_sym.size();
		    if(deg == 0) deg = 1;
		    
		    auto res = result.insert({ np, { nn, deg} });
		    
		    if(res.second) {
			todo.push_back({ np, { nn, 1 }});
			
			int whichsym;
			int minswaps = np.minSwaps(symvec, whichsym);
			
			//printf("CUBE: %50s %10s %d %d :%d\n", np.dump2Str(fglb::CubeMapUnrotatedCorners).c_str(), nn.c_str(), level, np.nSwaps(), minswaps);
			
		    }
		}
	    }
	}     
	if(todo.size() == 0) break;
    }

    
}


// basenames[i] --> replacements[i] to reach -symgrp[i] * x symgrp[i]
//
template<int N> void FastPermutation<N>::getSymmetryReplacements(std::vector<FastPermutation<N>> &bases,
								 std::vector<char> &basenames,
								 std::map<FastPermutation<N>, ElementDescriptor> &symgrp,
								 std::vector<std::vector<char>> &replacements)
{
    printf("%lu symmetries   A=tB  B=lR   C=centerFlip\n", symgrp.size());
    int k=0;
    for(auto p : symgrp) {
	k++;
	FastPermutation<N> S = p.first;
	printf("SYM: %-20s - %50s\n",
	       p.second.name.c_str(),
	       p.first.dump2Str(fglb::CubeMapCorners).c_str()
	       );

	std::vector<char> replace;
	
	printf("REPLACE for sym: %9s ", p.second.name.c_str());
	for(int i=0;i<basenames.size();i++) {
	    // x = i  -SxS = x' = i'
	    FastPermutation<N> x = bases[i];
	    std::string ii;
	    ii += basenames[i];

	    FastPermutation<N> sXS = (-S) * x * S;
	    //FastPermutation<N> sXS = x * S;
	    
	    std::string ip = FastPermutation<N>::getNameForCube(sXS, bases, basenames);
	    if((i%2) == 0)
		printf("%s -> %s, ", ii.c_str(), ip.c_str());
	    replace.push_back(ip[0]);
	}
	printf("\n");

	/*
	for(int i=0;i<basenames.size();i++) {
	    for(int j=0;j<basenames.size();j++) {
		// x = ij   x' = i'j'
		// (-s)xS = x'
		FastPermutation<N> x = bases[j] * bases[i];
		std::string ij;
		ij += basenames[i];
		ij += basenames[j];
		FastPermutation<N> sxS = (-S) * x * S;
		//FastPermutation<N> sxS = x * S;
		std::string ipjp = FastPermutation<N>::getNameForCube(sxS, bases, basenames);
		ipjp = Permutation::reduceName(ipjp);
		std::string ipjp_calc;
	
		
		ipjp_calc += replace[i];
		ipjp_calc += replace[j];
		ipjp_calc = Permutation::reduceName(ipjp_calc);
		
		if(ipjp_calc != ipjp) {
		    printf("\tS_%d (%s) = %s %s\n", k, ij.c_str(), ipjp.c_str(), ipjp_calc.c_str());
		}
	    }
	}
	*/

	replacements.push_back(replace);
    }
}


Permutation::Permutation(std::string cycle_string, std::string nm) {
    std::vector<std::vector<int> > base_cycles;
    
    name = nm;
    
    int open = 0;
    int close = 0;
    

    //printf("cons:  %s %s\n", cycle_string.c_str(), nm.c_str());
    while(1) {
	open = cycle_string.find_first_of('(', open);
	if(open == std::string::npos) break;
	close = cycle_string.find_first_of(')', close);
	if(close == std::string::npos) break;
	if(open+1 == close) break;
	
	std::string cs = cycle_string.substr(open + 1, close-open-1);
	    
	base_cycles.push_back(readSingleCycle(cs));
	    
	open++;
	close++;
    }
    
    //printf("here\n");
    cycles = base_cycles;
    //printf("there\n");
    cycles = pairRepresentation(cycles);
    //	printf("ok\n");
    cycles = fullRepresentation(cycles);
    //sortedorder(cycles);
    //printf("yeah\n");
}

Permutation::Permutation(std::vector<std::vector<int>> x, std::string nm) {
    cycles = x;
    cycles = pairRepresentation(cycles);
    cycles = fullRepresentation(cycles);
    name = nm;
}

void Permutation::sortedorder(std::vector<std::vector<int>> &vec) {
    std::sort(vec.begin(), vec.end(), [](std::vector<int> &a, std::vector<int> &b) { return a[0] < b[0]; });
}

std::vector<int> Permutation::spinToMin(std::vector<int> cyc) {
    int minval = cyc[0];
    int minidx = 0;

    std::vector<int> outcyc;
	
    for(int i=1;i<cyc.size();i++) {
	if(cyc[i] < minval) {
	    minidx = i;
	    minval = cyc[i];
	}
    }

    for(int i=0;i<cyc.size();i++) {
	outcyc.push_back(cyc[(i+minidx) % cyc.size()]);
    }
    return outcyc;
}


std::vector<std::vector<int>> Permutation::pairRepresentation(std::vector<std::vector<int>> base_cycles) {
    std::vector<std::vector<int>> ret;
    
    for(int i=0;i<base_cycles.size();i++) {
	base_cycles[i] = spinToMin(base_cycles[i]);
	std::vector<std::vector<int>> decom = decompose(base_cycles[i]);
	
	for(std::vector<int> pp : decom) {
	    ret.push_back(pp);
	}
    }
    
    //sortedorder(ret);
    return ret;    
}

std::vector<std::vector<int>> Permutation::fullRepresentation(std::vector<std::vector<int>> pairRep) {
    std::vector<int> all;

    //printf("boo\n");
    for(std::vector<int> p : pairRep) {
	//  printf("hoo\n");
	for(int x : p) {
	    //printf("zoo\n");
	    if(std::find(all.begin(), all.end(), x) == all.end()) {
		all.push_back(x);
	    }
	}
    }

    //printf("aaaa\n");
    for(int i : all) {
	//printf("all:   %d\n", i);
    }

    std::vector<std::vector<int>> ncc;

    for(;;) {
	//printf("bbbbb\n");
	std::vector<int> nc;
	if(all.size() == 0) break;
	int x = all[0];
	int curr = x;
	//printf("aa\n");
	nc.push_back(x);
	//printf("bb\n");
	for(;;) {
		
	    // Get what x transforms into...
	    for(int i=pairRep.size()-1;i>=0;i--) {
		if(pairRep[i][0] == curr) {
		    curr = pairRep[i][1];
		}
		else if (pairRep[i][1] == curr) {
		    curr = pairRep[i][0];
		}
	    }
		
	    if(curr == nc[0]) break;
		
	    nc.push_back(curr);
	}
	if(nc.size() > 1) {
		
	    ncc.push_back(spinToMin(nc));
	}
	    
	all.erase(all.begin());

	// for(int i : all) printf("all2: %d\n", i);
	//for(int i : nc) printf("nc: %d\n", i);

	std::vector<int> nall;
	for(int i : all) {
	    if(std::find(nc.begin(), nc.end(), i) == nc.end()) {
		nall.push_back(i);
	    }
	}
	all = nall;

	//for(int i : all) printf("all3: %d\n", i);

	if(all.size() == 0) break;
    }

    sortedorder(ncc);
    return ncc;
}

std::vector<int> Permutation::readSingleCycle(std::string cycle_string) {
    std::vector<int> cycle;
    std::string cs = cycle_string;
    while(1) {
	// printf("[%s]   \n",cs.c_str());
	int sp = cs.find_first_of(' ');
	//printf("]%d[\n",sp);
	if(sp == std::string::npos) {
	    //	printf("0---\n");
	    //	printf("{%d}\n", std::stoi(cs));
	    cycle.push_back(std::stoi(cs));
	    return cycle;
	}

	//printf("-- %s -- :%s:\n", cs.c_str(), cs.substr(0,sp).c_str());
	//printf("{%d}", std::stoi(cs.substr(0,sp)));
	    
	cycle.push_back(std::stoi(cs.substr(0,sp)));
	cs = cs.substr(sp+1);
    }
    return cycle;
}

Permutation Permutation::cycleIndexValues(Permutation idxcycle) {
    std::vector<std::vector<int>> cyc = cycleIndexValues(cycles, idxcycle.getCycles());
    cycles = cyc;
    for(std::vector<int> &c : cycles) {
	c = spinToMin(c);
    }
    sortedorder(cycles);
    return Permutation(cyc, "perm");
}

std::string Permutation::cycleString(std::vector<std::vector<int>> _cyc) {
    std::string str;
	
    if(_cyc.size() == 0) {
	str = "()";
	return str;
    }
    for(std::vector<int> cyc : _cyc) {
	str += "(";
	int f=1;
	for(int o : cyc) {
	    if(!f) {
		str += " ";
	    }
	    if(f) f=0;
		
	    str += std::to_string(o);  // sprintf("%d", o);
	}
	str += ")";
    }
    return str;
}

void Permutation::reduceName() {
    std::string newname = reduceName(name);
    name = newname;
}

std::string Permutation::reduceName(std::string n) {
    std::string nn;

    //printf("trying to reduce (%s)[%d,%d,%d]\n", n.c_str(), n.length(), n.size(), strlen(n.c_str()));
    // reduce:
    //   1. "xX" --> ""
    //   2. "Xx" --> ""
    //   2a."XX" --> "xx"
    //   3. "xxx" --> "X"
    //   4. "XXX" --> "x"
    //   5.  "xxxx"/"XXXX" --> ""
    //   6.  swap lL / rR to sort lL first  (they commute)
    //   7.  swap fF / xX to sort fF first  (they commute)
    //   8.  swap tT / bB to sort tT first
    
    if(n.size() < 2) return n;
	
    // 1 & 2
    for(int i=0;i<n.size()-1;i++) {
	// printf("check tolowers: %c-%c-%d-%d\n",n[i], n[i+1], i, n.size()); 
	if(tolower(n[i]) == tolower(n[i+1])) {
	    if(n[i] != n[i+1]) {
		if(n.size() == 2) return "";
		if(i>0) nn = n.substr(0, i);
		else nn = "";
		    
		if(n.size() >  i+2) nn += n.substr(i+2);
		//printf("Reducing Xx to %s\n",nn.c_str());
		return reduceName(nn);
	    }
	}	
    }
    for(int i=0;i<n.size()-1;i++) {
	if((n[i] == n[i+1]) && isupper(n[i])) {
	    if(i>0) nn = n.substr(0, i);
	    nn += tolower(n[i]);
	    nn += tolower(n[i]);
	    if(n.size() > i+ 2) nn += n.substr(i+2);
	    return reduceName(nn);
	}
    }

    // 3 & 4 & (5 automatically because it first gets the xxx -> X then Xx -> I)
    if(n.size() >=3) {
	for(int i=0;i<n.size()-2;i++) {
	    //printf("in xx loop:  n.size=%d i=%d\n",n.size(),i);
	    if((n[i] == n[i+1]) && (n[i] == n[i+2])) {
		nn = n.substr(0,i);
		char c = n[i];
		if(islower(c)) c = toupper(c);
		else c = tolower(c);
		nn += c;
		if(n.size() > i+3) nn += n.substr(i+3);
		    
		//  printf("reducing xxx --> %s   (%d)\n", nn.c_str(), n.size());
		return reduceName(nn);
	    }
	}
    }

    // 6,7,8
    for(int i=0;i<n.size() -1 ;i++) {
	if(((tolower(n[i]) == 'r') && (tolower(n[i+1]) == 'l')) ||
	   ((tolower(n[i]) == 'x') && (tolower(n[i+1]) == 'f')) ||
	   ((tolower(n[i]) == 'b') && (tolower(n[i+1]) == 't'))) {
	    char c = n[i];
	    n[i] = n[i+1];
	    n[i+1] = c;

	    return reduceName(n);
	}
    }
	    
	    
    return n;
}


    // Note name is assembled backwards!
Permutation Permutation::operator* (Permutation B) {
    std::vector<std::vector<int>> Acyc = cycles;
    std::vector<std::vector<int>> Bcyc = B.getCycles();

    Acyc.insert(Acyc.end(), Bcyc.begin(), Bcyc.end());

    std::string bbb = B.getName() + name;
    //printf("in mult %s  (%s-%s)\n", bbb.c_str(), name.c_str(), B.name.c_str());
	
    Permutation C(Acyc, B.getName() + name);
    return C;
}

Permutation Permutation::operator- () {
    std::vector<std::vector<int>> res;

    for(std::vector<int> c : cycles) {
	std::vector<int> nv;
	    
	for(int idx=c.size()-1;idx >= 0; idx--) {
	    nv.push_back(c[idx]);
	}
	res.push_back(spinToMin(nv));
    }

    std::string nname = name;
    std::reverse(nname.begin(), nname.end());
    for(int i=0;i<nname.size();i++) {
	if(isupper(nname[i])) nname[i] = tolower(nname[i]);
	else nname[i] = toupper(nname[i]);
    }
	
	
    Permutation MR(res, nname);
    return MR;
}

    // 1->3->2->5, 3->4->5->6, 1->4->2->6
std::vector<std::vector<int>> Permutation::cycleIndexValues(std::vector<std::vector<int>> cyc, std::vector<std::vector<int>> idxcyc) {
    std::vector<std::vector<int>> ncyc;

    // build table for the transfer...
    int o2n[10];
    for(int i=0;i<10;i++) o2n[i] = i;

    for(std::vector<int> idx_s_cyc : idxcyc) {
	for(int i=0;i<idx_s_cyc.size();i++) {
	    int j = (i+1)%idx_s_cyc.size();
		
	    o2n[idx_s_cyc[i]] = idx_s_cyc[j];
	}
    }

	
    for(int i=0;i<10;i++) {
	//printf("o2n[%d]=%d\n", i,o2n[i]);
    }

    // do the transfer
    for(std::vector<int> s_cyc : cyc) {
	std::vector<int> n_s_cyc;
	    
	for(int x : s_cyc) {
	    int nx = 0;

	    int digit3 = o2n[((x/100)%10)];
	    int digit2 = o2n[((x/10)%10)];
	    int digit1 = o2n[(x%10)];
	    if((digit3 > 0) && (digit2 > digit1)) {
		nx = digit3 * 100 + digit2 + digit1 * 10;
	    }
	    else {
		nx = digit3 * 100 + digit2 * 10 + digit1;
	    }
				 
	    n_s_cyc.push_back(nx);
	}
	ncyc.push_back(n_s_cyc);
    }
    return ncyc;
}

std::vector<std::vector<int>> Permutation::decompose(std::vector<int> cyc) {
    std::vector<std::vector<int>> res;
	
    for(int i=cyc.size()-1;i>=1;i--) {
	std::vector<int> ts;
	ts.push_back(cyc[0]);
	ts.push_back(cyc[i]);
	res.push_back(ts);
    }
    return res;
}


int Permutation::getSourcePosition(int x) {
    for(std::vector<int> c : cycles) {
	for(int i=0;i<c.size();i++) {
	    if(x == c[i]) {
		i = i + c.size() - 1;
		i = i % c.size();
		return c[i];
	    }
	}
    }
    return x;
}

int Permutation::order() {
    std::vector<std::vector<int>> pairs = pairRepresentation(cycles);
    return pairs.size();
}

int Permutation::nswaps() {
    int spins = 0;
    int swaps = 0;
    std::set<int> swapped_cubes;

    for(std::vector<int> cyc : cycles) {
	std::set<int> cubes;

	for(int x : cyc) {
	    x = x % 10;
	    cubes.insert(x);
	}

	if(cubes.size() == 1) spins++;
	if(cubes.size() > 1) {
	    for(int y : cubes) {
		swapped_cubes.insert(y);
	    }
	}
    }
    swaps = swapped_cubes.size();

    if(swaps > 1) return swaps-1;
    if(spins > 0) return 1;
    return 0;
}

int Permutation::countInvolvedCubes(int &corners, int &edges) {
    std::vector<int> cubes;

    int found;
    corners = edges = 0;
	
    for(auto cyc : cycles) {
	for(auto cc : cyc) {
	    std::vector<int> digits;
		
	    digits.push_back(cc/100);
	    digits.push_back((cc/10) % 10);
	    digits.push_back(cc % 10);
		
	    std::sort(digits.begin(), digits.end(), [](int &a, int &b) { return a<b; });
		
	    int ccc = digits[0] * 100 + digits[1] * 10 + digits[2];

	    found = 0;
	    for(auto x : cubes) { 
		if(x == ccc) {
		    found = 1;
		    break;
		}
	    }

	    if(!found) {
		//  printf("--- %d %d %d %d\n",cc, digits[0], digits[1], digits[2]);
		if(ccc > 100) corners++;
		else if(ccc > 10) edges++;
		    
		cubes.push_back(ccc);
	    }
	}
    }

    //for(int i : cubes) {
    //  printf("  -- %d\n",i);
    //}
    return cubes.size();
}

TransTable::TransTable() {
    readTransTable((char *)"face_permutations.txt", face_permutations);

    // Build face renames...
    for(int i=0;i<face_permutations.size();i++) {
	std::vector<std::vector<int>> face_rename;

	for(std::vector<int> v : face_permutations[i].getCycles()) {
	    if(v[0] < 10) {
		face_rename.push_back(v);
	    }
	}

	Permutation frn(face_rename, "");
	//printf("%d\n",i);
	//frn.dump();
	face_renames.push_back(frn);
    }
}

bool TransTable::add(Permutation &p) {
    for(int i=0;i<face_renames.size();i++) {
	Permutation x = p;
	x.cycleIndexValues(face_renames[i]);

	std::string key = x.cycleString(x.getCycles());
	if(transtab.count(key) > 0) {
	    return false;
	}
    }
    transtab.insert({p.cycleString(p.getCycles()),
		p.reduceName(p.getName()) });
    return true;
}

Permutation TransTable::applyFacePermutation(int idx, Permutation &P) {
    Permutation np = face_permutations[idx] * P;
    np = np.cycleIndexValues(face_renames[idx]);
    return np;
}

void TransTable::writeTransTable(char *filename, std::map<std::string, std::string> &transtab) {
    FILE *f = fopen(filename, "w");
    if(!f) {
	printf("Error! opening\n");
	return;
    }
	
    for(auto x : transtab) {
	fprintf(f, "%s:%s:\n", x.first.c_str(), x.second.c_str());
    }
	
    fclose(f);
}

void TransTable::readTransTable(char *filename, std::vector<Permutation> &perms) {
    FILE *f = fopen(filename, "r");
    if(!f) {
	printf("Error! opening reading\n");
	return;
    }
	
    char s[1024];
    while(fgets(s, 1024, f)) {
	std::string str = s;
	std::istringstream iss(str);
	std::string cyc;
	std::string name;
	std::getline(iss, cyc, ':');
	std::getline(iss, name, ':');
	    
	//printf("HUH:  %s %s\n", cyc.c_str(), name.c_str());
	Permutation p(cyc, name);
	//	p.dump();
	perms.push_back(p);
    }
}

FastName::FastName(const char *s) {
    len = strlen(s);
    //assert(len < 19);
    strcpy(name, s);
}

FastName::FastName(const FastName &fn) {
    this->len = fn.len;
    memcpy(this->name, fn.name, fn.len);
    this->name[this->len] = '\0';
}

FastName::FastName(FastName &fn, char nxt) {
    this->len = fn.len;
    memcpy(this->name, fn.name, fn.len);
    this->name[this->len] = nxt;
    this->len++;
    this->name[this->len] = '\0';
}

bool FastName::isAddValid(char nxt) {
    if(len == 0) return true;

    char last, Ulast, Unxt;
    last = name[len-1];
    Ulast = toupper(last);
    Unxt = toupper(nxt);

    // No xX / Xx
    if((Ulast == Unxt) && (nxt != last)) {
	return false;
    }

    // No XX (doubles via xx)
    if((last == nxt) && isupper(nxt)) {
	return false;
    }

    // sort l, t, f among commuting...
    if((Unxt == 'L') && (Ulast == 'R') ||
       (Unxt == 'T') && (Ulast == 'B') ||
       (Unxt == 'F') && (Ulast == 'X')) {
	return false;
    }

    if(len >= 2) {
	char prev = name[len-2];
	if((prev == last) && (last == nxt)) {
	    return false;
	}
    }

    return true;
}

void FastName::add(char nxt) {
    name[len] = nxt;
    len++;
    name[len] = '\0';
}

FastName FastName::operator+ (FastName &b) {
    FastName res;
    res.len = len + b.len;
    memcpy(res.name, name, len);
    memcpy(&res.name[len], b.name, b.len);
    res.name[res.len] = '\0';

    return res;
}

template class FastPermutation<54>;
template class FastPermutation<24>;
template class FastPermutation<8>;
template class CubeCounter<54>;
template class CubeCounter<24>;
template class CubeCounter<8>;


bool incrementIdx(int *idx, int depth, int nbases) {
    int i = depth-1;

    while(i >= 0) {
        if(idx[i] == nbases - 1) {
            idx[i] = 0;
            i--;
        }
        else {
            idx[i]++;

            return true;
        }
    }
    return false;
}
