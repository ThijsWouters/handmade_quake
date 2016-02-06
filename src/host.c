#include "common.h"

double realTime = 0;
double oldRealTime = 0;
double host_frameTime = 0;

qboolean Host_FilterTime(float time) {
  realTime += time;

  if (realTime - oldRealTime < 1.0f / 72.0f) return false;

  host_frameTime = realTime - oldRealTime;
  oldRealTime = realTime;
  return true;
}

void Host_Init() {
}

void Host_Frame(float time) {
  if(!Host_FilterTime(time)) return;
}

void Host_Shutdown() {
}
