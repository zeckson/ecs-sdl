//
// Created by Evgenii Shchepotev on 20.06.2024.
//

#ifndef ECS_ACTION_H
#define ECS_ACTION_H

#include <string>

enum ActionType {
  UNKNOWN = 0, START, END
};

class Action {
 public:
  const ActionType type;
  const std::string& name;

  Action(const std::string& name, const ActionType type) : name(name), type(type) {}
};

#endif  // ECS_ACTION_H
