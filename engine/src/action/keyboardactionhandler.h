#ifndef KEYBOARDACTIONHANDLER_H
#define KEYBOARDACTIONHANDLER_H

#include <map>
#include <string>
#include <SDL.h>
#include "action.h"

class KeyboardActionHandler {
 public:
    KeyboardActionHandler();
    ~KeyboardActionHandler();

    void handleKeyboardEvent(const SDL_Event& event);

 private:
    std::map<SDL_Scancode, std::string> actionMap;

protected:
    void registerKeyboardAction(const SDL_Scancode code, const std::string& actionName);

    virtual void onKeyboardAction(const Action& action) = 0;
};

#endif  // KEYBOARDACTIONHANDLER_H
