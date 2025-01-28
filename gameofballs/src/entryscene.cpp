#include "entryscene.h"

EntryScene::EntryScene(SceneGame& game) : MenuScene({"Start", "Exit"}, game) {}

void EntryScene::onMenuItemSelected(const std::string& item) {
  if (item == "Start") {
    game.changeScene("game");
  } else if (item == "Exit") {
    game.quit();
  }
}