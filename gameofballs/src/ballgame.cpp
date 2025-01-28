//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"
#include "ballscene.h"
#include <scene/menuscene.h>

bool BallGame::onGameCreate() {
  auto menu = std::make_shared<MenuScene>(MenuScene({"Start", "Exit"}, *this));
  registerScene("menu", menu);
  registerScene("game", std::make_shared<BallScene>(BallScene(*this)));
  changeScene("menu");
  return true;
}
