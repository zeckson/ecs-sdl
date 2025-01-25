//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#ifndef ECS_SPACESCENE_H
#define ECS_SPACESCENE_H

#include "scene/scene.h"

class SpaceScene: public Scene {
  void update() override;
  void init() override;
  void onAction(const Action& action) override;
};

#endif  // ECS_SPACESCENE_H
