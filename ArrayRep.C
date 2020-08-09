#include "ArrayRep.h"
#include "Permutation.h"
#include "PermutationMap.h"
#include <assert.h>
#include <unistd.h>

PermutationMap &ArrayRep::pm = RubiksMap;
PermutationMap &CornerStore::pm = RubiksMap;
PermutationMap &SideStore::pm = RubiksMap;

SideStore::SideStore(u_int64_t x) {
    data = x;
}

SideStore::SideStore(ArrayRep &x, u_int64_t cnt) {
    set(x,cnt);
}

// cnt is the 16 least significant bits...
void SideStore::set(ArrayRep &x, u_int64_t cnt) {
    data = 0;
    for(int i=0;i<12;i++) {
	int locIdx = pm.sidecubies.ccIdx2Idx[i];          // sampling idx
	int faceIdx = x.data[locIdx];                     // faceIdx @ samplingIdx

	if(faceIdx == 0xff) {                             // if wildcard
	    data += (0xfll << (4 + (i*4)));              
	}
	else {
	    u_int64_t cubieOrient = pm.sidecubies.face2Orientation[i][faceIdx];
	    u_int64_t cubieCcIdx = pm.sidecubies.idx2ccIdx[faceIdx];  // ccIdx of the face..
	    if((cubieCcIdx < 0) || (cubieCcIdx > 12)) {
		printf("Bad cubieIdx: %lu\n", cubieCcIdx);
	    }
	    data |= (cubieCcIdx << (4 + (i*4)));
	    if((cubieOrient < 0) || (cubieOrient > 2)) {
		printf("Bad cubieOrient: %lu\n", cubieOrient);
	    }
	
	    data |= (cubieOrient << (4 + 48 + i));
	}
    }
    data |= cnt & 0xfll;
}

ArrayRep SideStore::build() {
    ArrayRep x;
    memset(x.data, 0xff, sizeof(x.data));

    for(int i=0;i<12;i++) {
	u_int64_t ccidx = data >> (4 + i*4);
	ccidx &= 0xfll;
	if(ccidx == 0xfll) continue;   // This is a wildcard, already set!
	
	u_int64_t orient = data >> (4 + 48 + i);
	orient &= 1;
	
	int locIdx = pm.sidecubies.ccIdx2Idx[i];
	int faceIdx = pm.sidecubies.ccIdx2Idx[ccidx];

	int loc = pm.idx2label.at(locIdx);
	int face = pm.idx2label.at(faceIdx);

	//printf("orient = %d %d\n", orient,face);
	
	if(orient == 0) face = pm.flipDigits(face);

	// The other face of the cubie
	int rloc = pm.flipDigits(loc);
	int rface = pm.flipDigits(face);

	x.data[pm.label2idx.at(loc)] = pm.label2idx.at(face);
	x.data[pm.label2idx.at(rloc)] = pm.label2idx.at(rface);
    }
    return x;
}


int SideStore::getCount() {
    return (int)(data & 0xfll);
}

// The cnt is data, not indexable.  If set, always the same...
bool SideStore::operator<(const SideStore &b) const {
    return ((data & ~0xfll) < (b.data & ~0xfll));
}

// The cnt is data, not indexable.  If set, always the same...
bool SideStore::operator>(const SideStore &b) const {
    return ((data & ~0xfll) > (b.data & ~0xfll));
}

// equality also works bare, because the same twist always must
// have the same count...
bool SideStore::operator==(const SideStore &b) const {
    return ((data & ~0xfll) == (b.data & ~0xfll));
}

// As does inequality!
bool SideStore::operator!=(const SideStore &b) const {
    return ((data & ~0xfll) != (b.data & ~0xfll));
}

/////////

CornerStore::CornerStore(u_int64_t x) {
    data = x;
}

CornerStore::CornerStore(ArrayRep &x, u_int64_t cnt) {
    set(x,cnt);
}

