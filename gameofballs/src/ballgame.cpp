//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"
#include "ballscene.h"
#include "entryscene.h"

bool BallGame::onGameCreate() {
  registerScene("menu", std::make_shared<EntryScene>(EntryScene(*this)));
  registerScene("game", std::make_shared<BallScene>(BallScene(*this)));
  changeScene("menu");
  return true;
}
