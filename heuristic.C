#include "Permutation.h"
#include "ArrayRep.h"
#include "heuristic.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void Heuristic::init() {
    loadCubes(cubeWithCountsSymSuppressed);
    loadCornerStore(cornerStore);
    loadSideStore("sidestore1.bin", sideStoreFront);
    loadSideStore("sidestore2.bin", sideStoreBack);
}

int Heuristic::Manhatten(ArrayRep &x) {
    ArrayRep front = x;
    ArrayRep back = x;

    std::vector<int> frontPositions = {	16,61,13,31,14,41,15,51,45,54,43,34 };
    std::vector<int> backPositions = { 24,42,23,32,26,62,25,52,63,36,56,65 };
    std::sort(frontPositions.begin(), frontPositions.end());
    std::sort(backPositions.begin(), backPositions.end());
    
    front.maskLabelPositions(backPositions);
    back.maskLabelPositions(frontPositions);

    CornerStore cs(x,0);
    SideStore ssf(front, 0);
    SideStore ssb(back, 0);

    auto csit = std::lower_bound(cornerStore.begin(), cornerStore.end(), cs);
    auto ssfit = std::lower_bound(sideStoreFront.begin(), sideStoreFront.end(), ssf);
    auto ssbit = std::lower_bound(sideStoreBack.begin(), sideStoreBack.end(), ssb);

    ArrayRep search = ssf.build();
    ArrayRep found = (*ssfit).build();
    // printf("-front-------------\n%s\n<->\n%s\n",
    // 	   search.dump2DStr().c_str(),
    // 	   found.dump2DStr().c_str());
    assert(*csit == cs);
    assert(*ssfit == ssf);
    assert(*ssbit == ssb);

    int cs_val = (*csit).getCount();
    int ssf_val = (*ssfit).getCount();
    int ssb_val = (*ssbit).getCount();

    //printf("corners -> %2d,  ssf -> %2d,   ssb -> %2d   :", cs_val, ssf_val, ssb_val);

    int biggest = cs_val;
    if(ssf_val > biggest) biggest = ssf_val;
    if(ssb_val > biggest) biggest = ssb_val;
    return biggest;
}

//int Heuristic::BackManhatten(const ArrayRep &x) {
//}

void Heuristic::loadCubes(std::vector<ArrayRepCnt> &cubes) {
    time_t stime = time(NULL);
    
    int sz = 820757056;
    const char *fn = "generateDeep.bin";
    
    u_int8_t *store = (u_int8_t *)malloc(sz);
    
    int fd = open(fn, O_RDONLY);
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

    for(int i=0;i<sz/49;i++) {
       	ArrayRepCnt x(&store[i*49]);
	//printf("i=%d cnt=%d\n", x.cnt, store[i*49 + 48]);
	cubes.push_back(x);
    }

    free(buff);
    
    ntime = time(NULL);
    printf("cubes.size() = %lu   (%lu secs)\n", cubes.size(), ntime - stime);
    stime = ntime;
   
    int sorterror=0;
    for(int i=1;i<cubes.size();i++) {
	if(cubes[i].x < cubes[i-1].x) {
	    printf("not sorted\n");
	    sorterror++;
	}
    }
    
}

void Heuristic::loadSideStore(const char *fn, std::vector<SideStore> &sStore) {
    time_t stime = time(NULL);
    
    int sz = 340623360;;
    u_int64_t *store = (u_int64_t *)malloc(sz);
    
    int fd = open(fn, O_RDONLY);
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
       	SideStore x(store[i]);
	sStore.push_back(x);
    }

    free(buff);
    
    ntime = time(NULL);
    printf("%s: sStore.size() = %lu   (%lu secs)\n", fn, sStore.size(), ntime - stime);
    stime = ntime;
    /*
    int sorterror=0;
    for(int i=1;i<sStore.size();i++) {
	if(sStore[i] < sStore[i-1]) {
	    printf("not sorted\n");
	    sorterror++;
	}
    }
    */
}

void Heuristic::loadCornerStore(std::vector<CornerStore> &cStore) {
    time_t stime = time(NULL);
    
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
	cStore.push_back(x);
    }

    free(buff);
    
    ntime = time(NULL);
    printf("cStore.size() = %lu   (%lu secs)\n", cStore.size(), ntime - stime);
    stime = ntime;

    /*
    int sorterror=0;
    for(int i=1;i<cStore.size();i++) {
	if(cStore[i] < cStore[i-1]) {
	    printf("not sorted\n");
	    sorterror++;
	}
    }

    ntime = time(NULL);
    printf("checked sorting   (%lu secs)\n", ntime - stime);
    stime = ntime;
    */
}
