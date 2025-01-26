//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"
#include "ballscene.h"

bool BallGame::onGameCreate() {
  auto scene = std::make_shared<BallScene>(*this);
  this->changeScene("balls", scene);
  return true;
}
