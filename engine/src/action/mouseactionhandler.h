#ifndef MOUSEACTIONHANDLER_H
#define MOUSEACTIONHANDLER_H

#include <map>
#include <string>
#include <SDL.h>
#include "action.h"
#include "mouseaction.h"

enum MouseActionType {
  MOUSE_LEFT_CLICK = SDL_BUTTON_LEFT,
  MOUSE_RIGHT_CLICK = SDL_BUTTON_RIGHT,
};

class MouseActionHandler {
 public:
    MouseActionHandler();
    ~MouseActionHandler();

    void handleMouseEvent(const SDL_Event& event);

 private:
    std::map<int, std::string> actionMap;

protected:
    void registerMouseAction(const MouseActionType type, const std::string& actionName);

    virtual void onMouseAction(const MouseAction& action) = 0;
};

#endif  // MOUSEACTIONHANDLER_H
