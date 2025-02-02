//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"
#include "ballscene.h"
#include "entryscene.h"

bool BallGame::onGameCreate() {
  registerScene("game", std::make_shared<BallScene>(BallScene(*this)));
  registerScene("menu", std::make_shared<EntryScene>(EntryScene(*this, std::make_shared<BallScene>(BallScene(*this, true)))));
  changeScene("menu");
  return true;
}
