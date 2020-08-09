#include "Permutation.h"
#include "ArrayRep.h"
#include "heuristic.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

typedef ArrayRep AR;

class Payload {
    u_int8_t x[48];
};

void testSizes() {
    std::random_device r;
    std::default_random_engine e(r());
    printf("Sizeof(AR) = %lu\n", sizeof(AR));

    Payload ppp;
    
    int good=0;
    int bad=0;
    std::map<u_int64_t, u_int8_t> testmap;
    u_int64_t x=0;
    
    for(int i=0;;i++) {
	//AR x = AR::random(e);
	x++;
	
	auto res = testmap.insert({x, 0});
	if(res.second) {
	    good++;
	}
	else {
	    bad++;
	}

	if(((good % ((1024*1024*100)/48)) == 0)) {
	    printf("%d inserted / %d not:   %fmb",good,bad,float(good * 9)/(1024*1024));
	    char str[256];
	    scanf("%s",str);
	}
    }
}

void testShuffle() {
    std::random_device r;
    std::default_random_engine e(r());
    //std::uniform_int_distribution<int> dice(1,6);
    std::vector<int> cards({1,2,3,4,5,6});

    


  
    for(int i=0;i<20;i++) {
    	std::shuffle(cards.begin(), cards.end(), e);
    	printf("(");
    	for(auto x : cards) {
    	    printf("%d ", x);
    	};
    	printf(") 0x%x\n", r());
    }
    printf("\n");
}

void testPermutationMap() {
    // The sorting of the labels is homomorphic to the sorting of the idx's
    //
    int i=0;
    printf("sides:\n");
    for(auto x : AR::pm.s_label2idx) {
	int idx = x.second;
	int lab = x.first;
	printf("%d %d %d\n", i, idx, lab);
	i++;
    }
    i=0;
    printf("corners:\n");
    for(auto x : AR::pm.c_label2idx) {
	int idx = x.second;
	int lab = x.first;
	printf("%d %d %d\n", i, idx, lab);
	i++;
    }   
}

void testValidity() {
    int x = 1666543782;
    int y = AR::pm.sortDigits(x);
    printf("%d -- %d\n",x,y);
    
    std::vector<AR> vec = { AR::Af,
			    AR::Af * AR::Ar * AR::At * AR::Ax,
			    AR("(56 65)(52 25)"),
			    AR("(134 413 314)"),
			    AR("(134 314 413)"),
			    
    };

    for(auto x : vec) {
	bool valid = AR::isValid(x);

	printf("%s:  valid = %d\n", x.dump2CStr().c_str(), valid);
    }
    
}

void testRandom() {
    std::random_device r;
    std::default_random_engine e(r());

    for(int i=0;i<1000;i++) {
	AR x = AR::random(e);
	printf("random:  %s\n", x.dump2CStr().c_str());
    }
}

void testCornerStore() {
    std::random_device r;
    std::default_random_engine e(r());
    
    std::vector<AR> vec = { AR::Ar
    };

    for(auto x : vec) {
	bool valid = AR::isValid(x);

	if(!valid) {
	    printf("%s:  valid = %d\n", x.dump2CStr().c_str(), valid);
	    continue;
	}

	//printf("a\n");
	CornerStore cs;
	//printf("b\n");

	cs.set(x, 50);
	//	printf("c\n");
	AR z = cs.build();
	//	printf("d\n");
	printf("original:%s", x.dump2CStr().c_str());
	printf("        :\n%s\n\n", x.dump2DStr().c_str());
	printf("restored:\n%s\n", z.dump2DStr().c_str());

	printf("x == z = %d\n", CornerStore(x,-1) == CornerStore(z,60000));
    }

    std::vector<AR> vecs;
    
    for(int i=0;i<1000;i++) {
	vecs.push_back(AR::random(e));
    }

    printf("done with random\n");
    for(auto x : vecs) {
	CornerStore cs(x, 500);
	AR z = cs.build();
	if(CornerStore(x, -1) != CornerStore(z, 2)) {
	    printf("ne\n");
	}
    }
    printf("done\n");
}

