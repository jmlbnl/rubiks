#include "Permutation.h"
#include "ArrayRep.h"

typedef ArrayRep AR;

class Payload {
    u_int8_t x[48];
};

int main(int argc, char *argv[]) {
    std::random_device r;
    std::default_random_engine e(r());
    //std::uniform_int_distribution<int> dice(1,6);
    //std::vector<int> cards({1,2,3,4,5,6});

    printf("Sizeof(AR) = %d\n", sizeof(AR));

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

  
    //for(int i=0;i<20;i++) {
    //	std::shuffle(cards.begin(), cards.end(), e);
    //	printf("(");
    //	for(auto x : cards) {
    //	    printf("%d ", x);
    //	};
    //	printf(") 0x%x\n", r());
    //}
    //printf("\n");
    
}
