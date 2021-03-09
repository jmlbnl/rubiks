#include "Permutation.h"
#include "ArrayRep.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int last_time=-1;
void printTime(FILE *ff) {
    time_t newtime = time(NULL);
    fprintf(ff, "elapsed time: %3lu sec:   ", newtime - last_time);
    last_time = newtime;
}

typedef ArrayRep AR;

int main(int argc, char *argv[]) {
    SideStore Af(AR::Af, 0);
    SideStore Ar(AR::Ar, 0);
    SideStore At(AR::At, 0);
    SideStore Ax(AR::Ax, 0);
    SideStore Ab(AR::Ab, 0);
    SideStore Al(AR::Al, 0);

    std::vector<SideStore> bases = { Af, Ar, At, Ax, Ab, Al,
				     -Af, -Ar, -At, -Ax, -Ab, -Al };
    
    std::vector<char> basenames = { 'f','r','t','x','b','l',
				    'F','R','T','X','B','L'
    };

    SideStore origin;
    std::set<SideStore> results;
    results.insert(origin);
    
    std::vector<SideStore> todo[2];
    int level = 0,  curr_todo = 0,  next_todo = 1;
    todo[curr_todo].push_back(origin);

    printTime(stderr);fprintf(stderr,"\n");
    
    while(todo[curr_todo].size() > 0) {
	level++;
	SideStore::getGeneratedGroupLevelCnts(level, bases, results, todo[curr_todo], todo[next_todo]);

	printTime(stderr); fprintf(stderr,"  sides: level=%d results: %12lu todo: %12lu\n", level, results.size(), todo[next_todo].size());

	curr_todo = (curr_todo == 1) ? 0 : 1;
	next_todo = (next_todo == 1) ? 0 : 1;

	if(level>=8) break;
    }

    if(0) {
	for(auto cs : results) {
	    printf("%2lu %s\n", cs.data & 0xf, cs.dump2CStr().c_str());
	}
    }

    
    if(1) {
	char *fn = "sideStore-8_210307.bin";
	int fd = open(fn, O_WRONLY | O_CREAT,0644);
	assert(fd > 0);
	
	for(auto cs : results) {
	    int ret = write(fd, (char *)&cs.data, sizeof(cs.data));
	    assert(ret == sizeof(cs.data));
	}
	close(fd);
    }	
}