// cnt is the 16 least significant bits...
void CornerStore::set(ArrayRep &x, u_int64_t cnt) {
    data = 0;
    for(int i=0;i<8;i++) {
	int locIdx = pm.cornercubies.ccIdx2Idx[i];           // sampling idx
	int faceIdx = x.data[locIdx];                        // faceIdx @ samplingIdx
	u_int64_t cubieOrient = pm.cornercubies.face2Orientation[i][faceIdx];
	u_int64_t cubieCcIdx = pm.cornercubies.idx2ccIdx[faceIdx];                // ccIdx of the face..
	if((cubieCcIdx < 0) || (cubieCcIdx > 7)) {
	    printf("Bad cubieIdx: %lu\n", cubieCcIdx);
	}
	data |= (cubieCcIdx << (16 + (i*3)));
	if((cubieOrient < 0) || (cubieOrient > 2)) {
	    printf("Bad cubieOrient: %lu\n", cubieOrient);
	}
	
	data |= (cubieOrient << (16 + 24 + (i*2)));
    }
    data |= cnt & 0xffll;
}

ArrayRep CornerStore::build() {
    ArrayRep x;
    memset(x.data, 0xff, sizeof(x.data));

    for(int i=0;i<8;i++) {
	u_int64_t ccidx = data >> (16 + i*3);
	ccidx &= 0x7;
	u_int64_t orient = data >> (16 + 24 + i*2);
	orient &= 3;
	
	//printf("i=%d\n", i);
	
	int locIdx = pm.cornercubies.ccIdx2Idx[i];
	//printf("ccidx=%d\n", ccidx);
	
	int faceIdx = pm.cornercubies.ccIdx2Idx[ccidx];

	int loc = pm.idx2label.at(locIdx);
	int face = pm.idx2label.at(faceIdx);

	while(orient>0) {
	    face = pm.c_label_clockwise.at(face);
	    face = pm.c_label_clockwise.at(face);
	    orient--;
	}
	
	int j=0;
	while(j<3) {
	    //printf("loc=%d face=%d\n", loc, face);
	    x.data[pm.label2idx.at(loc)] = pm.label2idx.at(face);
	    loc = pm.c_label_clockwise.at(loc);
	    face = pm.c_label_clockwise.at(face);
	    //face = pm.c_label_clockwise.at(face);    // rotating location like rotating -face
	    j++;
	}
    }
    return x;
}


int CornerStore::getCount() {
    return (int)(data & 0xffffll);
}

// The cnt is data, not indexable.  If set, always the same...
bool CornerStore::operator<(const CornerStore &b) const {
    return ((data & ~0xffffll) < (b.data & ~0xffffll));
}

// The cnt is data, not indexable.  If set, always the same...
bool CornerStore::operator>(const CornerStore &b) const {
    return ((data & ~0xffffll) > (b.data & ~0xffffll));
}

// equality also works bare, because the same twist always must
// have the same count...
bool CornerStore::operator==(const CornerStore &b) const {
    return ((data & ~0xffffll) == (b.data & ~0xffffll));
}

// As does inequality!
bool CornerStore::operator!=(const CornerStore &b) const {
    return ((data & ~0xffffll) != (b.data & ~0xffffll));
}


ArrayRep ArrayRep::origin("");


// clockwise from facing the slice...
ArrayRep ArrayRep::Af(Permutation::Pf);
ArrayRep ArrayRep::Ax(Permutation::Px);
ArrayRep ArrayRep::Ar(Permutation::Pr);
ArrayRep ArrayRep::Al(Permutation::Pl);
ArrayRep ArrayRep::At(Permutation::Pt);
ArrayRep ArrayRep::Ab(Permutation::Pb);

ArrayRep ArrayRep::AF = -ArrayRep::Af;
ArrayRep ArrayRep::AX = -ArrayRep::Ax;
ArrayRep ArrayRep::AR = -ArrayRep::Ar;
ArrayRep ArrayRep::AL = -ArrayRep::Al;
ArrayRep ArrayRep::AT = -ArrayRep::At;
ArrayRep ArrayRep::AB = -ArrayRep::Ab;

