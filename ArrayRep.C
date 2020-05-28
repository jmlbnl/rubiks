#include "ArrayRep.h"
#include "Permutation.h"
#include "PermutationMap.h"
#include <assert.h>

PermutationMap &ArrayRep::pm = RubiksMap;
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
    for(int i=0;i<48;i++) {
	data[i] = i;
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
			   
			 

// generates groups from the existing ArrayRep, which may
// have wildcards!  (0xff's)
void ArrayRep::getGeneratedGroup(std::vector<ArrayRep> &bases,
				 std::vector<char> &basenames,
				 std::map<ArrayRep, ElementDescriptor> &result) {
    result.insert({ ArrayRep::origin, { "", 1 }});
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
    
    u_int8_t used[48];
    memset(used, 0, sizeof(used));
    for(int i=0;i<48;i++) {
	if(data[i] == i) continue;
	if(used[i]) continue;

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