void getblahSymVec(std::vector<AR> &vec) {
    //AR reflect("(326 514)(32 51)(324 516)(36 54)(34 56)(316 524)(31 52)(314 526)(623 415)(63 45)(613 425)(62 41)(61 42)(625 413)(65 43)(615 423)(136 245)(13 25)(134 256)(16 24)(14 26)(156 234)(15 23)(145 236)");
    AR spin_l = AR::At * AR::AB; // ("(136 623 234 413)(13 63 23 43)(16 62 24 41)(156 625 245 415)(15 65 25 45)(145 615 256 425)(14 61 26 42)(134 613 236 423)(516 526 524 514)(316 326 324 314)(36 32 34 31)(56 52 54 51)");
    AR spin_d = AR::Al * AR::AR; // ("(136 516 256 326)(156 526 236 316)(314 145 524 234)(324 134 514 245)(36 16 56 26)(32 13 51 25)(34 14 54 24)(31 15 52 23)(61 65 62 63)(615 625 623 613)(413 415 425 423)(41 45 42 43)");
  
    std::vector<AR> symBase;
    std::vector<char> symBaseLabels;
    
    //symBase.push_back(reflect);   symBaseLabels.push_back('r');
    symBase.push_back(spin_l);    symBaseLabels.push_back('l');
    symBase.push_back(spin_d);    symBaseLabels.push_back('d');

    std::map<ArrayRep, ElementDescriptor> Smap;

    AR::origin.getGeneratedGroup(symBase, symBaseLabels, Smap);

    for(auto p : Smap) {
	AR perm = p.first;
	vec.push_back(perm);
    }
}

void getOandISymVec(std::vector<AR> &vec) {
    AR reflect("(326 514)(32 51)(324 516)(36 54)(34 56)(316 524)(31 52)(314 526)(623 415)(63 45)(613 425)(62 41)(61 42)(625 413)(65 43)(615 423)(136 245)(13 25)(134 256)(16 24)(14 26)(156 234)(15 23)(145 236)");
    AR spin_l("(136 623 234 413)(13 63 23 43)(16 62 24 41)(156 625 245 415)(15 65 25 45)(145 615 256 425)(14 61 26 42)(134 613 236 423)(516 526 524 514)(316 326 324 314)(36 32 34 31)(56 52 54 51)");
    AR spin_d("(136 516 256 326)(156 526 236 316)(314 145 524 234)(324 134 514 245)(36 16 56 26)(32 13 51 25)(34 14 54 24)(31 15 52 23)(61 65 62 63)(615 625 623 613)(413 415 425 423)(41 45 42 43)");
  
    std::vector<AR> symBase;
    std::vector<char> symBaseLabels;
    
    symBase.push_back(reflect);   symBaseLabels.push_back('r');
    symBase.push_back(spin_l);    symBaseLabels.push_back('l');
    symBase.push_back(spin_d);    symBaseLabels.push_back('d');

    std::map<ArrayRep, ElementDescriptor> Smap;

    AR::origin.getGeneratedGroup(symBase, symBaseLabels, Smap);

    for(auto p : Smap) {
	AR perm = p.first;
	vec.push_back(perm);
    }
}


