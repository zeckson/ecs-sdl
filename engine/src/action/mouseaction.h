//
// Created by Evgenii Shchepotev on 20.06.2024.
//

#ifndef ECS_MOUSEACTION_H
#define ECS_MOUSEACTION_H

#include <string>
#include <geometry/vec2.h>

class MouseAction: public Action {

 public:
  const Vec2 position;
  MouseAction(const std::string& name, const ActionType type, const int x, const int y) : Action(name, type), position(x, y) {}
};

#endif  // ECS_MOUSEACTION_H
