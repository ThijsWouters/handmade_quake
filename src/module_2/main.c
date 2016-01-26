#include <stdint.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>

int8_t IsRunning = 1;

double time_in_sec(){
  struct timespec time;
  double result;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
  result = (double) time.tv_nsec;
  result /= 1000000000.0;
  result += (double) time.tv_sec;
  return result;
}

int32_t main(int32_t argc, char* argv[]) {
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

  double seconds_per_clock = 1.0 / (double) CLOCKS_PER_SEC;

  double tick, tock;
  tick = time_in_sec();

  while(IsRunning) {
    if (XEventsQueued(display, QueuedAfterFlush) > 0) {
      XNextEvent(display, (XEvent*) &event);

      switch(event.type) {
        case KeyPress:
          IsRunning = 0;
          break;
        case ClientMessage:
          if (event.xclient.data.l[0] == WM_DELETE_WINDOW) {
            IsRunning = 0;
          }
          break;
        default:
          break;
      }
    }

    tock = time_in_sec();

    double seconds_gone_by = tock - tick;
    tick = tock;
    printf("%3.9f\n", seconds_gone_by);
  }

  return 0;
}

