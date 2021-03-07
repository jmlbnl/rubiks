#include "Permutation.h"
#include "ArrayRep.h"
#include "heuristic.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

typedef ArrayRep AR;

Heuristic h;


void solveCorners(AR &cube, AR &result, std::vector<char> &solution) {
  std::vector<AR> bases = { AR::Ar, AR::Al, AR::At, AR::Ab, AR::Af, AR::Ax, AR::AR, AR::AL, AR::AT, AR::AB, AR::AF, AR::AX };
  std::vector<char> basenames = { 'r', 'l', 't', 'b', 'f', 'x', 'R', 'L', 'T', 'B', 'F', 'X' };

  ArrayRep curr = cube;
  int n = h.CornerTurnsToSolve(curr);
 
  while(n > 0) {
    for(int i=0;i<bases.size();i++) {
      ArrayRep x = bases[i] * curr;
      int nextn = h.CornerTurnsToSolve(x);     
      if(nextn < n) {
	n = nextn;
	curr = x;
	solution.push_back(basenames[i]);
	break;
      }
    }
  }
  result = curr;
}

int main(int argc, char *argv[]) {
  std::random_device r;
  std::default_random_engine e(r());
  h.loadCornerStore(h.cornerStore);
  AR x = AR::random(e);

  int n=h.CornerTurnsToSolve(x);
  printf("Try to solve: %s  [n=%d]\n", x.dump2CStr().c_str(), n);

  AR solutionCube;
  std::vector<char> solution;

  solveCorners(x, solutionCube, solution);
  // Solve top
  // Solve bottom
  // Solve sides
  
  printf("The solution is: ");
  for(auto c : solution) {
    printf("%c", c);
  }
  printf(":  %s\n", solutionCube.dump2CStr().c_str());
    
  
}
