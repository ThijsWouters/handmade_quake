#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int32_t int32;
typedef uint8_t uint8;

int32 largc;
uint8** largv;

int32 Q_strcmp(uint8 *s1, uint8 *s2) {
  while (*s1 == *s2) {
    if (*s1 == 0) {
      return 0;
    }

    s1++;
    s2++;
  }

  return *s1 > *s2 ? 1 : -1;
}

int32 Q_atoi(uint8 *str) {
  int32 sign = 1;
  int32 result = 0;
  uint8 c;

  if (*str == '-') {
    sign = -1;
    str++;
  }

  if (*str == '0' && (str[1] == 'x' || str[1] == 'X')) {
    // Hexadecimal
    str += 2;
    while (
        (*str >= '0' && *str <= '9') ||
        (*str >= 'a' && *str <= 'f') ||
        (*str >= 'A' && *str <= 'F')
        ) {
      result *= 16;
      if (*str >= 'a' && *str <= 'f') {
        result += (*str - 'a' + 10);
      } else if (*str >= 'A' && *str <= 'F') {
        result += (*str - 'A' + 10);
      } else {
        result += (*str - '0');
      }
      str++;
    }
  } else {
    // Decimal
    while (*str >= '0' && *str <= '9') {
      result *= 10;
      result += (*str - '0');
      str++;
    }
  }

  return result * sign;
}

int32 COM_CheckParm(uint8* parm) {
  for(int32 i = 0;i<largc;i++) {
    if (Q_strcmp(parm, largv[i]) == 0) {
      return i;
    }
  }
  return 0;
}

int32 main(int32 argc, uint8** argv) {
  largc = argc;
  largv = argv;

  int32 test = COM_CheckParm("-setalpha");
  int32 value = Q_atoi(largv[test+1]);
  return value;
}