// middle (front slice up),  equator (equator slice left),  standing (over slice like top)
ArrayRep ArrayRep::Am = ArrayRep::AR * ArrayRep::Al;
ArrayRep ArrayRep::Ae = ArrayRep::AT * ArrayRep::Ab;
ArrayRep ArrayRep::As = ArrayRep::AF * ArrayRep::Ax;
ArrayRep ArrayRep::AM = -Am;
ArrayRep ArrayRep::AE = -Ae;
ArrayRep ArrayRep::AS = -As;



ArrayRep::ArrayRep() {
    //for(int i=0;i<48;i++) {
    //	data[i] = i;
    //}
}

ArrayRep::ArrayRep(const u_int8_t *x) {
    for(int i=0;i<48;i++) {
	data[i] = x[i];
    }
}

ArrayRep::ArrayRep(const ArrayRep &p) {
    for(int i=0;i<48;i++) {
	data[i] = p.data[i];
    }
}

void ArrayRep::initFromPermutation(const Permutation &p) {
    for(int i=0;i<48;i++) data[i] = i;
    
    const std::vector<std::vector<int>> cycles = p.getCycles();
    for(std::vector<int> cyc : cycles) {
	for(int i=0; i<cyc.size(); i++) {
	    
	    int j = (i+1)%cyc.size();
	    int l1 = cyc[j];
	    int l2 = cyc[i];
	   	    
	    int idx2 = pm.label2idx.at(l2);
	    int idx1 = pm.label2idx.at(l1);

	    
	    data[idx1] = idx2;
	}
    }
}

ArrayRep::ArrayRep(const Permutation &p) {
    initFromPermutation(p);
}

ArrayRep::ArrayRep(const std::string s) {
    Permutation p(s);
    initFromPermutation(p);
}

ArrayRep::ArrayRep(std::vector<std::pair<int, int>> &label_positions)
{
    for(int i=0;i<48;i++) {
	data[i] = 0xff;
    }
    
    for(auto &p: label_positions) {
	int pos = p.first;
	int face = p.second;
	
	u_int8_t pos_idx = pm.label2idx.at(pos);
	u_int8_t face_idx = pm.label2idx.at(face);
	
	data[pos_idx] = face_idx;
    }
}

void ArrayRep::maskLabelPositions(std::vector<int> &invalid) {
  
    
    for(int pos_idx = 0;pos_idx<48;pos_idx++) {
	if(std::binary_search(invalid.begin(), invalid.end(), pm.idx2label.at(data[pos_idx]))) {
	    data[pos_idx] = 0xff;
	}
    }
}


bool ArrayRep::operator< (const ArrayRep &b) const {
    for(int i=0;i<48;i++) {
	if(data[i] < b.data[i]) return true;
	if(data[i] > b.data[i]) return false;
    }
    return false;
}
    
bool ArrayRep::operator== (const ArrayRep &b) const {
    if(memcmp(data, b.data, sizeof(data)) == 0) return true;
    return false;
}

bool ArrayRep::operator!= (const ArrayRep &b) const {
    if(memcmp(data, b.data, sizeof(data)) != 0) return true;
    return false;
}

ArrayRep ArrayRep::operator* (const ArrayRep &b) const {
    ArrayRep r;
    for(int i=0;i<48;i++) {
	assert(data[i] != 0xff);
	r.data[i] = b.data[data[i]];
    }
    return r;
}

ArrayRep ArrayRep::operator- () const {
    ArrayRep r;
    for(int i=0;i<48;i++) {
	assert(data[i] != 0xff);
	r.data[data[i]] = i;
    }
    return r;
}

