#include <stdint.h>

int32_t Q_atoi(uint8_t *str) {
  int32_t sign = 1;
  int32_t result = 0;
  uint8_t c;

  if (*str == '-') {
    sign = -1;
    ++str;
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
      ++str;
    }
  } else {
    // Decimal
    while (*str >= '0' && *str <= '9') {
      result *= 10;
      result += (*str - '0');
      ++str;
    }
  }

  return result * sign;
}

