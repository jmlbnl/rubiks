#include "Permutation.h"
#include "ArrayRep.h"
#include <unistd.h>
#include <fcntl.h>

typedef ArrayRep AR;

int last_time=-1;
void printTime() {
    time_t newtime = time(NULL);
    printf("elapsed time: %3lu sec:   ", newtime - last_time);
    last_time = newtime;
}

std::vector<ArrayRep> getSVec() {
    AR reflect("(326 514)(32 51)(324 516)(36 54)(34 56)(316 524)(31 52)(314 526)(623 415)(63 45)(613 425)(62 41)(61 42)(625 413)(65 43)(615 423)(136 245)(13 25)(134 256)(16 24)(14 26)(156 234)(15 23)(145 236)");
    
    AR spin_l("(136 623 234 413)(13 63 23 43)(16 62 24 41)(156 625 245 415)(15 65 25 45)(145 615 256 425)(14 61 26 42)(134 613 236 423)(516 526 524 514)(316 326 324 314)(36 32 34 31)(56 52 54 51)");
    
    AR spin_d("(136 516 256 326)(156 526 236 316)(314 145 524 234)(324 134 514 245)(36 16 56 26)(32 13 51 25)(34 14 54 24)(31 15 52 23)(61 65 62 63)(615 625 623 613)(413 415 425 423)(41 45 42 43)");
  
    std::vector<AR> symBase;
    std::vector<char> symBaseLabels;
    
    symBase.push_back(reflect);   symBaseLabels.push_back('r');
    symBase.push_back(spin_l);    symBaseLabels.push_back('l');
    symBase.push_back(spin_d);    symBaseLabels.push_back('d');

    std::map<ArrayRep, ElementDescriptor> SVec;
    AR::origin.getGeneratedGroup(symBase, symBaseLabels, SVec);
    int symIdx = 0;
    std::vector<AR> result;
    for(auto p : SVec) {
	symIdx++;
	AR perm = p.first;
	result.push_back(perm);
	
	ElementDescriptor ed = p.second;
	//printf("SYM: %d %s\n", symIdx, ed.name.c_str());//, perm.dump2CStr().c_str());
    }

    /*
      std::map<ArrayRep, u_int8_t> svec2;
      AR::getGeneratedGroupCnts(symBase, svec2);
      printf("svec2: %lu\n", svec2.size());
    */

   
    return result;
}
    
int main(int argc, char *argv[]) {
    std::vector<AR> SVec = getSVec();
    printf("There are %lu symmetry operators\n", SVec.size());

    std::vector<AR> bases = {
	AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax,
	AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };

    std::map<ArrayRep, u_int8_t> results, results_sym;

    results.insert({ AR::origin, 0 });
    results_sym.insert({ AR::origin, 0 });
    std::vector<ArrayRep> todo[2];
    std::vector<ArrayRep> todo_sym[2];
    int level=0;
    int curr_todo = 0;
    int next_todo = 1;
    todo[curr_todo].push_back(AR::origin);
    todo_sym[curr_todo].push_back(AR::origin);

    while(level < 9) {
	level++;
	bool save = true;
	if(level == 9) save = false;
	AR::getGeneratedGroupLevelCntsSym(level,bases,results_sym,todo_sym[curr_todo],todo_sym[next_todo],SVec, save);
	printTime(); printf("  SYM: level=%d results: %12lu todo: %12lu\n", level, results_sym.size(), todo_sym[next_todo].size());

	curr_todo = (curr_todo == 1) ? 0 : 1;
	next_todo = (next_todo == 1) ? 0 : 1;
    }
    
    int fd = open("generateDeep.bin", O_CREAT | O_WRONLY , 0666);
    assert(fd > 0);
    for(auto p : results_sym) {
	AR x = p.first;
	u_int8_t cnt = p.second;
	int ret = write(fd, x.data, sizeof(x.data));
	assert(ret == sizeof(x.data));
	ret = write(fd, &cnt, sizeof(cnt));
	assert(ret == sizeof(cnt));
    }
    close(fd);
}
