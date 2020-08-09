#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include "Permutation.h"

Permutation Permutation::ODr("(1 3 2 5)","r");
Permutation Permutation::ODf("(3 4 5 6)","f");
Permutation Permutation::ODt("(1 4 2 6)","t");

// Define Static transformations!
Permutation Permutation::Cf("(134 145 156 136)(314 415 516 613)(316 413 514 615)","f");
Permutation Permutation::Cx("(234 236 256 245)(324 623 526 425)(326 625 524 423)","x");
Permutation Permutation::Cr("(413 423 425 415)(134 324 245 514)(145 314 234 524)","r");
Permutation Permutation::Cl("(623 613 615 625)(136 516 256 326)(156 526 236 316)","l");
Permutation Permutation::Ct("(314 316 326 324)(134 613 236 423)(136 623 234 413)", "t");
Permutation Permutation::Cb("(516 514 524 526)(156 415 245 625)(145 425 256 615)", "b");

Permutation Permutation::CF = -Cf;
Permutation Permutation::CX = -Cx;
Permutation Permutation::CR = -Cr;
Permutation Permutation::CL = -Cl;
Permutation Permutation::CT = -Ct;
Permutation Permutation::CB = -Cb;

//Permutation Permutation::UCf("(1 2 4 3)","f");
//Permutation Permutation::UCx("(5 6 8 7)","x");
//Permutation Permutation::UCr("(2 5 7 4)","r");
//Permutation Permutation::UCl("(1 3 8 6)","l");
//Permutation Permutation::UCt("(1 6 5 2)", "t");
//Permutation Permutation::UCb("(3 4 7 8)", "b");

Permutation Permutation::UCf("(136 134 145 156)","f");
Permutation Permutation::UCx("(234 236 256 245)","x");
Permutation Permutation::UCr("(134 234 245 145)","r");
Permutation Permutation::UCl("(236 136 156 256)","l");
Permutation Permutation::UCt("(236 234 134 136)","t");
Permutation Permutation::UCb("(156 145 245 256)","b");

Permutation Permutation::UCF = -UCf;
Permutation Permutation::UCX = -UCx;
Permutation Permutation::UCR = -UCr;
Permutation Permutation::UCL = -UCl;
Permutation Permutation::UCT = -UCt;
Permutation Permutation::UCB = -UCb;

Permutation Permutation::Pf("(13 14 15 16)(134 145 156 136)(31 41 51 61)(314 415 516 613)(316 413 514 615)","f");
Permutation Permutation::Px("(23 26 25 24)(234 236 256 245)(32 62 52 42)(324 623 526 425)(326 625 524 423)","x");
Permutation Permutation::Pr("(41 43 42 45)(413 423 425 415)(14 34 24 54)(134 324 245 514)(145 314 234 524)","r");
Permutation Permutation::Pl("(61 65 62 63)(615 625 623 613)(16 56 26 36)(136 516 256 326)(156 526 236 316)","l");
Permutation Permutation::Pt("(31 36 32 34)(314 316 326 324)(13 63 23 43)(134 613 236 423)(136 623 234 413)", "t");
Permutation Permutation::Pb("(51 54 52 56)(514 524 526 516)(15 45 25 65)(145 425 256 615)(156 415 245 625)", "b");

Permutation Permutation::PF = -Pf;
Permutation Permutation::PX = -Px;
Permutation Permutation::PR = -Pr;
Permutation Permutation::PL = -Pl;
Permutation Permutation::PT = -Pt;
Permutation Permutation::PB = -Pb;



Permutation::Permutation(std::string cycle_string, std::string nm) {
    std::vector<std::vector<int> > base_cycles;
    
    name = nm;
    
    int open = 0;
    int close = 0;
    

    //printf("cons:  %s %s\n", cycle_string.c_str(), nm.c_str());
    while(1) {
	open = cycle_string.find_first_of('(', open);
	if(open == std::string::npos) break;
	close = cycle_string.find_first_of(')', close);
	if(close == std::string::npos) break;
	if(open+1 == close) break;
	
	std::string cs = cycle_string.substr(open + 1, close-open-1);
	    
	base_cycles.push_back(readSingleCycle(cs));
	    
	open++;
	close++;
    }
    
    //printf("here\n");
    cycles = base_cycles;
    //printf("there\n");
    cycles = pairRepresentation(cycles);
    //	printf("ok\n");
    cycles = fullRepresentation(cycles);
    //sortedorder(cycles);
    //printf("yeah\n");
}

Permutation::Permutation(std::vector<std::vector<int>> x, std::string nm) {
    cycles = x;
    cycles = pairRepresentation(cycles);
    cycles = fullRepresentation(cycles);
    name = nm;
}

