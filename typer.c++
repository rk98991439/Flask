#include <iostream>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/keysym.h>

using namespace std;

int main() {
    // Set the URL and the comment to be typed
    string url = "https://www.example.com/comments";
    string comment = "This is a sample comment.";

    // Open the URL in the default browser
    string command = "xdg-open " + url;
    system(command.c_str());

    // Wait for the page to load
    usleep(5000000);

    // Get the current active window
    Display* d = XOpenDisplay(NULL);
    Window active_win;
    int revert;
    XGetInputFocus(d, &active_win, &revert);

    // Simulate typing the comment
    XEvent event;
    memset(&event, 0, sizeof(event));
    event.xkey.type = KeyPress;
    event.xkey.display = d;

    for (char c : comment) {
        // Convert the character to its keycode
        KeySym keysym = XStringToKeysym(string(1, c).c_str());
        KeyCode keycode = XKeysymToKeycode(d, keysym);

        // Simulate pressing the key
        event.xkey.keycode = keycode;
        XSendEvent(d, active_win, True, KeyPressMask, &event);
        event.xkey.type = KeyRelease;
        XSendEvent(d, active_win, True, KeyReleaseMask, &event);
        event.xkey.type = KeyPress;

        // Wait for a short time before typing the next character
        usleep(50000);
    }

    XCloseDisplay(d);

    return 0;
}
