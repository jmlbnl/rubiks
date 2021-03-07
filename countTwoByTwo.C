//   Count number of minimum length paths to each two by two solution
//
//

#include "Permutation.h"
#include "PermutationMap.h"
#include "ArrayRep.h"
#include "heuristic.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

typedef ArrayRep AR;
Heuristic h;
std::vector<ArrayRep> bases;
std::vector<char> basenames;

void getSolutions(int n_orig, AR cube, std::vector<std::string> &solutions) {
  if(n_orig == 0) {   // return single null solution...
    solutions.push_back("");
    return;
  }
  
  for(int i=0;i<bases.size();i++) {
    ArrayRep new_cube = bases[i] * cube;
    int n_next = h.CornerTurnsToSolve(new_cube);
    if(n_next < n_orig) {
      std::vector<std::string> new_solutions;
      getSolutions(n_next, new_cube, new_solutions);

      for(auto s : new_solutions) {
	solutions.push_back(basenames[i] + s);
      }
    }
  }
}

AR baseFromChar(char c) {
  for(int i=0;i<basenames.size();i++) {
    if(c == basenames[i]) return bases[i];
  }

  return AR::origin;
}

std::string invertString(std::string s) {
  std::string res(s.rbegin(), s.rend());
  for(auto &c : res) { 
    if(isupper(c)) c = tolower(c);
    else c = toupper(c);
  }

  //printf("reversed %s is %s\n", s.c_str(), res.c_str());
  
  return res;
}

  
    
void printAffectedSides(std::vector<std::string> &sol_str, std::vector<AR> &sol_cubes) {
  for(int i=0;i<sol_str.size()-1;i++) {
    for(int j= i+1;j<sol_str.size();j++) {
      std::string a = sol_str[i] + invertString(sol_str[j]);
      AR cube = sol_cubes[i] * -sol_cubes[j];
      
      printf("cubs: %s: %s\n", a.c_str(), cube.dump2CStr().c_str());
      printf("cube: %s\n", cube.dump2CStr().c_str());
    }
  }
}


int countRealSolutions(std::vector<std::string> &solutions) {
  if(solutions.size() < 2) return 1;

  std::vector<AR> v;
  
  for(auto sol : solutions) {
    AR x = AR::origin;

    for(char &c : sol) {
      x = baseFromChar(c) * x;
    }

    v.push_back(x);
  }

  std::vector<AR> u_v;
  std::vector<std::string> u_s;

  for(int i=0;i<solutions.size();i++) {
    if(std::find(u_v.begin(), u_v.end(), v[i]) == u_v.end()) {
      u_v.push_back(v[i]);
      u_s.push_back(solutions[i]);
    }
  }
  
  int cnt = u_v.size();
  printf("cnt = %d  %ld\n", cnt, v.size());
  
  if(cnt > 1) printAffectedSides(u_s, u_v);
  return cnt;
}

void test_checkIfOrientationsAreConsistent() {
  std::vector<int> faces = { 136,613,316, 134,314,413, 145,415,514, 156,516,615,
			     234,423,324, 236,326,623, 245,425,524, 256,526,625 };

  for(int i=0;i<faces.size(); i++) {
    for(int j=0;j<faces.size();j++) {
      int oo = -1;
      for(int k=0;k<faces.size();k++) {
	if(i==j) continue;
	
	int o_ik = RubiksMap.getCornerOrientation(faces[i], faces[k]);
	int o_jk = RubiksMap.getCornerOrientation(faces[j], faces[k]);
	int o_diff = (3 + o_jk - o_ik) % 3;
	if(oo == -1) oo = o_diff;
	if(oo != o_diff) {
	  printf("BAD!\n");
	}
	printf("%d moves from %d -> %d ::: o changes %d -> %d   (diff = %d)\n", faces[k], faces[i], faces[j], o_ik, o_jk, o_diff);
      }
    }
  }
  return;
}

void test_checkIfSideOrientationsAreConsistent() {
    std::vector<int> faces = { 16,61, 13,31, 14,41, 15,51,
			       54,45, 34,43, 36,63, 65,56,
			       25,52, 24,42, 23,32, 26,62 };
    
    for(int i=0;i<faces.size(); i++) {
	for(int j=0;j<faces.size();j++) {
	    int oo = -1;
	    for(int k=0;k<faces.size();k++) {
		if(i==j) continue;
		
		int o_ik = RubiksMap.getSideOrientation(faces[i], faces[k]);
		int o_jk = RubiksMap.getSideOrientation(faces[j], faces[k]);
		int o_diff = (2 + o_jk - o_ik) % 2;
		if(oo == -1) oo = o_diff;
		if(oo != o_diff) {
		    printf("BAD!\n");
		}
		printf("%d moves from %d -> %d ::: o changes %d -> %d   (diff = %d)\n", faces[k], faces[i], faces[j], o_ik, o_jk, o_diff);
	    }
	}
    }
    return;
}