void loadCornerData() {
    std::vector<AR> OandISymVec;
    getOandISymVec(OandISymVec);

    fflush(stdout);
    
    printf("OandISymVec.size() = %lu\n", OandISymVec.size());
    
    std::set<CornerStore> corner_manhatten;

    FILE *f = fopen("corners.asci.data", "ro");
    assert(f);

    char line[5000];

    int cnt=0;
    int cnt2=0;
    while(fgets(line, 5000, f)) {
	char *str[5];
       	if(memcmp(line, "CUBE_OandI:", strlen("CUBE_OandI:")) != 0) continue;

	int j=0;
	int tok=0;
	int space=1;
	//printf("eh\n");
	while(line[j] != '\0') {
	    if((space == 1) && (!isspace(line[j]))) {
		str[tok] = &line[j];
		tok++;
		space = 0;
		if(tok > 4) break;
	    }
	    else if (isspace(line[j])) {
		space = 1;
	    }
	    j++;
	}
	//printf("ah [%s][%s][%s][%s][%s]\n", str[0], str[1], str[2], str[3], str[4]);
	
	cnt2++;
	int steps = atoi(str[1]);
	int degeneracy = atoi(str[3]);

	//printf("ach %s\n", str[4]);
	AR x(str[4]);
	for(auto S : OandISymVec) {
	    AR conjugate = (-S) * x * S;
	    
	    CornerStore cs(conjugate,steps);
	    corner_manhatten.insert(cs);
	    
	    cnt++;
	    if(cnt % 1000000 == 0) printf("cnt=%d %d\n",cnt, cnt2);
	}
    }
    printf("corners.size() = %lu\n", corner_manhatten.size());
    fclose(f);

    int fd = open("cornerstore.bin", O_WRONLY | O_CREAT);
    assert(fd > 0);

    for(auto cs : corner_manhatten) {
	int ret = write(fd, (char *)&cs.data, sizeof(cs.data));
	assert(ret == sizeof(cs.data));
    }
    close(fd);
}


void loadCornerStore(std::vector<CornerStore> &cornerStore) {
    time_t stime = time(NULL);
    const int readcount=1024*1024*50;

    int sz = 705438720;
    u_int64_t *store = (u_int64_t *)malloc(sz);
    
    int fd = open("cornerstore.bin", O_RDONLY);
    assert(fd > 0);

    int offset=0;
    int left=sz;
    char *buff = (char *)store;
    
    while(left) {
	int ret = read(fd, buff+offset, left);
	assert(ret > 0);
	offset += ret;
	left -=  ret;
    }
    time_t ntime = time(NULL);
    printf("got buffer (%lu sec)\n", ntime - stime);
    stime = ntime;

    for(int i=0;i<sz/8;i++) {
       	CornerStore x(store[i]);
	cornerStore.push_back(x);
    }

    free(buff);
    
    ntime = time(NULL);
    printf("cornerStore.size() = %lu   (%lu secs)\n", cornerStore.size(), ntime - stime);
    stime = ntime;
    
    int sorterror=0;
    for(int i=1;i<cornerStore.size();i++) {
	if(cornerStore[i] < cornerStore[i-1]) {
	    printf("not sorted\n");
	    sorterror++;
	}
    }
}



void testNodes(std::vector<CornerStore> &cornerStore) {
    std::vector<std::vector<AR>> nodes;
    std::random_device r;
    std::default_random_engine e(r());

    std::vector<AR> bases = { AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax, AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };
    
    std::vector<AR> v; 
    nodes.push_back(v);


    AR x = AR::random(e); 
    nodes[0].push_back(x);
    CornerStore cs(x,0);

    auto val = std::lower_bound(cornerStore.begin(), cornerStore.end(), cs);
    CornerStore found = *val;
    AR found_AR = found.build();

    printf("x:   %s\n", x.dump2CStr().c_str());
    printf("f:%s\n", found_AR.dump2CStr().c_str());
    printf("steps=%d\n", found.getCount());
}

// returns length to arrive at node
int getAllSolutions(AR &node,
		    std::vector<CornerStore> &cornerStore,
		    std::vector<AR> &bases,
		    std::vector<char> &basenames,
		    std::vector<std::string> &solutions) {
    CornerStore orig(node, 0);

    auto val = std::lower_bound(cornerStore.begin(), cornerStore.end(), orig);
    orig = *val;   // adds in the count...
    int orig_length = orig.getCount();
    
    if(orig_length == 0) {
	solutions.push_back("");
	return 0;
    }

    for(u_int32_t i=0;i<bases.size();i++) {
	AR pnode = bases[i] * node;
	CornerStore pcs(pnode, 0);
	auto val = std::lower_bound(cornerStore.begin(), cornerStore.end(), pcs);
	pcs = *val;   // adds in the count...
	int prev_length = pcs.getCount();

	if(prev_length != (orig_length - 1)) continue;

	// We've got a correct move...
	std::vector<std::string> mysolutions;
	getAllSolutions(pnode, cornerStore, bases, basenames, mysolutions);

	for(auto s : mysolutions) {
	    solutions.push_back(basenames[i]+s);
	}
    }
    return orig_length;
}