void ArrayRep::searchForConjigisor(int nconjigisors,
				   ArrayRep &conjugate,
				   std::vector<ArrayRep> &bases,
				   std::vector<char> &basenames,
				   std::map<ArrayRep, ElementDescriptor> &results) {
    int nfound = 0;
    std::map<ArrayRep, ElementDescriptor> history;
    
    history.insert({ ArrayRep::origin, { "", 1 }});
    std::vector<std::pair<ArrayRep, ElementDescriptor>> todo;
    todo.push_back({ ArrayRep::origin, { "", 1 }});
    int level = 0;
    
    for(;;) {
	level++;

	std::vector<std::pair<ArrayRep, ElementDescriptor>> todo_now = todo;
	todo.clear();
	
	for(auto p : todo_now) {
	    for(int i=0;i<bases.size();i++) {
		ArrayRep np = bases[i] * p.first;
		
		std::string nn;
		if(basenames.size() > 0) {
		    nn = p.second.name + basenames[i];
		}
		
		// Do the insert
		auto res = history.insert({ np, { nn,1} });
		if(res.second) {  // the insert worked!
		    todo.push_back({ np, { nn, 1 }});

		    if(((-np) * conjugate * np) == *this) {
			// found me!
			printf("Found one! %s:%s\n", np.dump2CStr().c_str(), nn.c_str());
			printf("%s =\n   %s\n *    %s\n *    %s\n",
			       this->dump2CStr().c_str(),
			       (-np).dump2CStr().c_str(),
			       conjugate.dump2CStr().c_str(),
			       np.dump2CStr().c_str());
			
			results.insert({np, {nn, 1}});
			return;
		    }
		}
	    }
	}     
	if(todo.size() == 0) break;
    }
}

void ArrayRep::searchForMe(std::vector<ArrayRep> &bases,
			   std::vector<char> &basenames,
			   std::map<ArrayRep, ElementDescriptor> &results) {
    std::map<ArrayRep, ElementDescriptor> history;

    history.insert({ ArrayRep::origin, { "", 1 }});
    std::vector<std::pair<ArrayRep, ElementDescriptor>> todo;
    todo.push_back({ ArrayRep::origin, { "", 1 }});
    int level = 0;
    
    for(;;) {
	level++;

	std::vector<std::pair<ArrayRep, ElementDescriptor>> todo_now = todo;
	todo.clear();
	
	for(auto p : todo_now) {
	    for(int i=0;i<bases.size();i++) {
		ArrayRep np = bases[i] * p.first;
		
		std::string nn;
		if(basenames.size() > 0) {
		    nn = p.second.name + basenames[i];
		}
		
		// Do the insert
		auto res = history.insert({ np, { nn,1} });
		if(res.second) {  // the insert worked!
		    todo.push_back({ np, { nn, 1 }});

		    if(np == *this) {
			// found me!
			printf("Found one! %s:%s\n", np.dump2CStr().c_str(), nn.c_str());
			results.insert({np, {nn, 1}});
			return;
		    }
		}
	    }
	}     
	if(todo.size() == 0) break;
    }
}
			   
// todo starts full and end empty
// todo_next starts empty and ends full
void ArrayRep::getGeneratedGroupLevelCntsSym(u_int8_t level,
					     std::vector<ArrayRep> &bases,
					     std::map<ArrayRep, u_int8_t> &result,
					     std::vector<ArrayRep> &todo,
					     std::vector<ArrayRep> &todo_next,
					     std::vector<ArrayRep> &Svec,
					     bool savenext) {
    
    while(!todo.empty()) {
	ArrayRep td = todo.back();
	todo.pop_back();
	
	for(int i=0;i<bases.size();i++) {
	    ArrayRep np = bases[i] * td;

	    int found = 0;
	    for(auto S : Svec) {
		if(result.find(-S * np * S) != result.end()) {
		    found = 1;
		    break;
		}
	    }

	    if(found == 0) {
		// Do the insert
		auto res = result.insert({ np, level });
		if(res.second) {
		    if(savenext) {
			todo_next.push_back(np);
		    }
		}
	    }
	}
    }     
}


// todo starts full and end empty
// todo_next starts empty and ends full
void ArrayRep::getGeneratedGroupLevelCnts(u_int8_t level,
					  std::vector<ArrayRep> &bases,
					  std::map<ArrayRep, u_int8_t> &result,
					  std::vector<ArrayRep> &todo,
					  std::vector<ArrayRep> &todo_next) {
    
    while(!todo.empty()) {
	ArrayRep td = todo.back();
	todo.pop_back();

	for(int i=0;i<bases.size();i++) {
	    ArrayRep np = bases[i] * td;

	    // Do the insert
	    auto res = result.insert({ np, level });
	    
	    if(res.second) {
		todo_next.push_back(np);
		
	    }
	}
    }     
}

