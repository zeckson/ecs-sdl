#include "keyboardactionhandler.h"
#include <resource/logger.h>

// Constructor
KeyboardActionHandler::KeyboardActionHandler() {
    // Initialize any member variables or resources here

}

// Destructor
KeyboardActionHandler::~KeyboardActionHandler() {
    // Clean up any resources here
}

// Method to handle keyboard events
void KeyboardActionHandler::handleKeyboardEvent(const SDL_Event& event) {
    const auto key = event.key.keysym;

  const auto it = actionMap.find(key.scancode);

  if (it == actionMap.end()) {
    Logger::debug("Action is not registered for event: ", key.scancode);
    return;  // Action is not registered for event
  }

  const auto actionName = it->second;

  if (event.type == SDL_KEYDOWN) {
    onAction(Action(actionName, ActionType::START));
  }

  if (event.type == SDL_KEYUP) {
    onAction(Action(actionName, ActionType::END));
  }
}

void KeyboardActionHandler::registerAction(const SDL_Scancode code, const std::string& actionName) {
    actionMap[code] = actionName;
}
