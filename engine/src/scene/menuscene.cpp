#include "menuscene.h"

#include <renderer/textrenderer.h>
#include <resource/logger.h>

const Pixel GRAY = Pixel{100, 100, 100, 255};

#define MENU_ITEM_HEIGHT 40
#define MENU_ITEM_INDENT 10

MenuScene::MenuScene(const std::vector<std::string>& items, SceneGame& game)
    : Scene(game), menuItems(items), selectedItem(0) {}

MenuScene::~MenuScene() {}

void MenuScene::init() {
  registerKeyboardAction(SDL_SCANCODE_UP, "UP");
  registerKeyboardAction(SDL_SCANCODE_DOWN, "DOWN");
  registerKeyboardAction(SDL_SCANCODE_RETURN, "RETURN");
}

void MenuScene::onKeyboardAction(const Action& action) {
  if (action.type == ActionType::END) {
    if (action.name == "UP") {
      selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
    } else if (action.name == "DOWN") {
      selectedItem = (selectedItem + 1) % menuItems.size();
    } else if (action.name == "RETURN") {
      const auto& item = menuItems[selectedItem];

      Logger::info("Selected item: %s", item.c_str());
      onMenuItemSelected(item);
    }
  }
}

void MenuScene::onMouseAction(const MouseAction& action) {}

void MenuScene::update() {
  auto& renderer = game.renderer;

  int menuStartX = game.width / 4;
  int menuStartY = game.height / 4;
  int menuItemWidth = game.width / 2;
  int menuItemHeight = MENU_ITEM_HEIGHT;

  auto font = game.getAssetsManager().getFont("glitchgoblin");
  auto textBuilder = TextRenderer::Builder(font);

  for (size_t i = 0; i < menuItems.size(); ++i) {
    Pixel background = (i == selectedItem) ? WHITE : GRAY;
    Pixel textColor = (i == selectedItem) ? Pixel{255, 0, 0, 255} : BLACK;

    int y = menuStartY + static_cast<int>(i) * (menuItemHeight + MENU_ITEM_INDENT);

    const SDL_Rect box = {menuStartX, y, menuItemWidth, menuItemHeight};

    renderer->render(textBuilder.withText(menuItems[i])
                         .withColor(textColor)
                         .withBackgroundColor(background)
                         .justify(TextRenderer::Center)
                         .inside(box)
                         .build());
  }
}