void test_cornerMultiply() {
    printf("origin: \n%s\n", ArrayRep::origin.dump2CStr().c_str());
    CornerStore mycs;
    printf("corner store origin = 0x%lx\n", mycs.data);
    ArrayRep x1 = mycs.build();
    ArrayRep x2 = (-mycs).build();
    printf("%s %s\n", x1.dump2CStr().c_str(), x2.dump2CStr().c_str());
    
    mycs.set(AR::Ar, 0);
    x1 = mycs.build();
    printf("CS set to AR::Ar:  \n%s\n", x1.dump2CStr().c_str());
    
    CornerStore cs_o;
    mycs = mycs * cs_o;
    x1 = mycs.build();
    x2 = (-mycs).build();
    printf("CS set to AR::Ar * O:  \n%s\n%s\n%s\n", AR::AR.dump2CStr().c_str(), x1.dump2CStr().c_str(), x2.dump2CStr().c_str());
    
    mycs.set(AR::At, 0);
    mycs = mycs * cs_o;
    x1 = mycs.build();
    x2 = (-mycs).build();
    printf("CS set to AR::At * O:  \n%s\n%s\n%s\n", AR::AT.dump2CStr().c_str(), x1.dump2CStr().c_str(), x2.dump2CStr().c_str());
    
    mycs.set(AR::Af, 0);
    mycs = mycs * cs_o;
    x1 = mycs.build();
    x2 = (-mycs).build();
    printf("CS set to AR::Af * O:  \n%s\n%s\n%s\n", AR::AF.dump2CStr().c_str(), x1.dump2CStr().c_str(), x2.dump2CStr().c_str());
    
    
    CornerStore ar(AR::Ar, 0);
    CornerStore at(AR::At, 0);
    CornerStore ax(AR::Ax, 0);
    
    AR arcx = AR::Ar * AR::Ax * AR::At * AR::Ax * AR::At;
    CornerStore csx = ar * ax * at * ax * at;
    
    printf("bigone: \n%s\n%s\n", arcx.dump2CStr().c_str(), csx.dump2CStr().c_str());
    
    csx = csx* (-csx);
    printf("then I is:\n");
    printf("%s\n", csx.dump2CStr().c_str());
    
    
    SideStore myss(ArrayRep::origin, 0);
    printf("side store origin = 0x%lx\n", myss.data);
    
}

void test_sideMultiply() {
    
    printf("origin: \n%s\n", ArrayRep::origin.dump2CStr().c_str());

    SideStore myss(ArrayRep::origin, 0);
    printf("side store origin = 0x%lx\n", myss.data);

    SideStore mycs;
    printf("side store origin direct = 0x%lx\n", mycs.data);
    
    printf("%s %s\n", mycs.dump2CStr().c_str(), mycs.dump2CStr().c_str());
    
    mycs.set(AR::Ar, 0);
    printf("AR: %s\n", AR::Ar.dump2CStr().c_str());
    
    printf("CS set to AR::Ar:  \n%s\n", mycs.dump2CStr().c_str());
    
    SideStore cs_o;
    mycs = mycs * cs_o;
    printf("origin:  %s\n", cs_o.dump2CStr().c_str());
    
    printf("CS set to AR::Ar * O:  \n%s\n%s\n", AR::Ar.dump2CStr().c_str(), mycs.dump2CStr().c_str());
    
    mycs.set(AR::At, 0);
    printf("AR:At = \n%s\n", AR::At.dump2DStr().c_str());
    
    mycs = mycs * cs_o;
    printf("b\n");
    printf("CS set to AR::At * O:  \n%s\n", mycs.dump2DStr().c_str());
    printf("-(At) ==>  \n%s\n", (-mycs).dump2DStr().c_str());
    
    mycs.set(AR::Af, 0);
    mycs = mycs * cs_o;
    printf("CS set to AR::Af * O:  \n%s\n%s\n%s\n", AR::AF.dump2CStr().c_str(), mycs.dump2CStr().c_str(), (-mycs).dump2CStr().c_str());
    
    
    SideStore ar(AR::Ar, 0);
    SideStore at(AR::At, 0);
    SideStore ax(AR::Ax, 0);
    
    AR arcx = AR::Ar * AR::Ax * AR::At * AR::Ax * AR::At;
    SideStore csx = ar * ax * at * ax * at;
    
    printf("bigone: \n%s\n%s\n", arcx.dump2CStr().c_str(), csx.dump2CStr().c_str());
    
    csx = csx* (-csx);
    printf("then I is:\n");
    printf("%s\n", csx.dump2CStr().c_str());
    
    
    
}

int main(int argc, char *argv[]) {
    std::vector<AR> mybases = { AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax, AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };
    std::vector<char> mybasenames = { 'r', 'l', 't', 'b', 'f', 'x', 'R', 'L', 'T', 'B', 'F', 'X' };
    
    bases = mybases;
    basenames = mybasenames;

    //test_checkIfSideOrientationsAreConsistent(); return 0;
    test_sideMultiply();  return 0;


    h.loadCornerStore(h.cornerStore);
 
    
    
    int min_mult = 10000;
    int i=0;
    for(auto x : h.cornerStore) {
	if(x.getCount() <= 3) { 
	    AR cube = x.build();
	    
	    std::vector<std::string> solutions;
	    int needed_turns = h.CornerTurnsToSolve(cube);
	    getSolutions(needed_turns, cube, solutions);
	    int nsolutions = countRealSolutions(solutions);
	    
	    if(nsolutions > 1) {
		min_mult = x.getCount();
		printf("%4d %2d %d",  min_mult, x.getCount(), nsolutions);
		
		for(auto s : solutions) {
		    printf("%4s ", s.c_str());
		}
		printf("\n");
		i++;
	    }
	}
    }
    
    printf("count = %d\n",i);
}


