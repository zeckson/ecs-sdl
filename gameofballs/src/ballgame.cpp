//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"
#include "ballscene.h"
#include <scene/menuscene.h>

bool BallGame::onGameCreate() {
  auto menu = MenuScene({"Start", "Exit"}, *this);
  // auto scene = std::make_shared<BallScene>(*this);
  this->changeScene("menu", std::make_shared<MenuScene>(menu));
  return true;
}
