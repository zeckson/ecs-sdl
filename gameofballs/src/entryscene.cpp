#include "entryscene.h"

EntryScene::EntryScene(SceneGame& game, std::shared_ptr<BallScene> bgScene)
    : MenuScene({"Start", "Exit"}, game), bgScene(bgScene) {}

void EntryScene::onMenuItemSelected(const std::string& item) {
  if (item == "Start") {
    game.changeScene("game");
  } else if (item == "Exit") {
    game.quit();
  }
}

void EntryScene::init() {
    MenuScene::init();
    bgScene->init();
}

void EntryScene::update() {
  bgScene->update();
  MenuScene::update();
}