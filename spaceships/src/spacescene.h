//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#ifndef ECS_SPACESCENE_H
#define ECS_SPACESCENE_H

#include "scene/scene.h"
#include <engine/game.h>

class SpaceScene: public Scene {
  private:
    Game& game;
    std::shared_ptr<Sprite> player;
    Vec2 playerPos{100, 100};
    int currentFrame = 0;

  public:
    SpaceScene(Game& gameObj): game(gameObj) {} 

    void update() override;
    void init() override;
    void onAction(const Action& action) override;
};

#endif  // ECS_SPACESCENE_H
