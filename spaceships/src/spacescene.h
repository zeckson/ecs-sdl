//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#ifndef ECS_SPACESCENE_H
#define ECS_SPACESCENE_H

#include <scene/playscene.h>
#include <engine/scenegame.h>

class SpaceScene: public PlayScene {
  private:
    std::shared_ptr<Sprite> player;
    Vec2 playerPos{100, 100};
    int currentFrame = 0;

  public:
    SpaceScene(SceneGame& game): PlayScene(game) {}

    void update() override;
    void checkBounds();
    void init() override;
    void onKeyboardAction(const Action& action) override;
    void onMouseAction(const MouseAction& action) override;
};

#endif  // ECS_SPACESCENE_H
