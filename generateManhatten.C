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
    // Permutation::Pf.dump();
    // Permutation::PF.dump();
    // printf("Pf.nswaps()=%d\n", Permutation::Pf.nswaps());

    // ArrayRep S = AR::Af * AR::AX;
    // ArrayRep z = AR::Ar * AR::At;
    // ArrayRep zp = AR::At * AR::Al;
    // ArrayRep ZZ = -S * zp * S;
    // ArrayRep ZZZ = S * zp * -S;
    // printf("%s\n%s\n%s\n%s\n",
    // 	   z.dump2CStr().c_str(),
    // 	   ZZ.dump2CStr().c_str(),
    // 	   ZZZ.dump2CStr().c_str(),
    // 	   S.dump2CStr().c_str());
  
    std::vector<std::pair<int, int>> six_sides_vec_origin1 = { 
	{16,16},{61,61},
	{13,13},{31,31},
	{14,14},{41,41},
	{15,15},{51,51},
	{45,45},{54,54},
	{43,43},{34,34}
    };
    std::vector<std::pair<int, int>> six_sides_vec_origin2 = {
    	{24,24},{42,42},
	{23,23},{32,32},
	{26,26},{62,62},
	{25,25},{52,52},
	{63,63},{36,36},
	{56,56},{65,65}
    };
    
    std::vector<std::pair<int, int>> eight_corners_vec_origin = { 
	{136,136},{134,134},{156,156},{145,145},
	{234,234},{236,236},{245,245},{256,256}
    };

    //const char *fn = "sidestore1.bin";
    //ArrayRep active_origin(six_sides_vec_origin1);
    const char *fn = "sidestore2.bin";
    ArrayRep active_origin(six_sides_vec_origin2);
    // const char *fn = "cornerstore.bin"
    // ArrayRep eight_corners_origin(eight_corners_vec_origin);

    
    std::vector<ArrayRep> bases = { AR::Af, AR::Ar, AR::At, AR::Ax, AR::Ab, AR::Al,
				    AR::AF, AR::AR, AR::AT, AR::AX, AR::AB, AR::AL 
    };
    
    std::vector<char> basenames = { 'f','r','t','x','b','l',
				    'F','R','T','X','B','L'
    };

    printf("active: %s\n", active_origin.dump2DStr().c_str());

    std::map<ArrayRep, u_int8_t> results;
    results.insert({ active_origin, 0 });
    std::vector<ArrayRep> todo[2];
    int level = 0,  curr_todo = 0,  next_todo = 1;
    todo[curr_todo].push_back(active_origin);

    printTime(stderr);fprintf(stderr,"\n");
    
    while(todo[curr_todo].size() > 0) {
	level++;
	AR::getGeneratedGroupLevelCnts(level, bases, results, todo[curr_todo], todo[next_todo]);

	printTime(stderr); fprintf(stderr,"  sides: level=%d results: %12lu todo: %12lu\n", level, results.size(), todo[next_todo].size());

	curr_todo = (curr_todo == 1) ? 0 : 1;
	next_todo = (next_todo == 1) ? 0 : 1;
    }

    std::set<SideStore> side_manhatten;

    printf("results.size() = %lu\n", results.size());
    for(auto x : results) {
	AR xx = x.first;
	int cnt = x.second;

   	//printf("ss\n");
	SideStore ss(xx, cnt);
	side_manhatten.insert(ss);
    }
    printf("sides.size() = %lu\n", side_manhatten.size());

    int fd = open(fn, O_WRONLY | O_CREAT,0644);
    assert(fd > 0);

    for(auto cs : side_manhatten) {
	int ret = write(fd, (char *)&cs.data, sizeof(cs.data));
	assert(ret == sizeof(cs.data));
    }
    close(fd);
}
