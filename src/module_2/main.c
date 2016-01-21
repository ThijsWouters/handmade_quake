#include <stdint.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int32_t main(int32_t argc, char* argv[]) {
  Display *display;
  Visual *visual;
  int depth;
  XSetWindowAttributes frame_attributes;
  Window frame_window;
  XKeyEvent event;

  display = XOpenDisplay(NULL);
  visual = DefaultVisual(display, 0);
  depth = DefaultDepth(display, 0);

  frame_attributes.background_pixel = XWhitePixel(display, 0);

  frame_window = XCreateWindow(display, XRootWindow(display, 0),
      0, 0, 400, 400, 5, depth,
      InputOutput, visual, CWBackPixel,
      &frame_attributes);

  XStoreName(display, frame_window, "Handmade Quake");
  XSelectInput(display, frame_window, ExposureMask | StructureNotifyMask);

  XMapWindow(display, frame_window);

  while(1) {
    XNextEvent(display, (XEvent*) &event);
    switch(event.type) {
      default:
        break;
    }
  }

  return 0;
}
