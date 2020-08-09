#include "Permutation.h"
#include "ArrayRep.h"
#include <unistd.h>
#include <fcntl.h>

typedef ArrayRep AR;

int main(int argc, char *argv[]) {
    std::vector<ArrayRepCount> bin;

    u_int8_t data[49];
    int fd = open("generateDeep.bin", O_RDONLY, 0666);
    for(;;) {
	int ret = read(fd, data, 49);
	if(ret != 49) break;

	ArrayRepCount x(&data[0], data[48]);
	bin.push_back(x);
    }

    printf("BIN[%lu]\n", bin.size());


    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> dist(0,bin.size()-1);

    printf("start\n");
    time_t t = time(NULL);
    int nn = bin.size();
    u_int64_t twists=0;
    for(int i=0;i<nn;i++) {
	int x = dist(e);
	int cnt = bin[x].getCount(bin);
	twists += cnt;
	//printf("cnt %d\n", cnt);
    }
    printf("et = %lu tot=%lu twists = %lu\n", time(NULL) - t, bin.size(), twists);
    
    sleep(1000);
}
