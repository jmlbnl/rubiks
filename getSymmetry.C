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
    
    AR reflect("(326 514)(32 51)(324 516)(36 54)(34 56)(316 524)(31 52)(314 526)(623 415)(63 45)(613 425)(62 41)(61 42)(625 413)(65 43)(615 423)(136 245)(13 25)(134 256)(16 24)(14 26)(156 234)(15 23)(145 236)");
    
    AR spin_l("(136 623 234 413)(13 63 23 43)(16 62 24 41)(156 625 245 415)(15 65 25 45)(145 615 256 425)(14 61 26 42)(134 613 236 423)(516 526 524 514)(316 326 324 314)(36 32 34 31)(56 52 54 51)");
    
    AR spin_d("(136 516 256 326)(156 526 236 316)(314 145 524 234)(324 134 514 245)(36 16 56 26)(32 13 51 25)(34 14 54 24)(31 15 52 23)(61 65 62 63)(615 625 623 613)(413 415 425 423)(41 45 42 43)");
  
    std::vector<AR> symBase;
    std::vector<char> symBaseLabels;

    
    symBase.push_back(reflect);   symBaseLabels.push_back('r');
    symBase.push_back(spin_l);    symBaseLabels.push_back('l');
    symBase.push_back(spin_d);    symBaseLabels.push_back('d');

    AR x;
    std::map<ArrayRep, ElementDescriptor> SVec;

    x.getGeneratedGroup(symBase, symBaseLabels, SVec);
    int symIdx = 0;
    for(auto p : SVec) {
	symIdx++;
	AR perm = p.first;
	ElementDescriptor ed = p.second;
	printf("SYM: %d %s %s\n", symIdx, ed.name.c_str(), perm.dump2CStr().c_str());
    }


    
    std::vector<AR> base = baseVec[0];
    std::vector<char> baseLabels = baseVecLabels[0];

    symIdx = 0;
    for(auto p : SVec) {
	symIdx++;
	AR S = p.first;
	ElementDescriptor ed = p.second;
	printf("REP: ");
	for(int i=0;i<base.size();i++) {
	    AR x = (-S) * base[i] * S;

	    int cidx=-1;
	    for(int j=0;j<base.size();j++) {
		if(x == base[j]) {
		    cidx = j;
		    break;
		}
	    }

	    assert(cidx != -1);

	    printf("%c == %c : ", baseLabels[i], baseLabels[cidx]);
	}
	printf("%d\n", symIdx);
    }
}