void Permutation::sortedorder(std::vector<std::vector<int>> &vec) {
    std::sort(vec.begin(), vec.end(), [](std::vector<int> &a, std::vector<int> &b) { return a[0] < b[0]; });
}

std::vector<int> Permutation::spinToMin(std::vector<int> cyc) {
    int minval = cyc[0];
    int minidx = 0;

    std::vector<int> outcyc;
	
    for(int i=1;i<cyc.size();i++) {
	if(cyc[i] < minval) {
	    minidx = i;
	    minval = cyc[i];
	}
    }

    for(int i=0;i<cyc.size();i++) {
	outcyc.push_back(cyc[(i+minidx) % cyc.size()]);
    }
    return outcyc;
}


std::vector<std::vector<int>> Permutation::pairRepresentation(std::vector<std::vector<int>> base_cycles) {
    std::vector<std::vector<int>> ret;
    
    for(int i=0;i<base_cycles.size();i++) {
	base_cycles[i] = spinToMin(base_cycles[i]);
	std::vector<std::vector<int>> decom = decompose(base_cycles[i]);
	
	for(std::vector<int> pp : decom) {
	    ret.push_back(pp);
	}
    }
    
    //sortedorder(ret);
    return ret;    
}

std::vector<std::vector<int>> Permutation::fullRepresentation(std::vector<std::vector<int>> pairRep) {
    std::vector<int> all;

    //printf("boo\n");
    for(std::vector<int> p : pairRep) {
	//  printf("hoo\n");
	for(int x : p) {
	    //printf("zoo\n");
	    if(std::find(all.begin(), all.end(), x) == all.end()) {
		all.push_back(x);
	    }
	}
    }

    //printf("aaaa\n");
    for(int i : all) {
	//printf("all:   %d\n", i);
    }

    std::vector<std::vector<int>> ncc;

    for(;;) {
	//printf("bbbbb\n");
	std::vector<int> nc;
	if(all.size() == 0) break;
	int x = all[0];
	int curr = x;
	//printf("aa\n");
	nc.push_back(x);
	//printf("bb\n");
	for(;;) {
		
	    // Get what x transforms into...
	    for(int i=pairRep.size()-1;i>=0;i--) {
		if(pairRep[i][0] == curr) {
		    curr = pairRep[i][1];
		}
		else if (pairRep[i][1] == curr) {
		    curr = pairRep[i][0];
		}
	    }
		
	    if(curr == nc[0]) break;
		
	    nc.push_back(curr);
	}
	if(nc.size() > 1) {
		
	    ncc.push_back(spinToMin(nc));
	}
	    
	all.erase(all.begin());

	// for(int i : all) printf("all2: %d\n", i);
	//for(int i : nc) printf("nc: %d\n", i);

	std::vector<int> nall;
	for(int i : all) {
	    if(std::find(nc.begin(), nc.end(), i) == nc.end()) {
		nall.push_back(i);
	    }
	}
	all = nall;

	//for(int i : all) printf("all3: %d\n", i);

	if(all.size() == 0) break;
    }

    sortedorder(ncc);
    return ncc;
}

std::vector<int> Permutation::readSingleCycle(std::string cycle_string) {
    std::vector<int> cycle;
    std::string cs = cycle_string;
    while(1) {
	// printf("[%s]   \n",cs.c_str());
	int sp = cs.find_first_of(' ');
	//printf("]%d[\n",sp);
	if(sp == std::string::npos) {
	    //	printf("0---\n");
	    //	printf("{%d}\n", std::stoi(cs));
	    cycle.push_back(std::stoi(cs));
	    return cycle;
	}

	//printf("-- %s -- :%s:\n", cs.c_str(), cs.substr(0,sp).c_str());
	//printf("{%d}", std::stoi(cs.substr(0,sp)));
	    
	cycle.push_back(std::stoi(cs.substr(0,sp)));
	cs = cs.substr(sp+1);
    }
    return cycle;
}

Permutation Permutation::cycleIndexValues(Permutation idxcycle) {
    std::vector<std::vector<int>> cyc = cycleIndexValues(cycles, idxcycle.getCycles());
    cycles = cyc;
    for(std::vector<int> &c : cycles) {
	c = spinToMin(c);
    }
    sortedorder(cycles);
    return Permutation(cyc, "perm");
}

std::string Permutation::cycleString(std::vector<std::vector<int>> _cyc) {
    std::string str;
	
    if(_cyc.size() == 0) {
	str = "()";
	return str;
    }
    for(std::vector<int> cyc : _cyc) {
	str += "(";
	int f=1;
	for(int o : cyc) {
	    if(!f) {
		str += " ";
	    }
	    if(f) f=0;
		
	    str += std::to_string(o);  // sprintf("%d", o);
	}
	str += ")";
    }
    return str;
}

