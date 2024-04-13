//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_INPUTCOMPONENT_H
#define ECS_SDL_INPUTCOMPONENT_H

#include <SDL.h>

#include "component.h"

#define INPUT_COMPONENT_NAME "input"

// Define bitmask flags
enum class Direction : Uint8 {
  NONE = 0,       // 0
  UP = 0b0001,    // 1
  DOWN = 0b0010,  // 2
  LEFT = 0b0100,  // 4
  RIGHT = 0b1000  // 8
};

class InputComponent : public Component {
 public:
  InputComponent() : Component(INPUT_COMPONENT_NAME) { reset(); }

  void reset() {
    xAxisMove = 0;
    yAxisMove = 0;

    direction = static_cast<Uint8>(Direction::NONE);

    fire = false;
  }

  void set(Direction bit) { direction |= static_cast<Uint8>(bit); }

  void unset(Direction bit) { direction &= ~static_cast<Uint8>(bit); }

  bool isset(Direction bit) const {
    // Perform bitwise AND operation
    unsigned int result = static_cast<unsigned int>(direction) & static_cast<unsigned int>(bit);
    // If result is non-zero, the bit is set
    return result != 0;
  }

  Uint8 direction = static_cast<Uint8>(Direction::NONE);

  int xAxisMove = 0;
  int yAxisMove = 0;
  bool fire = false;
};

#endif  // ECS_SDL_INPUTCOMPONENT_H
