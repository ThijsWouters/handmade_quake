#include <stdint.h>
#include <string.h>

int32_t com_argc;
uint8_t** com_argv;

int32_t COM_CheckParm(uint8_t* parm) {
  for(int32_t i = 0;i<com_argc;i++) {
    if (strcmp(parm, com_argv[i]) == 0) {
      return i;
    }
  }
  return 0;
}

