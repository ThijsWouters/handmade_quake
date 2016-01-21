#include <stdint.h>
#include "common.h"
#include "q_stl.h"

int32_t main(int32_t argc, char** argv) {
  com_argc = argc;
  com_argv = argv;

  int32_t test = COM_CheckParm("-setalpha");
  int32_t value = Q_atoi(com_argv[test+1]);

  return value;
}

