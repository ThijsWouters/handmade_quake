#include <stdint.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <stdio.h>

int8_t IsRunning = 1;

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
  }

  return 0;
}
