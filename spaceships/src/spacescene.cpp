//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#include "spacescene.h"
#include <assets/sprite.h>

void SpaceScene::update() {
    const std::unique_ptr<Sprite>& sprite = game.getAssetsManager().getTexture("spaceship");
    game.renderer->renderSprite(sprite, {100, 100});
}
void SpaceScene::init() {}
void SpaceScene::onAction(const Action& action) {}
