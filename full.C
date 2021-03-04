#include "Permutation.h"
#include "ArrayRep.h"

typedef ArrayRep AR;

int main(int argc, char *argv[]) {
    // Permutation::Pf.dump();
    // Permutation::PF.dump();
    // printf("Pf.nswaps()=%d\n", Permutation::Pf.nswaps());

    ArrayRep S = AR::Af * AR::AX;
    ArrayRep z = AR::Ar * AR::At;
    ArrayRep zp = AR::At * AR::Al;
    ArrayRep ZZ = -S * zp * S;
    ArrayRep ZZZ = S * zp * -S;
    printf("%s\n%s\n%s\n%s\n",
	   z.dump2CStr().c_str(),
	   ZZ.dump2CStr().c_str(),
	   ZZZ.dump2CStr().c_str(),
	   S.dump2CStr().c_str());
  

    
    if(0) {
	//std::vector<std::pair<int, int>> cube = { 
	//	{16, 16}, {13,13}, {14,14}, { 15,15 },
	//	{45, 45}, {43, 43}
	//};
	std::vector<std::pair<int, int>> cube = { 
	    {136,136},{134,134},{156,156},{145,145},
	    {234,234},{236,236},{245,245},{256,256}
	};


    
	ArrayRep z(cube);
    
	std::vector<ArrayRep> bases = { AR::Af, AR::Ar, AR::At, AR::Ax, AR::Ab, AR::Al,
					AR::AF, AR::AR, AR::AT, AR::AX, AR::AB, AR::AL 
	};

	std::vector<char> basenames = { 'f','r','t','x','b','l',
					'F','R','T','X','B','L'
	};
    
	std::map<ArrayRep, ElementDescriptor> result;

	z.getGeneratedGroup(bases, basenames, result);

	int n=0;int cnt = 0;
	for(auto p : result) {
	    AR perm = p.first;
	    ElementDescriptor ed = p.second;
	
	    cnt++;
	    n += ed.degeneracy;
	    printf("CUBE: %3lu %30s\n", ed.name.size(), ed.name.c_str());
	}
    
	printf("n=%lu\n", result.size());
    }
}
