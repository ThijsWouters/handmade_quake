#include <stdint.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <time.h>

#include "common.h"
#include "q_stl.h"
#include "host.h"

int8_t IsRunning = 1;

void Sys_Shutdown() {
  IsRunning = 0;
}

///////////////
// Timer
///////////////

double tick = 0;
double time_passed = 0;

double time_in_sec() {
  struct timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  double result = (double) time.tv_nsec;
  result /= 1000000000.0;
  result += (double) time.tv_sec;
  return result;
}

float Sys_InitFloatTime() {
  tick = time_in_sec();
  return 0;
}

float Sys_FloatTime() {
  double tock = time_in_sec();
  double result = tock - tick;
  tick = tock;
  time_passed += result;
  return (float) time_passed;
}

/////////////////
// End Timer
////////////////

int32_t main(int32_t argc, char* argv[]) {
  com_argc = argc;
  com_argv = argv;

  Display *display;
  Window frame_window;
  XEvent event;

  display = XOpenDisplay(NULL);

  frame_window = XCreateSimpleWindow(display, XRootWindow(display, 0),
      0, 0, 800, 600, 0, XBlackPixel(display, 0), XBlackPixel(display, 0));

  XStoreName(display, frame_window, "Handmade Quake");
  XSelectInput(display, frame_window,
      KeyPressMask | KeyReleaseMask);

  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, frame_window, &WM_DELETE_WINDOW, 1);

  XMapWindow(display, frame_window);

  Host_Init();

  float oldTime = Sys_InitFloatTime();
  float targetTime = 1.0f / 60.0f;
  float timeAcc = 0;

  while(IsRunning) {
    while (XEventsQueued(display, QueuedAfterFlush) > 0) {
      XNextEvent(display, (XEvent*) &event);

      switch(event.type) {
        case ClientMessage:
          if (event.xclient.data.l[0] == WM_DELETE_WINDOW) {
            Sys_Shutdown();
          }
          break;
        default:
          break;
      }
    }

    float newTime = Sys_FloatTime();
    timeAcc += newTime - oldTime;
    oldTime = newTime;

    if (timeAcc > targetTime) {
      Host_Frame(targetTime);
      timeAcc -= targetTime;
    }
  }

  return 0;
}