AR applyString(AR x,
	       std::string str,
	       std::vector<AR> &bases,
	       std::vector<char> &basenames) {
    int c2Base[256];
    memset(c2Base,0,sizeof(c2Base));
    
    for(int i=0;i<bases.size();i++) {
	c2Base[basenames[i]] = i;
    }
    
    AR curr = x;
    for(int i = 0;i<str.length();i++) {
	//printf("i=%d\n",i);
	//printf("str[i]=%d\n",str[i]);
	int b = c2Base[str[i]];
	//printf("b=%d\n", b);
	AR base = bases[b];
	curr = base * curr;
    };
    
    return curr;
}


void testSolutions(AR x, std::vector<AR> &bases, std::vector<char> &basenames,  std::vector<CornerStore> & cornerStore) {
    std::vector<std::string> solutions;
    int len = getAllSolutions(x,
			      cornerStore,
			      bases,
			      basenames,
			      solutions);

    // printf("%s : len=%d,  nsolutions=%lu\n", x.dump2CStr().c_str(), len, solutions.size());

    //printf("sol: %s\n", solutions[0].c_str());
    x = -(applyString(AR::origin, solutions[0], bases, basenames));
    solutions.clear();
    int len2 = getAllSolutions(x, cornerStore, bases, basenames, solutions);
    
    int same_solutions=0;
    int different_solutions=0;
    for(auto s : solutions) {
	//printf("-->%s\n", s.c_str());
	AR test = applyString(AR::origin, s, bases, basenames);
	//	printf("  x = %s\n",x.dump2CStr().c_str());
	//printf(" -s = %s\n",(-test).dump2CStr().c_str());

	if((-test) == x) {
	    same_solutions++;
	}
	else {
	    different_solutions++;
	}

	
    }
    printf("%4d  %8d %8d %8d\n", len, same_solutions, different_solutions, same_solutions + different_solutions);
}

    
void testManySolutions(AR &x, std::vector<AR> &bases, std::vector<char> &basenames,  std::vector<CornerStore> & cornerStore) {

    std::vector<std::vector<AR>> nodes;
    std::random_device r;
    std::default_random_engine e(r());

    for(int i=0;i<10000;i++) {
	AR x = AR::random(e);
	testSolutions(x, bases, basenames, cornerStore);
    }
}

void testHeuristics()
{
    std::random_device r;
    std::default_random_engine e(r());
    std::vector<AR> bases = { AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax, AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };
    std::vector<char> basenames = { 'r', 'l', 't', 'b', 'f', 'x', 'R', 'L', 'T', 'B', 'F', 'X' };

    std::uniform_int_distribution<int> rbases(1,6);
    std::uniform_int_distribution<int> rnbases(1,30);

    Heuristic h;
    h.init();

    int cnts[30];
    int hcnts[30];
    memset(cnts, 0, sizeof(cnts));
    memset(hcnts, 0, sizeof(hcnts));
    int q=0;
    for(auto x : h.cubeWithCountsSymSuppressed) {
	cnts[x.cnt]++;
	//int man = h.Manhatten(x.x);
	//hcnts[man]++;

	//if(q < 400000)
	//  printf("%d %d\n", x.cnt, man);
	
	q++;
	if(q % 100000 == 0) {
	    printf("q=%d\n",q);
	}
	//     for(int i=0;i<12;i++) {
	// 	printf("cnt[%d] = %d   mhttn = %d\n", i,cnts[i],hcnts[i]);
	//     }
	// }
    }
    for(int i=0;i<12;i++) {
	printf("cnt[%d] = %d   mhttn = %d\n", i,cnts[i],hcnts[i]);
    }
    
    for(int i=0;i<10;i++) {
	std::string name;
	
	int len = rnbases(e);
	AR x = AR::origin;

	for(int j=0; j<len;j++) {
	    int base = rbases(e);
	    x = bases[base] * x;
	    name += basenames[base];
	}

	int cnt = h.Manhatten(x);
	printf("%30s : %d - %d\n", name.c_str(), len, cnt);
	
    }
}