void ArrayRep::getGeneratedGroupCnts(std::vector<ArrayRep> &bases,
				     std::map<ArrayRep, u_int8_t> &result) {
    ArrayRep me = ArrayRep::origin;
    result.insert({me, 0});
    std::vector<ArrayRep> todo[2];

    int level = 0;
    int curr_todo=0;
    todo[0].push_back(me);

    while(!todo[curr_todo].empty()) {
	level++;
	getGeneratedGroupLevelCnts(level,
				   bases,
				   result,
				   todo[curr_todo],
				   todo[(curr_todo == 1) ? 0 : 1]);


	printf("level=%d %lu %lu %lu\n", level, todo[0].size(), todo[1].size(), result.size());
	curr_todo = (curr_todo == 1) ? 0 : 1;

	if(level == 7) {
	    for(;;) {
		sleep(1000);
	    }
	}
    }
}

// generates groups from the existing ArrayRep, which may
// have wildcards!  (0xff's)
void ArrayRep::getGeneratedGroup(std::vector<ArrayRep> &bases,
				 std::vector<char> &basenames,
				 std::map<ArrayRep, ElementDescriptor> &result) {
    ArrayRep me = *this;
    result.insert({ me, { "", 1 }});
    std::vector<std::pair<ArrayRep, ElementDescriptor>> todo;
    todo.push_back({ me, { "", 1 }});
    int level = 0;
    
    for(;;) {
	level++;
	//fprintf(stderr, "level=%d count=%lu\n", level, result.size());
	
	std::vector<std::pair<ArrayRep, ElementDescriptor>> todo_now = todo;
	todo.clear();
	
	for(auto p : todo_now) {
	    for(int i=0;i<bases.size();i++) {
		ArrayRep np = bases[i] * p.first;
		
		std::string nn;
		if(basenames.size() > 0) {
		    nn = p.second.name + basenames[i];
		}
		
		// Do the insert
		auto res = result.insert({ np, { nn,1} });
		
		if(res.second) {
		    todo.push_back({ np, { nn, 1 }});
		    
		    int whichsym;
		    //int minswaps = np.minSwaps(symvec, whichsym);
		    
		    //printf("CUBE: %50s %10s %d %d :%d\n", np.dump2Str(fglb::CubeMapUnrotatedCorners).c_str(), nn.c_str(), level, np.nSwaps(), minswaps);
		    
		}
	    }
	}     
	if(todo.size() == 0) break;
    }
}

std::string ArrayRep::dump2CStr() {
    std::string res;
    bool haswildcard = false;
    u_int8_t used[48];
    memset(used, 0, sizeof(used));
    for(int i=0;i<48;i++) {
	if(data[i] == 255) {
	    haswildcard = true;
	    continue;
	}
	if(data[i] == i) continue;
	if(used[i]) continue;

	//printf("i=%d\n",i);
	res += "(" + std::to_string(pm.idx2label.at(i));
	//res += "(" + std::to_string(i);
	int j = data[i];
	std::string cyc = "";
	while(j != i) {
	    if(cyc.length() == 0) {
		cyc += ")";
	    }
	    else {
		cyc = " " + cyc;
	    }
	    //printf("i=%d j=%d\n",i,j);
	    used[j] = 1;
	    cyc = std::to_string(pm.idx2label.at(j)) + cyc;
	  
	    j = data[j];
	}
	res += " "+cyc;
    }
    if(res.size() == 0) res += "()";

    if(haswildcard) {
	res = "(*)" + res;
    }
	
    return res;        // automatically sorted (smallest x x x)(nextsmallest x x x)
}