void Permutation::reduceName() {
    std::string newname = reduceName(name);
    name = newname;
}

std::string Permutation::reduceName(std::string n) {
    std::string nn;

    //printf("trying to reduce (%s)[%d,%d,%d]\n", n.c_str(), n.length(), n.size(), strlen(n.c_str()));
    // reduce:
    //   1. "xX" --> ""
    //   2. "Xx" --> ""
    //   2a."XX" --> "xx"
    //   3. "xxx" --> "X"
    //   4. "XXX" --> "x"
    //   5.  "xxxx"/"XXXX" --> ""
    //   6.  swap lL / rR to sort lL first  (they commute)
    //   7.  swap fF / xX to sort fF first  (they commute)
    //   8.  swap tT / bB to sort tT first
    
    if(n.size() < 2) return n;
	
    // 1 & 2
    for(int i=0;i<n.size()-1;i++) {
	// printf("check tolowers: %c-%c-%d-%d\n",n[i], n[i+1], i, n.size()); 
	if(tolower(n[i]) == tolower(n[i+1])) {
	    if(n[i] != n[i+1]) {
		if(n.size() == 2) return "";
		if(i>0) nn = n.substr(0, i);
		else nn = "";
		    
		if(n.size() >  i+2) nn += n.substr(i+2);
		//printf("Reducing Xx to %s\n",nn.c_str());
		return reduceName(nn);
	    }
	}	
    }
    for(int i=0;i<n.size()-1;i++) {
	if((n[i] == n[i+1]) && isupper(n[i])) {
	    if(i>0) nn = n.substr(0, i);
	    nn += tolower(n[i]);
	    nn += tolower(n[i]);
	    if(n.size() > i+ 2) nn += n.substr(i+2);
	    return reduceName(nn);
	}
    }

    // 3 & 4 & (5 automatically because it first gets the xxx -> X then Xx -> I)
    if(n.size() >=3) {
	for(int i=0;i<n.size()-2;i++) {
	    //printf("in xx loop:  n.size=%d i=%d\n",n.size(),i);
	    if((n[i] == n[i+1]) && (n[i] == n[i+2])) {
		nn = n.substr(0,i);
		char c = n[i];
		if(islower(c)) c = toupper(c);
		else c = tolower(c);
		nn += c;
		if(n.size() > i+3) nn += n.substr(i+3);
		    
		//  printf("reducing xxx --> %s   (%d)\n", nn.c_str(), n.size());
		return reduceName(nn);
	    }
	}
    }

    // 6,7,8
    for(int i=0;i<n.size() -1 ;i++) {
	if(((tolower(n[i]) == 'r') && (tolower(n[i+1]) == 'l')) ||
	   ((tolower(n[i]) == 'x') && (tolower(n[i+1]) == 'f')) ||
	   ((tolower(n[i]) == 'b') && (tolower(n[i+1]) == 't'))) {
	    char c = n[i];
	    n[i] = n[i+1];
	    n[i+1] = c;

	    return reduceName(n);
	}
    }
	    
	    
    return n;
}


    // Note name is assembled backwards!
Permutation Permutation::operator* (Permutation B) {
    std::vector<std::vector<int>> Acyc = cycles;
    std::vector<std::vector<int>> Bcyc = B.getCycles();

    Acyc.insert(Acyc.end(), Bcyc.begin(), Bcyc.end());

    std::string bbb = B.getName() + name;
    //printf("in mult %s  (%s-%s)\n", bbb.c_str(), name.c_str(), B.name.c_str());
	
    Permutation C(Acyc, B.getName() + name);
    return C;
}

Permutation Permutation::operator- () {
    std::vector<std::vector<int>> res;

    for(std::vector<int> c : cycles) {
	std::vector<int> nv;
	    
	for(int idx=c.size()-1;idx >= 0; idx--) {
	    nv.push_back(c[idx]);
	}
	res.push_back(spinToMin(nv));
    }

    std::string nname = name;
    std::reverse(nname.begin(), nname.end());
    for(int i=0;i<nname.size();i++) {
	if(isupper(nname[i])) nname[i] = tolower(nname[i]);
	else nname[i] = toupper(nname[i]);
    }
	
	
    Permutation MR(res, nname);
    return MR;
}

    // 1->3->2->5, 3->4->5->6, 1->4->2->6