bool depthFirstHeuristic(AR &x, Heuristic &h, std::vector<AR> &bases, std::vector<char> &basenames, std::string &path, int threashold, std::string &solution) {

    if(x == AR::origin) {
	solution = path;
	return true;
    }

    int hcnt = h.Manhatten(x);
    int dcnt = path.size();
    if(hcnt + dcnt > threashold) return false;
    
    for(int i=0;i<bases.size();i++) {
	AR nx = bases[i] * x;
	std::string npath = path + basenames[i];

	bool found = depthFirstHeuristic(nx, h, bases, basenames, npath, threashold, solution);
	if(found) return true;
    }

    return false;
}


std::string solveHeuristic(AR &x, Heuristic &h, std::vector<AR> &bases, std::vector<char> &basenames)
{
    bool found;
    std::string solution;

    time_t starttime = time(NULL);
    std::string NONE="";
    for(int thresh=0;thresh<30;thresh++) {
	time_t lasttime = time(NULL);
	found = depthFirstHeuristic(x,h,bases,basenames,NONE,thresh, solution);
	time_t now = time(NULL);
	printf("thresh = %d, total time=%ld  time=%ld   %s\n",
	       thresh, now - starttime, now - lasttime, found ? "found" : "not found");
	if(found) break;
    }
    return solution;
}

void testSolveHeuristics() {
    std::random_device r;
    std::default_random_engine e(r());
    std::vector<AR> bases = { AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax, AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };
    std::vector<char> basenames = { 'r', 'l', 't', 'b', 'f', 'x', 'R', 'L', 'T', 'B', 'F', 'X' };
    
    std::uniform_int_distribution<int> rbases(1,6);
 
    Heuristic h;
    h.init();

    std::string solution;

    for(int i=0;i<10;i++) {
	AR x = AR::random(e);
	
	solution = solveHeuristic(x, h, bases, basenames);

	assert(x == -applyString(AR::origin, solution, bases, basenames));
	solution = solveHeuristic(AR::origin, h, bases, basenames);
	printf("%2ld (%30s)   SOLUTION", solution.size(), solution.c_str());

    }
    
	/*
    printf("----: origin: \n");
    solution = solveHeuristic(AR::origin, h, bases, basenames);
    printf("----: (%30s)\n-----------------------------\n", solution.c_str());

    printf("----: r: \n");
    solution = solveHeuristic(AR::Ar, h, bases, basenames);
    printf("----: (%30s)\n-----------------------------\n", solution.c_str());

    printf("----: rr: \n");
    AR x = AR::Ar * AR::Ar;
    solution = solveHeuristic(x,h, bases, basenames);
    printf("----: (%30s)\n-----------------------------\n", solution.c_str());

    x = AR::Ax * AR::Af * AR::Ar * AR::Al * AR::Ax * AR::AB;
    printf("----: xfrLxB: \n");
    solution = solveHeuristic(x, h, bases, basenames);
    printf("----: (%30s)\n-----------------------------\n", solution.c_str());

    printf("%s =?\n%s\n", x.dump2CStr().c_str(), (-applyString(AR::origin, solution, bases, basenames)).dump2CStr().c_str());
	*/
	
}

    
int main(int argc, char *argv[]) {
    std::vector<AR> bases = { AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax, AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };
    std::vector<char> basenames = { 'r', 'l', 't', 'b', 'f', 'x', 'R', 'L', 'T', 'B', 'F', 'X' };
    
    //testShuffle();
    //testSizes();
    //testPermutationMap();
    //testValidity();
    //testRandom();
    //testCornerStore();

    /*
    std::vector<CornerStore> cornerStore;
    loadCornerStore(cornerStore);
    AR x = AR::Ax*AR::Ar*AR::AT*AR::AT;
    testManySolutions(x, bases, basenames, cornerStore);
    */

    //testHeuristics();
    testSolveHeuristics();
   
}