std::string ArrayRep::dump2DStr() {
    std::string ret;
    std::vector<std::vector<int>> laborder = {
	{ 326, 32, 324 },
	{ 36, -1, 34 },
	{ 316, 31, 314 },
	{ 623, 63, 613, 136, 13, 134, 413, 43, 423, 234, 23, 236 },
	{ 62, -1, 61, 16, -1, 14, 41, -1, 42, 24, -1, 26 },
	{ 625, 65, 615, 156, 15, 145, 415, 45, 425, 245, 25, 256 },
	{ 516, 51, 514 },
	{ 56, -1, 54 },
	{ 526, 52, 524 }
    };

    int i=0;
    for(auto &r : laborder) {
	i++;
	if((i<=3) || (i>6)) {
	    ret += "                  ";
	}
	
	for(auto idx : r) {
	    char str[10];
	    if(idx < 0) {
		ret += "(***) ";
	    }
	    else {
		if(data[pm.label2idx.at(idx)] == 0xff) {
		    ret += "(***) ";
		}else { 
		    int lab = pm.idx2label[data[pm.label2idx.at(idx)]];
		    
		    sprintf(str, "(%03d) ", pm.idx2label[data[pm.label2idx.at(idx)]]);
		    ret += str;
		}
	    }
	}
	ret += "\n";
	
	//for(int i=0;i<48;i++) {
	//printf("%d: %d %d\n", i, pm.idx2label.at(i), (data[i] == 0xff) ? -1 :  pm.idx2label.at(data[i]));
    }
    return ret;
}

int ArrayRepCount::getCount(std::vector<ArrayRepCount> &arc) {
    auto result = std::lower_bound(arc.begin(), arc.end(), *this);
    //printf("%s : %d\n", (*result).dump2CStr().c_str(), (*result).cnt);
    return cnt;
}

ArrayRep ArrayRep::random(std::default_random_engine &e) {
    ArrayRep x;
    int tries = 0;
    do {
	x = _random(e);
	tries++;
    } while(!isValid(x));

    //printf("Took %d tries for a valid cube! (should average about 12!)\n", tries);
    return x;
}
    
// DOES not give a ***legal*** permuation currently!
ArrayRep ArrayRep::_random(std::default_random_engine &e) {
    ArrayRep ret;
    std::uniform_int_distribution<int> d2(0,1);
    std::uniform_int_distribution<int> d3(0,2);

    // identify cubies by the following 
    std::vector<int> corners = { 136, 134, 156, 145, 234, 236, 245, 256 };
    std::vector<int> sides = { 13, 14, 15, 16 , 23, 24, 25, 26, 43, 45, 63, 65 };
    // these are the shuffled cubies
    std::vector<int> scorners = corners;
    std::vector<int> ssides = sides;
    
    std::shuffle(scorners.begin(), scorners.end(), e);
    std::shuffle(ssides.begin(), ssides.end(), e);

    //   printf("a\n");
    for(int i=0;i<corners.size();i++) {
	//	printf("b\n");
	int o = d3(e);

	// loc_labs contain the 3 sides of the cubies position
	std::vector<int> loc_labs;
	int loc_lab = corners[i];
	for(int j=0;j<3;j++) {
	    loc_labs.push_back(loc_lab);
	    //	    printf("aa: %d\n",loc_lab);
	    loc_lab = pm.c_label_clockwise.at(loc_lab);
	}

	// fac_labs contain the 3 sides of the cubies faces
	// also rotated by the randomized orientation...
	std::vector<int> fac_labs;
	int fac_lab = scorners[i];
	for(int j=0;j<o;j++) {
	    //  printf("bb: %d\n",fac_lab);
	    fac_lab = pm.c_label_clockwise.at(fac_lab);
	}
	for(int j=0;j<3;j++) {
	    fac_labs.push_back(fac_lab);
	    //  printf("cc: %d\n",fac_lab);
	    fac_lab = pm.c_label_clockwise.at(fac_lab);
	}

	//	printf("here\n");
	// Set the data appropriately...
	for(int j=0;j<3;j++) {
	    ret.data[pm.c_label2idx.at(loc_labs[j])] = pm.c_label2idx.at(fac_labs[j]);
	}
    }
    //   printf("c\n");
    
    for(int i=0;i<sides.size();i++) {
	//	printf("d\n");
	int o = d2(e);

	//	printf("dd %d\n", sides[i]);
	std::vector<int> loc_labs;
	loc_labs.push_back(sides[i]);
	loc_labs.push_back(pm.s_label_opposites.at(sides[i]));

	std::vector<int> fac_labs;
	int fac_lab = ssides[i];
	if(o == 1) {
	    //    printf("ee %d\n", fac_lab);
	    fac_lab = pm.s_label_opposites.at(fac_lab);
	}
	fac_labs.push_back(fac_lab);
	//	printf("ff %d\n", fac_lab);
	fac_labs.push_back(pm.s_label_opposites.at(fac_lab));

	//	printf("gg\n");
	
	for(int j=0;j<2;j++) {
	    ret.data[pm.s_label2idx.at(loc_labs[j])] = pm.s_label2idx.at(fac_labs[j]);
	}
    }

    return ret;
}

