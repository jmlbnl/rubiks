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
  AR x[100];

  int n = 1;
  x[n] = AR::origin;
  for(int i=0;i<3;i++) {
    x[n+1] = AR::Ar * x[n];
    n++;
  }
  n++;
  
  x[n] = AR::At * AR::origin;
  for(int i=0;i<3;i++) {
    x[n+1] = AR::Ar * x[n];
    n++;
  }
  n++;

  for(int i=1;i<n;i++) {
    printf("     %d : %s\n", i, x[i].dump2CStr().c_str());
  }


  printf("     At: %s\n",AR::At.dump2CStr().c_str());
  printf("At x[1]: %s\n",(x[1] * AR::At).dump2CStr().c_str());
  printf("At x[2]: %s\n",(x[2] * AR::At).dump2CStr().c_str());
  printf("At x[3]: %s\n",(x[3] * AR::At).dump2CStr().c_str());
  printf("At x[4]: %s\n",(x[4] * AR::At).dump2CStr().c_str());
    
}
