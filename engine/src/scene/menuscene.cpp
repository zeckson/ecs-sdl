#include "menuscene.h"

#include <resource/logger.h>

MenuScene::MenuScene(const std::vector<std::string>& items, SceneGame& game) : menuItems(items), game(game), selectedItem(0) {}

MenuScene::~MenuScene() {}

void MenuScene::init() {
  registerKeyboardAction(SDL_SCANCODE_UP, "UP");
  registerKeyboardAction(SDL_SCANCODE_DOWN, "DOWN");
  registerKeyboardAction(SDL_SCANCODE_RETURN, "RETURN");
}

void MenuScene::onKeyboardAction(const Action& action) {
  if (action.name == "UP") {
    selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
  } else if (action.name == "DOWN") {
    selectedItem = (selectedItem + 1) % menuItems.size();
  } else if (action.name == "RETURN") {
    Logger::info("Selected item: %s", menuItems[selectedItem].c_str());
  }
}

void MenuScene::onMouseAction(const MouseAction& action) {}

void MenuScene::update() {
  auto &renderer = game.renderer;

  for (size_t i = 0; i < menuItems.size(); ++i) {
    Pixel color = (i == selectedItem) ? Pixel{255, 0, 0, 255} : Pixel{255, 255, 255, 255};
    renderer->renderText(menuItems[i], 100, 100 + static_cast<int>(i) * 40);
  }
}