Permutation ArrayRep::getPermutation() {
    Permutation p(dump2CStr());
    return p;
}


// don't search at 48, follow the cycle from the base position...
int ArrayRep::getPositionOf(int face) {
    int face_idx = pm.label2idx.at(face);
    int idx = getPositionOfIdx(face_idx);
    return pm.idx2label.at(idx);
}

int ArrayRep::getPositionOfIdx(int face_idx) {
    int idx = face_idx;
    while(data[idx] != face_idx) {
	idx = data[idx];
    }
    return idx;
}

int ArrayRep::getFaceAt(int position) {
    int position_idx = pm.label2idx.at(position);
    int idx = getFaceAtIdx(position_idx);
    return pm.idx2label.at(idx);
}

// Parity of sides must match parity of corners!
// but note nswaps must be divided by 3 because
// in the notation, 1/3 of the swaps define the other 3x				      
bool ArrayRep::isValid(ArrayRep x) {
      bool valid = true;

    // Parity of sides must match parity of corners!
    // but note nswaps must be divided by 3 because
    // in the notation, 1/3 of the swaps define the other 3x
    Permutation px = x.getPermutation();
    Permutation dx = px.reduceToDegenerate();
    int p2 = dx.getNParity(2);
    int p3 = dx.getNParity(3);
    if(p2 != p3) {
	valid = false;
	//printf("%s: corner parity doesn't match side parity: p2=%d p3=%d\n", dx.dump2Str().c_str(), p2, p3);
    }
    //printf("%s parity: p2=%d p3=%d\n", dx.dump2Str().c_str(), p2, p3);

    // orientation of corners must sum to 0.
    std::vector<int> corners = { 136, 134, 156, 145, 234, 236, 245, 256 };
    int corner_orientation = 0;
    for(auto pos : corners) {
	int orientation = pm.getCornerOrientation(pos,x.getFaceAt(pos)); 
	corner_orientation += orientation;
    }
    corner_orientation %= 3;
    //printf("corner orientation is %d\n", corner_orientation);
    if(corner_orientation != 0) {
	valid = false;
	//printf("%s: Corner orientation is invalid: %d\n", x.dump2CStr().c_str(), corner_orientation);
    }

    // orientation of sides must sum to 0
    // Each marked position must have a marked side in it for the orientation to be 0
    // otherwise, the orientation is 1
    std::vector<int> marked_sides = { 13, 14, 15, 16, 23, 24, 25, 26, 43, 45, 63, 65 };
    int side_orientation = 0;
    for(auto pos : marked_sides) {
	int orientation = pm.getSideOrientation(pos, x.getFaceAt(pos));
	side_orientation += orientation;
    }

    side_orientation %= 2;
    //printf("side orientation is %d\n", side_orientation);
    if(side_orientation != 0) {
	valid = false;
	//printf("%s: side orientation is invalid: %d\n", x.dump2CStr().c_str(), side_orientation);
    }
	
    
    return valid;  
}
