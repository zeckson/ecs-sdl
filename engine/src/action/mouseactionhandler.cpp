#include "mouseactionhandler.h"

#include <resource/logger.h>

// Constructor
MouseActionHandler::MouseActionHandler() {
  // Initialize any member variables or resources here
}

// Destructor
MouseActionHandler::~MouseActionHandler() {
  // Clean up any resources here
}

// Method to handle keyboard events
void MouseActionHandler::handleMouseEvent(const SDL_Event& event) {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  if (event.type == SDL_MOUSEMOTION) {
    Logger::debug("Mouse moved to: [%u, %u]", mouseX, mouseY);
    // TODO: handle mouse movement
    return;
  }

  const auto button = event.button.button;

  const auto it = actionMap.find(button);
  if (it == actionMap.end()) {
    Logger::debug("Mouse button %u clicked at: [%u, %u] is unhandled", button, mouseX, mouseY);
    return;  // Action is not registered for event
  }

  const auto actionName = it->second;

  if (event.type == SDL_MOUSEBUTTONDOWN) {
    onMouseAction(MouseAction(actionName, ActionType::START, mouseX, mouseY));
  }

  if (event.type == SDL_MOUSEBUTTONUP) {
    onMouseAction(MouseAction(actionName, ActionType::END, mouseX, mouseY));
  }
}

void MouseActionHandler::registerMouseAction(const MouseActionType type, const std::string& actionName) {
  actionMap[type] = actionName;
}
