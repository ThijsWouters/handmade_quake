#pragma once
#include <stdint.h>

typedef enum {false, true} qboolean;

extern int32_t com_argc;
extern char** com_argv;

int32_t COM_CheckParm(const char* parm);

