#include "menuscene.h"

#include <renderer/textrenderer.h>
#include <resource/logger.h>

MenuScene::MenuScene(const std::vector<std::string>& items, SceneGame& game)
    : menuItems(items), game(game), selectedItem(0) {}

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

const Pixel GRAY = Pixel{100, 100, 100, 255};

void MenuScene::update() {
  auto& renderer = game.renderer;

  int menuWidth = game.width / 2;
  int menuStartY = game.height / 4;
  int menuItemHeight = 40;

  auto font = game.getAssetsManager().getFont("glitchgoblin");

  for (size_t i = 0; i < menuItems.size(); ++i) {
    Pixel background = (i == selectedItem) ? WHITE : GRAY;
    Pixel textColor = (i == selectedItem) ? Pixel{255, 0, 0, 255} : BLACK;
    const SDL_Rect box = {game.width / 2 - menuWidth / 2, menuStartY + static_cast<int>(i) * menuItemHeight, menuWidth,
                          menuItemHeight};
    TextRenderer textRenderer = TextRenderer::Builder(font)
                                    .withText(menuItems[i])
                                    .withColor(textColor)
                                    .withBackgroundColor(background)
                                    .justify(TextRenderer::Left)
                                    .inside(box)
                                    .build();
    textRenderer.render(renderer->renderer());
  }
}