std::vector<std::vector<int>> Permutation::cycleIndexValues(std::vector<std::vector<int>> cyc, std::vector<std::vector<int>> idxcyc) {
    std::vector<std::vector<int>> ncyc;

    // build table for the transfer...
    int o2n[10];
    for(int i=0;i<10;i++) o2n[i] = i;

    for(std::vector<int> idx_s_cyc : idxcyc) {
	for(int i=0;i<idx_s_cyc.size();i++) {
	    int j = (i+1)%idx_s_cyc.size();
		
	    o2n[idx_s_cyc[i]] = idx_s_cyc[j];
	}
    }

	
    for(int i=0;i<10;i++) {
	//printf("o2n[%d]=%d\n", i,o2n[i]);
    }

    // do the transfer
    for(std::vector<int> s_cyc : cyc) {
	std::vector<int> n_s_cyc;
	    
	for(int x : s_cyc) {
	    int nx = 0;

	    int digit3 = o2n[((x/100)%10)];
	    int digit2 = o2n[((x/10)%10)];
	    int digit1 = o2n[(x%10)];
	    if((digit3 > 0) && (digit2 > digit1)) {
		nx = digit3 * 100 + digit2 + digit1 * 10;
	    }
	    else {
		nx = digit3 * 100 + digit2 * 10 + digit1;
	    }
				 
	    n_s_cyc.push_back(nx);
	}
	ncyc.push_back(n_s_cyc);
    }
    return ncyc;
}

std::vector<std::vector<int>> Permutation::decompose(std::vector<int> cyc) {
    std::vector<std::vector<int>> res;
	
    for(int i=cyc.size()-1;i>=1;i--) {
	std::vector<int> ts;
	ts.push_back(cyc[0]);
	ts.push_back(cyc[i]);
	res.push_back(ts);
    }
    return res;
}


int Permutation::getSourcePosition(int x) {
    for(std::vector<int> c : cycles) {
	for(int i=0;i<c.size();i++) {
	    if(x == c[i]) {
		i = i + c.size() - 1;
		i = i % c.size();
		return c[i];
	    }
	}
    }
    return x;
}

int Permutation::nswaps() {
    std::vector<std::vector<int>> pairs = pairRepresentation(cycles);
    return pairs.size();
}

bool incrementIdx(int *idx, int depth, int nbases) {
    int i = depth-1;

    while(i >= 0) {
        if(idx[i] == nbases - 1) {
            idx[i] = 0;
            i--;
        }
        else {
            idx[i]++;

            return true;
        }
    }
    return false;
}

int Permutation::getCycleType(std::vector<int> &cyc) {
    int type = 0;

    for(auto x : cyc) {
	int t=-1;
	if(x >= 100) t = 3;
	else if(x>=10) t = 2;

	if (type == 0) type = t;
	else if (type != t) type = -1;
    }

    return type;
}   
    
int Permutation::getNParity(int N) {
    int ncycles = 0;
    int nsymbols = 0;
    int nswaps = 0;
    for(auto x : cycles) {
	int type = getCycleType(x);
	assert(type != -1);
	if(type != N) continue;
	
	nswaps += x.size()-1;
    }

    //printf("%d = %d\n", nswaps, nswaps/N);
    
    int p = (nswaps)%2;
}

// 1. rename all symbols to sorted versions
// 2. cut cycles short at first repeat
// 3. remove repeated cycles
// 4. put into standard form...
Permutation Permutation::reduceToDegenerate() {
    std::vector<std::vector<int>> dcycles1;

    // rename the symbols to sorted versions...
    for(auto x : cycles) {
	std::vector<int> dcyc;
	for(auto y : x) {
	    std::vector<int> digits;
	    digits.push_back(y/100);
	    digits.push_back((y%100)/10);
	    digits.push_back(y%10);
	    std::sort(digits.begin(), digits.end());
	    int nsymbol = digits[0] * 100 + digits[1] * 10 + digits[2];
	    
	    dcyc.push_back(nsymbol);
	}
	dcycles1.push_back(dcyc);
    }

    // cut off after first repeat
    std::vector<std::vector<int>> dcycles2;
    for(auto x : dcycles1) {
	std::vector<int> dcyc;
	int first = 0;
	for(auto y : x) {
	    if(first == 0) first = y;
	    else if (first == y) break;

	    dcyc.push_back(y);
	}
	if(dcyc.size() > 1) {
	    dcycles2.push_back(dcyc);
	}
    }

    // rotate to smallest
    for(auto &x : dcycles2) {
	auto it = std::min_element(x.begin(), x.end());
	std::rotate(x.begin(), it, x.end());
    }

    // sort the vectors...
    std::sort(dcycles2.begin(), dcycles2.end());

    std::vector<std::vector<int>> dcycles3;
    int j=-1;
    for(int i=0;i<dcycles2.size();i++) {
	std::vector<int> &x = dcycles2[i];

	if(j >= 0) {
	    if(dcycles2[i] == dcycles3[j]) continue;
	}

	dcycles3.push_back(dcycles2[i]);
	j++;
    }

    Permutation np(dcycles3);
    return np;
}

