#include "Permutation.h"
#include "ArrayRep.h"

typedef ArrayRep AR;

AR getBase(char twist) {
    switch(twist) {
    case 'r':
	return AR::Ar;
    case 't':
	return AR::At;
    case 'f':
	return AR::Af;
    case 'l':
	return AR::Al;
    case 'b':
	return AR::Ab;
    case 'x':
	return AR::Ax;
    case 'R':
	return AR::AR;
    case 'T':
	return AR::AT;
    case 'F':
	return AR::AF;
    case 'L':
	return AR::AL;
    case 'B':
	return AR::AB;
    case 'X':
	return AR::AX;
    }
    return AR::origin;
}

char flipCase(char x) {
    if(isupper(x)) return tolower(x);
    return toupper(x);
}

int main(int argc, char *argv[]) {

    std::vector<std::vector<AR>> baseVec;
    std::vector<std::vector<char>> baseVecLabels;
    
    FILE *f = fopen("replacements.txt", "ro");
    char str[256];
    while((fgets(str, 256, f) != NULL)) {
	if(str[0] == '#') continue;

	char rr,rt,rf,rl,rb,rx;
	char r,t,f,l,b,x;
	sscanf(str, "%c %c %c %c %c %c %c %c %c %c %c %c",
	       &r,&rr,
	       &t,&rt,
	       &f,&rf,
	       &l,&rl,
	       &b,&rb,
	       &x,&rx);

	std::vector<AR> base;
	base.push_back(getBase(rr));
	base.push_back(-getBase(rr));
	base.push_back(getBase(rt));
	base.push_back(-getBase(rt));
	base.push_back(getBase(rf));
	base.push_back(-getBase(rf));
	base.push_back(getBase(rl));
	base.push_back(-getBase(rl));
	base.push_back(getBase(rb));
	base.push_back(-getBase(rb));
	base.push_back(getBase(rx));
	base.push_back(-getBase(rx));
	baseVec.push_back(base);

	std::vector<char> labels;
	labels.push_back(rr);
	labels.push_back(flipCase(rr));
	labels.push_back(rt);
	labels.push_back(flipCase(rt));
	labels.push_back(rf);
	labels.push_back(flipCase(rf));
	labels.push_back(rl);
	labels.push_back(flipCase(rl));
	labels.push_back(rb);
	labels.push_back(flipCase(rb));
	labels.push_back(rx);
	labels.push_back(flipCase(rx));
	baseVecLabels.push_back(labels);
    }

    for(int i=0;i<baseVec.size();i++) {
	printf("base[%d] = ",i);
	for(char c: baseVecLabels[i]) {
	    printf(" %c ", c);
	}
	printf("\n");
    }

    for(int i=1;i<48;i++) {
	AR vec = baseVec[i][1] * baseVec[i][3] * baseVec[i][5];
	printf("%c%c%c:%s\n",baseVecLabels[i][5], baseVecLabels[i][3], baseVecLabels[i][1], vec.dump2CStr().c_str());

	fflush(stdout);
	
	std::map<AR, ElementDescriptor> result;
	//vec.searchForMe(baseVec[0],
	//baseVecLabels[0],
	//	    result);

	AR conjugate = baseVec[0][1] * baseVec[0][3] * baseVec[0][5];
	vec.searchForConjigisor(10,
				conjugate,
				baseVec[i],
				baseVecLabels[i],
				result);

	for(auto p : result) {
	    AR perm = p.first;
	    ElementDescriptor ed = p.second;
	    printf("  conjigizor: %s:%s\n",ed.name.c_str(), perm.dump2CStr().c_str());
	}
    }
}
