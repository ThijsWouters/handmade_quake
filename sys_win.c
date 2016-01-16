#include <stdio.h>
#include <string.h>

int largc;
char** largv;

int COM_CheckParm(char* parm) {
  for(int i = 0;i<largc;i++) {
    if (strcmp(parm, largv[i]) == 0) {
      return i;
    }
  }
  return 0;
}

int main(int argc, char** argv) {
  largc = argc;
  largv = argv;

  int test = COM_CheckParm("-setalpha");
  return test;
}
